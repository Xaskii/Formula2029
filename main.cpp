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
    Vehicle vehicle;

    initializeAllegro();

    ALLEGRO_DISPLAY *display = nullptr;

    display = al_create_display(SCREEN_W, SCREEN_H);


    al_rest(2);
    return 0;
}
