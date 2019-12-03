#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>                       // For allegro, must be in compiler search path.
#include <allegro5/allegro_native_dialog.h> 		// for message box
#include "game.h"


int initializeAllegro(){
    al_init();

    al_init_font_addon();
    al_init_native_dialog_addon();
    return 0;
}

