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
constexpr Vector2 BASE_SIZE = {100.0F, 100.0F};


constexpr char BG_COLOUR[] = "#09021F";
constexpr char SUN_FP[] = "assets/sun.png";

float gSunOrbitAngle = 0.0f;
float gSunRotate       = 0.0f;


// Global Variables
AppStatus gAppStatus = RUNNING;
Texture2D gSunTexture;
Vector2 gSunPosition = ORIGIN;
Vector2 gSunScale = BASE_SIZE;
float gPulseTime = 0.0f;
float gPreviousTicks = 0.0f;

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


    float size   = BASE_SIZE.x + 5.0f * cos(gPulseTime);
    float aspect = static_cast<float>(gSunTexture.height) / gSunTexture.width;

    gSunScale = {size, size * aspect};

    gSunOrbitAngle += 30.0f * deltaTime;
    float radius = 60.0f + 15.0f * sin(5 * gSunOrbitAngle * 3.14f / 180);

    gSunPosition.x = ORIGIN.x + radius * cos(gSunOrbitAngle * 3.14f / 180);
    gSunPosition.y = ORIGIN.y + radius * sin(gSunOrbitAngle * 3.14f / 180);

    gSunRotate += 15.0f * deltaTime;
}

void render()
{
    BeginDrawing();

    ClearBackground(ColorFromHex(BG_COLOUR));

    // Whole texture (UV coordinates)
    Rectangle textureArea = {
        // top left corner
        0.0f, 0.0f,

        // how large of a rectangle, starting from (0,0), do we want to "slice"?
        static_cast<float>(gSunTexture.width),
        static_cast<float>(gSunTexture.height)
    };

    Rectangle destinationArea = {
        // where we want our rectangle to start being drawn
        gSunPosition.x, gSunPosition.y,

        gSunScale.x, gSunScale.y
    };

    Vector2 originOffset = {gSunScale.x / 2, gSunScale.y / 2};

    DrawTexturePro(gSunTexture, textureArea, destinationArea, originOffset, gSunRotate, WHITE);

    EndDrawing();
}

void shutdown()
{
    UnloadTexture(gSunTexture);

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
