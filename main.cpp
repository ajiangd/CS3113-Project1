/**
* Author: Ashley Jiang
* Assignment: Simple 2D Scene
* Date due: 10/05/2026
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "CS3113/cs3113.h"
#include <math.h>

// Global Constants
constexpr int SCREEN_WIDTH  = 900,
              SCREEN_HEIGHT = 600,
              FPS           = 60;

constexpr Vector2 ORIGIN = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
constexpr char BG_COLOUR[] = "#09021F";

// Global Variables
AppStatus gAppStatus = RUNNING;
float gPulseTime = 0.0f;
float gPreviousTicks = 0.0f;

// Sun variables
constexpr char SUN_FP[] = "assets/sun.png";
constexpr float SUN_SIZE = 100.0f;

Texture2D gSunTexture;
Vector2 gSunPosition = ORIGIN;
Vector2 gSunScale = {SUN_SIZE, SUN_SIZE};
float gSunOrbitAngle = 0.0f;
float gSunRotate       = 0.0f;

// Earth Variables
constexpr char EARTH_FP[] = "assets/earth.png";
constexpr float EARTH_SIZE = 50.0f;

Texture2D gEarthTexture;
Vector2   gEarthPosition = ORIGIN;
Vector2   gEarthScale    = {EARTH_SIZE, EARTH_SIZE};
float     gEarthOrbitAngle = 0.0f;
float     gEarthRotate     = 0.0f;

// Moon Variables
constexpr char MOON_FP[] = "assets/moon.png";
constexpr float MOON_SIZE = 25.0f;

Texture2D gMoonTexture;
Vector2   gMoonPosition = ORIGIN;
Vector2   gMoonScale    = {MOON_SIZE, MOON_SIZE};
float     gMoonOrbitAngle = 0.0f;
float     gMoonRotate     = 0.0f;


// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Solar System");

    gSunTexture = LoadTexture(SUN_FP);
    gEarthTexture = LoadTexture(EARTH_FP);
    gMoonTexture = LoadTexture(MOON_FP);

    SetTargetFPS(FPS);
}

void processInput()
{
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() {
    float ticks = GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;
    
    gPulseTime += 3.0f * deltaTime;

    // Sun Movement
    float size   = SUN_SIZE + 5.0f * cos(gPulseTime);
    float aspect = static_cast<float>(gSunTexture.height) / gSunTexture.width;
    float radius = 60.0f + 15.0f * sin(5 * gSunOrbitAngle * 3.14f / 180);

    gSunScale = {size, size * aspect};
    gSunOrbitAngle += 30.0f * deltaTime;
    gSunPosition.x = ORIGIN.x + radius * cos(gSunOrbitAngle * 3.14f / 180);
    gSunPosition.y = ORIGIN.y + radius * sin(gSunOrbitAngle * 3.14f / 180);
    gSunRotate += 15.0f * deltaTime;

    // Earth Movement
    gEarthOrbitAngle += 40.0f * deltaTime;
    gEarthPosition.x = gSunPosition.x + 200.0f * cos(gEarthOrbitAngle * 3.14f / 180);
    gEarthPosition.y = gSunPosition.y + 100.0f * sin(gEarthOrbitAngle * 3.14f / 180);
    float earthAspect = static_cast<float>(gEarthTexture.height) / gEarthTexture.width;
    gEarthScale = {EARTH_SIZE, EARTH_SIZE * earthAspect};
    gEarthRotate += 60.0f * deltaTime;

    // Moon Movement
    gMoonOrbitAngle += 120.0f * deltaTime;
    gMoonPosition.x = gEarthPosition.x + 45.0f * cos(gMoonOrbitAngle * 3.14f / 180);
    gMoonPosition.y = gEarthPosition.y + 45.0f * sin(gMoonOrbitAngle * 3.14f / 180);
    float moonAspect = static_cast<float>(gMoonTexture.height) / gMoonTexture.width;
    gMoonScale = {MOON_SIZE, MOON_SIZE * moonAspect};
    gMoonRotate += -30.0f * deltaTime;
}

void render()
{
    BeginDrawing();

    ClearBackground(ColorFromHex(BG_COLOUR));

    // Render Sun

    // Whole texture (UV coordinates)
    Rectangle sunTextureArea = {
        // top left corner
        0.0f, 0.0f,

        // how large of a rectangle, starting from (0,0), do we want to "slice"?
        static_cast<float>(gSunTexture.width),
        static_cast<float>(gSunTexture.height)
    };

    Rectangle sunDestinationArea = {
        gSunPosition.x, gSunPosition.y,
        gSunScale.x, gSunScale.y
    };

    Vector2 sunOriginOffset = {gSunScale.x / 2, gSunScale.y / 2};

    DrawTexturePro(gSunTexture, sunTextureArea, sunDestinationArea, sunOriginOffset, gSunRotate, WHITE);


    // Render Earth

    Rectangle earthTextureArea = {
        // top left corner
        0.0f, 0.0f,

        // how large of a rectangle, starting from (0,0), do we want to "slice"?
        static_cast<float>(gEarthTexture.width),
        static_cast<float>(gEarthTexture.height)
    };
    

    Rectangle earthDestinationArea = {
        gEarthPosition.x, gEarthPosition.y,
        gEarthScale.x, gEarthScale.y
    };

    Vector2 earthOriginOffset = {gEarthScale.x / 2, gEarthScale.y / 2};

    DrawTexturePro(gEarthTexture, earthTextureArea, earthDestinationArea, earthOriginOffset, gEarthRotate, WHITE);


    // Render Moon
    Rectangle moonTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gMoonTexture.width),
        static_cast<float>(gMoonTexture.height)
    };

    Rectangle moonDestinationArea = {
        gMoonPosition.x, gMoonPosition.y,
        gMoonScale.x, gMoonScale.y
    };

    Vector2 moonOriginOffset = {gMoonScale.x / 2, gMoonScale.y / 2};

    DrawTexturePro(gMoonTexture, moonTextureArea, moonDestinationArea, moonOriginOffset, gMoonRotate, WHITE);

    EndDrawing();
}

void shutdown()
{
    UnloadTexture(gSunTexture);
    UnloadTexture(gEarthTexture);
    UnloadTexture(gMoonTexture);

    CloseWindow();
}

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}
