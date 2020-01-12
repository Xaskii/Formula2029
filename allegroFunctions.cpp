#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include "game.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer;
ALLEGRO_FONT *font;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_BITMAP *truckImage;
ALLEGRO_BITMAP *background;
ALLEGRO_BITMAP *fuelImage;
ALLEGRO_BITMAP *fuelFrame;

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

    al_clear_to_color(BACKGROUND);
}

int loadBitmaps() {
    truckImage = al_load_bitmap("truck.bmp");
    if (truckImage == nullptr) {
        al_show_native_message_box(display, "Error", "truck.bmp", "Could not load ",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 1;
    }
    al_convert_mask_to_alpha(truckImage, WHITE);

    background = al_load_bitmap("background.bmp");
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

void drawGameScreen(Vehicle truck) {
    al_clear_to_color(BACKGROUND);

    al_draw_scaled_rotated_bitmap(background,
                                  (SCREEN_W + truck.x) / 2, (SCREEN_H + truck.y) / 2,
                                  (SCREEN_H + vehicleWidth) / 2, (SCREEN_W + vehicleHeight) / 2,
                                  6, 6,
                                  truck.moveStats.direction - M_PI / 2, 0);

    al_draw_bitmap(truckImage, (SCREEN_H + vehicleWidth) / 2,
                   (SCREEN_W + vehicleHeight) / 2, 0);
    /*al_draw_scaled_bitmap(ALLEGRO_BITMAP *bitmap, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh, int flags) */
    al_draw_bitmap(fuelFrame, 50, 740, 0);

    al_draw_scaled_rotated_bitmap(fuelImage,
                                   27, 141,
                                   83, 888,
                                   1.02, truck.fuel * 1.02,
                                   0, 0);

    al_flip_display();
}



