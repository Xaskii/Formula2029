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
ALLEGRO_BITMAP *truckImage;
ALLEGRO_BITMAP *background;
ALLEGRO_KEYBOARD

void initializeAllegro() {
    al_init();

    display = al_create_display(SCREEN_W, SCREEN_H);
    al_set_window_title(display, "Formula 2029");

    al_install_keyboard();
    al_init_font_addon();
    al_init_native_dialog_addon();
    al_init_image_addon();

    al_clear_to_color(BACKGROUND);
}

void loadBitmaps() {
    truckImage = al_load_bitmap("truck.bmp");
    if (truck.bitmap == nullptr) {
		al_show_native_message_box(display, "Error", "truck.bmp", "Could not load ",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}

	background = al_load_bitmap("background.bmp");
    if (background == nullptr) {
		al_show_native_message_box(display, "Error", "background.bmp", "Could not load ",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
    }
}

void checkKeystrokes(Input &key) {
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    key.right = false;
    key.left = false;
    key.up = false;
    key.down = false;

    if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
        key.right = true;
    }
    if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
        key.left = true;
    }
    if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
        key.up = true;
    }
    if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
        key.down = true;
    }
    if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
        doexit = true;
    }
}

void drawGameScreen(Vehicle truck){
    al_clear_to_color(BACKGROUND);

    al_draw_rotated_bitmap(background, 340, 300, truck.x, truck.y, truck.moveStats.direction, 0);
    al_draw_bitmap(truckImage, (SCREEN_H + vehicleWidth) / 2,
                   (SCREEN_W + vehicleHeight) / 2, 0);


    al_flip_display();
}



