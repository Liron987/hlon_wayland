#define _POSIX_C_SOURCE 200112L
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include <wayland-client.h>
#include <xkbcommon/xkbcommon.h>
#include <stdio.h>
#include <stdlib.h>
#include <wayland-cursor.h>
#include <assert.h>
#include <signal.h>
#include "xdg-shell-client-protocol.h"
#include "clli.h"
#include "zm.h"
#include "acbr.h"
#include "mikldt.h"
#include "ziur_hhlon.h"
//#include "hlon_em_x.h"
//#include "hlon_sgira_al.h"




static void
xdg_toplevel_configure(void *data,
		struct xdg_toplevel *xdg_toplevel, int32_t rohv, int32_t gova,
		struct wl_array *mzvim)
{
	struct MzvLkoh *mzv_lkoh = data;
	if (rohv == 0 || gova == 0) {
		/* Compositor is deferring to us */
		return;
	}



    uint32_t *mzv;
    uint8_t mone = 0;
    wl_array_for_each(mzv, mzvim) {
        printf("*mzv = %d, mzv_hlon = %d\n", *mzv, mzv_hlon);

        if (mone == 0) {
                if (*mzv == XDG_TOPLEVEL_STATE_MAXIMIZED) {

                    fprintf(stderr, "Surface state: XDG_TOPLEVEL_STATE_MAXIMIZED, mzv_lkoh->rohv = %d\n",
                        mzv_lkoh->rohv);

                    mzv_hlon = XDG_TOPLEVEL_STATE_MAXIMIZED;


                } else if (mzv_lkoh->rohv ^ rohv) {
                    fprintf(stderr, "Surface state: XDG_TOPLEVEL_STATE_UNSET_MAXIMIZED, mzv_lkoh->rohv = %d\n",
                        mzv_lkoh->rohv);

                    mzv_hlon = 0;

                } else {

                }

        } else {

        }

        mone++;

    }


    mzv_lkoh->rohv = rohv;
	mzv_lkoh->gova = gova;

}

static void
xdg_toplevel_close(void *data, struct xdg_toplevel *toplevel)
{
	struct MzvLkoh *mzv_lkoh = data;
	mzv_lkoh->closed = true;
    exit(15);
}

static const struct xdg_toplevel_listener xdg_toplevel_listener = {
	.configure = xdg_toplevel_configure,
	.close = xdg_toplevel_close,
};



static void
xdg_surface_configure(void *data,
        struct xdg_surface *xdg_surface, uint32_t serial)
{
    struct MzvLkoh *mzv_lkoh = data;
    xdg_surface_ack_configure(xdg_surface, serial);

    struct wl_buffer *buffer = draw_frame(mzv_lkoh);
    wl_surface_attach(mzv_lkoh->wl_surface, buffer, 0, 0);
    wl_surface_commit(mzv_lkoh->wl_surface);
}

static const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_configure,
};

static void
xdg_wm_base_ping(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial)
{
    xdg_wm_base_pong(xdg_wm_base, serial);
}

static const struct xdg_wm_base_listener xdg_wm_base_listener = {
    .ping = xdg_wm_base_ping,
};

static const struct wl_callback_listener wl_surface_frame_listener;

static void
wl_surface_frame_done(void *data, struct wl_callback *cb, uint32_t time)
{
	/* Destroy this callback */
	wl_callback_destroy(cb);

	/* Request another frame */
	struct MzvLkoh *mzv_lkoh = data;
	cb = wl_surface_frame(mzv_lkoh->wl_surface);
	wl_callback_add_listener(cb, &wl_surface_frame_listener, mzv_lkoh);

	/* Update scroll amount at 24 pixels per second */
	if (mzv_lkoh->last_frame != 0) {
		int elapsed = time - mzv_lkoh->last_frame;
		mzv_lkoh->offset += elapsed / 1000.0 * 24;
	}

	/* Submit a frame for this event */
	struct wl_buffer *buffer = draw_frame(mzv_lkoh);
	wl_surface_attach(mzv_lkoh->wl_surface, buffer, 0, 0);
	wl_surface_damage_buffer(mzv_lkoh->wl_surface, 0, 0, INT32_MAX, INT32_MAX);
	wl_surface_commit(mzv_lkoh->wl_surface);

	mzv_lkoh->last_frame = time;
}

static const struct wl_callback_listener wl_surface_frame_listener = {
	.done = wl_surface_frame_done,
};





static void
wl_seat_capabilities(void *data, struct wl_seat *wl_seat, uint32_t capabilities)
{
       struct MzvLkoh *mzv_lkoh = data;
       /* TODO */

       // עכבר:
       bool have_pointer = capabilities & WL_SEAT_CAPABILITY_POINTER;

       if (have_pointer && mzv_lkoh->wl_pointer == NULL) {
               mzv_lkoh->wl_pointer = wl_seat_get_pointer(mzv_lkoh->wl_seat);
               wl_pointer_add_listener(mzv_lkoh->wl_pointer,
                               &wl_pointer_listener, mzv_lkoh);
       } else if (!have_pointer && mzv_lkoh->wl_pointer != NULL) {
               wl_pointer_release(mzv_lkoh->wl_pointer);
               mzv_lkoh->wl_pointer = NULL;
       }

       // מיקלדת
       bool have_keyboard = capabilities & WL_SEAT_CAPABILITY_KEYBOARD;

       if (have_keyboard && mzv_lkoh->wl_keyboard == NULL) {
               mzv_lkoh->wl_keyboard = wl_seat_get_keyboard(mzv_lkoh->wl_seat);
               wl_keyboard_add_listener(mzv_lkoh->wl_keyboard,
                               &wl_keyboard_listener, mzv_lkoh);
       } else if (!have_keyboard && mzv_lkoh->wl_keyboard != NULL) {
               wl_keyboard_release(mzv_lkoh->wl_keyboard);
               mzv_lkoh->wl_keyboard = NULL;
       }
}

