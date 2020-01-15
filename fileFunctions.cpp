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
#define FUELUSE 0.0005
#define IDLEFUELUSE 0.0001

void calcMovement(float &posX, float &posY, Movement prev, Input key) {
    float distance = 0;
    float angle = 0;

    distance = calcSpeed(prev.speed, key.up, prev.steering);
    angle = calcDirection(prev.direction, key.left, key.right, prev.steering, prev.speed);

    distance *= 1 - (fabs(prev.steering) * 50);

    posX += distance * cos(angle);
    posY -= distance * sin(angle);
}

//Use in a while loop
float calcSpeed(float prevSpeed, bool accel, float steering) {
    // Declaring variable
    float speed = 0;
    //Calculate return value

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

float calcDirection(float prevDir, bool left, bool right, float &steering, float speed) {
    float angle = 0;
    float target = 0;

    angle = prevDir;
    //determine target angle of steering wheel
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
    //increment steering value towards target
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

void calcFuel(float &fuel, bool up) {
    fuel -= IDLEFUELUSE;
    if (up) {
        fuel -= FUELUSE;
    }
}

void printVariables(Vehicle truck, Input key) {
    system("CLS");
    printf("Keystates: \n");
    if (key.left) {
        printf("L ");
    } else {
        printf("  ");
    }
    if (key.right) {
        printf("R ");
    } else {
        printf("  ");
    }
    if (key.up) {
        printf("U ");
    } else {
        printf(" ");
    }
    if (key.down) {
        printf("D ");
    } else {
        printf("  ");
    }
    printf("\n");

    printf("Truck Coords: %f, %f\n", truck.x, truck.y);
    printf("Direction: %f\n", truck.moveStats.direction);
    printf("Speed: %f\n", truck.moveStats.speed);

}



