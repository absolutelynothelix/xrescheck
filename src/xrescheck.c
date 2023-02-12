#include <execinfo.h>

#include <uthash.h>

#include "xrescheck.h"
#ifdef XRC_INTERCEPT_XCB_PIXMAPS
#include "interceptors/xcb_pixmaps.h"
#endif
#ifdef XRC_INTERCEPT_XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS
#include "interceptors/xcb_composite_named_windows_pixmaps.h"
#endif
#ifdef XRC_INTERCEPT_XCB_RENDER_PICTURES
#include "interceptors/xcb_render_pictures.h"
#endif

xrc_resource_t *xrc_resources = NULL;

__attribute__((constructor))
void xrc_constructor() {
	xrc_log_neutral("? xrescheck %s is here!", XRC_VERSION_STRING);
}

__attribute__((destructor))
void xrc_destructor() {
	xrc_log_neutral("? checking for leaks of %s...",
#ifdef XRC_INTERCEPT_XCB_PIXMAPS
		XRC_XCB_PIXMAPS_INTERCEPTOR_DESCRIPTION_STRING
#endif
#ifdef XRC_INTERCEPT_XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS
		XRC_XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_INTERCEPTOR_DESCRIPTION_STRING
#endif
#ifdef XRC_INTERCEPT_XCB_RENDER_PICTURES
		XRC_XCB_RENDER_PICTURES_INTERCEPTOR_DESCRIPTION_STRING
#endif
		);

	xrc_resource_t *resource, *temp;
	HASH_ITER(hh, xrc_resources, resource, temp) {
		xrc_log_bad("! %ld allocated by %s wasn't freed, the allocation was "
			"made here:", resource->id, resource->allocated_by);
		for (uint8_t i = 3; i < resource->backtrace_symbols_amount; i++) {
			xrc_log_bad("\t%s", resource->backtrace_symbols[i]);
		}

		free(resource->backtrace_symbols);
		HASH_DEL(xrc_resources, resource);
		free(resource);
	}
}

uint8_t xrc_get_backtrace_symbols(char ***bt_symbols) {
	void *buffer[XRC_BACKTRACE_SYMBOLS_AMOUNT + 3];
	uint8_t amount = backtrace(buffer, XRC_BACKTRACE_SYMBOLS_AMOUNT + 3);
	*bt_symbols = backtrace_symbols(buffer, amount);

	return amount;
}

void xrc_resource_allocated(uint64_t res_id, char *res_allocated_by) {
	xrc_resource_t *resource;
	HASH_FIND_INT(xrc_resources, &res_id, resource);
	if (resource) {
		xrc_log_bad("! %s tried to allocate %ld that's already allocated, it "
			"happened here:", res_allocated_by, res_id);

		char **res_backtrace_symbols;
		uint8_t res_backtrace_symbols_amount = xrc_get_backtrace_symbols(
			&res_backtrace_symbols);
		for (uint8_t i = 3; i < res_backtrace_symbols_amount; i++) {
			xrc_log_bad("\t%s", res_backtrace_symbols[i]);
		}

		free(res_backtrace_symbols);

		return;
	}

	resource = malloc(sizeof(xrc_resource_t));
	resource->id = res_id;
	resource->allocated_by = res_allocated_by;
	resource->backtrace_symbols_amount = xrc_get_backtrace_symbols(
		&resource->backtrace_symbols);

	HASH_ADD_INT(xrc_resources, id, resource);

	xrc_log_neutral("+ %s allocated %ld", resource->allocated_by, resource->id);
}

void xrc_resource_freed(uint64_t res_id, char *res_freed_by) {
	xrc_resource_t *resource;
	HASH_FIND_INT(xrc_resources, &res_id, resource);
	if (!resource) {
		xrc_log_bad("! %s tried to free %ld that's not allocated, it happened "
			"here:", res_freed_by, res_id);

		char **res_backtrace_symbols;
		uint8_t res_backtrace_symbols_amount = xrc_get_backtrace_symbols(
			&res_backtrace_symbols);
		for (uint8_t i = 3; i < res_backtrace_symbols_amount; i++) {
			xrc_log_bad("\t%s", res_backtrace_symbols[i]);
		}

		free(res_backtrace_symbols);

		return;
	}

	free(resource->backtrace_symbols);
	HASH_DEL(xrc_resources, resource);
	free(resource);

	xrc_log_good("- %s freed %ld", res_freed_by, res_id);
}
