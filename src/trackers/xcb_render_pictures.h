#ifndef XCB_RENDER_PICTURES_H
#define XCB_RENDER_PICTURES_H

#include "xcb_common.h"

/**
 * xcb_void_cookie_t xcb_render_create_picture[_checked](xcb_connection_t *c,
 *     xcb_render_picture_t pid, xcb_drawable_t drawable,
 *     xcb_render_pictformat_t format, uint32_t value_mask,
 *     const void *value_list)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XRC_TRACK_XCB_RENDER_PICTURES_BIT,
	xcb_void_cookie_t,
	xcb_render_create_picture,
	VA_LIST(xcb_connection_t *c, xcb_render_picture_t pid,
		xcb_drawable_t drawable, xcb_render_pictformat_t format,
		uint32_t value_mask, const void *value_list),
	VA_LIST(c, pid, drawable, format, value_mask, value_list),
	pid
)

/**
 * xcb_void_cookie_t xcb_render_create_picture_aux[_checked](
 *     xcb_connection_t *c, xcb_render_picture_t pid, xcb_drawable_t drawable,
 *     xcb_render_pictformat_t format, uint32_t value_mask,
 *     const xcb_render_create_picture_value_list_t *value_list)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XRC_TRACK_XCB_RENDER_PICTURES_BIT,
	xcb_void_cookie_t,
	xcb_render_create_picture_aux,
	VA_LIST(xcb_connection_t *c, xcb_render_picture_t pid,
		xcb_drawable_t drawable, xcb_render_pictformat_t format,
		uint32_t value_mask,
		const xcb_render_create_picture_value_list_t *value_list),
	VA_LIST(c, pid, drawable, format, value_mask, value_list),
	pid
)

/**
 * xcb_void_cookie_t xcb_render_free_picture[_checked](xcb_connection_t *c,
 *     xcb_render_picture_t picture)
 */
GEN_XCB_REQUEST_CHECK_FREE_FUNCS(
	XRC_TRACK_XCB_RENDER_PICTURES_BIT,
	xcb_void_cookie_t,
	xcb_render_free_picture,
	VA_LIST(xcb_connection_t *c, xcb_render_picture_t picture),
	VA_LIST(c, picture),
	picture
)

#endif
