#ifndef zlmit_acbr_h
#define zlmit_acbr_h


void zlmit_acbr(char *erca, char *zlmit, void *data) {

	struct MzvLkoh *mzv_lkoh = data;

	//wl_pointer_destroy(mzv_lkoh.wl_pointer);

	// אם כבר יש ערכת נושא של עכבר טעונה - ניפרוק אותה בטרם נטען מחדש/חדשה
	if (cursor_theme)
		wl_cursor_theme_destroy(cursor_theme);

	// טעינת ערכת נושא חדשה
    cursor_theme = wl_cursor_theme_load(
		erca
		//NULL
		, 24, mzv_lkoh->wl_shm
	);

    cursor = wl_cursor_theme_get_cursor(cursor_theme, zlmit);
	cursor_image = cursor->images[0]; // יתכן שיש צלמית עם הנפשה ולכן אולי יש מתמונה אחת במערך
	cursor_buffer = wl_cursor_image_get_buffer(cursor_image);
	cursor_surface = wl_compositor_create_surface(mzv_lkoh->wl_compositor);

	wl_surface_attach(cursor_surface, cursor_buffer, 0, 0);
	/*
	 * השורה הבאה כנראה אינה נחוצה, היא מאפשרת להחליף רק חלק מהמשטח אותו אנו טוענים ובכך לטעונו מהר יותר.
	 * אך מכיוון שהמשטח של העכבר הוא כולו (אם איני טועה) אז אין צורך להחליף רק חלק אלא הכל
	 */
	wl_surface_damage_buffer(cursor_surface, 0, 0, cursor_image->width, cursor_image->height);
	wl_surface_commit(cursor_surface);


	wl_pointer_set_cursor(mzv_lkoh->wl_pointer, mzv_lkoh->pointer_event.serial, cursor_surface, cursor_image->hotspot_x, cursor_image->hotspot_y);

}


#endif
