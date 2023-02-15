#ifndef XCB_SYNC_FENCES_H
#define XCB_SYNC_FENCES_H

#include "xcb_common.h"

/**
 * xcb_void_cookie_t xcb_sync_create_fence[_checked](xcb_connection_t *c,
 *     xcb_drawable_t drawable, xcb_sync_fence_t fence,
 *     uint8_t initially_triggered)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XRC_INTERCEPT_XCB_SYNC_FENCES_BIT,
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
	XRC_INTERCEPT_XCB_SYNC_FENCES_BIT,
	xcb_void_cookie_t,
	xcb_sync_destroy_fence,
	VA_LIST(xcb_connection_t *c, xcb_sync_fence_t fence),
	VA_LIST(c, fence),
	fence
)

#endif
