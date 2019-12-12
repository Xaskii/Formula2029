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
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>                       // For allegro, must be in compiler search path.
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include "game.h"

int main(){
    const int FPS = 60;
    const int vehicleWidth = 100;
    const int vehicleHeight = 100;
    bool doexit = false;

    Vehicle truck;
    Input key;

    truck.moveStats.direction = 0;
    truck.moveStats.onTrack = true;
    truck.x = 0;
    truck.y = 0;

    initializeAllegro();
    loadBitmaps();

    while (!doexit){
        al_rest(1/FPS);

        // get keyboard strokes on this frame
        checkKeystrokes(key);

        // Decide where the truck is
        truck.moveStats.speed = calcSpeed(truck.moveStats.speed, key.up);
        truck.moveStats.direction = calcDirection(truck.moveStats.direction, key.left, key.right);
        calcMovement(truck.x, truck.y, truck.moveStats, key);
        calcFuel(userFuel, key.up);

        // draw the truck and background
        drawGameScreen();
    }

    return 0;
}
