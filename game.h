#include <allegro5/allegro5.h>

// Constants
static const int FPS = 120;
static const int SCREEN_W = 1280;
static const int SCREEN_H = 960;
static const int vehicleHeight = 173;
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
    bool escape;
};

struct Movement {
    bool onTrack;
    float speed;
    float steering;
    float direction;
    float rightTurnTime;
    float leftTurnTime;
};

struct Vehicle {
    Movement moveStats;
    float fuel;
    float x;
    float y;
};

// Allegro prototypes
int initializeAllegro();
int loadBitmaps();
void checkKeystrokes(Input &key);
int drawWelcomeScreen();
void drawGameScreen(Vehicle truck, int fuelValue, int maxFuel);
int drawGameOver();
void destroyDisplay();

int checkTimer();
int checkDisplayClose();
int startQueue();
int checkEmpty();
int checkSpaceDown();
int checkEscape();
void destroyEventQueue();
void initializeEventQueue();


// Game prototypes
void calcMovement(float &posX, float &posY, Movement prev, Input key);
float calcSpeed(float prevSpeed, bool accelKey_down, int rFrame, int lFrame);
float calcDirection(float prevDir, bool left, bool right, float &steering);
void calcTurnTime(Input &key, Vehicle &truck);
void calcFuel(float &userFuel, bool up);
void printVariables(Vehicle truck, Input key);
