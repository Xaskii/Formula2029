/*****************************************************************************
 *	Name:       Xavi Simpson & David Xu
 *	Date:       2019-02-11
 *
 *	Purpose:
 *
 *	Usage:
 *	Revision History:
 *
 *	Known Issues:
 *
 *****************************************************************************/


#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>

#include "game.h"

int main(){
    const char filename[2][20] = {"Truck.bmp", "Fuelbar.bmp"};
    const int numBitmaps = 1;
    bool exit = false;

    Image images[numBitmaps];
    Vehicle truck;


    initializeAllegro();
    initBitmaps(truck, images, filename, numBitmaps);

    al_rest(2);
    return 0;
}
