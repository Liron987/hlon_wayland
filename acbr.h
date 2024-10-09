#ifndef acbr_h
#define acbr_h

#include "zlmit_acbr.h"

unsigned char POINTER_EVENT_ENTER = 1 << 0,
       POINTER_EVENT_LEAVE = 1 << 1,
       POINTER_EVENT_MOTION = 1 << 2,
       POINTER_EVENT_BUTTON = 1 << 3,
       POINTER_EVENT_AXIS = 1 << 4,
       POINTER_EVENT_AXIS_SOURCE = 1 << 5,
       POINTER_EVENT_AXIS_STOP = 1 << 6,
       POINTER_EVENT_AXIS_DISCRETE = 1 << 7;

unsigned short CFTOR_SMAL = 272,
               CFTOR_YMIN = 273;

/*
// בקשה לצלמית עכבר
static void
wl_pointer_set_cursor(void *data, struct wl_pointer *wl_pointer,
               uint32_t serial, struct wl_surface *surface,
               wl_fixed_t surface_x, wl_fixed_t surface_y)
{
       struct client_state *client_state = data;
       mzv_lkoh->pointer_event.event_mask |= POINTER_EVENT_ENTER;
       mzv_lkoh->pointer_event.serial = serial;
       mzv_lkoh->pointer_event.surface_x = surface_x,
               mzv_lkoh->pointer_event.surface_y = surface_y;
}
*/

// טיפול באירועי עכבר
static void
wl_pointer_enter(void *data, struct wl_pointer *wl_pointer,
               uint32_t serial, struct wl_surface *surface,
               wl_fixed_t surface_x, wl_fixed_t surface_y)
{
       struct MzvLkoh *mzv_lkoh = data;
       mzv_lkoh->pointer_event.event_mask |= POINTER_EVENT_ENTER;
       mzv_lkoh->pointer_event.serial = serial;
       mzv_lkoh->pointer_event.surface_x = surface_x,
        mzv_lkoh->pointer_event.surface_y = surface_y;


        // נעצב את צלמית העכבר בכניסה לחלון
        /*cursor_theme = wl_cursor_theme_load(
		"breeze_cursors"
		//NULL
		, 24, mzv_lkoh->wl_shm
	);*/
        zlmit_acbr("breeze_cursors", "left_ptr", mzv_lkoh);
        //wl_pointer_set_cursor(wl_pointer, serial, cursor_surface, cursor_image->hotspot_x, cursor_image->hotspot_y);
}

static void
wl_pointer_leave(void *data, struct wl_pointer *wl_pointer,
               uint32_t serial, struct wl_surface *surface)
{
       struct MzvLkoh *mzv_lkoh = data;
       mzv_lkoh->pointer_event.serial = serial;
       mzv_lkoh->pointer_event.event_mask |= POINTER_EVENT_LEAVE;
}

static void
wl_pointer_motion(void *data, struct wl_pointer *wl_pointer, uint32_t time,
               wl_fixed_t surface_x, wl_fixed_t surface_y)
{
       struct MzvLkoh *mzv_lkoh = data;
       mzv_lkoh->pointer_event.event_mask |= POINTER_EVENT_MOTION;
       mzv_lkoh->pointer_event.time = time;
       mzv_lkoh->pointer_event.surface_x = surface_x,
               mzv_lkoh->pointer_event.surface_y = surface_y;
}

static void
wl_pointer_button(void *data, struct wl_pointer *wl_pointer, uint32_t serial,
               uint32_t time, uint32_t button, uint32_t state)
{
        struct MzvLkoh *mzv_lkoh = data;
        mzv_lkoh->pointer_event.event_mask |= POINTER_EVENT_BUTTON;
        mzv_lkoh->pointer_event.time = time;
        mzv_lkoh->pointer_event.serial = serial;
        mzv_lkoh->pointer_event.button = button,
        mzv_lkoh->pointer_event.state = state;
/*
        // לצורך הזזת החלון
        if (! (SGIRA) && ! (MIRUV) )
                if (button == 272 && state == WL_POINTER_BUTTON_STATE_PRESSED && SURT_COTR)
                        xdg_toplevel_move(mzv_lkoh->xdg_toplevel, mzv_lkoh->wl_seat, serial);
*/
}

