#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "game.h"

#define MAPWIDTH 2000
#define MAPHEIGHT 2000

void setMap1(float arr[][MAPHEIGHT]) {
    //staring area
    setRectangle(arr, 145, 208, 140, 120, -1);

    setSegment(arr, 235, 210, 290, 520, 116, -1);
    setSegment(arr, 290, 520, 220, 657, 116, -1);
    setSegment(arr, 220, 657, 252, 875, 116, -1);
    setSegment(arr, 252, 875, 390, 1028, 116, -1);
    setSegment(arr, 390, 1028, 634, 1085, 116, -1);
    setRectangle(arr, 598, 1048, 431, 69, -1);
    setSegment(arr, 1016, 1072, 1193, 825, 75, -1);
    setSegment(arr, 1193, 825, 1532, 812, 75, -1);
    setSegment(arr, 1534, 798, 1591, 1058, 75, -1);
    setSegment(arr, 1591, 1058, 1543, 1282, 75, -1);
    setSegment(arr, 1543, 1282, 1655, 1518, 75, -1);
}
int smaller(int a, int b) {
    int value = 0;

    if (a < b) {
        value = a;
    } else if (b < a) {
        value = b;
    }
    return value;
}

int larger(int a, int b) {
    int value = 0;

    if (a > b) {
        value = a;
    } else if (b > a) {
        value = b;
    }
    return value;
}

void setRectangle(float arr[][MAPHEIGHT], int x, int y, int width, int height, float value) {
    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            arr[i][j] = value;
        }
    }
}

void setSegment(float arr[][MAPHEIGHT], int x1, int y1, int x2, int y2, float width, float value) {
    ///original line
    float m0 = 0; ///slope
    float b0 = 0; ///y-intercept

    ///for line perpendicular to original line
    float m1 = 0;
    float b1 = 0;
    float distance = 0;

    ///corners of the rectangle of points we're checking
    float topLeftX = 0;
    float topLeftY = 0;

    float botRightX = 0;
    float botRightY = 0;

    ///set the box within we check for the points within the designated segment
    topLeftX = smaller(x1, x2);
    topLeftY = smaller(y1, y2);

    botRightX = larger(x1, x2);
    botRightY = larger(y1, y2);


    m0 = (float) (y2 - y2) / (x2 - x1);
    b0 = (float) y1 - m0 * x1;

    for (int i = topLeftX - width / 2; i < botRightX + width / 2; i++) {
        for (int j = topLeftY - width / 2; j < botRightY + width / 2; j++) {
            ///point on the original line to check the distance of the perpendicular
            float checkX = 0;
            float checkY = 0;

            ///find equation of the second line
            m1 = (-1) / m0;
            b1 = j - m1 * i;
            checkX = (b0 - b1) / (m1 - m0);
            checkY = checkX * m0 + b0;

            distance = sqrt(pow((i - checkX), 2) + pow((j - checkY), 2));

            if (distance < width / 2) {
                arr[i][j] = value;
            }
        }
    }

}
