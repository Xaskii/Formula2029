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

    al_init_font_addon();
    al_init_native_dialog_addon();
    al_init_image_addon();

    //font = al_load_ttf_font("SF_Cartoonist_Hand.ttf", 36, 0);
    display = al_create_display(SCREEN_W, SCREEN_H);
    al_set_window_title(display, "Formula 2029");
    al_clear_to_color(BACKGROUND);

    return 0;
}

int initBitmap(Image image, const char *filename) {
    image.bitmap = al_load_bitmap(filename);
    if (image.bitmap == nullptr) {
		al_show_native_message_box(display, "Error", filename, "Could not load ",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	al_convert_mask_to_alpha(image.bitmap, BACKGROUND);
    return 0;
}



