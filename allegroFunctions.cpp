#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer;
ALLEGRO_FONT *font;
ALLEGRO_BITMAP *truckImage;
ALLEGRO_BITMAP *background;
ALLEGRO_BITMAP *fuelImage;
ALLEGRO_BITMAP *fuelFrame;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_EVENT ev;

int initializeAllegro() {
    al_init();
    // Creates displays and check if exists
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    al_set_window_title(display, "Formula 2029");

    // Installs all other components
    if (!al_install_keyboard()) {
        al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    if (!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error",
                                   "Failed to initialize al_init_image_addon!",nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    al_init_font_addon();
    al_init_ttf_addon();
    font = al_load_ttf_font("Roboto-Regular.ttf", 36, 0);
    if (!font) {
        al_show_native_message_box(display, "Error", "Error", "Could not load Roboto-Regular.ttf",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
   	if (!timer) {
   		al_show_native_message_box(display, "Error", "Error", "Failed to create timer!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
   	}
   	al_start_timer(timer);

    event_queue = al_create_event_queue();
    if (!event_queue) {
        printf("error");
		al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
      	return -1;
	}

	if (!al_init_primitives_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	if (!al_install_mouse()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize mouse addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
	}

    al_clear_to_color(BACKGROUND);

    return 0;
}

int loadBitmaps() {
    truckImage = al_load_bitmap("truck.bmp");
    if (truckImage == nullptr) {
        al_show_native_message_box(display, "Error", "truck.bmp", "Could not load ",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 1;
    }
    al_convert_mask_to_alpha(truckImage, WHITE);

    background = al_load_bitmap("background1.bmp");
    if (background == nullptr) {
        al_show_native_message_box(display, "Error", "background.bmp", "Could not load ",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 1;
    }

    fuelFrame = al_load_bitmap("fuelframe.bmp");
    if (fuelFrame == nullptr) {
        al_show_native_message_box(display, "Error", "fuelframe.bmp", "Could not load ",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 1;
    }

    fuelImage = al_load_bitmap("fuel.bmp");
    if (fuelImage == nullptr) {
        al_show_native_message_box(display, "Error", "fuel.bmp", "Could not load ",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 1;
    }
    return 0;
}

void checkKeystrokes(Input &key) {
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    key.right = false;
    key.left = false;
    key.up = false;
    key.down = false;
    key.escape = false;

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
        key.escape = true;
    }
}

int drawWelcomeScreen(){
    ALLEGRO_FONT *font100 = al_load_font("SFPixelateShaded-Bold.ttf", 100, 0);
    ALLEGRO_FONT *font50 = al_load_font("SFPixelateShaded-Bold.ttf", 50, 0);
    al_clear_to_color(BACKGROUND);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_text(font100, al_map_rgb(0, 0, 0), SCREEN_W / 2, 400, ALLEGRO_ALIGN_CENTER, "Formula 2029");

    al_draw_text(font50, al_map_rgb(0, 0, 0), SCREEN_W / 2, 700, ALLEGRO_ALIGN_CENTER, "PRESS SPACE TO START");
    al_flip_display();
}

void drawGameScreen(Vehicle truck, float fuelValue, float maxFuel) {
    al_clear_to_color(BACKGROUND);

    // draw background image rotating around the truck
    al_draw_scaled_rotated_bitmap(background, SCREEN_W / 2 + truck.x, SCREEN_W / 2 + truck.y + 200,
                                  (SCREEN_W - vehicleWidth) / 2, (SCREEN_H - vehicleHeight) / 2 + 200,
                                  8, 8,
                                  truck.moveStats.direction - M_PI / 2, 0);

    // draw truck image
    al_draw_bitmap(truckImage, (SCREEN_W - vehicleWidth) / 2,
                   (SCREEN_H - vehicleHeight) / 2 + 200, 0);

    al_draw_bitmap(fuelFrame, 50, 740, 0);

    al_draw_scaled_rotated_bitmap(fuelImage,
                                   27, 141,
                                   83, 888,
                                   1.02, truck.fuel * 1.02,
                                   0, 0);

    al_flip_display();
}

int drawGameOver() {
    ALLEGRO_FONT *font100 = al_load_font("SFPixelateShaded-Bold.ttf", 100, 0);
    al_clear_to_color(BACKGROUND);
    al_clear_to_color(al_map_rgb(10, 10, 10));
    al_draw_text(font100, al_map_rgb(255, 10, 10), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "GAME OVER");
    al_flip_display();
    return 0;
}

int checkTimer(){
    if (ev.type == ALLEGRO_EVENT_TIMER){
        return 0;
    } else {
        return 1;
    }
}

int startQueue(){
    al_wait_for_event(event_queue, &ev);
}

int checkDisplayClose(){
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        return 0;
    } else {
        return 1;
    }
}

int checkEmpty(){
    if (al_is_event_queue_empty(event_queue)){
        return 0;
    } else {
        return 1;
    }
}

int checkSpaceDown(){
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
        switch (ev.keyboard.keycode){
        case ALLEGRO_KEY_SPACE:
            return 0;
            break;
        default:
            return 1;
            break;
        }
    }
}

int checkEscape(){
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE:
            return 0;
            break;
        default:
            return 1;
        }
    }
}

void destroyEventQueue(){
    al_destroy_event_queue(event_queue);;
}

void initializeEventQueue(){
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
   	al_register_event_source(event_queue, al_get_display_event_source(display));
   	al_register_event_source(event_queue, al_get_keyboard_event_source());
}

void destroyDisplay() {
    al_destroy_display(display);
}
