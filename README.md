# xrescheck
xrescheck is a small and trivial utility to identify X11-related memory leaks similiar to the [apitrace](https://apitrace.github.io)'s LeakTrace. It was initially developed as a standalone replacement for the [compton](https://github.com/chjj/compton)'s legacy builtin [xrescheck](https://github.com/yshui/picom/blob/cee12875625465292bc11bf09dc8ab117cae75f4/src/xrescheck.c) in [picom](https://github.com/yshui/picom).

xrescheck works by intercepting functions that allocate and free resources. When a resource is allocated, xrescheck adds it to the internal resources array. When a resource is freed, xrescheck removes it from the internal resources array. If an application exited and there are resources in the internal resources array they're considered leaked. That's it. xrescheck also considers an error if a resource was either allocated or freed multiple times in a row.

xrescheck itself doesn't check for leaks of any particular kind of resources. It uses interceptors - header files that have to be compiled in in order to get a xrescheck library that check for leaks of a particular kind of resources. There are few interceptors provided:
* xcb pixmaps interceptor;
	* allocation functions:
		* `xcb_void_cookie_t xcb_create_pixmap[_checked](xcb_connection_t *c, uint8_t depth, xcb_pixmap_t pid, xcb_drawable_t drawable, uint16_t width, uint16_t height)`
	* freeing functions:
		* `xcb_void_cookie_t xcb_free_pixmap[_checked](xcb_connection_t *c, xcb_pixmap_t pixmap)`
* xcb composite named windows' pixmaps interceptor;
	* allocation functions:
		* `xcb_void_cookie_t xcb_composite_name_window_pixmap[_checked](xcb_connection_t *c, xcb_window_t window, xcb_pixmap_t pixmap)`
	* freeing functions:
		* `xcb_void_cookie_t xcb_free_pixmap[_checked](xcb_connection_t *c, xcb_pixmap_t pixmap)`
* xcb render pictures interceptor.
	* allocation functions:
		* `xcb_void_cookie_t xcb_render_create_picture[_checked](xcb_connection_t *c, xcb_render_picture_t pid, xcb_drawable_t drawable, xcb_render_pictformat_t format, uint32_t value_mask, const void *value_list)`
		* `xcb_void_cookie_t xcb_render_create_picture_aux[_checked](xcb_connection_t *c, xcb_render_picture_t pid, xcb_drawable_t drawable, xcb_render_pictformat_t format, uint32_t value_mask, const xcb_render_create_picture_value_list_t *value_list)`
	* freeing functions:
		* `xcb_void_cookie_t xcb_render_free_picture(xcb_connection_t *c, xcb_render_picture_t picture)`

Note that since both xcb pixmaps and xcb composite named window's pixmaps are freed by the same free function xrescheck may complain that the free function tried to free a resource that's not allocated.

Writing your own interceptor isn't hard as well, see provided interceptors for examples on this.

## Building
> xrescheck itself doesn't check for leaks of any particular kind of resources. It uses interceptors - header files that have to be compiled in in order to get a xrescheck library that checks for leaks of a particular kind of resources.

There is the `build.sh` file that'll build a xrescheck library for each provided interceptor.

Using multiple interceptors at the same time is not recommended. Not using interceptors at all is not recommended as well.

## Usage and examples
Build an xrescheck library with an interceptor you want to use and preload it with the `LD_PRELOAD` environment variable to an application you want to check leaks in:
```
LD_PRELOAD=path/to/a/xrescheck/library.so path/to/an/application
```

As an example, checking for leaks of xcb composite named windows' pixmaps in [picom](https://github.com/yshui/picom) looks like this:
```
$ ./build.sh
+ mkdir -p build
...
+ gcc -shared -fpic -DXRC_INTERCEPT_XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS -obuild/xrescheck_xcb_composite_named_windows_pixmaps.so src/xrescheck.c
+ gcc -shared -fpic -DXRC_INTERCEPT_XCB_RENDER_PICTURES -obuild/xrescheck_xcb_render_pictures.so src/xrescheck.c
```
```
$ LD_PRELOAD=build/xrescheck_xcb_composite_named_windows_pixmaps.so ~/Documents/picom/build/src/picom
? xrescheck 0.0.1 is here!
...
+ xcb_composite_name_window_pixmap_checked allocated 29360172
...
+ xcb_composite_name_window_pixmap_checked allocated 29360179
^C
- xcb_free_pixmap freed 29360172
...
- xcb_free_pixmap freed 29360179
? checking for leaks of xcb composite named windows' pixmaps...
```
As you can see, no xcb composite named windows' pixmaps were leaked.

Here is another example of checking for leaks of xcb render pictures in [picom](https://github.com/yshui/picom):
```
$ LD_PRELOAD=build/xrescheck_xcb_render_pictures.so ~/Documents/picom/build/src/picom --backend=xrender
? xrescheck 0.0.1 is here!
...
? checking for leaks of xcb render pictures...
! 29360694 allocated by xcb_render_create_picture_checked wasn't freed, the allocation was made here:
	/home/helix/Documents/picom/build/src/picom(+0x2b378) [0x560c9bd48378]
	/home/helix/Documents/picom/build/src/picom(+0x2b460) [0x560c9bd48460]
	/home/helix/Documents/picom/build/src/picom(+0x569da) [0x560c9bd739da]
...
```
As you can see, some xcb render pictures were leaked and xrescheck provided a backtrace for each leaked resource telling where the allocation was made. To get a meaningful backtrace you can either recompile the application you are checking leaks in with such compiler command line arguments as `-rdynamic` or use the `addr2line` command line utility which is way more convenient:
```
$ addr2line -e ~/Documents/picom/build/src/picom +0x2b378 +0x2b460 +0x569da
/home/helix/Documents/picom/build/../src/x.c:298
/home/helix/Documents/picom/build/../src/x.c:315
/home/helix/Documents/picom/build/../src/backend/xrender/xrender.c:523 (discriminator 2)
```

## Miscellaneous
xrescheck probably won't be actively maintained until it'll be proven to be useful and used by people other than me.
