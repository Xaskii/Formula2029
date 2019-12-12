/*****************************************************************************
 *	Name:       Xavi Simpson & David Xu
 *	Date:       2019-02-11
 *
 *	Purpose:
 *
 *	Usage:
 *	Revision History:
 *
 *	Known Issues:
 *
 *****************************************************************************/


#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>                       // For allegro, must be in compiler search path.
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include "game.h"

int main(){
    int numBitmaps = 1;
    const int FPS = 60;
    bool doexit = false;
    const int vehicleWidth = 100;
    const int vehicleHeight = 100;


    Image fuelBar;
    Image background;
    Vehicle truck;
    Input key;

    truck.moveStats.direction = M_PI / 2;
    truck.moveStats.onTrack = true;
    truck.x = 0;
    truck.y = 0;

    initializeAllegro();

    truck.bitmap = al_load_bitmap("truck.bmp");
    if (truck.bitmap == nullptr) {
		al_show_native_message_box(display, "Error", "truck.bmp", "Could not load ",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}

	background.bitmap = al_load_bitmap("background.bmp");
    if (background.bitmap == nullptr) {
		al_show_native_message_box(display, "Error", "background.bmp", "Could not load ",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
    }
    //set some stuff at the start
    background.y = 0;

    while (!doexit){
        al_rest(1/FPS);
        key.right = false;
        key.left = false;
        key.up = false;
        key.down = false;
        // get keyboard state

        ALLEGRO_KEYBOARD_STATE keyState;
        al_get_keyboard_state(&keyState);

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

        // Decide where the truck is
        truck.moveStats.speed = calcSpeed(truck.moveStats.speed, key.up);
        truck.moveStats.direction = calcDirection(truck.moveStats.direction, key.left, key.right);
        calcMovement(truck.x, truck.y, truck.moveStats, key);


        printf("Keystates: \n");
        if (key.left){
            printf("Left\n");
        }
        if (key.right){
            printf("right\n");
        }

        printf("\n");

        printf("Truck: %f, %f\n", truck.x, truck.y);
        printf("Background: %d, %d\n", background.x, background.y);
        // Draw everything
        al_clear_to_color(BACKGROUND);
        // draws the truck to the middle of the screen
        al_draw_scaled_rotated_bitmap(background.bitmap,
                                    340 + truck.x, 300 + truck.y,
                                    (SCREEN_H + vehicleWidth) / 2, (SCREEN_W + vehicleHeight) / 2,
                                    6, 6,
                                    truck.moveStats.direction - M_PI / 2, 0);

        al_draw_bitmap(truck.bitmap, (SCREEN_H + vehicleWidth) / 2,
                       (SCREEN_W + vehicleHeight) / 2, 0);

        al_flip_display();

    }
    al_destroy_display(display);
    return 0;
}
