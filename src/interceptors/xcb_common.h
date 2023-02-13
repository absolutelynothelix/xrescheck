#ifndef XCB_COMMON_H
#define XCB_COMMON_H

#include <xcb/xcb.h>

#include "../xrescheck.h"

#define VA_LIST(...) __VA_ARGS__

#define XCB_FUNC(returns, name, target_name, accepts, pass_through_args, \
	resource, xrc_resource_action_function) \
returns name(accepts) { \
	returns (* target_func)(accepts) = dlsym(RTLD_NEXT, #target_name); \
	returns ret = target_func(pass_through_args); \
	xcb_generic_error_t *e = xcb_request_check(c, ret); \
	if (e) { \
		free(e); \
		return ret; \
	} \
	xrc_resource_action_function(resource, #name); \
	return ret; \
}

#define GEN_XCB_ALLOC_FUNCS(returns, name, accepts, pass_through_args, \
	resource) \
XCB_FUNC(returns, name, name##_checked, VA_LIST(accepts), \
	VA_LIST(pass_through_args), resource, xrc_resource_allocated) \
XCB_FUNC(returns, name##_checked, name##_checked, VA_LIST(accepts), \
	VA_LIST(pass_through_args), resource, xrc_resource_allocated)

#define GEN_XCB_FREE_FUNCS(returns, name, accepts, pass_through_args, \
	resource) \
XCB_FUNC(returns, name, name##_checked, VA_LIST(accepts), \
	VA_LIST(pass_through_args), resource, xrc_resource_freed) \
XCB_FUNC(returns, name##_checked, name##_checked, VA_LIST(accepts), \
	VA_LIST(pass_through_args), resource, xrc_resource_freed)

#endif
