#include <execinfo.h>

#include <uthash.h>

#include "xrescheck.h"
#include "interceptors/xcb_composite_named_windows_pixmaps.h"
#include "interceptors/xcb_damage_damage.h"
#include "interceptors/xcb_gcs.h"
#include "interceptors/xcb_pixmaps.h"
#include "interceptors/xcb_render_pictures.h"
#include "interceptors/xcb_sync_fences.h"
#include "interceptors/xcb_xfixes_regions.h"

__attribute__((constructor))
void xrc_constructor() {
	xrc_log_neutral("? xrescheck %s is here!", XRC_VERSION_STRING);
#define array_length(x) sizeof(x)/sizeof(x[0])
	char *intercept = secure_getenv("XRC_INTERCEPT");
	if (intercept) {
		char *intercept_strings[] = {
			XRC_INTERCEPT_XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_STRING,
			XRC_INTERCEPT_XCB_DAMAGE_DAMAGE_STRING,
			XRC_INTERCEPT_XCB_GCS_STRING,
			XRC_INTERCEPT_XCB_PIXMAPS_STRING,
			XRC_INTERCEPT_XCB_RENDER_PICTURES_STRING,
			XRC_INTERCEPT_XCB_SYNC_FENCES_STRING,
			XRC_INTERCEPT_XCB_XFIXES_REGIONS_STRING
		};

		xrc_intercept = 0;
		for (uint8_t i = 0; i < array_length(intercept_strings); i++) {
			if (strstr(intercept, intercept_strings[i])) {
				xrc_intercept |= 1 << i;
			}
		}
	}

	char *print = secure_getenv("XRC_PRINT");
	if (print) {
		char *print_strings[] = {
			XRC_PRINT_RESOURCE_ALLOCATED_STRING,
			XRC_PRINT_RESOURCE_FREED_STRING,
			XRC_PRINT_RESOURCE_LEAKED_STRING,
			XRC_PRINT_RESOURCE_ALREADY_ALLOCATED_STRING,
			XRC_PRINT_RESOURCE_NOT_ALLOCATED_STRING
		};

		xrc_print = 0;
		for (uint8_t i = 0; i < array_length(print_strings); i++) {
			if (strstr(print, print_strings[i])) {
				xrc_print |= 1 << i;
			}
		}
	}
#undef array_length
	char *backtrace_symbols = secure_getenv("XRC_BACKTRACE_SYMBOLS");
	if (backtrace_symbols) {
		xrc_backtrace_symbols = strtoul(backtrace_symbols, NULL, 10);
	}
}

__attribute__((destructor))
void xrc_destructor() {
	xrc_log_neutral("? checking for leaked resources...");

	xrc_resource_t *resource, *temp;
	HASH_ITER(hh, xrc_resources, resource, temp) {
		if (xrc_print & XRC_PRINT_RESOURCE_LEAKED_BIT) {
			xrc_log_bad("! %ld allocated by %s wasn't freed, the allocation "
				"was made here:", resource->id, resource->allocated_by);
			for (uint8_t i = 3; i < resource->backtrace_symbols_amount; i++) {
				xrc_log_bad("\t%s", resource->backtrace_symbols[i]);
			}
		}

		free(resource->backtrace_symbols);
		HASH_DEL(xrc_resources, resource);
		free(resource);
	}
}

uint8_t xrc_get_backtrace_symbols(char ***bt_symbols) {
	void *buffer[xrc_backtrace_symbols + 3];
	uint8_t amount = backtrace(buffer, xrc_backtrace_symbols + 3);
	*bt_symbols = backtrace_symbols(buffer, amount);

	return amount;
}

void xrc_resource_allocated(uint16_t intercept_bit, char *res_allocated_by,
	uint64_t res_id) {
	if (!(xrc_intercept & intercept_bit)) {
		return;
	}

	xrc_resource_t *resource;
	HASH_FIND_INT(xrc_resources, &res_id, resource);
	if (resource) {
		if (xrc_print & XRC_PRINT_RESOURCE_ALREADY_ALLOCATED_BIT) {
			xrc_log_bad("! %s tried to allocate %ld that's already allocated, "
				"it happened here:", res_allocated_by, res_id);

			char **res_backtrace_symbols;
			uint8_t res_backtrace_symbols_amount = xrc_get_backtrace_symbols(
				&res_backtrace_symbols);
			for (uint8_t i = 3; i < res_backtrace_symbols_amount; i++) {
				xrc_log_bad("\t%s", res_backtrace_symbols[i]);
			}

			free(res_backtrace_symbols);
		}

		return;
	}

	resource = malloc(sizeof(xrc_resource_t));
	resource->id = res_id;
	resource->allocated_by = res_allocated_by;
	resource->backtrace_symbols_amount = xrc_get_backtrace_symbols(
		&resource->backtrace_symbols);

	HASH_ADD_INT(xrc_resources, id, resource);

	if (xrc_print & XRC_PRINT_RESOURCE_ALLOCATED_BIT) {
		xrc_log_neutral("+ %s allocated %ld", resource->allocated_by,
			resource->id);
	}
}

void xrc_resource_freed(uint16_t intercept_bit, char *res_freed_by,
	uint64_t res_id) {
	if (!(xrc_intercept & intercept_bit)) {
		return;
	}

	xrc_resource_t *resource;
	HASH_FIND_INT(xrc_resources, &res_id, resource);
	if (!resource) {
		if (xrc_print & XRC_PRINT_RESOURCE_NOT_ALLOCATED_BIT) {
			xrc_log_bad("! %s tried to free %ld that's not allocated, it "
				"happened here:", res_freed_by, res_id);

			char **res_backtrace_symbols;
			uint8_t res_backtrace_symbols_amount = xrc_get_backtrace_symbols(
				&res_backtrace_symbols);
			for (uint8_t i = 3; i < res_backtrace_symbols_amount; i++) {
				xrc_log_bad("\t%s", res_backtrace_symbols[i]);
			}

			free(res_backtrace_symbols);
		}

		return;
	}

	free(resource->backtrace_symbols);
	HASH_DEL(xrc_resources, resource);
	free(resource);

	if (xrc_print & XRC_PRINT_RESOURCE_FREED_BIT) {
		xrc_log_good("- %s freed %ld", res_freed_by, res_id);
	}
}
