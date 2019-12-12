#include <allegro5/allegro5.h>

// Constants
static const int SCREEN_W = 1280;
static const int SCREEN_H = 960;

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_FONT *font;
extern ALLEGRO_EVENT_QUEUE *event_queue;

// Colors
#define BACKGROUND al_map_rgb(0xff, 0xff, 0xff)
#define WHITE      al_map_rgb(0xff, 0xff, 0xff)
#define PINK       al_map_rgb(255, 0, 255)

// Structures
struct Image {
    ALLEGRO_BITMAP *bitmap;               // picture
    int x, y;
};

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
    ALLEGRO_BITMAP *bitmap;
    Movement moveStats;
    int fuel;
    float x;
    float y;
};

// Prototypes
int initializeAllegro();
int checkSetup();
int initBitmap(ALLEGRO_BITMAP *image, const char *filename);
int displayPassScreen();
int displayFailScreen();
int displayEndScreen();
int displayCrash();

int checkKeyboard(Input &key);
void calcFuel(int &userFuel, Input key);
void calcMovement(float &posX, float &posY, Movement prev, Input key);
float calcSpeed(float prevSpeed, bool accelKey_down);
float calcDirection(float prevDir, bool leftTurn_down, bool rightTurn_down);
