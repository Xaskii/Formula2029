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
    Vehicle truck;
    Input key;
    bool gameOver = false;
    bool redraw = true;
    bool exitProgram = false;

    initializeAllegro();
    loadBitmaps();
    initializeEventQueue();

    while (!exitProgram) {
        gameOver = false;
        key.escape = false;
        truck.fuel = 500;
        truck.x = 0;
        truck.y = 0;
        truck.moveStats.direction = M_PI / 2;
        truck.moveStats.onTrack = true;
        truck.moveStats.speed = 0;
        truck.moveStats.leftTurnTime = 0;
        truck.moveStats.rightTurnTime = 0;

        startQueue();

        if (redraw) {
            drawWelcomeScreen();
            redraw = false;
        }

        if (!checkDisplayClose() || !checkEscape()) {
            break;
        } else if (!checkEscape()) {
            break;
        } else if(!checkSpaceDown()) {
            while (!key.escape) {
                startQueue();

                // check if the timer went off
                if (!checkTimer()) {
                    redraw = true;
                // check if the user pressed the x on the display window
                } else if (!checkDisplayClose()) {
                    break;
                }

                // draw the game if nothing else has happened
                if (redraw && !checkEmpty()) {
                    checkKeystrokes(key);

                    // Calculate turning time
                    calcTurnTime(key, truck);
                    // Decide where the truck isi
                    if (truck.fuel <= 0) {
                        key.up = false;
                        gameOver = true;
                        drawGameOver();
                    }

                    // Calculate where the truck should go
                    truck.moveStats.speed = calcSpeed(truck.moveStats.speed, key.up, truck.moveStats.rightTurnTime, truck.moveStats.leftTurnTime);
                    truck.moveStats.direction = calcDirection(truck.moveStats.direction, truck.moveStats.speed, truck.moveStats.rightTurnTime, truck.moveStats.leftTurnTime);
                    calcMovement(truck.x, truck.y, truck.moveStats, key);
                    calcFuel(truck.fuel, key.up);

                    printf("Fuel: %d\n", truck.fuel);

                    drawGameScreen(truck, truck.fuel, 500);
                    redraw = false;
                }
            }
            redraw = true;
        }
    }

    return 0;
}
