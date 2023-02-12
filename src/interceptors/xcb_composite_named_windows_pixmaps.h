#ifndef XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_H
#define XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_H

#include <xcb/composite.h>

#include "../xrescheck.h"

#define XRC_XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_INTERCEPTOR_DESCRIPTION_STRING \
"xcb composite named windows' pixmaps"

// xcb_void_cookie_t xcb_composite_name_window_pixmap[_checked](
//     xcb_connection_t *c, xcb_window_t window, xcb_pixmap_t pixmap)
GEN_XCB_DEFAULT_ALLOC_FUNCS(
	xcb_void_cookie_t,
	xcb_composite_name_window_pixmap,
	VA_LIST(xcb_connection_t *c, xcb_window_t window, xcb_pixmap_t pixmap),
	VA_LIST(c, window, pixmap),
	pixmap
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