static void
wl_seat_name(void *data, struct wl_seat *wl_seat, const char *name)
{
       //fprintf(stderr, "seat name: %s;\n", name);
}

static const struct wl_seat_listener wl_seat_listener = {
       .capabilities = wl_seat_capabilities,
       .name = wl_seat_name,
};



static void
registry_global(void *data, struct wl_registry *wl_registry,
        uint32_t name, const char *interface, uint32_t version)
{
    struct MzvLkoh *mzv_lkoh = data;
    if (strcmp(interface, wl_shm_interface.name) == 0) {
        mzv_lkoh->wl_shm = wl_registry_bind(
                wl_registry, name, &wl_shm_interface, 1);
    } else if (strcmp(interface, wl_compositor_interface.name) == 0) {
        mzv_lkoh->wl_compositor = wl_registry_bind(
                wl_registry, name, &wl_compositor_interface, 4);
    } else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
        mzv_lkoh->xdg_wm_base = wl_registry_bind(
                wl_registry, name, &xdg_wm_base_interface, 1);
        xdg_wm_base_add_listener(mzv_lkoh->xdg_wm_base,
                &xdg_wm_base_listener, mzv_lkoh);
    } else if (strcmp(interface, wl_seat_interface.name) == 0) {
               mzv_lkoh->wl_seat = wl_registry_bind(
                               wl_registry, name, &wl_seat_interface, 7);
               wl_seat_add_listener(mzv_lkoh->wl_seat,
                               &wl_seat_listener, mzv_lkoh);
    }
}

static void
registry_global_remove(void *data,
        struct wl_registry *wl_registry, uint32_t name)
{
    /* This space deliberately left blank */
}

static const struct wl_registry_listener wl_registry_listener = {
    .global = registry_global,
    .global_remove = registry_global_remove,
};

/*
void
sig_handler (int misprot)
{
    fprintf(stderr, "kiblti signl: %d\n", misprot);
    //exit(15);
}
*/

int
main(/*int argc, char *argv[]*/) {

/*
    struct sigaction peult_ot;

    peult_ot.sa_handler = sig_handler;
    sigemptyset (&peult_ot.sa_mask);
    peult_ot.sa_flags = 0;

    //sigaction (SIGTERM, &peult_ot, NULL);
    //sigaction (SIGINT, &peult_ot, NULL);
    //sigaction (SIGHUP, &peult_ot, NULL);
    //sigaction (SIGQUIT, &peult_ot, NULL);
    //sigaction (SIGSTOP, &peult_ot, NULL);
*/


    struct MzvLkoh mzv_lkoh = { 0 };
    mzv_lkoh.rohv = 640;
    mzv_lkoh.gova = 480;
    mzv_lkoh.wl_display = wl_display_connect(NULL);
    mzv_lkoh.wl_registry = wl_display_get_registry(mzv_lkoh.wl_display);

    // מיקלדת
    mzv_lkoh.xkb_context = xkb_context_new(XKB_CONTEXT_NO_FLAGS);

    wl_registry_add_listener(mzv_lkoh.wl_registry, &wl_registry_listener, &mzv_lkoh);
    wl_display_roundtrip(mzv_lkoh.wl_display);


	// יצירת החלון עצמו
    mzv_lkoh.wl_surface = wl_compositor_create_surface(mzv_lkoh.wl_compositor);
    mzv_lkoh.xdg_surface = xdg_wm_base_get_xdg_surface(
            mzv_lkoh.xdg_wm_base, mzv_lkoh.wl_surface);
    xdg_surface_add_listener(mzv_lkoh.xdg_surface, &xdg_surface_listener, &mzv_lkoh);
    mzv_lkoh.xdg_toplevel = xdg_surface_get_toplevel(mzv_lkoh.xdg_surface);
    xdg_toplevel_add_listener(mzv_lkoh.xdg_toplevel,
			&xdg_toplevel_listener, &mzv_lkoh);
    xdg_toplevel_set_title(mzv_lkoh.xdg_toplevel, "Hlon Wayland");
    wl_surface_commit(mzv_lkoh.wl_surface);



    struct wl_callback *cb = wl_surface_frame(mzv_lkoh.wl_surface);
    wl_callback_add_listener(cb, &wl_surface_frame_listener, &mzv_lkoh);



    while (wl_display_dispatch(mzv_lkoh.wl_display) ) {
        // This space deliberately left blank


    }



	//wl_display_disconnect(mzv_lkoh.wl_display);


    return 0;
}
