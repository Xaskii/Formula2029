/**FORMULA 2029, a driving game by Xavi Simpson and David Xu**/

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

ALLEGRO_FONT *shaded100;
ALLEGRO_FONT *shaded50;
ALLEGRO_FONT *solid50;
ALLEGRO_FONT *solid25;

unsigned char red;
unsigned char green;

int main() {
    Level levelInfo[2];
    Vehicle truck;
    Input key;
    bool gameRun = false;
    bool gameWon = false;
    bool gameOver = false;
    bool crash = false;
    bool redraw = true;
    bool exitProgram = false;

    int timesPlayed = 0;
    int currentLevel = 0;
    int emptyTime = 0;

    const int numLevels = 2;

    levelInfo[0].startX = 224;
    levelInfo[0].startY = 273;
    levelInfo[0].finishX = 1713;
    levelInfo[0].finishY = 1506;
    levelInfo[0].fuelUse = 0.0006;
    levelInfo[0].startAngle = 275.0 / 180.0 * M_PI;

    levelInfo[1].startX = 927;
    levelInfo[1].startY = 173;
    levelInfo[1].finishX = 1713;
    levelInfo[1].finishY = 1506;
    levelInfo[1].fuelUse = 0.0003;
    levelInfo[1].startAngle = 290.0 / 180.0 * M_PI;

    initializeAllegro();
    loadFonts(shaded100, shaded50, solid50);
    initializeRG(red, green);
    loadBitmaps();
    initializeEventQueue();

    timesPlayed = readFile(1);

    while (!exitProgram) {

        gameRun = true;
        key.escape = false;

        startQueue();

        if (redraw) {
            drawWelcomeScreen(timesPlayed);
            redraw = false;
        }

        if (!checkDisplayClose() || !checkEscape()) {
            break;
        } else if (!checkEscape()) {
            break;
        } else if(!checkSpaceDown()) {
            // Adds one to the number of times played
            timesPlayed++;
            printFile(1, timesPlayed);
            // Runs the game as long as there are levels to be completed
            while (gameRun) {
                //set variables to desired values
                gameOver = false;
                gameWon = false;

                truck.fuel = 1;
                truck.x = levelInfo[currentLevel].startX;
                truck.y = levelInfo[currentLevel].startY;
                truck.moveStats.direction = levelInfo[currentLevel].startAngle;
                truck.moveStats.groundValue = 0;
                truck.moveStats.speed = 0;
                truck.moveStats.steering = 0;

                while (!gameOver && !gameWon) {
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

                        if (truck.fuel == 0) {
                            key.up = false;
                            truck.moveStats.steering = 0;
                            emptyTime++;
                        }

                        // Calculate where the truck should go
                        truck.moveStats.direction = calcDirection(truck.moveStats.direction, key.left, key.right, truck.moveStats.steering, truck.moveStats.speed);
                        truck.moveStats.speed = calcSpeed(truck.moveStats.speed, key.up, truck.moveStats.steering);
                        calcMovement(truck.x, truck.y, truck.moveStats, key, truck.fuel);
                        calcFuel(truck.fuel, key.up, levelInfo[currentLevel].fuelUse);

                        drawGameScreen(truck, levelInfo[currentLevel], currentLevel);

                        // Determines if the use
                        if (emptyTime >= 240 || key.escape || crash) {
                            gameOver = true;
                        }

                        //check for win condition
                        if (checkFinish(levelInfo[currentLevel].finishX, levelInfo[currentLevel].finishY, truck.x, truck.y)) {
                            gameWon = true;
                        }

                        // Tells the user if they lost and lets them retry the level
                        if (gameOver) {
                            drawGameOver();
                            gameRun = false;
                            al_rest(2);
                        }

                        // Tells the user if they won the level and lets them go to the next level
                        if (gameWon) {
                            drawGameWin();
                            currentLevel++;
                            al_rest(2);
                        }

                        redraw = false;
                    }
                }

                if (currentLevel > numLevels){
                    gameRun = false;
                }

            }
            redraw = true;
        }
    }

    return 0;
}
