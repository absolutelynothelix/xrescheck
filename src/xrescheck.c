#include <execinfo.h>

#include <uthash.h>

#include "trackers/xcb.h"
#include "xrescheck.h"

__attribute__((constructor))
void xrc_constructor() {
	xrc_log_neutral("? xrescheck %s is here!", XRC_VERSION_STRING);
#define array_length(x) sizeof(x)/sizeof(x[0])
	char *track = secure_getenv("XRC_TRACK");
	if (track && track[0]) {
		char *track_strings[] = {
			XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_TRACKER_STRING,
			XCB_DAMAGE_DAMAGE_TRACKER_STRING,
			XCB_GCS_TRACKER_STRING,
			XCB_PIXMAPS_TRACKER_STRING,
			XCB_RENDER_PICTURES_TRACKER_STRING,
			XCB_SYNC_FENCES_TRACKER_STRING,
			XCB_XFIXES_REGIONS_TRACKER_STRING
		};

		xrc_track = 0;
		for (uint8_t i = 0; i < array_length(track_strings); i++) {
			if (strstr(track, track_strings[i])) {
				xrc_track |= 1 << i;
			}
		}
	}

	char *print = secure_getenv("XRC_PRINT");
	if (print && print[0]) {
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
	if (backtrace_symbols && backtrace_symbols[0]) {
		xrc_backtrace_symbols = strtoul(backtrace_symbols, NULL, 10);
	}
}

__attribute__((destructor))
void xrc_destructor() {
	xrc_log_neutral("? checking for leaked resources...");

	xrc_resource_t *resource, *temp;
	HASH_ITER(hh, xrc_resources, resource, temp) {
		if (xrc_print & XRC_PRINT_RESOURCE_LEAKED_BIT) {
			xrc_log_bad("! %#08lx allocated by %s wasn't freed, the allocation "
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

void xrc_resource_allocated(uint16_t tracker_bit, char *res_allocated_by,
	uint64_t res_id) {
	if (!(xrc_track & tracker_bit)) {
		return;
	}

	xrc_resource_t *resource;
	HASH_FIND_INT(xrc_resources, &res_id, resource);
	if (resource) {
		if (xrc_print & XRC_PRINT_RESOURCE_ALREADY_ALLOCATED_BIT) {
			xrc_log_bad("! %s tried to allocate %#08lx that's already "
				"allocated, it happened here:", res_allocated_by, res_id);

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
		xrc_log_neutral("+ %s allocated %#08lx", resource->allocated_by,
			resource->id);
	}
}

void xrc_resource_freed(uint16_t track_bit, char *res_freed_by,
	uint64_t res_id) {
	if (!(xrc_track & track_bit)) {
		return;
	}

	xrc_resource_t *resource;
	HASH_FIND_INT(xrc_resources, &res_id, resource);
	if (!resource) {
		if (xrc_print & XRC_PRINT_RESOURCE_NOT_ALLOCATED_BIT) {
			xrc_log_bad("! %s tried to free %#08lx that's not allocated, it "
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
		xrc_log_good("- %s freed %#08lx", res_freed_by, res_id);
	}
}
