#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>                       // For allegro, must be in compiler search path.
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include "game.h"



int main() {
    const int FPS = 60;

    Vehicle truck;
    Input key;

    key.escape = false;
    truck.x = 0;
    truck.y = 0;
    truck.moveStats.steering = 0;
    truck.moveStats.direction = M_PI / 2;
    truck.moveStats.onTrack = true;
    truck.moveStats.speed = 0;
    truck.moveStats.leftTurnTime = 0;
    truck.moveStats.rightTurnTime = 0;


    initializeAllegro();

    loadBitmaps();

    while (!key.escape) {
        al_rest(1/FPS);

        // get keyboard strokes on this frame
        checkKeystrokes(key);

        // Calculate turning time
        calcTurnTime(key, truck);
        // Decide where the truck is
        truck.moveStats.speed = calcSpeed(truck.moveStats.speed, key.up, truck.moveStats.rightTurnTime, truck.moveStats.leftTurnTime);
        truck.moveStats.direction = calcDirection(truck.moveStats.direction, key.left, key.right, truck.moveStats.steering);
        calcMovement(truck.x, truck.y, truck.moveStats, key);
        calcFuel(truck.fuel, key.up);

        // draw the truck and background
        drawGameScreen(truck);

        // prints out the keyStates and truck variables
        //printVariables(truck, key);
    }
    return 0;
}
