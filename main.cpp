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

// Global Variables
AppStatus gAppStatus = RUNNING;
float gPulseTime = 0.0f;
float gPreviousTicks = 0.0f;
Color gBgColour = {9, 2, 31, 255};
float gBgTime   = 0.0f;

// Orbit ring variables
constexpr char DOT_FP[] = "assets/dot.png";
Texture2D gDotTexture;

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
void drawDot(float x, float y);

// Function Definitions
void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Solar System");

    gDotTexture = LoadTexture(DOT_FP);
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

    // Extra credit
    gBgTime += 2.0f * deltaTime;
    float fade = (sin(gBgTime) + 1.0f) / 2.0f;

    gBgColour.r = static_cast<unsigned char>( 9 + fade * (45 -  9));
    gBgColour.g = static_cast<unsigned char>( 2 + fade * (10 -  2));
    gBgColour.b = static_cast<unsigned char>(31 + fade * (70 - 31));

    // Sun Movement
    float size   = SUN_SIZE + 10.0f * cos(gPulseTime);
    float aspect = static_cast<float>(gSunTexture.height) / gSunTexture.width;
    gSunScale = {size, size * aspect};
    gSunOrbitAngle += 30.0f * deltaTime;
    float radius = 60.0f + 15.0f * sin(5 * gSunOrbitAngle * 3.14f / 180);
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

void drawDot(float x, float y)
{
    Rectangle source = {0.0f, 0.0f,
                        static_cast<float>(gDotTexture.width),
                        static_cast<float>(gDotTexture.height)};
    Rectangle dest   = {x, y, 3.0f, 3.0f};
    Vector2   origin = {1.5f, 1.5f};

    Color faintWhite = {255, 255, 255, 90};
    DrawTexturePro(gDotTexture, source, dest, origin, 0.0f, faintWhite);
}


void render()
{
    BeginDrawing();

    ClearBackground(gBgColour);

    // Orbit rings
    for (int i = 0; i < 360; i += 2)
    {
        float a = i * 3.14f / 180;

        // Dots around the Sun's sinusoidal path
        float r = 60.0f + 15.0f * sin(5 * a);
        drawDot(ORIGIN.x + r * cos(a), ORIGIN.y + r * sin(a));

        // Dots around the Earth's elliptical orbit around the Sun
        drawDot(gSunPosition.x + 200.0f * cos(a), gSunPosition.y + 100.0f * sin(a));

        // Dots around the moon's orbit around the Earth
        drawDot(gEarthPosition.x + 45.0f * cos(a), gEarthPosition.y + 45.0f * sin(a));
    }

    // Render Sun
    Rectangle sunTextureArea = {
        // top left corner
        0.0f, 0.0f,

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
    UnloadTexture(gDotTexture);

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
