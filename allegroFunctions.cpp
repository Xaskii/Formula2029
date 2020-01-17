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
ALLEGRO_BITMAP *background[2];
ALLEGRO_BITMAP *fuelImage;
ALLEGRO_BITMAP *fuelFrame;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_EVENT ev;

extern ALLEGRO_FONT *shaded100;
extern ALLEGRO_FONT *shaded50;
extern ALLEGRO_FONT *solid50;

extern unsigned char red;
extern unsigned char green;

// Initializes two colors that will be used for our game
void initializeRG(unsigned char &red, unsigned char &green) {
    red = 10;
    green = 255;
}
// Loads three different styles of our game's font
void loadFonts(ALLEGRO_FONT *&shaded100, ALLEGRO_FONT *&shaded50, ALLEGRO_FONT *&solid50) {
    shaded100 = al_load_font("SFPixelateShaded-Bold.ttf", 100, 0);
    shaded50 = al_load_font("SFPixelateShaded-Bold.ttf", 50, 0);
    solid50 = al_load_font("SFPixelate-Bold.ttf", 50, 0);
}

// Initializes allegro and it's addons.
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

    background[0] = al_load_bitmap("background1.bmp");
    if (background[0] == nullptr) {
        al_show_native_message_box(display, "Error", "background1.bmp", "Could not load ",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 1;
    }

    background[1] = al_load_bitmap("background2.bmp");
    if (background[1] == nullptr) {
        al_show_native_message_box(display, "Error", "background2.bmp", "Could not load ",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 1;
    }

    fuelFrame = al_load_bitmap("fuelframe.bmp");
    if (fuelFrame == nullptr) {
        al_show_native_message_box(display, "Error", "fuelframe.bmp", "Could not load ",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 1;
    }
    al_convert_mask_to_alpha(fuelFrame, WHITE);

    fuelImage = al_load_bitmap("fuel.bmp");
    if (fuelImage == nullptr) {
        al_show_native_message_box(display, "Error", "fuel.bmp", "Could not load ",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 1;
    }

    return 0;
}
// Changes a variable using the input structure which contains
// a boolean for each key.
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

// Draws the welcome menu onto the screen and flips the display.
int drawWelcomeScreen(int timesPlayed){
    al_clear_to_color(BACKGROUND);

    al_clear_to_color(al_map_rgb(200, 100, 255));

    al_draw_textf(solid50, al_map_rgb(0, 0, 0), 0, 5, ALLEGRO_ALIGN_LEFT, "%d TIMES PLAYED", timesPlayed);

    al_draw_text(shaded100, al_map_rgb(0, 0, 0), SCREEN_W / 2, 100, ALLEGRO_ALIGN_CENTER, "Formula: 2029");

    al_draw_text(solid50, al_map_rgb(0, 0, 0), SCREEN_W / 2, 300, ALLEGRO_ALIGN_CENTER, "USE ARROW KEYS TO MOVE");
    al_draw_text(solid50, al_map_rgb(0, 0, 0), SCREEN_W / 2, 350, ALLEGRO_ALIGN_CENTER, "MAKE IT TO THE END OF THE");
    al_draw_text(solid50, al_map_rgb(0, 0, 0), SCREEN_W / 2, 400, ALLEGRO_ALIGN_CENTER, "TRACK BEFORE RUNNING OUT");
    al_draw_text(solid50, al_map_rgb(0, 0, 0), SCREEN_W / 2, 450, ALLEGRO_ALIGN_CENTER, "OF FUEL");

    al_draw_text(shaded50, al_map_rgb(0, 0, 0), SCREEN_W / 2, 650, ALLEGRO_ALIGN_CENTER, "PRESS SPACE TO START");

    al_draw_text(solid50, al_map_rgb(0, 0, 0), SCREEN_W / 2, 800, ALLEGRO_ALIGN_CENTER, "PRESS ESCAPE TO EXIT");

    al_flip_display();

    return 0;
}
// Draws the background, truck, and fuel display, then flips.
void drawGameScreen(Vehicle truck, Level info, int stage) {
    al_clear_to_color(BACKGROUND);

    // Draws the background that rotates around the truck.
    // 2nd, and 3rd arguments correspond to the axis of rotation on the bitmap.
    // 4th, and 5th arguments correspond to where the axis of rotation will
    // appear on the screen, which is on our truck.
    al_draw_scaled_rotated_bitmap(background[stage], truck.x, truck.y,
                                  (SCREEN_W - vehicleWidth) / 2, (SCREEN_H - vehicleHeight) / 2 + 200,
                                  8, 8,
                                  truck.moveStats.direction - M_PI / 2, 0);


    // Draws the truck in the middle of screen
    al_draw_bitmap(truckImage, (SCREEN_W - vehicleWidth) / 2,
                   (SCREEN_H - vehicleHeight) / 2 + 200, 0);

    // Draws fuel display
    drawFuelDisplay(truck.fuel);
    drawFuelNumber(truck.fuel);

    al_flip_display();
}

// Draws the fuel bar inside a frame
void drawFuelDisplay(float fuel) {
    // Draws the bitmap to set coordinates on the screen
    al_draw_scaled_rotated_bitmap(fuelImage,
                                   27, 141,
                                   83, 888,
                                   1.02, fuel * 1.02,
                                   0, 0);
    // Draws frame
    al_draw_bitmap(fuelFrame, 50, 740, 0);
}

// Draws the fuel number on the screen based on the remaining fuel value
void drawFuelNumber(float fuel) {

    if (green > red) {
        red = 10 + (int) ((1 - fuel) * 490);
    } else if (red > green) {
        green = 253 - (int) ((0.5 - fuel) * 490);
    }
    if (green == 255 && red == 255) {
        green-= 2;
    }

    // Draws text on the screen corresponding to the remaining fuel (0 - 100)
    al_draw_textf(solid50, al_map_rgb(red, green, 16), 200, 788, ALLEGRO_ALIGN_CENTER, "%.0f%%", fabs(fuel * 100));
}
// Draws the game over screen saying "GAME OVER"
int drawGameOver() {
    al_clear_to_color(BACKGROUND);
    al_clear_to_color(al_map_rgb(10, 10, 10));
    al_draw_text(shaded100, al_map_rgb(255, 10, 10), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "GAME OVER");
    al_flip_display();
    return 0;
}

// Draws the game win screen saying "YOU WON!"
int drawGameWin() {
    al_clear_to_color(BACKGROUND);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_text(shaded100, al_map_rgb(255, 10, 10), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "YOU WON!");
    al_flip_display();
    return 0;
}

// Checks if the event queue's timer has gone off
int checkTimer(){
    if (ev.type == ALLEGRO_EVENT_TIMER){
        return 0;
    } else {
        return 1;
    }
}

// Starts the event queue to be used
int startQueue(){
    al_wait_for_event(event_queue, &ev);
    return 0;
}

// Checks if the display has been closed
int checkDisplayClose(){
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        return 0;
    } else {
        return 1;
    }
}

// Checks if the event queue is empty
int checkEmpty(){
    if (al_is_event_queue_empty(event_queue)){
        return 0;
    } else {
        return 1;
    }
}

// Checks if the space key has been pressed, uses an event queue because
// the key doesn't need to be held down or anything
int checkSpaceDown(){
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
        // Uses a switch statement because a normal comparison wasn't working
        switch (ev.keyboard.keycode){
        case ALLEGRO_KEY_SPACE:
            return 0;
            break;
        default:
            return 1;
            break;
        }
    }
    return 1;
}

// Checks if the user presses escape
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
    return 1;
}

// Destroys the event queue
void destroyEventQueue(){
    al_destroy_event_queue(event_queue);;
}

// Initializes the event queue(s)
void initializeEventQueue(){
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
   	al_register_event_source(event_queue, al_get_display_event_source(display));
   	al_register_event_source(event_queue, al_get_keyboard_event_source());
}

// Destroys the display
void destroyDisplay() {
    al_destroy_display(display);
}
