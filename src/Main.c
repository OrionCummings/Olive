#include <stdio.h>
#include <stdint.h>
#include <raylib.h>
#include "Debug.h"
#include "Constants.h"
#include "Draw.h"
#include "Animation.h"
#include "Graphics.h"

Camera2D C;

float T;
float DELTA_T = 0.001f;

/// @brief A setup function that initializes everything the program needs to operate smoothly.
/// @param 
/// @return An non zero integer indicating failure or zero indicating success.
int Setup(void){

    // Initialize the window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "");

    // Set window properties
    SetTraceLogLevel(LOG_ERROR);
    SetTargetFPS(60);
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    // Initialize the camera zooming and panning
    C.target = (Vector2){ 0.0f, 0.0f };
    C.offset = (Vector2){ (WINDOW_WIDTH / 2.0f), (WINDOW_HEIGHT / 2.0f) };
    C.rotation = 0.0f;
    C.zoom = 1.0f;
    // InitZoomAnimation(EasingInOutCubic);
    // InitDragAnimation(EasingInOutCubic);
    // InitPanAnimation(EasingOutBack);

    return 0;
}

/// @brief An update function updates any variables during program execution. Handles user input and time.
/// @param 
/// @return An non zero integer indicating failure or zero indicating success.
int Update(void){

    // Tick time
    T += DELTA_T;

    // Update zooming and dragging
    UpdateZoom(&C);
    UpdateDrag(&C);

    return 0;
}

/// @brief A drawing function that displays pixels to the window. Called every frame.
/// @param 
/// @return An non zero integer indicating failure or zero indicating success.
int Draw(void){

    // Draw the background
    DrawBackground();

    // Draw the grid
    DrawGrid2D(20, DOTS_AND_LINES);

    // ...
    DrawCircleOutline(0, 0, 40, (Color){255, 0, 255, 70});

    return 0;
}

/// @brief The main function of the program. Initializes the window and contains the main event loop.
/// @param argc The number of arguments passed to the program beginning with the program name.
/// @param argv A list containing the arguments passed to the program.
/// @return An non zero integer indicating failure or zero indicating success.
int Main(int argc, char** argv){

    if (Setup()) ERROR("Setup failed!");

    while (!WindowShouldClose())
    {
        if (Update()) ERROR("Update failed");

        BeginDrawing();
        BeginMode2D(C);

        if (Draw()) ERROR("Draw failed");

        EndMode2D();
        EndDrawing();
    }

    CloseWindow();

    printf("Exiting program\n");

    return 0;
}

/// @brief The entry point for the program.
/// @param argc The number of arguments passed to the program beginning with the program name.
/// @param argv A list containing the arguments passed to the program.
/// @return An non zero integer indicating failure or zero indicating success.
int main(int argc, char** argv){
    return Main(argc, argv);
}