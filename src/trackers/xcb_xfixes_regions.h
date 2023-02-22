#ifndef XCB_XFIXES_REGIONS_H
#define XCB_XFIXES_REGIONS_H

#include "xcb_common.h"

/**
 * xcb_void_cookie_t xcb_xfixes_create_region[_checked](xcb_connection_t *c,
 *     xcb_xfixes_region_t region, uint32_t rectangles_len,
 *     const xcb_rectangle_t *rectangles)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XRC_TRACK_XCB_XFIXES_REGIONS_BIT,
	xcb_void_cookie_t,
	xcb_xfixes_create_region,
	VA_LIST(xcb_connection_t *c, xcb_xfixes_region_t region,
		uint32_t rectangles_len, const xcb_rectangle_t *rectangles),
	VA_LIST(c, region, rectangles_len, rectangles),
	region
)

/**
 * xcb_void_cookie_t xcb_xfixes_create_region_from_bitmap[_checked](
 *     xcb_connection_t *c, xcb_xfixes_region_t region, xcb_pixmap_t bitmap)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XRC_TRACK_XCB_XFIXES_REGIONS_BIT,
	xcb_void_cookie_t,
	xcb_xfixes_create_region_from_bitmap,
	VA_LIST(xcb_connection_t *c, xcb_xfixes_region_t region,
		xcb_pixmap_t bitmap),
	VA_LIST(c, region, bitmap),
	region
)

/**
 * xcb_void_cookie_t xcb_xfixes_create_region_from_window[_checked](
 *     xcb_connection_t *c, xcb_xfixes_region_t region, xcb_window_t window,
 *     xcb_shape_kind_t kind)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XRC_TRACK_XCB_XFIXES_REGIONS_BIT,
	xcb_void_cookie_t,
	xcb_xfixes_create_region_from_window,
	VA_LIST(xcb_connection_t *c, xcb_xfixes_region_t region,
		xcb_window_t window, xcb_shape_kind_t kind),
	VA_LIST(c, region, window, kind),
	region
)

/**
 * xcb_void_cookie_t xcb_xfixes_create_region_from_gc[_checked](
 *     xcb_connection_t *c, xcb_xfixes_region_t region, xcb_gcontext_t gc)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XRC_TRACK_XCB_XFIXES_REGIONS_BIT,
	xcb_void_cookie_t,
	xcb_xfixes_create_region_from_gc,
	VA_LIST(xcb_connection_t *c, xcb_xfixes_region_t region, xcb_gcontext_t gc),
	VA_LIST(c, region, gc),
	region
)

/**
 * xcb_void_cookie_t xcb_xfixes_create_region_from_picture[_checked](
 *     xcb_connection_t *c, xcb_xfixes_region_t region,
 *     xcb_render_picture_t picture)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XRC_TRACK_XCB_XFIXES_REGIONS_BIT,
	xcb_void_cookie_t,
	xcb_xfixes_create_region_from_picture,
	VA_LIST(xcb_connection_t *c, xcb_xfixes_region_t region,
		xcb_render_picture_t picture),
	VA_LIST(c, region, picture),
	region
)

/**
 * xcb_void_cookie_t xcb_xfixes_destroy_region[_checked](xcb_connection_t *c,
 *     xcb_xfixes_region_t region)
 */
GEN_XCB_REQUEST_CHECK_FREE_FUNCS(
	XRC_TRACK_XCB_XFIXES_REGIONS_BIT,
	xcb_void_cookie_t,
	xcb_xfixes_destroy_region,
	VA_LIST(xcb_connection_t *c, xcb_xfixes_region_t region),
	VA_LIST(c, region),
	region
)

#endif
