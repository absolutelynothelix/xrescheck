#ifndef XRESCHECK_H
#define XRESCHECK_H

#include <dlfcn.h>
#include <stdio.h>

#define XRC_VERSION_STRING "0.0.1"

// XXX(absolutelynothelix): don't tell me how ugly it is, I already know it.

#define XRC_INTERCEPT_XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_BIT    1 << 0
#define XRC_INTERCEPT_XCB_DAMAGE_DAMAGE_BIT                      1 << 1
#define XRC_INTERCEPT_XCB_GCS_BIT                                1 << 2
#define XRC_INTERCEPT_XCB_PIXMAPS_BIT                            1 << 3
#define XRC_INTERCEPT_XCB_RENDER_PICTURES_BIT                    1 << 4
#define XRC_INTERCEPT_XCB_SYNC_FENCES_BIT                        1 << 5
#define XRC_INTERCEPT_XCB_XFIXES_REGIONS_BIT                     1 << 6

#define XRC_INTERCEPT_XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_STRING "xcb_composite_named_windows_pixmaps"
#define XRC_INTERCEPT_XCB_DAMAGE_DAMAGE_STRING                   "xcb_damage_damage"
#define XRC_INTERCEPT_XCB_GCS_STRING                             "xcb_gcs"
#define XRC_INTERCEPT_XCB_PIXMAPS_STRING                         "xcb_pixmaps"
#define XRC_INTERCEPT_XCB_RENDER_PICTURES_STRING                 "xcb_render_pictures"
#define XRC_INTERCEPT_XCB_SYNC_FENCES_STRING                     "xcb_sync_fences"
#define XRC_INTERCEPT_XCB_XFIXES_REGIONS_STRING                  "xcb_xfixes_regions"

#define XRC_PRINT_RESOURCE_ALLOCATED_BIT                         1 << 0
#define XRC_PRINT_RESOURCE_FREED_BIT                             1 << 1
#define XRC_PRINT_RESOURCE_LEAKED_BIT                            1 << 2
#define XRC_PRINT_RESOURCE_ALREADY_ALLOCATED_BIT                 1 << 3
#define XRC_PRINT_RESOURCE_NOT_ALLOCATED_BIT                     1 << 4

#define XRC_PRINT_RESOURCE_ALLOCATED_STRING                      "resource_allocated"
#define XRC_PRINT_RESOURCE_FREED_STRING                          "resource_freed"
#define XRC_PRINT_RESOURCE_LEAKED_STRING                         "resource_leaked"
#define XRC_PRINT_RESOURCE_ALREADY_ALLOCATED_STRING              "resource_already_allocated"
#define XRC_PRINT_RESOURCE_NOT_ALLOCATED_STRING                  "resource_not_allocated"

#define xrc_log(format_string, ...) printf(format_string "\e[0m\n" \
	__VA_OPT__(,) __VA_ARGS__)
#define xrc_log_bad(...) xrc_log("\e[31m" __VA_ARGS__)
#define xrc_log_neutral(...) xrc_log("\e[36m" __VA_ARGS__)
#define xrc_log_good(...) xrc_log("\e[32m" __VA_ARGS__)

typedef struct {
	uint64_t id;
	char *allocated_by;
	uint8_t backtrace_symbols_amount;
	char **backtrace_symbols;
	UT_hash_handle hh;
} xrc_resource_t;

uint8_t xrc_intercept = UINT8_MAX;
uint8_t xrc_print = UINT8_MAX;
uint8_t xrc_backtrace_symbols = 3;

xrc_resource_t *xrc_resources = NULL;

void xrc_resource_allocated(uint16_t, char *, uint64_t);
void xrc_resource_freed(uint16_t, char *, uint64_t);

#endif
