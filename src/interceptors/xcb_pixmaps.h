#ifndef XCB_PIXMAPS_H
#define XCB_PIXMAPS_H

#include "xcb_common.h"

/**
 * xcb_void_cookie_t xcb_create_pixmap[_checked](xcb_connection_t *c,
 *     uint8_t depth, xcb_pixmap_t pid, xcb_drawable_t drawable, uint16_t width,
 *     uint16_t height)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XRC_INTERCEPT_XCB_PIXMAPS_BIT,
	xcb_void_cookie_t,
	xcb_create_pixmap,
	VA_LIST(xcb_connection_t *c, uint8_t depth, xcb_pixmap_t pid,
		xcb_drawable_t drawable, uint16_t width, uint16_t height),
	VA_LIST(c, depth, pid, drawable, width, height),
	pid
)

#endif
