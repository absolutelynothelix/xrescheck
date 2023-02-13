#!/bin/sh -ex

mkdir -p build
gcc -shared -fpic -DXRC_INTERCEPT_XCB_PIXMAPS -obuild/xrescheck_xcb_pixmaps.so \
src/xrescheck.c
gcc -shared -fpic -DXRC_INTERCEPT_XCB_GCS -obuild/xrescheck_xcb_gcs.so \
src/xrescheck.c
gcc -shared -fpic -DXRC_INTERCEPT_XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS \
-obuild/xrescheck_xcb_composite_named_windows_pixmaps.so src/xrescheck.c
gcc -shared -fpic -DXRC_INTERCEPT_XCB_RENDER_PICTURES \
-obuild/xrescheck_xcb_render_pictures.so src/xrescheck.c
