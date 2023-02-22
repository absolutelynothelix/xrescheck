#define XCB_SYNC_FENCES_TRACKER_BIT 1 << 5
#define XCB_SYNC_FENCES_TRACKER_STRING "xcb_sync_fences"

/**
 * xcb_void_cookie_t xcb_sync_create_fence[_checked](xcb_connection_t *c,
 *     xcb_drawable_t drawable, xcb_sync_fence_t fence,
 *     uint8_t initially_triggered)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XCB_SYNC_FENCES_TRACKER_BIT,
	xcb_void_cookie_t,
	xcb_sync_create_fence,
	VA_LIST(xcb_connection_t *c, xcb_drawable_t drawable,
		xcb_sync_fence_t fence, uint8_t initially_triggered),
	VA_LIST(c, drawable, fence, initially_triggered),
	fence
)

/**
 * xcb_void_cookie_t xcb_sync_destroy_fence[_checked](xcb_connection_t *c,
 *     xcb_sync_fence_t fence)
 */
GEN_XCB_REQUEST_CHECK_FREE_FUNCS(
	XCB_SYNC_FENCES_TRACKER_BIT,
	xcb_void_cookie_t,
	xcb_sync_destroy_fence,
	VA_LIST(xcb_connection_t *c, xcb_sync_fence_t fence),
	VA_LIST(c, fence),
	fence
)
