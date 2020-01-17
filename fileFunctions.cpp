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
#define ACCEL 0.005
#define NATDECEL 0.005
#define MAXTURN 0.01
#define STEER 0.0002
#define IDLEFUELUSE 0.0002

// Calculates the truck's position based on the previous speed
// previous direction, and user inputs.
// Takes the coordinates, key inputs, and fuel value.
void calcMovement(float &posX, float &posY, Movement prev, Input key, float fuel) {
    //declaring distance and angle
    float distance = 0;
    float angle = 0;

    //call direction and speed functions to calculate the distance vector per frame
    distance = calcSpeed(prev.speed, key.up, prev.steering);
    angle = calcDirection(prev.direction, key.left, key.right, prev.steering, prev.speed);

    //the vehicle slows down in proportion to how sharply it's turning
    distance *= 1 - (fabs(prev.steering) * 50);

    //use trig to convert vector information into distance in each coordinate
    posX += distance * cos(angle);
    posY -= distance * sin(angle);
}

// Note: Use in a while loop
// Calculates the speed of the car based on the previous speed, a steering
// value and whether the car is moving.
float calcSpeed(float prevSpeed, bool accel, float steering) {
    // Declaring speed
    float speed = 0; //return value

    //if the accelerate button is pressed, accelerate up to max speed
    if (accel) {
        if (prevSpeed < MAX - ACCEL) {
            speed = prevSpeed + ACCEL;
        } else {
            speed = MAX;
        }
    //otherwise, decelerate down to 0
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
//The steering value is the change in direction as radians
float calcDirection(float prevDir, bool left, bool right, float &steering, float speed) {
    //declaring variables
    float angle = 0; //return value
    float target = 0; //the value that we are incrementing or decrementing the steering value towards

    angle = prevDir;

    // Determines target angle of steering wheel

    if (!left && !right) {
        target = 0;
    //if both turns are pressed, they cancel out
    } else if (left && right) {
        target = 0;
    } else if (left && !right) {
        target = MAXTURN;
    } else if (!left && right) {
        target = -MAXTURN;
    }

    //if the car is stationary, set the target angle to 0 --> no turning in place
    if (speed == 0) {
        target = 0;
    }

    //increment/decrement steering value towards target, determined by constant STEER value
    if (target != steering) {
        //add by STEER up to target
        if (steering < target) {
            if (steering < target - STEER) {
                steering += STEER;
            } else {
                steering = target;
            }
        //subtract by STEER down to target
        } else if (steering > target) {
            if (steering > target + STEER) {
                steering -= STEER;
            } else {
                steering = target;
            }
        }
    }

    //change the angle by steering value
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
void calcFuel(float &fuel, bool accel, int fuelUse) {
    //fuel will constantly be used every frame, regardless of user activity
    fuel -= IDLEFUELUSE;

    //if the gas is pressed down, fuel use will increase
    if (accel) {
        fuel -= fuelUse;
    }

    //prevent momentary calculations of -0 fuel
    if (fuel <= 0) {
        fuel = 0;
    }
}

int readFile (int n) {
    //declare variables
    int output = 0; //return value
    FILE *inputFile;

    //set mode to read
    inputFile = fopen("played.txt", "r");

    for (int i = 0; i < n; i++) {
        // Reads in from the file
        fscanf(inputFile, "%d", &output);
    }

    //close file
    fclose(inputFile);

    return output;
}

void printFile(int n, int input) {
    //declare variables
    FILE *outputFile;

    //set mode to write
    outputFile = fopen("played.txt", "w");

    for (int i = 0; i < n; i++) {
        // Prints to the file
        fprintf(outputFile, "%d", input);
    }

    //close file
    fclose(outputFile);
}


