#ifndef XCB_GCS_H
#define XCB_GCS_H

#include <xcb/xcb.h>

#include "../xrescheck.h"

#define XRC_XCB_GCS_INTERCEPTOR_DESCRIPTION_STRING "xcb gcs"

// xcb_void_cookie_t xcb_create_gc[_checked](xcb_connection_t *c,
//     xcb_gcontext_t cid, xcb_drawable_t drawable, uint32_t value_mask,
//     const void *value_list)
GEN_XCB_DEFAULT_ALLOC_FUNCS(
	xcb_void_cookie_t,
	xcb_create_gc,
	VA_LIST(xcb_connection_t *c, xcb_gcontext_t cid, xcb_drawable_t drawable,
		uint32_t value_mask, const void *value_list),
	VA_LIST(c, cid, drawable, value_mask, value_list),
	cid
)

// xcb_void_cookie_t xcb_create_gc_aux[_checked](xcb_connection_t *c,
//     xcb_gcontext_t cid, xcb_drawable_t drawable, uint32_t value_mask,
//     const xcb_create_gc_value_list_t *value_list)
GEN_XCB_DEFAULT_ALLOC_FUNCS(
	xcb_void_cookie_t,
	xcb_create_gc_aux,
	VA_LIST(xcb_connection_t *c, xcb_gcontext_t cid, xcb_drawable_t drawable,
		uint32_t value_mask, const xcb_create_gc_value_list_t *value_list),
	VA_LIST(c, cid, drawable, value_mask, value_list),
	cid
)

// xcb_void_cookie_t xcb_free_gc[_checked](xcb_connection_t *c,
//     xcb_gcontext_t gc)
GEN_XCB_DEFAULT_FREE_FUNCS(
	xcb_void_cookie_t,
	xcb_free_gc,
	VA_LIST(xcb_connection_t *c, xcb_gcontext_t gc),
	VA_LIST(c, gc),
	gc
)

#endif
