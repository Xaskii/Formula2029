#include <stdio.h>
#include <string.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>                       // For allegro, must be in compiler search path.
#include <allegro5/allegro_native_dialog.h>
#include "game.h"// for message box


#define MAX 5
#define ACCEL 1
#define NATDECEL 3
#define TURN 0.03
#define FUELUSE 1

void calcMovement(float &posX, float &posY, Movement prev, Input key) {
    float distance = 0;
    float angle = 0;

    distance = calcSpeed(prev.speed, key.up);
    angle = calcDirection(prev.direction, key.left, key.right);

    posX -= distance * cos(angle);
    posY += distance * sin(angle);
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

float calcDirection(float prevDir, bool leftTurn_down, bool rightTurn_down) {
    float angle = 0;
    angle = prevDir;

    if (leftTurn_down) {
        angle += TURN;
    } else if (rightTurn_down) {
        angle -= TURN;
    }

    return angle;
}



void calcFuel(int &userFuel, Input key){
    if (key.up){
        userFuel -= FUELUSE;
    }
}

/*struct Input {
    bool up;
    bool down;
    bool left;
    bool right;
};

struct Movement {
    bool onTrack;
    float speed;
    float direction;
};

struct Vehicle {
    ALLEGRO_BITMAP *bitmap;
    Movement moveStats;
    int fuel;
    int x;
    int y;
};*/






