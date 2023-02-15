#ifndef XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_H
#define XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_H

#include "xcb_common.h"

/**
 * xcb_void_cookie_t xcb_composite_name_window_pixmap[_checked](
 *     xcb_connection_t *c, xcb_window_t window, xcb_pixmap_t pixmap)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XRC_INTERCEPT_XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_BIT,
	xcb_void_cookie_t,
	xcb_composite_name_window_pixmap,
	VA_LIST(xcb_connection_t *c, xcb_window_t window, xcb_pixmap_t pixmap),
	VA_LIST(c, window, pixmap),
	pixmap
)

#endif