static void
wl_pointer_axis(void *data, struct wl_pointer *wl_pointer, uint32_t time,
               uint32_t axis, wl_fixed_t value)
{
       struct MzvLkoh *mzv_lkoh = data;
       mzv_lkoh->pointer_event.event_mask |= POINTER_EVENT_AXIS;
       mzv_lkoh->pointer_event.time = time;
       mzv_lkoh->pointer_event.axes[axis].valid = true;
       mzv_lkoh->pointer_event.axes[axis].value = value;
}

static void
wl_pointer_axis_source(void *data, struct wl_pointer *wl_pointer,
               uint32_t axis_source)
{
       struct MzvLkoh *mzv_lkoh = data;
       mzv_lkoh->pointer_event.event_mask |= POINTER_EVENT_AXIS_SOURCE;
       mzv_lkoh->pointer_event.axis_source = axis_source;
}

static void
wl_pointer_axis_stop(void *data, struct wl_pointer *wl_pointer,
               uint32_t time, uint32_t axis)
{
       struct MzvLkoh *mzv_lkoh = data;
       mzv_lkoh->pointer_event.time = time;
       mzv_lkoh->pointer_event.event_mask |= POINTER_EVENT_AXIS_STOP;
       mzv_lkoh->pointer_event.axes[axis].valid = true;
}

static void
wl_pointer_axis_discrete(void *data, struct wl_pointer *wl_pointer,
               uint32_t axis, int32_t discrete)
{
       struct MzvLkoh *mzv_lkoh = data;
       mzv_lkoh->pointer_event.event_mask |= POINTER_EVENT_AXIS_DISCRETE;
       mzv_lkoh->pointer_event.axes[axis].valid = true;
       mzv_lkoh->pointer_event.axes[axis].discrete = discrete;
}

/*
struct wl_surface *cursor_surface;
struct wl_cursor_image *cursor_image;
static void
pointer_enter_handler(void *data, struct wl_pointer *wl_pointer,
    uint32_t serial, struct wl_surface *surface,
    wl_fixed_t surface_x, wl_fixed_t surface_y)
{
   wl_pointer_set_cursor(wl_pointer, serial, cursor_surface, cursor_image->hotspot_x, cursor_image->hotspot_y);
}
*/


