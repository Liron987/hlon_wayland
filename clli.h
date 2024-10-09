#ifndef clli_h
#define clli_h



// מבנה עבור אירועי עכבר
struct pointer_event {
       uint32_t event_mask;
       wl_fixed_t surface_x, surface_y;
       uint32_t button, state;
       uint32_t time;
       uint32_t serial;
       struct {
               bool valid;
               wl_fixed_t value;
               int32_t discrete;
       } axes[2];
       uint32_t axis_source;
};


//מבנה עבור מצב החלון ואירועיו
struct MzvLkoh {
    /* Globals */
    struct wl_display *wl_display;
    struct wl_registry *wl_registry;
    struct wl_shm *wl_shm;
    struct wl_compositor *wl_compositor;
    struct xdg_wm_base *xdg_wm_base;
    struct wl_seat *wl_seat;
    /* Objects */
    struct wl_surface *wl_surface;
    struct xdg_surface *xdg_surface;
    struct wl_keyboard *wl_keyboard;
    struct wl_pointer *wl_pointer;
    struct wl_touch *wl_touch;
    struct xdg_toplevel *xdg_toplevel;
    /* state */
    float offset;
    uint32_t last_frame;
    int rohv, gova;
    struct wl_array *mzvim;
    bool closed;
    struct pointer_event pointer_event;
    /* מיקלדת */
    struct xkb_state *xkb_state;
    struct xkb_context *xkb_context;
    struct xkb_keymap *xkb_keymap;
};


// משתנים לשמירת מיקום העכבר
int acbr_bx = 0,
    acbr_by = 0;

// משתנה לקביעת מצב החלון
unsigned char mzv_hlon;
/*
    // גודל חלון התחלתי
const int rohv_hthla = 640, gova_hthla = 480;
int rohv = rohv_hthla, gova = gova_hthla;
*/
// מבנים ליצירת צלמית העכבר
struct wl_surface *cursor_surface;
struct wl_cursor_image *cursor_image;
struct wl_cursor *cursor;
struct wl_cursor_theme *cursor_theme;
struct wl_buffer *cursor_buffer;

// משתנה לשמירת נתוני לחיצות בעכבר (לטובת שיחרור הלחיצה על כפותרים כמו: סגירה, מירוב וכו')
unsigned char CFTOR_SGIRA = 1,
                CFTOR_MIRUV = 2,
                CFTOR_MIZUR = 3,
                SURT_HCOTR = 4;

// מבנה לחיצות עכבר - זמן ונקודות ציון
struct Lhiza {
    int x1,
             x2,
             y1,
             y2;

    time_t zmn_nochi,
           zmn1,
           zmn2;
} lhiza = {
    .x1 = 0,
    .x2 = 0,
    .y1 = 0,
    .y2 = 0,

    .zmn_nochi = 0,
    .zmn1 = 0,
    .zmn2 = 0
};

char ezor_lhiza = 0, mone_lhizot_rzufot = 0;
time_t zmn_lhiza = 0;

// גובה הכותרת (תמיד להכפיל את מספר התאי-תמונה ב- 256, שזה שווה להסטה ב- 8)
#define COTRT 40

#define SGIRA (acbr_bx > 0 && acbr_bx < (mzv_lkoh->rohv << 8) && acbr_bx > (mzv_lkoh->rohv << 8) - (COTRT << 8) \
                    && acbr_by >= 0 && acbr_by <= (COTRT << 8) )

#define MIRUV acbr_bx > (mzv_lkoh->rohv << 8) - ( (COTRT << 8) << 1) && acbr_bx < (mzv_lkoh->rohv << 8) - (COTRT << 8) \
                    && acbr_by >= 0 && acbr_by <= (COTRT << 8)

#define MIZUR acbr_bx > (mzv_lkoh->rohv << 8) - ( (COTRT << 8) * 3) && acbr_bx < (mzv_lkoh->rohv << 8) - (COTRT << 8) * 2 \
                    && acbr_by >= 0 && acbr_by <= (COTRT << 8)

#define SURT_COTR acbr_bx > 0 && acbr_bx < (mzv_lkoh->rohv << 8 * 2) - (COTRT << 8) \
                    && acbr_by >= 0 && acbr_by <= (COTRT << 8)

#define RIZPA (mzv_lkoh->gova - 40)

#define SURT_RIZPA acbr_bx > 0 && acbr_bx < (mzv_lkoh->rohv << 8) && acbr_by >= (RIZPA << 8)


#endif
