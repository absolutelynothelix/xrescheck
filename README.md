# xrescheck
xrescheck is a small and trivial utility to identify X11-related memory leaks similar to the [apitrace]()'s LeakTrace. It was initially developed as a standalone replacement for the [compton]()'s legacy builtin [xrescheck]() in [picom]().

xrescheck works by intercepting functions that allocate and free resources:
* When a resource is allocated, it's added to the xrescheck's internal resources hash table;
* When a resource is freed, it's removed from the hash table;
* If application exits and there are resources in the hash table, they're considered leaked;
* If a resource that's already in the hash table is allocated, an error is considered;
* If a resource that's not in the hash table is freed, an error is considered;
* If a wrong free function tried to free a resource, an error is considered.

That's it.

xrescheck itself doesn't check for leaks of any particular kinds of resources. It's an interface for trackers - header files containing declarations of functions to intercept. Builtin trackers are:
* xcb colormaps tracker (`xcb_colormaps`);
* xcb composite named windows' pixmaps tracker (`xcb_composite_named_windows_pixmaps`);
* xcb damage damage tracker (`xcb_damage_damage`);
* xcb gcs tracker (`xcb_gcs`);
* xcb pixmaps tracker (`xcb_pixmaps`);
* xcb render pictures tracker (`xcb_render_pictures`);
* xcb sync fences tracker (`xcb_sync_fences`);
* xcb windows tracker (`xcb_windows`);
* xcb xfixes regions tracker (`xcb_xfixes_regions`).

See the corresponding tracker header file in the `src/trackers` for details on what functions are intercepted.

Writing your own tracker, at least for xcb functions, isn't hard. See the builtin trackers header files in the `src/trackers` folder for examples.

## Building
You need:
* xcb composite header file;
* xcb damage header file;
* xcb render header file;
* xcb sync header file;
* xcb xfixes header file;
* xcb header file;
* uthash header file;

On Arch Linux it's the `libxcb` and the `uthash` packages.

The `build.sh` script builds the xrescheck library (`xrescheck.so`) and places it in the `build` folder.

## Usage
There is the `xrescheck.sh` wrapper script:
```
$ xrescheck.sh 
usage: xrescheck.sh [option]... application
identify x11-related memory leaks in an application
```

Available options are:
* `-b` or `--backtrace-symbols` - a number of backtrace symbols to print. Defaults to 3;
* `-p` or `--print` - a comma-separated list of messages to print. Defaults to all available messages:
	* `resource_allocated` - a resource is allocated;
	* `resource_freed` - a resource is freed;
	* `resource_leaked` - a resource is considered leaked;
	* `resource_already_allocated` - a resource that's already allocated is allocated;
	* `resource_not_allocated` - a resource that's not allocated is freed;
	* `wrong_free_function` - a wrong free function tried to free a resource;
* `-r` or `--resolve-backtrace-symbols` - resolve backtrace symbols at run-time using the `addr2line` (a part of the `binutils` package) command line utility. This option is experimental and is recommended to be used only with the `resource_leaked` messages;
* `-t` or `--track` - a comma-separated list of trackers to enable. Defaults to all available trackers (listed above).

Note: the xcb composite named windows' pixmaps and the xcb pixmaps trackers share the same free function so if you have only one of these enabled xrescheck may complain about freeing resources that are not allocated. You can either enable both of these trackers or suppress these errors by excluding the `resource_not_allocated` messages from printed messages.

If the wrapper script fails, you can manually preload the xrescheck library with the `LD_PRELOAD` environment variable and configure it with the `XRC_TRACK`, `XRC_PRINT` and the `XRC_BACKTRACE_SYMBOLS` environment variables.

## Examples
Enable only the xcb render pictures tracker, print only messages about resources considered leaked, print five backtrace symbols and resolve them at run-time:
```
$ xrescheck.sh -t xcb_render_pictures -p resource_leaked -b 5 -r picom
? xrescheck 0.0.1 is here!
...
? checking for leaked resources...
! 0x1c0024b allocated by xcb_render_create_picture_checked wasn't freed, the allocation was made here:
	/home/helix/Documents/picom/build/../src/x.c:298
	/home/helix/Documents/picom/build/../src/x.c:326
	/home/helix/Documents/picom/build/../src/backend/backend_common.c:35 (discriminator 4)
	/home/helix/Documents/picom/build/../src/backend/backend_common.c:297
	/home/helix/Documents/picom/build/../src/win.c:369
...
```

Enable only the xcb composite named window's pixmaps tracker and suppress errors about freeing resources that are not allocated:
```
$ xrescheck.sh -p resource_allocated,resource_freed,resource_leaked,resource_already_allocated picom
? xrescheck 0.0.1 is here!
...
+ xcb_composite_name_window_pixmap_checked allocated 0x1c00247
...
- xcb_free_pixmap freed 0x1c0026f
? checking for leaked resources...
```
