#ifndef XRESCHECK_H
#define XRESCHECK_H

#include <stdio.h>

#define XRC_VERSION_STRING "0.0.1"

#define XRC_PRINT_RESOURCE_ALLOCATED_BIT 1 << 0
#define XRC_PRINT_RESOURCE_ALLOCATED_STRING "resource_allocated"

#define XRC_PRINT_RESOURCE_FREED_BIT 1 << 1
#define XRC_PRINT_RESOURCE_FREED_STRING "resource_freed"

#define XRC_PRINT_RESOURCE_LEAKED_BIT 1 << 2
#define XRC_PRINT_RESOURCE_LEAKED_STRING "resource_leaked"

#define XRC_PRINT_RESOURCE_ALREADY_ALLOCATED_BIT 1 << 3
#define XRC_PRINT_RESOURCE_ALREADY_ALLOCATED_STRING "resource_already_allocated"

#define XRC_PRINT_RESOURCE_NOT_ALLOCATED_BIT 1 << 4
#define XRC_PRINT_RESOURCE_NOT_ALLOCATED_STRING "resource_not_allocated"

#define XRC_PRINT_WRONG_FREE_FUNCTION_BIT 1 << 5
#define XRC_PRINT_WRONG_FREE_FUNCTION_STRING "wrong_free_function"

#define xrc_log(format_string, ...) printf(format_string "\e[0m\n" \
	__VA_OPT__(,) __VA_ARGS__)
#define xrc_log_bad(...) xrc_log("\e[31m" __VA_ARGS__)
#define xrc_log_neutral(...) xrc_log("\e[36m" __VA_ARGS__)
#define xrc_log_good(...) xrc_log("\e[32m" __VA_ARGS__)

typedef struct {
	uint64_t id;
	char *allocated_by;
	uint16_t tracker_bit;
	uint8_t backtrace_symbols_amount;
	char **backtrace_symbols;
	UT_hash_handle hh;
} xrc_resource_t;

uint16_t xrc_track = UINT16_MAX;
uint16_t xrc_print = UINT16_MAX;
uint8_t xrc_backtrace_symbols = 3;

xrc_resource_t *xrc_resources = NULL;

#endif
