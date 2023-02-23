#ifndef XCB_H
#define XCB_H

#include <xcb/composite.h>
#include <xcb/damage.h>
#include <xcb/render.h>
#include <xcb/sync.h>
#include <xcb/xcb.h>
#include <xcb/xfixes.h>

#include "../xrescheck.h"

#define VA_LIST(...) __VA_ARGS__

#define XCB_REQUEST_CHECK_FUNC(tracker_bit, returns, name, target_name, \
	accepts, pass_through_args, resource, xrc_resource_action_function) \
returns name(accepts) { \
	returns (* target_func)(accepts) = dlsym(RTLD_NEXT, #target_name); \
	returns ret = target_func(pass_through_args); \
	xcb_generic_error_t *e = xcb_request_check(c, ret); \
	if (e) { \
		free(e); \
		return ret; \
	} \
	xrc_resource_action_function(tracker_bit, #name, resource); \
	return ret; \
}

#define GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(tracker_bit, returns, name, \
	accepts, pass_through_args, resource) \
XCB_REQUEST_CHECK_FUNC(tracker_bit, returns, name, name##_checked, \
	VA_LIST(accepts), VA_LIST(pass_through_args), resource, \
	xrc_resource_allocated) \
XCB_REQUEST_CHECK_FUNC(tracker_bit, returns, name##_checked, \
	name##_checked, VA_LIST(accepts), VA_LIST(pass_through_args), resource, \
	xrc_resource_allocated)

#define GEN_XCB_REQUEST_CHECK_FREE_FUNCS(tracker_bit, returns, name, \
	accepts, pass_through_args, resource) \
XCB_REQUEST_CHECK_FUNC(tracker_bit, returns, name, name##_checked, \
	VA_LIST(accepts), VA_LIST(pass_through_args), resource, \
	xrc_resource_freed) \
XCB_REQUEST_CHECK_FUNC(tracker_bit, returns, name##_checked, \
	name##_checked, VA_LIST(accepts), VA_LIST(pass_through_args), resource, \
	xrc_resource_freed)

#include "xcb_colormaps.h"
#include "xcb_composite_named_windows_pixmaps.h"
#include "xcb_damage_damage.h"
#include "xcb_gcs.h"
#include "xcb_pixmaps.h"
#include "xcb_render_pictures.h"
#include "xcb_sync_fences.h"
#include "xcb_windows.h"
#include "xcb_xfixes_regions.h"

GEN_XCB_REQUEST_CHECK_FREE_FUNCS(
	XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_TRACKER_BIT |
	XCB_PIXMAPS_TRACKER_BIT,
	xcb_void_cookie_t,
	xcb_free_pixmap,
	VA_LIST(xcb_connection_t *c, xcb_pixmap_t pixmap),
	VA_LIST(c, pixmap),
	pixmap
)

#endif
