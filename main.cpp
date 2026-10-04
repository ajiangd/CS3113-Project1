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
<<<<<<< HEAD
constexpr Vector2 BASE_SIZE = {100.0F, 100.0F};


constexpr char BG_COLOUR[] = "#09021F";
constexpr char SUN_FP[] = "assets/sun.png";

=======
constexpr char BG_COLOUR[] = "#09021F";

// Sun variables
constexpr char SUN_FP[] = "assets/sun.png";
constexpr float SUN_SIZE = 100.0f;

Texture2D gSunTexture;
Vector2 gSunPosition = ORIGIN;
Vector2 gSunScale = {SUN_SIZE, SUN_SIZE};
>>>>>>> c01a43b (added earth movement)
float gSunOrbitAngle = 0.0f;
float gSunRotate       = 0.0f;


<<<<<<< HEAD
// Global Variables
AppStatus gAppStatus = RUNNING;
Texture2D gSunTexture;
Vector2 gSunPosition = ORIGIN;
Vector2 gSunScale = BASE_SIZE;
=======
// Earth Variables
constexpr char EARTH_FP[] = "assets/earth.png";
constexpr float EARTH_SIZE = 50.0f;

Texture2D gEarthTexture;
Vector2   gEarthPosition = ORIGIN;
Vector2   gEarthScale    = {EARTH_SIZE, EARTH_SIZE};
float     gEarthOrbitAngle = 0.0f;
float     gEarthRotate     = 0.0f;


// Global Variables
AppStatus gAppStatus = RUNNING;
>>>>>>> c01a43b (added earth movement)
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
<<<<<<< HEAD
=======
    gEarthTexture = LoadTexture(EARTH_FP);
>>>>>>> c01a43b (added earth movement)

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

<<<<<<< HEAD

    float size   = BASE_SIZE.x + 5.0f * cos(gPulseTime);
=======
    // Sun Movement
    float size   = SUN_SIZE + 5.0f * cos(gPulseTime);
>>>>>>> c01a43b (added earth movement)
    float aspect = static_cast<float>(gSunTexture.height) / gSunTexture.width;

    gSunScale = {size, size * aspect};

    gSunOrbitAngle += 30.0f * deltaTime;
    float radius = 60.0f + 15.0f * sin(5 * gSunOrbitAngle * 3.14f / 180);

    gSunPosition.x = ORIGIN.x + radius * cos(gSunOrbitAngle * 3.14f / 180);
    gSunPosition.y = ORIGIN.y + radius * sin(gSunOrbitAngle * 3.14f / 180);

    gSunRotate += 15.0f * deltaTime;
<<<<<<< HEAD
=======


    // Earth Movement
    gEarthOrbitAngle += 40.0f * deltaTime;

    gEarthPosition.x = gSunPosition.x + 200.0f * cos(gEarthOrbitAngle * 3.14f / 180);
    gEarthPosition.y = gSunPosition.y + 100.0f * sin(gEarthOrbitAngle * 3.14f / 180);

    float earthAspect = static_cast<float>(gEarthTexture.height) / gEarthTexture.width;
    gEarthScale = {EARTH_SIZE, EARTH_SIZE * earthAspect};

    gEarthRotate += 60.0f * deltaTime;
>>>>>>> c01a43b (added earth movement)
}

void render()
{
    BeginDrawing();

    ClearBackground(ColorFromHex(BG_COLOUR));

<<<<<<< HEAD
    // Whole texture (UV coordinates)
    Rectangle textureArea = {
=======
    // Render Sun

    // Whole texture (UV coordinates)
    Rectangle sunTextureArea = {
>>>>>>> c01a43b (added earth movement)
        // top left corner
        0.0f, 0.0f,

        // how large of a rectangle, starting from (0,0), do we want to "slice"?
        static_cast<float>(gSunTexture.width),
        static_cast<float>(gSunTexture.height)
    };

<<<<<<< HEAD
    Rectangle destinationArea = {
        // where we want our rectangle to start being drawn
        gSunPosition.x, gSunPosition.y,

        gSunScale.x, gSunScale.y
    };

    Vector2 originOffset = {gSunScale.x / 2, gSunScale.y / 2};

    DrawTexturePro(gSunTexture, textureArea, destinationArea, originOffset, gSunRotate, WHITE);
=======
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
    
    Vector2 earthOriginOffset = {gEarthScale.x / 2, gEarthScale.y / 2};

    Rectangle earthDestinationArea = {
        gEarthPosition.x, gEarthPosition.y,
        gEarthScale.x, gEarthScale.y
    };
    DrawTexturePro(gEarthTexture, earthTextureArea, earthDestinationArea, earthOriginOffset, gEarthRotate, WHITE);
>>>>>>> c01a43b (added earth movement)

    EndDrawing();
}

void shutdown()
{
    UnloadTexture(gSunTexture);
<<<<<<< HEAD
=======
    UnloadTexture(gEarthTexture);
>>>>>>> c01a43b (added earth movement)

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
