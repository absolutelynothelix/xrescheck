#define XCB_RENDER_PICTURES_TRACKER_BIT 1 << 4
#define XCB_RENDER_PICTURES_TRACKER_STRING "xcb_render_pictures"

/**
 * xcb_void_cookie_t xcb_render_create_picture[_checked](xcb_connection_t *c,
 *     xcb_render_picture_t pid, xcb_drawable_t drawable,
 *     xcb_render_pictformat_t format, uint32_t value_mask,
 *     const void *value_list)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XCB_RENDER_PICTURES_TRACKER_BIT,
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
	XCB_RENDER_PICTURES_TRACKER_BIT,
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
	XCB_RENDER_PICTURES_TRACKER_BIT,
	xcb_void_cookie_t,
	xcb_render_free_picture,
	VA_LIST(xcb_connection_t *c, xcb_render_picture_t picture),
	VA_LIST(c, picture),
	picture
)
