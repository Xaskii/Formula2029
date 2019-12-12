#include <allegro5/allegro5.h>

// Constants
static const int SCREEN_W = 1280;
static const int SCREEN_H = 960;
static const int vehicleHeight = 100;
static const int vehicleWidth = 100;

// Colors
#define BACKGROUND al_map_rgb(0xff, 0xff, 0xff)
#define WHITE      al_map_rgb(0xff, 0xff, 0xff)
#define PINK       al_map_rgb(255, 0, 255)

struct Input {
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
    Movement moveStats;
    int fuel;
    float x;
    float y;
};

// Prototypes
void initializeAllegro();
void loadBitmaps();
