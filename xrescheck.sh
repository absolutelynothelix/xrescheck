#!/bin/sh

resolve_backtrace_symbols=0

if [ $# -eq 0 ]; then
	echo "usage: xrescheck.sh [option]... application"
	echo "identify x11-related memory leaks in an application"
	echo
	echo "  -b, --backtrace-symbols=        a number of backtrace symbols to"
	echo "                                  print"
	echo "  -p, --print=                    a comma-separated list of messages"
	echo "                                  to print"
	echo "  -r, --resolve-backtrace-symbols resolve symbols at run-time using"
	echo "                                  the addr2line command line utility"
	echo "  -t, --track=                    a comma-separated list of resources"
	echo "                                  to track"
else
	while [ $# -gt 0 ]; do
		case $1 in
			-b) backtrace_symbols=$2; shift 2;;
			--backtrace-symbols=*) backtrace_symbols=${1#*=}; shift 1;;

			-p) print=$2; shift 2;;
			--print=*) print=${1#*=}; shift 1;;

			-r) resolve_backtrace_symbols=1; shift 1;;
			--resolve-backtrace-symbols) resolve_backtrace_symbols=1; shift 1;;

			-t) track=$2; shift 2;;
			--track=*) track=${1#*=}; shift 1;;

			*) application="$application$1 "; shift 1;;
		esac
	done

	if [ -z "$application" ]; then
		echo "no application specified"
		exit 1
	fi
fi

if [ -e "build/xrescheck.so" ]; then
	xrescheck="build/xrescheck.so"
else
	echo "unable to find the xrescheck library (tried build/xrescheck.so)"
	exit 1
fi

if [ $resolve_backtrace_symbols -eq 1 ]; then
	trap "" INT
	# shellcheck disable=SC2086
	XRC_TRACK=$track XRC_PRINT=$print XRC_BACKTRACE_SYMBOLS=$backtrace_symbols \
	LD_PRELOAD=$xrescheck stdbuf --output=L --error=L $application | sed -E \
	"s/(^.*\t)(.+)\((.+)\).+\](.*$)/printf '\1' \&\& addr2line -e \2 \3 | \
	tr -d '\n' \&\& printf '\4'/e"
else
	XRC_TRACK=$track XRC_PRINT=$print XRC_BACKTRACE_SYMBOLS=$backtrace_symbols \
	LD_PRELOAD=$xrescheck $application
fi
