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

#endif
