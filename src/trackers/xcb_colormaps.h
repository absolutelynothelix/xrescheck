#define XCB_COLORMAPS_TRACKER_BIT 1 << 0
#define XCB_COLORMAPS_TRACKER_STRING "xcb_colormaps"

/**
 * xcb_void_cookie_t xcb_create_colormap[_checked](xcb_connection_t *c,
 *     uint8_t alloc, xcb_colormap_t mid, xcb_window_t window,
 *     xcb_visualid_t visual)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
    XCB_COLORMAPS_TRACKER_BIT,
    xcb_void_cookie_t,
    xcb_create_colormap,
    VA_LIST(xcb_connection_t *c, uint8_t alloc, xcb_colormap_t mid,
        xcb_window_t window, xcb_visualid_t visual),
    VA_LIST(c, alloc, mid, window, visual),
    mid
)

/**
 * xcb_void_cookie_t xcb_free_colormap[_checked](xcb_connection_t *c,
 *     xcb_colormap_t cmap)
 */
GEN_XCB_REQUEST_CHECK_FREE_FUNCS(
    XCB_COLORMAPS_TRACKER_BIT,
    xcb_void_cookie_t,
    xcb_free_colormap,
    VA_LIST(xcb_connection_t *c, xcb_colormap_t cmap),
    VA_LIST(c, cmap),
    cmap
)
