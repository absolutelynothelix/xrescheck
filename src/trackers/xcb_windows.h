#define XCB_WINDOWS_TRACKER_BIT 1 << 7
#define XCB_WINDOWS_TRACKER_STRING "xcb_windows"

/**
 * xcb_void_cookie_t xcb_create_window[_checked](xcb_connection_t *c,
 *     uint8_t depth, xcb_window_t wid, xcb_window_t parent, int16_t x,
 *     int16_t y, uint16_t width, uint16_t height, uint16_t border_width,
 *     uint16_t _class, xcb_visualid_t visual, uint32_t value_mask,
 *     const void *value_list)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
    XCB_WINDOWS_TRACKER_BIT,
    xcb_void_cookie_t,
    xcb_create_window,
    VA_LIST(xcb_connection_t *c, uint8_t depth, xcb_window_t wid,
        xcb_window_t parent, int16_t x, int16_t y, uint16_t width,
        uint16_t height, uint16_t border_width, uint16_t _class,
        xcb_visualid_t visual, uint32_t value_mask, const void *value_list),
    VA_LIST(c, depth, wid, parent, x, y, width, height, border_width, _class,
        visual, value_mask, value_list),
    wid
)

/**
 * xcb_void_cookie_t xcb_create_window_aux[_checked](xcb_connection_t *c,
 *     uint8_t depth, xcb_window_t wid, xcb_window_t parent, int16_t x,
 *     int16_t y, uint16_t width, uint16_t height, uint16_t border_width,
 *     uint16_t _class, xcb_visualid_t visual, uint32_t value_mask,
 *     const xcb_create_window_value_list_t *value_list)
 */
GEN_XCB_REQUEST_CHECK_ALLOC_FUNCS(
    XCB_WINDOWS_TRACKER_BIT,
    xcb_void_cookie_t,
    xcb_create_window_aux,
    VA_LIST(xcb_connection_t *c, uint8_t depth, xcb_window_t wid,
        xcb_window_t parent, int16_t x, int16_t y, uint16_t width,
        uint16_t height, uint16_t border_width, uint16_t _class,
        xcb_visualid_t visual, uint32_t value_mask,
        const xcb_create_window_value_list_t *value_list),
    VA_LIST(c, depth, wid, parent, x, y, width, height, border_width, _class,
        visual, value_mask, value_list),
    wid
)

/**
 * xcb_void_cookie_t xcb_destroy_window[_checked](xcb_connection_t *c,
 *     xcb_window_t window)
 */
GEN_XCB_REQUEST_CHECK_FREE_FUNCS(
    XCB_WINDOWS_TRACKER_BIT,
    xcb_void_cookie_t,
    xcb_destroy_window,
    VA_LIST(xcb_connection_t *c, xcb_window_t window),
    VA_LIST(c, window),
    window
)