#include <allegro5/allegro5.h>

/// Constants
static const int FPS = 120;
static const int SCREEN_W = 1280;
static const int SCREEN_H = 960;
static const int vehicleHeight = 173;
static const int vehicleWidth = 100;

/// Colors
#define BACKGROUND al_map_rgb(0xff, 0xff, 0xff)
#define WHITE      al_map_rgb(0xff, 0xff, 0xff)
#define PINK       al_map_rgb(255, 0, 255)

#define MAX 0.8
#define ACCEL 0.1
#define NATDECEL 0.005

#define MAXTURN 0.015
#define STEER 0.0001

#define FUELUSE 0.0003
#define IDLEFUELUSE 0.0003

#define MAPWIDTH 2000
#define MAPHEIGHT 2000

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

// Allegro prototypes
int initializeAllegro();
int loadBitmaps();
void initializeRG(unsigned char &red, unsigned char &green);
void loadFonts(ALLEGRO_FONT *&shaded100, ALLEGRO_FONT *&shaded50, ALLEGRO_FONT *&solid50);
void checkKeystrokes(Input &key);
int drawWelcomeScreen();
void drawGameScreen(Vehicle truck);
void drawFuelDisplay(float fuel);
void drawFuelNumber(float fuel);
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

/// Game prototypes
void calcMovement(float &posX, float &posY, Movement prev, Input key, float fuel, float groundVal, float arr[][MAPHEIGHT]);
float calcSpeed(float prevSpeed, bool accelKey_down, float steering);
float calcDirection(float prevDir, bool left, bool right, float &steering, float speed);
void calcTurnTime(Input &key, Vehicle &truck);
void calcFuel(float &fuel, bool up);
void printVariables(Vehicle truck, Input key);

void setMap1(float arr[][MAPHEIGHT]);
int smaller(int a, int b);
int larger(int a, int b);
void setRectangle(float arr[][MAPHEIGHT], int x, int y, int width, int height, float value);
void setSegment(float arr[][MAPHEIGHT], int x1, int y1, int x2, int y2, float width, float value);

