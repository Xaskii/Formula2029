#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>                       // For allegro, must be in compiler search path.
#include <allegro5/allegro_native_dialog.h> 		// for message box
#include <allegro5/allegro_image.h>
#include "game.h"
ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer;
ALLEGRO_FONT *font;
ALLEGRO_EVENT_QUEUE *event_queue;


int initializeAllegro() {
    al_init();



    //font = al_load_ttf_font("SF_Cartoonist_Hand.ttf", 36, 0);
    display = al_create_display(SCREEN_W, SCREEN_H);
    al_set_window_title(display, "Formula 2029");

    al_install_keyboard();
    al_init_font_addon();
    al_init_native_dialog_addon();
    al_init_image_addon();

    al_clear_to_color(BACKGROUND);



    return 0;
}

int initBitmap(ALLEGRO_BITMAP *image, const char *filename) {

}



