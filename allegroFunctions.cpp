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

    font = al_load_ttf_font("SF_Cartoonist_Hand.ttf", 36, 0);
    display = al_create_display(SCREEN_W, SCREEN_H);
    al_set_window_title(display, "Monarchs");
    al_clear_to_color(BACKGROUND);

    return 0;
}

int initBitmaps(Vehicle character, Image image[], const char filename[][20], const int n) {

    for (int i = 0; i < n; i++){
        image[i].bitmap = al_load_bitmap(filename[i]);
        if (image[i].bitmap == nullptr) {
            al_show_native_message_box(display, "Error", filename[i], "Could not load",
                                     nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            return false;
        }
        al_convert_mask_to_alpha(image[i].bitmap, WHITE);
    }
	return 0;
}