// מסגרת לניהול אירועי עכבר
static void
wl_pointer_frame(void *data, struct wl_pointer *wl_pointer)
{
       struct MzvLkoh *mzv_lkoh = data;
       struct pointer_event *event = &mzv_lkoh->pointer_event;
       //fprintf(stderr, "pointer frame @ %d: ", event->time);

       if (event->event_mask & POINTER_EVENT_ENTER) {
               fprintf(stderr, "entered %f, %f, acbr_bx = %d, acbr_by = %d\n",
                        wl_fixed_to_double(event->surface_x),
                        wl_fixed_to_double(event->surface_y),
                        acbr_bx, acbr_by
                );

               // נשמור את מיקום העכבר
               acbr_bx = event->surface_x;
               acbr_by = event->surface_y;
               //fprintf(stderr, "slm %d, %d ", acbr_bx, acbr_by);


               // איפוס מניית הלחיצות הרצופות ברגע שישנה כניסת עכבר
                if (mone_lhizot_rzufot > 0)
                       mone_lhizot_rzufot = 0;

               /*if (ezor_lhiza != SURT_HCOTR)
                       ezor_lhiza = SURT_HCOTR;*/

       }

        if (event->event_mask & POINTER_EVENT_LEAVE) {
                fprintf(stderr, "leave\n");

                if (mzv_hlon != XDG_TOPLEVEL_STATE_MAXIMIZED)
                        acbr_bx = 0;

                //mone_lhizot_rzufot = 0;

                if (ezor_lhiza > 0 && ezor_lhiza != SURT_HCOTR)
                        ezor_lhiza = 0;
       }

       if (event->event_mask & POINTER_EVENT_MOTION) {
/*
                fprintf(stderr, "motion %f, %f, mone_lhizot_rzufot = %d\n",
                        wl_fixed_to_double(event->surface_x),
                        wl_fixed_to_double(event->surface_y),
                        mone_lhizot_rzufot
                );
*/
               // נשמור את מיקום העכבר
                acbr_bx = event->surface_x;
                acbr_by = event->surface_y;
                //fprintf(stderr, "slm %d, %d ", acbr_bx, acbr_by);

                // איפוס מניית הלחיצות הרצופות ברגע שישנה תנועת עכבר
                if (mone_lhizot_rzufot == 0)
                       mone_lhizot_rzufot = 1;

                if (zmn_lhiza > 0)
                        zmn_lhiza = 0;

               /*if (mzv_hlon ^ 0)
                       mzv_hlon = 0;*/
               // שינוי גודל החלון (הדרך הידנית, מבלי לתקשר עם המנצח - כומפוזיטור)
               /*if (strcmp("size_ver", cursor->name) == 0)
                       mzv_lkoh->gova = (acbr_by >> 8);*/
       }

       if (event->event_mask & POINTER_EVENT_BUTTON) {
               char *state = event->state == WL_POINTER_BUTTON_STATE_RELEASED ?
                       "released" : "pressed";

               fprintf(stderr, "button %d %s %d event->state = %s, acbr_bx = %d, acbr_by = %d,"
                       "mone_lhizot_rzufot = %d, ezor_lhiza = %d\n",
                       event->button, state, acbr_bx, event->state == 1 ? "לחוץ" : "משוחרר",
                       acbr_bx, acbr_by, mone_lhizot_rzufot, ezor_lhiza);


                // במקרה של לחיצה בכפתור השמאלי של העכבר
               if (event->button == CFTOR_SMAL) {
                       fprintf(stderr, "כפתור שמאל בעכבר\n");


                        // בכל מקרה של שיחרור כפתור שמאל בעכבר - נתזמן ונאמוד את מספר הלחיצות הרצופות (האם לחיצה כפולה / משולשת / וכו')
                        if (event->state == WL_POINTER_BUTTON_STATE_PRESSED) {
/*
                                fprintf(stderr, "zmn_lhiza = %li, time(NULL) - zmn_lhiza = %li\n", zmn_lhiza, time(NULL) - zmn_lhiza);

                                if (time(NULL) - zmn_lhiza <= 1)
                                        if (mone_lhizot_rzufot >= 2)
                                                mone_lhizot_rzufot = 0;
                                        else
                                                mone_lhizot_rzufot++;

                                else
                                        mone_lhizot_rzufot = 0;

                                zmn_lhiza = time(NULL);
*/
                                lhiza.zmn_nochi = time(NULL);
                                if (lhiza.zmn_nochi - lhiza.zmn1 < 1) {

                                        lhiza.x2 = acbr_bx;
                                        lhiza.y2 = acbr_by;
                                        lhiza.zmn2 = lhiza.zmn_nochi;
                                } else {
                                        lhiza.x1 = acbr_bx;
                                        lhiza.y1 = acbr_by;
                                        lhiza.zmn1 = lhiza.zmn_nochi;
                                }

                        }
                        fprintf(stderr, "time(NULL) - zmn_lhiza = %li, mone_lhizot_rzufot = %d\n",
                                                time(NULL) - zmn_lhiza, mone_lhizot_rzufot);



                       // פה אנו נסגור את החלון
                       if (SGIRA) {
                                fprintf(stderr, "\nעל הסגירה\n");

                                if (event->state == WL_POINTER_BUTTON_STATE_PRESSED)
                                        ezor_lhiza = CFTOR_SGIRA;

                                if (event->state == WL_POINTER_BUTTON_STATE_RELEASED && ezor_lhiza == CFTOR_SGIRA) {
                                        //wl_display_disconnect(mzv_lkoh->wl_display);
                                        exit(15);
                                }
                               // פה אנו נמרב את החלון
                        } else if (MIRUV) {
                                fprintf(stderr, "\nעל המירוב\n");

                                if (event->state == WL_POINTER_BUTTON_STATE_PRESSED)
                                        ezor_lhiza = CFTOR_MIRUV;

                                if (event->state == WL_POINTER_BUTTON_STATE_RELEASED /*&& ezor_lhiza == CFTOR_MIRUV*/) {


                                        printf("mzv_hlon = %d\n", mzv_hlon);
                                        if (mzv_hlon == XDG_TOPLEVEL_STATE_MAXIMIZED) {
                                                xdg_toplevel_unset_maximized(mzv_lkoh->xdg_toplevel);
                                                //mzv_hlon = 0;
                                        } else
                                                xdg_toplevel_set_maximized(mzv_lkoh->xdg_toplevel);


                                        // הדרך לקבוע גודל החלון מבלי להשתמש ב- XDG
                                        /*
                                        if (mzv_lkoh->rohv == 1920 && mzv_lkoh->gova == 1080) {

                                                xdg_surface_set_window_geometry(
                                                        mzv_lkoh->xdg_surface, 0, 0, 640, 480
                                                );
                                                mzv_lkoh->rohv = 640;
                                                mzv_lkoh->gova = 480;
                                        } else {

                                                mzv_lkoh->rohv = 1920;
                                                mzv_lkoh->gova = 1080;

                                                xdg_surface_set_window_geometry(
                                                        mzv_lkoh->xdg_surface, 640, 480, mzv_lkoh->rohv, mzv_lkoh->gova
                                                );

                                        }
                                        */

                                }
                                // פה אנו נמזער החלון
                        } else if (MIZUR) {

                                if (event->state == WL_POINTER_BUTTON_STATE_PRESSED)
                                        ezor_lhiza = CFTOR_MIZUR;

                                if (event->state == WL_POINTER_BUTTON_STATE_RELEASED && ezor_lhiza == CFTOR_MIZUR)
                                        xdg_toplevel_set_minimized(mzv_lkoh->xdg_toplevel);


                        } else if (SURT_COTR) {
                                fprintf(stderr, "\nעל הכותר\n");

                        // נבדוק אם לחיצה כפולה על שורת הכותרת אז נמרב / בל-נמרב
                                fprintf(stderr, "tevent->state = %s\n", event->state == WL_POINTER_BUTTON_STATE_PRESSED ? "לחוץ" : "שוחרר");


                                //if (event->state == WL_POINTER_BUTTON_STATE_RELEASED) {


                                if (event->state == WL_POINTER_BUTTON_STATE_PRESSED) {

                                        fprintf(stderr, "lhiza.x1 = %d, lhiza.x2 = %d, lhiza.y1 = %d, lhiza.y2 = %d, "
                                                        "lhiza.zmn1 = %li, lhiza.zmn2 = %li, lhiza.zmn2 - lhiza.zmn1 = %li\n",
                                                lhiza.x1,
                                                lhiza.x2,
                                                lhiza.y1,
                                                lhiza.y2,
                                                lhiza.zmn1,
                                                lhiza.zmn2,
                                                lhiza.zmn2 - lhiza.zmn1
                                        );


                                        if (
                                                (lhiza.x1 > 0 && lhiza.x1 < (mzv_lkoh->rohv << 8 * 2) - (COTRT << 8)
                                                && lhiza.y1 >= 0 && lhiza.y1 <= (COTRT << 8) )
                                                &&
                                                (lhiza.x2 > 0 && lhiza.x2 < (mzv_lkoh->rohv << 8 * 2) - (COTRT << 8)
                                                && lhiza.y2 >= 0 && lhiza.y2 <= (COTRT << 8) )
                                                &&
                                                lhiza.zmn2 - lhiza.zmn1 == 0

                                                /*
                                                lhiza.x1 - lhiza.x2 <= 100 && lhiza.x1 - lhiza.x2 >= -100
                                                && lhiza.y1 - lhiza.y2 <= 100 && lhiza.y1 - lhiza.y2 >= -100
                                                && (lhiza.zmn2 - lhiza.zmn1 < 1 || lhiza.zmn1 - lhiza.zmn2 < 1)
                                                && lhiza.zmn2 - lhiza.zmn1 >= 0
                                                */
                                        ) {

                                                if (mzv_hlon == XDG_TOPLEVEL_STATE_MAXIMIZED) {
                                                        xdg_toplevel_unset_maximized(mzv_lkoh->xdg_toplevel);
                                                        mzv_hlon = 0;
                                                } else
                                                        xdg_toplevel_set_maximized(mzv_lkoh->xdg_toplevel);


                                        /*
                                        * עקב התנהגות מוזרה של ווילנד או של קווין,
                                        * גם כאשר החלון מורב / בל-מורב - לחיצה נוספת
                                        * באותו המקום נחשבת כלחיצה על שורת הכותר
                                        * על אף ששורת הכותר כבר אינה באותו מקום.
                                        *
                                        * כדי לעקוף זאת אנו ממקמים את העכבר באיקס
                                        * במיקום אחר מה שגורם לכך שהלחיצה אינה נחשבת
                                        * ללחיצה על שורת הכותר.
                                        */
                                                //acbr_bx = -1;
                                                //mone_lhizot_rzufot = 0;
                                                //ezor_lhiza = 0;
                                        } else {

                                                ezor_lhiza = SURT_HCOTR;

                                                // פה אנו נגרור את החלון
                                                xdg_toplevel_move(mzv_lkoh->xdg_toplevel, mzv_lkoh->wl_seat, event->serial);

                                        }
                                }

                                //}

                                //ezor_lhiza = SURT_HCOTR;
                                //mone_lhizot_rzufot = 0;
/*
                                // פה אנו נגרור את החלון
                                if (event->state == WL_POINTER_BUTTON_STATE_PRESSED)
                                        xdg_toplevel_move(mzv_lkoh->xdg_toplevel, mzv_lkoh->wl_seat, event->serial);
*/

                        } else if (SURT_RIZPA) {
                                fprintf(stderr, "\nעל הריצפה\n");

                                if (event->state == WL_POINTER_BUTTON_STATE_PRESSED) {

                                        // נתאים את העכבר לפעולת שיגדול
                                        zlmit_acbr("breeze_cursors", "size_ver", mzv_lkoh);

                                        //gova = (acbr_by >> 8);

                                        /*enum xdg_toplevel_resize_edge edge = component_edge(mzv_lkoh->width, mzv_lkoh->height,
                                                                                            acbr_bx, acbr_by, 15);*/
                                        xdg_toplevel_resize(mzv_lkoh->xdg_toplevel, mzv_lkoh->wl_seat, event->serial, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM);

                                }


                        } else {
                                ezor_lhiza = 0;
                                //mone_lhizot_rzufot = 0;
                        }

                        if (event->state == WL_POINTER_BUTTON_STATE_RELEASED) {

                                //ezor_lhiza = 0;

                                //printf("cursor->cursor.name = %s\n", cursor->name);

                                if (strcmp("size_ver", cursor->name) == 0)
                                        zlmit_acbr("breeze_cursors", "left_ptr", mzv_lkoh);
                        }
               }
       }

       uint32_t axis_events = POINTER_EVENT_AXIS
               | POINTER_EVENT_AXIS_SOURCE
               | POINTER_EVENT_AXIS_STOP
               | POINTER_EVENT_AXIS_DISCRETE;
       char *axis_name[2] = {
               [WL_POINTER_AXIS_VERTICAL_SCROLL] = "vertical",
               [WL_POINTER_AXIS_HORIZONTAL_SCROLL] = "horizontal",
       };
       char *axis_source[4] = {
               [WL_POINTER_AXIS_SOURCE_WHEEL] = "wheel",
               [WL_POINTER_AXIS_SOURCE_FINGER] = "finger",
               [WL_POINTER_AXIS_SOURCE_CONTINUOUS] = "continuous",
               [WL_POINTER_AXIS_SOURCE_WHEEL_TILT] = "wheel tilt",
       };
       if (event->event_mask & axis_events) {
               for (size_t i = 0; i < 2; ++i) {
                       if (!event->axes[i].valid) {
                               continue;
                       }
                       fprintf(stderr, "%s axis ", axis_name[i]);
                       if (event->event_mask & POINTER_EVENT_AXIS) {
                               fprintf(stderr, "value %f ", wl_fixed_to_double(
                                                       event->axes[i].value));
                       }
                       if (event->event_mask & POINTER_EVENT_AXIS_DISCRETE) {
                               fprintf(stderr, "discrete %d ",
                                               event->axes[i].discrete);
                       }
                       if (event->event_mask & POINTER_EVENT_AXIS_SOURCE) {
                               fprintf(stderr, "via %s ",
                                               axis_source[event->axis_source]);
                       }
                       if (event->event_mask & POINTER_EVENT_AXIS_STOP) {
                               fprintf(stderr, "(stopped) ");
                       }
               }
       }

       memset(event, 0, sizeof(*event));
}

// מאזין לאירועי עכבר
static const struct wl_pointer_listener wl_pointer_listener = {
       .enter = wl_pointer_enter,
       .leave = wl_pointer_leave,
       .motion = wl_pointer_motion,
       .button = wl_pointer_button,
       .axis = wl_pointer_axis,
       .frame = wl_pointer_frame,
       .axis_source = wl_pointer_axis_source,
       .axis_stop = wl_pointer_axis_stop,
       .axis_discrete = wl_pointer_axis_discrete,
};


#endif
