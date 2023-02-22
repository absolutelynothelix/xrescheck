#define XCB_GCS_TRACKER_BIT 1 << 2
#define XCB_GCS_TRACKER_STRING "xcb_gcs"

/**
 * xcb_void_cookie_t xcb_create_gc[_checked](xcb_connection_t *c,
 *     xcb_gcontext_t cid, xcb_drawable_t drawable, uint32_t value_mask,
 *     const void *value_list)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XCB_GCS_TRACKER_BIT,
	xcb_void_cookie_t,
	xcb_create_gc,
	VA_LIST(xcb_connection_t *c, xcb_gcontext_t cid, xcb_drawable_t drawable,
		uint32_t value_mask, const void *value_list),
	VA_LIST(c, cid, drawable, value_mask, value_list),
	cid
)

/**
 * xcb_void_cookie_t xcb_create_gc_aux[_checked](xcb_connection_t *c,
 *     xcb_gcontext_t cid, xcb_drawable_t drawable, uint32_t value_mask,
 *     const xcb_create_gc_value_list_t *value_list)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XCB_GCS_TRACKER_BIT,
	xcb_void_cookie_t,
	xcb_create_gc_aux,
	VA_LIST(xcb_connection_t *c, xcb_gcontext_t cid, xcb_drawable_t drawable,
		uint32_t value_mask, const xcb_create_gc_value_list_t *value_list),
	VA_LIST(c, cid, drawable, value_mask, value_list),
	cid
)

/**
 * xcb_void_cookie_t xcb_free_gc[_checked](xcb_connection_t *c,
 *     xcb_gcontext_t gc)
 */
GEN_XCB_REQUEST_CHECK_FREE_FUNCS(
	XCB_GCS_TRACKER_BIT,
	xcb_void_cookie_t,
	xcb_free_gc,
	VA_LIST(xcb_connection_t *c, xcb_gcontext_t gc),
	VA_LIST(c, gc),
	gc
)
