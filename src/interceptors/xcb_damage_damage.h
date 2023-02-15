#ifndef XCB_DAMAGE_DAMAGE_H
#define XCB_DAMAGE_DAMAGE_H

#include "xcb_common.h"

/**
 * xcb_void_cookie_t xcb_damage_create[_checked](xcb_connection_t *c,
 *     xcb_damage_damage_t damage, xcb_drawable_t drawable, uint8_t level)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XRC_INTERCEPT_XCB_DAMAGE_DAMAGE_BIT,
	xcb_void_cookie_t,
	xcb_damage_create,
	VA_LIST(xcb_connection_t *c, xcb_damage_damage_t damage,
		xcb_drawable_t drawable, uint8_t level),
	VA_LIST(c, damage, drawable, level),
	damage
)

/**
 * xcb_void_cookie_t xcb_damage_destroy[_checked](xcb_connection_t *c,
 *     xcb_damage_damage_t damage)
 */
GEN_XCB_REQUEST_CHECK_FREE_FUNCS(
	XRC_INTERCEPT_XCB_DAMAGE_DAMAGE_BIT,
	xcb_void_cookie_t,
	xcb_damage_destroy,
	VA_LIST(xcb_connection_t *c, xcb_damage_damage_t damage),
	VA_LIST(c, damage),
	damage
)

#endif
