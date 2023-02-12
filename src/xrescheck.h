#ifndef XRESCHECK_H
#define XRESCHECK_H

#include <dlfcn.h>
#include <stdio.h>

#define XRC_VERSION_STRING "0.0.1"

#define XRC_BACKTRACE_SYMBOLS_AMOUNT 3

#define xrc_log(format_string, args...) printf(format_string "\e[0m\n", args)
#define xrc_log_good(...) xrc_log("\e[32m" __VA_ARGS__)
#define xrc_log_neutral(...) xrc_log("\e[36m" __VA_ARGS__)
#define xrc_log_bad(...) xrc_log("\e[31m" __VA_ARGS__)

typedef struct {
	uint64_t id;
	char *allocated_by;
	uint8_t backtrace_symbols_amount;
	char **backtrace_symbols;
	UT_hash_handle hh;
} xrc_resource_t;

void xrc_resource_allocated(uint64_t, char *);
void xrc_resource_freed(uint64_t, char *);

#define VA_LIST(...) __VA_ARGS__

#define DEFAULT_ALLOC_FUNC(returns, name, accepts, pass_through_args, \
	resource) \
returns name(accepts) { \
	returns (* target_func)(accepts) = dlsym(RTLD_NEXT, #name); \
	returns ret = target_func(pass_through_args); \
	xrc_resource_allocated(resource, #name); \
	return ret; \
}

#define GEN_XCB_DEFAULT_ALLOC_FUNCS(returns, name, accepts, pass_through_args, \
	resource) \
DEFAULT_ALLOC_FUNC(returns, name, VA_LIST(accepts), \
	VA_LIST(pass_through_args), resource) \
DEFAULT_ALLOC_FUNC(returns, name##_checked, VA_LIST(accepts), \
	VA_LIST(pass_through_args), resource)

#define DEFAULT_FREE_FUNC(returns, name, accepts, pass_through_args, resource) \
returns name(accepts) { \
	returns (* target_func)(accepts) = dlsym(RTLD_NEXT, #name); \
	returns ret = target_func(pass_through_args); \
	xrc_resource_freed(resource, #name); \
	return ret; \
}

#define GEN_XCB_DEFAULT_FREE_FUNCS(returns, name, accepts, pass_through_args, \
	resource) \
DEFAULT_FREE_FUNC(returns, name, VA_LIST(accepts), VA_LIST(pass_through_args), \
	resource) \
DEFAULT_FREE_FUNC(returns, name##_checked, VA_LIST(accepts), \
	VA_LIST(pass_through_args), resource)

#endif
