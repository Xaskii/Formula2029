#include <stdio.h>
#include <string.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>                       // For allegro, must be in compiler search path.
#include <allegro5/allegro_native_dialog.h> 		// for message box
#include "monarchs.h"

// Movement constants
#define MAX 20
#define ACCEL 3
#define NATDECEL 3
#define TURN 0.25

//Use in a while loop
float calcSpeed(float prevSpeed, bool accelKey_down) {
    // Declaring variable
    float speed = 0;

    //Calculate return value
    if (accelKey_down) {
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

void calcMovement(float &posX, float &posY, Vehicle prev, Input key) {
    float distance = 0;
    float angle = 0;

    distance = calcSpeed(prev.moveStats.speed, key.up);
    angle = calcDirection(prev.moveStats.direction, key.left, key.right);

    posX += distance * cos(angle);
    posY += distance * sin(angle);
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






