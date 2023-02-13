#!/bin/sh -ex

mkdir -p build

CC="gcc"
CFLAGS="-shared -fpic -D_GNU_SOURCE"

$CC $CFLAGS -DXRC_INTERCEPT_XCB_PIXMAPS -obuild/xrescheck_xcb_pixmaps.so \
src/xrescheck.c
$CC $CFLAGS -DXRC_INTERCEPT_XCB_GCS -obuild/xrescheck_xcb_gcs.so src/xrescheck.c
$CC $CFLAGS -DXRC_INTERCEPT_XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS \
-obuild/xrescheck_xcb_composite_named_windows_pixmaps.so src/xrescheck.c
$CC $CFLAGS -DXRC_INTERCEPT_XCB_RENDER_PICTURES \
-obuild/xrescheck_xcb_render_pictures.so src/xrescheck.c
