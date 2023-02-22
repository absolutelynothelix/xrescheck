#define XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_TRACKER_BIT 1 << 0
#define XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_TRACKER_STRING \
	"xcb_composite_named_windows_pixmaps"

/**
 * xcb_void_cookie_t xcb_composite_name_window_pixmap[_checked](
 *     xcb_connection_t *c, xcb_window_t window, xcb_pixmap_t pixmap)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
	XCB_COMPOSITE_NAMED_WINDOWS_PIXMAPS_TRACKER_BIT,
	xcb_void_cookie_t,
	xcb_composite_name_window_pixmap,
	VA_LIST(xcb_connection_t *c, xcb_window_t window, xcb_pixmap_t pixmap),
	VA_LIST(c, window, pixmap),
	pixmap
)
