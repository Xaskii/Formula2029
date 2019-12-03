#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>                       // For allegro, must be in compiler search path.
#include <allegro5/allegro_native_dialog.h> 		// for message box
#include "game.h"

static const int MAX = 20;
static const int ACCEL = 3;
static const int NATDECEL = 3;
static const int TURN = 0.25;

float calcSpeed(float prevSpeed, bool accelKey_down) {
    float speed = 0;

    // Calculate speed depending on if the acceleration key is pressed
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
    float slope = 0;
    float angle = 0;

    angle = atan(prevDir);

    if (leftTurn_down && rightTurn_down) {
        angle = angle;
    } else if (leftTurn_down) {
        angle += TURN;
    } else if (rightTurn_down) {
        angle -= TURN;
    }

    slope = tan(angle);
    return slope;
}

