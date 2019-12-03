// Constants
const int SCREEN_W = 1280;
const int SCREEN_H = 960;

// Structures
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
    int x;
    int y;
};

// Prototypes
int initializeAllegro();
int initBitmaps();
int displayPassScreen();
int displayFailScreen();
int displayEndScreen();
int calcFuel();
int drawFuelBar();
int calcMovement();
int calcSpeed();
int calcDirection();
int displayCrash();
