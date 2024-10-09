#ifndef ziur_hhlon_h
#define ziur_hhlon_h



static void wl_buffer_release(void *data, struct wl_buffer *wl_buffer)
{
    /* Sent by the compositor when it's no longer using this buffer */
    wl_buffer_destroy(wl_buffer);
}

static const struct wl_buffer_listener wl_buffer_listener = {
    .release = wl_buffer_release,
};


static struct wl_buffer *
draw_frame(struct MzvLkoh *mzv_lkoh)
{

    int rohv = mzv_lkoh->rohv,
        gova = mzv_lkoh->gova;

    unsigned stride = rohv * 4; // כך אנו מגדירים שכל תא-תמונה מכיל אלפא, אדום, ירוק, כחול
    unsigned size = stride * gova;

    int fd = allocate_shm_file(size);
    if (fd == -1) {
        return NULL;
    }

    uint32_t *data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        close(fd);
        return NULL;
    }

    struct wl_shm_pool *pool = wl_shm_create_pool(mzv_lkoh->wl_shm, fd, size);
    struct wl_buffer *buffer = wl_shm_pool_create_buffer(pool, 0,
            rohv, gova, stride, WL_SHM_FORMAT_ARGB8888);
    wl_shm_pool_destroy(pool);
    close(fd);


    unsigned char alpha, adom, yrok, chol;
    // הכנה עבור כפתור האיקס בהמשך (מונים לקו שיורד משמאל ומימין)
    const short godl_klf = 40, mirvh = 12;
    //unsigned short smol = mirvh, ymin = mirvh;
    for (int h = 0, sura = 0, amuda = 0; h < rohv * gova; h++, amuda++) {
        if (h % rohv == 0) {
            sura++;
            amuda = 0;
        }

        // כותרת החלון
        if (sura < COTRT) {

            if (amuda < rohv - COTRT * 3) {

                alpha = 255;
                adom = 33;
                yrok = 33;
                chol = 33;

            } else if (amuda < rohv - COTRT * 2) {
                // נצייר כפתור מיזעור
                // סמל הכפתור
                if
                (
                    sura > godl_klf - 14 && sura < godl_klf - 9
                    && amuda > rohv - godl_klf * 3 + 9 && amuda < rohv - godl_klf * 2 - 9 - 1
                ) {
                    alpha = 255;
                    adom = 200;
                    yrok = 200;
                    chol = 200;
                }
                else
                {
                    // רקע הכפתור
                    alpha = 255;
                    adom = 33;
                    yrok = (MIZUR) ? 220 : ezor_lhiza == 3 ? 150 : 90;
                    chol = 33;
                }

            } else if (amuda < rohv - COTRT) {
                // נצייר כפתור מירוב
                // סמל הכפתור
                if
                (
                    (amuda > rohv - godl_klf * 2 + 9 && amuda < rohv - godl_klf - 9 - 1)
                    && (sura > 9 && sura < godl_klf - 9)
                    &&
                    (
                        (sura < 15) || (sura > godl_klf - 13)
                        || amuda == rohv - godl_klf * 2 + 9 + 1
                        || amuda == rohv - godl_klf - 9 - 1 - 1
                    )

                ) {
                    alpha = 255;
                    adom = 200;
                    yrok = 200;
                    chol = 200;
                }
                else
                {
                    alpha = 255;
                    adom = 33;
                    yrok = 33;
                    chol = (MIRUV) ? 220 : ezor_lhiza == 2 ? 150 : 90;
                }
            } else {
                // נצייר כפתור סגירה

                    // סמל הכפתור - האיקס
                if
                (
                    (amuda > rohv - godl_klf && amuda < rohv - 9 + 1)
                    && (sura > 9 && sura < godl_klf - 9)
                    &&
                    (
                        (
                            amuda >= rohv - godl_klf + sura - 1
                            && amuda <= rohv - godl_klf + sura + 1
                        )
                        ||
                        (
                            amuda >= rohv - sura - 1
                            && amuda <= rohv - sura + 1
                        )
                    )

                ) {
                    alpha = 255;
                    adom = 200;
                    yrok = 200;
                    chol = 200;
                }
                else
                {
                    // רקע הכפתור
                    alpha = 255;
                    adom = (SGIRA) ? 220 : ezor_lhiza == 1 ? 150 : 90;
                    yrok = 33;
                    chol = 33;
                }
            }

        } else if (sura > RIZPA) {

            alpha = 10;
            adom = 70;
            yrok = 70;
            chol = 70;
        // גוף החלון
        } else {

            alpha = 200;
            adom = 0;
            yrok = 0;
            chol = 0;
        }

        data[h] = (uint32_t)alpha << 24 | adom << 16 | (unsigned short)yrok << 8 | chol;

    }


    munmap(data, size);
    wl_buffer_add_listener(buffer, &wl_buffer_listener, NULL);
    return buffer;
}


#endif


/*
    // צייר החלון
	unsigned char *eize_hlon;
	!(acbr_bx > SGIRA_X && acbr_by < SGIRA_Y) ? eize_hlon = hlon_em_x : (eize_hlon = hlon_sgira_al);
	for (int i = 0; i < width * height; i++) {

        int r = eize_hlon[i * 3 + 0];
        int g = eize_hlon[i * 3 + 1];
        int b = eize_hlon[i * 3 + 2];

        data[i] = (r << 16) | (g << 8) | b;
	}
*/


/*
                if (sura == smol && amuda == rohv - godl_klf + smol - 1 && smol < godl_klf - mirvh + 2) {
                    //printf("smol = %d : ", smol);

                    alpha = 255;
                    adom = 255;
                    yrok = 255;
                    chol = 255;

                    smol++;

                } else if (sura == ymin && amuda == rohv - ymin && ymin < godl_klf - mirvh + 2) {

                    alpha = 255;
                    adom = 255;
                    yrok = 255;
                    chol = 255;

                    ymin++;
*/
