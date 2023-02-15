# xrescheck
xrescheck is a small and trivial utility to identify X11-related memory leaks similar to the [apitrace](https://apitrace.github.io)'s LeakTrace. It was initially developed as a standalone replacement for the [compton](https://github.com/chjj/compton)'s legacy builtin [xrescheck](https://github.com/yshui/picom/blob/cee12875625465292bc11bf09dc8ab117cae75f4/src/xrescheck.c) in [picom](https://github.com/yshui/picom).

xrescheck works by intercepting functions that allocate and free resources. When a resource is allocated it's added to the xrescheck's internal resources hash table. When a resource is freed it's removed from the xrescheck's internal resources hash table. If application exits while there are resources left in the xrescheck's internal resources hash table they're considered leaked. If a resource that's already in the xrescheck's internal resources hash table is allocated xrescheck considers an error. If a resource that's not in the xrescheck's internal resources hash table is freed xrescheck considers an error. That's it.

xrescheck itself doesn't check for leaks of any particular kind of resources. It's an interface for interceptors - header files containing declarations of intercepting functions. Builtin interceptors are:
* xcb composite named windows' pixmaps interceptor (`xcb_composite_named_windows_pixmaps`);
* xcb damage damage interceptor (`xcb_damage_damage`);
* xcb gcs interceptor (`xcb_gcs`);
* xcb pixmaps interceptor (`xcb_pixmaps`);
* xcb render pictures interceptor (`xcb_render_pictures`);
* xcb sync fences interceptor (`xcb_sync_fences`);
* xcb xfixes regions interceptor (`xcb_xfixes_regions`).

Note 1: the xcb composite named windows' pixmaps and the xcb pixmaps interceptors share the same freeing function so if you have only one of these enabled xrescheck may complain about freeing a resource that's not allocated. You can suppress this error by excluding `resource_not_allocated` messages from printed messages, see below for details.

Note 2: see the corresponding interceptor header file in the `src/interceptors` folder for details on what functions are intercepted.

Writing your own interceptors, at least for xcb functions, isn't hard. See builtin interceptors header files in the `src/interceptors` folder for examples.

## Building
You need:
* xcb composite header file;
* xcb damage header file;
* xcb render header file;
* xcb sync header file;
* xcb xfixes header file;
* xcb header file;
* uthash header file.

On Arch Linux it's the `libxcb` and the `uthash` packages.

The `build.sh` script builds the xrescheck library and places it in the `build` folder.

## Usage
The xrescheck library is preloaded into an application with the `LD_PRELOAD` environment variable and configured using environment variables as well:
* `XRC_INTERCEPT` - a list of interceptors to enable. Defaults to all builtin interceptors (see the list of builtin interceptors above);
* `XRC_PRINT` - a list of messages to print. Defaults to all messages:
	* `resource_allocated` - a message when a function allocates a resource;
	* `resource_freed` - a message when a function frees a resource;
	* `resource_leaked` - a message when a resource is considered leaked;
	* `resource_already_allocated` - a message when a function tried to allocate a resource that's already allocated;
	* `resource_not_allocated` - a message when a function tried to free a resource that's not allocated;
* `XRC_BACKTRACE_SYMBOLS` - a number of backtrace symbols to print on error. Defaults to 3.

## Examples
Checking only for leaks of xcb render pictures in picom and printing five backtrace symbols on errors:
```
$ XRC_INTERCEPT="xcb_render_pictures" XRC_BACKTRACE_SYMBOLS="5" LD_PRELOAD="xrescheck.so" picom
? xrescheck 0.0.1 is here!
...
+ xcb_render_create_picture_checked allocated 25165829
...
- xcb_render_free_picture freed 25165829
? checking for leaked resources...
! 25166395 allocated by xcb_render_create_picture_checked wasn't freed, the allocation was made here:
	/home/helix/Documents/picom/build/src/picom(+0x2b378) [0x556060d7f378]
	/home/helix/Documents/picom/build/src/picom(+0x2b4ed) [0x556060d7f4ed]
	/home/helix/Documents/picom/build/src/picom(+0x51179) [0x556060da5179]
	/home/helix/Documents/picom/build/src/picom(+0x523a9) [0x556060da63a9]
	/home/helix/Documents/picom/build/src/picom(+0x1aafc) [0x556060d6eafc]
...
```

Checking only for leaks of xcb composite named windows' pixmaps and suppressing errors about functions trying to free resources that are not allocated:
```
$ XRC_INTERCEPT="xcb_composite_named_windows_pixmaps" XRC_PRINT="resource_allocated,resource_freed,resource_leaked,resource_already_allocated" LD_PRELOAD="xrescheck.so" picom
? xrescheck 0.0.1 is here!
...
+ xcb_composite_name_window_pixmap_checked allocated 25166392
...
- xcb_free_pixmap freed 25166422
? checking for leaked resources...
```

To get more meaningful backtrace symbols you can either rebuild the application you're checking for leaks in with such compiler options as `-rdynamic` or use the `addr2line` command line utility which is way more convenient:
```
$ addr2line -e /home/helix/Documents/picom/build/src/picom +0x2b378 +0x2b4ed +0x51179 +0x523a9 +0x1aafc
/home/helix/Documents/picom/build/../src/x.c:298
/home/helix/Documents/picom/build/../src/x.c:326
/home/helix/Documents/picom/build/../src/backend/backend_common.c:35 (discriminator 4)
/home/helix/Documents/picom/build/../src/backend/backend_common.c:297
/home/helix/Documents/picom/build/../src/win.c:369
```
