#ifndef mikldt_h
#define mikldt_h


static void
wl_keyboard_keymap(void *data, struct wl_keyboard *wl_keyboard,
               uint32_t format, int32_t fd, uint32_t size)
{
       struct MzvLkoh *mzv_lkoh = data;
       assert(format == WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1);

       // Per the Wayland spec, this must be mapped with MAP_PRIVATE in version 7 of the protocol and higher.
       // https://discourse.libsdl.org/t/sdl-wayland-use-map-private-when-mapping-the-keyboard-keymap-file-descriptor/39367
       char *map_shm = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
       assert(map_shm != MAP_FAILED);

       struct xkb_keymap *xkb_keymap = xkb_keymap_new_from_string(
                       mzv_lkoh->xkb_context, map_shm,
                       XKB_KEYMAP_FORMAT_TEXT_V1, XKB_KEYMAP_COMPILE_NO_FLAGS);
       munmap(map_shm, size);
       close(fd);


       /* מעקף להשגת קלט מקלדת כאשר אתה מעוניין בהצגה שמית, כגון:
        * key press: sym: w            (119), utf8: 'w'
        * key release: sym: w            (119), utf8: 'w'
       struct xkb_keymap *xkb_keymap = xkb_keymap_new_from_names (mzv_lkoh->xkb_context, NULL, XKB_KEYMAP_COMPILE_NO_FLAGS);
*/


       struct xkb_state *xkb_state = xkb_state_new(xkb_keymap);
       xkb_keymap_unref(mzv_lkoh->xkb_keymap);
       xkb_state_unref(mzv_lkoh->xkb_state);
       mzv_lkoh->xkb_keymap = xkb_keymap;
       mzv_lkoh->xkb_state = xkb_state;
}


static void
wl_keyboard_enter(void *data, struct wl_keyboard *wl_keyboard,
               uint32_t serial, struct wl_surface *surface,
               struct wl_array *keys)
{
       struct MzvLkoh *mzv_lkoh = data;
       fprintf(stderr, "keyboard enter; keys pressed are:\n");
       uint32_t *key;
       wl_array_for_each(key, keys) {
               char buf[128];
               xkb_keysym_t sym = xkb_state_key_get_one_sym(
                               mzv_lkoh->xkb_state, *key + 8);
               xkb_keysym_get_name(sym, buf, sizeof(buf));
               fprintf(stderr, "sym: %-12s (%d), ", buf, sym);
               xkb_state_key_get_utf8(mzv_lkoh->xkb_state,
                               *key + 8, buf, sizeof(buf));
               fprintf(stderr, "utf8: '%s'\n", buf);
       }
}


static void
wl_keyboard_leave(void *data, struct wl_keyboard *wl_keyboard,
               uint32_t serial, struct wl_surface *surface)
{
       fprintf(stderr, "keyboard leave\n");
}


static void
wl_keyboard_key(void *data, struct wl_keyboard *wl_keyboard,
               uint32_t serial, uint32_t time, uint32_t key, uint32_t state)
{
       struct MzvLkoh *mzv_lkoh = data;
       char buf[128];
       uint32_t keycode = key + 8;
       xkb_keysym_t sym = xkb_state_key_get_one_sym(
                       mzv_lkoh->xkb_state, keycode);
       xkb_keysym_get_name(sym, buf, sizeof(buf));
       const char *action =
               state == WL_KEYBOARD_KEY_STATE_PRESSED ? "press" : "release";
       fprintf(stderr, "key %s: sym: %-12s (%d), ", action, buf, sym);
       xkb_state_key_get_utf8(mzv_lkoh->xkb_state, keycode,
                       buf, sizeof(buf));
       fprintf(stderr, "utf8: '%s'\n", buf);
}


static void
wl_keyboard_modifiers(void *data, struct wl_keyboard *wl_keyboard,
               uint32_t serial, uint32_t mods_depressed,
               uint32_t mods_latched, uint32_t mods_locked,
               uint32_t group)
{
       struct MzvLkoh *mzv_lkoh = data;
       xkb_state_update_mask(mzv_lkoh->xkb_state,
               mods_depressed, mods_latched, mods_locked, 0, 0, group);
}

static void
wl_keyboard_repeat_info(void *data, struct wl_keyboard *wl_keyboard,
               int32_t rate, int32_t delay)
{
       /* Left as an exercise for the reader */
}


// מאזין לאירועי מיקלדת
static const struct wl_keyboard_listener wl_keyboard_listener = {
       .keymap = wl_keyboard_keymap,
       .enter = wl_keyboard_enter,
       .leave = wl_keyboard_leave,
       .key = wl_keyboard_key,
       .modifiers = wl_keyboard_modifiers,
       .repeat_info = wl_keyboard_repeat_info,
};


#endif
