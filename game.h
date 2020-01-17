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

// Game logic structures
struct Level {
    float startX;
    float startY;
    float startAngle;
    float fuelUse;
    float finishX;
    float finishY;
};

struct Input {
    bool up;
    bool down;
    bool left;
    bool right;
    bool escape;
};

struct Movement {
    float groundValue;
    float speed;
    float steering;
    float direction;
};

struct Vehicle {
    Movement moveStats;
    float fuel;
    float x;
    float y;
};

struct backgroundGrid {
    float groundValue;
};

// Allegro prototypes
int initializeAllegro();
int loadBitmaps();
void initializeRG(unsigned char &red, unsigned char &green);
void loadFonts(ALLEGRO_FONT *&shaded100, ALLEGRO_FONT *&shaded50, ALLEGRO_FONT *&solid50);
void checkKeystrokes(Input &key);
void drawWelcomeScreen(int timesPlayed);
void drawGameScreen(Vehicle truck, Level info, int stage);
void drawFuelDisplay(float fuel);
void drawFuelNumber(float fuel);
int drawGameOver();
int drawGameWin();
void destroyDisplay();

// Event queue prototypes
int checkTimer();
int checkDisplayClose();
int startQueue();
int checkEmpty();
int checkSpaceDown();
int checkEscape();
void destroyEventQueue();
void initializeEventQueue();

//Movement logic prototypes
void calcMovement(float &posX, float &posY, Movement prev, Input key, float fuel);
float calcSpeed(float prevSpeed, bool accel, float steering);
float calcDirection(float prevDir, bool left, bool right, float &steering, float speed);
void calcFuel(float &fuel, bool accel, int fuelUse);

//Game play/menu functionality
bool checkFinish(int finishX, int finishY, int truckX, int truckY);
void printVariables(Vehicle truck, Input key);
int readFile (int n);
void printFile(int n, int input);
