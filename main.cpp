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
    bool crash = false;
    bool redraw = true;
    bool exitProgram = false;

    key.escape = false;
    truck.x = 0;
    truck.y = 0;
    truck.fuel = 1;

    truck.moveStats.steering = 0;
    truck.moveStats.direction = M_PI / 2;
    truck.moveStats.onTrack = true;
    truck.moveStats.speed = 0;

    initializeAllegro();
    loadBitmaps();
    initializeEventQueue();

    while (!exitProgram) {
        gameOver = false;
        key.escape = false;
        truck.fuel = 1;
        truck.x = 0;
        truck.y = 0;
        truck.moveStats.direction = M_PI / 2;
        truck.moveStats.onTrack = true;
        truck.moveStats.speed = 0;

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
            while (!gameOver) {
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

                    // Decide where the truck isi

                    // Calculate where the truck should go
                    truck.moveStats.direction = calcDirection(truck.moveStats.direction, key.left, key.right, truck.moveStats.steering);
                    truck.moveStats.speed = calcSpeed(truck.moveStats.speed, key.up, truck.moveStats.steering);
                    calcMovement(truck.x, truck.y, truck.moveStats, key);
                    calcFuel(truck.fuel, key.up);

                    printf("Fuel: %.2f\n", truck.fuel);

                    drawGameScreen(truck, truck.fuel, 1);

                    if (truck.fuel <= 0 || key.escape ||crash) {
                        key.up = false;
                        gameOver = true;
                    }
                    if (gameOver) {
                        al_rest(0.5);
                        drawGameOver();
                        al_rest(0.5);
                    }

                    redraw = false;
                }
            }
            redraw = true;
        }
    }

    return 0;
}
