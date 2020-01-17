#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "game.h"

#define MAX 0.8
#define MAXTURN 0.015
#define STEER 0.0001
#define ACCEL 0.1
#define NATDECEL 0.005
#define IDLEFUELUSE 0.0001

// Calculates the truck's position based on the previous speed
// previous direction, and user inputs.
// Takes the coordinates, key inputs, and fuel value.
void calcMovement(float &posX, float &posY, Movement prev, Input key, float fuel) {
    float distance = 0;
    float angle = 0;

    distance = calcSpeed(prev.speed, key.up, prev.steering);
    angle = calcDirection(prev.direction, key.left, key.right, prev.steering, prev.speed);

    distance *= 1 - (fabs(prev.steering) * 50);

    posX += distance * cos(angle);
    posY -= distance * sin(angle);
}

// Note: Use in a while loop
// Calculates the speed of the car based on the previous speed, a steering
// value and whether the car is moving.
float calcSpeed(float prevSpeed, bool accel, float steering) {
    /// Declaring variable
    float speed = 0;
    ///Calculate return value

    if (accel) {
        if (prevSpeed < MAX - ACCEL) {
            speed = prevSpeed + ACCEL;
        } else {
            speed = MAX;
        }
    } else {
        if (prevSpeed > 0 + NATDECEL) {
            speed = prevSpeed - NATDECEL;
        } else {
            speed = 0;
        }
    }
    return speed;
}

// Calculates the direction that the car should go towards based on the
// previous direction, turning keys being pressed, velocity, and the steering value.
float calcDirection(float prevDir, bool left, bool right, float &steering, float speed) {
    float angle = 0;
    float target = 0;

    angle = prevDir;

    // Determines target angle of steering wheel
    if (!left && !right) {
        target = 0;
    } else if (left && right) {
        target = 0;
    } else if (left && !right) {
        target = MAXTURN;
    } else if (!left && right) {
        target = -MAXTURN;
    }

    if (speed == 0) {
        target = 0;
    }
    // Increments steering value towards target
    if (target != steering) {
        if (steering < target) {
            if (steering < target - STEER) {
                steering += STEER;
            } else {
                steering = target;
            }
        } else if (steering > target) {
            if (steering > target + STEER) {
                steering -= STEER;
            } else {
                steering = target;
            }
        }
    }

    angle += steering;
    return angle;
}

// Checks if the vehicle coordinates have reached the goal.
bool checkFinish(int finishX, int finishY, int truckX, int truckY){
    // Since the goal isn't one pixel, it tests if the X is within 8 pixels and the Y within 12 pixels.
    if ((finishX - 8 < truckX) && (finishX + 8 > truckX) && (finishY - 12 < truckY) && (finishY + 12 > truckY)) {
        return true;
    } else {
        return false;
    }
}

// Changes the amount of fuel remaining based on the current fuel, accel key,
// and the amount of fuel that is supposed to be drained per frame.
void calcFuel(float &fuel, bool up, int fuelUse) {
    fuel -= IDLEFUELUSE;
    if (up) {
        fuel -= fuelUse;
    }

    if (fuel <= 0) {
        fuel = 0;
    }
}

int readFile (int n) {
    printf("test");
    int output = 0;
    FILE *inputFile;
    inputFile = fopen("played.txt", "r");

    for (int i = 0; i < n; i++) {
        // Reads in from the file
        fscanf(inputFile, "%d", &output);
    }
    printf("test");
    fclose(inputFile);

    return output;
}

void printFile(int n, int input) {
    FILE *outputFile;
    outputFile = fopen("played.txt", "w");

    for (int i = 0; i < n; i++) {
        // Prints to the file
        fprintf(outputFile, "%d", input);
    }

    fclose(outputFile);
}


