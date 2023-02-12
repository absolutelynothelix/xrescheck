#ifndef XCB_PIXMAPS_H
#define XCB_PIXMAPS_H

#include <xcb/xcb.h>

#include "../xrescheck.h"

#define XRC_XCB_PIXMAPS_INTERCEPTOR_DESCRIPTION_STRING "xcb pixmaps"

// xcb_void_cookie_t xcb_create_pixmap[_checked](xcb_connection_t *c,
//     uint8_t depth, xcb_pixmap_t pid, xcb_drawable_t drawable, uint16_t width,
//     uint16_t height)
GEN_XCB_DEFAULT_ALLOC_FUNCS(
	xcb_void_cookie_t,
	xcb_create_pixmap,
	VA_LIST(xcb_connection_t *c, uint8_t depth, xcb_pixmap_t pid,
		xcb_drawable_t drawable, uint16_t width, uint16_t height),
	VA_LIST(c, depth, pid, drawable, width, height),
	pid
)

// xcb_void_cookie_t xcb_free_pixmap[_checked](xcb_connection_t *c,
//     xcb_pixmap_t pixmap)
GEN_XCB_DEFAULT_FREE_FUNCS(
	xcb_void_cookie_t,
	xcb_free_pixmap,
	VA_LIST(xcb_connection_t *c, xcb_pixmap_t pixmap),
	VA_LIST(c, pixmap),
	pixmap
)

#endif
