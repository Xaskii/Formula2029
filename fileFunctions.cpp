#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>                       // For allegro, must be in compiler search path.
#include <allegro5/allegro_native_dialog.h>
#include "game.h"// for message box


#define MAX 1
#define ACCEL 0.1
#define NATDECEL 3
#define FUELUSE 1

void calcMovement(float &posX, float &posY, Movement prev, Input key) {
    float distance = 0;
    float angle = 0;

    distance = calcSpeed(prev.speed, key.up);
    angle = calcDirection(prev.direction, prev.speed, prev.rightTurnTime, prev.rightTurnTime);

    posX += distance * cos(angle);
    posY -= distance * sin(angle);
}

//Use in a while loop
float calcSpeed(float prevSpeed, bool accelKey_down) {
    // Declaring variable
    float speed = 0;

    //Calculate return value
    if (accelKey_down) {
        if (prevSpeed < (MAX - ACCEL)) {
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

float calcDirection(float prevDir, float prevSpeed, int rFrame, int lFrame) {
    float angle = 0;
    float rTurn = 0;
    float lTurn = 0;

    rTurn = rFrame * prevSpeed * 0.0075;
    lTurn = lFrame * prevSpeed * 0.0075;

    angle = prevDir;
    angle += lTurn;
    angle -= rTurn;

    return angle;
}

void calcTurnTime(Input &key, Vehicle &truck){
    if (!key.left && !key.right) {
            truck.moveStats.rightTurnTime = 0;
            truck.moveStats.leftTurnTime = 0;
        } else if (key.left && key.right) {
            truck.moveStats.leftTurnTime++;
            truck.moveStats.rightTurnTime++;
        } else if (key.left && !key.right) {
            truck.moveStats.leftTurnTime++;
            truck.moveStats.rightTurnTime = 0;
        } else if (!key.left && key.right) {
            truck.moveStats.leftTurnTime = 0;
            truck.moveStats.rightTurnTime++;
    }
}


void calcFuel(int &userFuel, bool up){
    if (up){
        userFuel -= FUELUSE;
    }
}

void printVariables(Vehicle truck, Input key){
    system("CLS");
    printf("Keystates: \n");
    if (key.left){
        printf("L ");
    } else {
        printf("  ");
    }
    if (key.right){
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
    printf("L: %f R: %f\n", truck.moveStats.leftTurnTime, truck.moveStats.rightTurnTime);

}




