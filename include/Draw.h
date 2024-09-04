#pragma once
#ifndef H_DRAW
#define H_DRAW

#include <raylib.h>
#include <stdint.h>
#include "Constants.h"
#include "Helpers.h"

#define COLOR_BACKGROUND ((Color){80, 80, 80, 255})
#define COLOR_GRID ((Color){127, 127, 127, 255})
#define COLOR_AXIS ((Color){30, 30, 30, 255})
#define COLOR_SETPOINT ((Color){30, 30, 240, 255})

typedef enum GridType {
    NONE = 0,
    LINES = 1,
    DOTS = 2,
    DOTS_AND_LINES = 3
} GridType;

/// @brief Clears the screen to the background color.
static inline void DrawBackground() {
    ClearBackground(COLOR_BACKGROUND);
}

/// @brief Draws columns (as part of a grid).
/// @param H The height of the columns.
/// @param W The width of the columns.
/// @param GridSize The size (spacing) of the grid.
static inline void DrawColumns(uint16_t H, uint16_t W, uint16_t GridSize){
    for (uint16_t C = 0; C <= W; C += (W / (GridSize))) {
        int X  = -(W  / 2) + C;
        int Y1 =  (H / 2);
        int Y2 = -(H / 2);
        DrawLine(X, Y1, X, Y2, COLOR_GRID);
    }
}

/// @brief Draws rows (as part of a grid).
/// @param H The height of the rows.
/// @param W The width of the rows.
/// @param GridSize The size (spacing) of the grid.
static inline void DrawRows(uint16_t H, uint16_t W, uint16_t GridSize){
    for (uint16_t R = 0; R <= H; R += (H / (GridSize))) {
        int X1 =  (H / 2);
        int X2 = -(H / 2);
        int Y  =  (W  / 2) - R;
        DrawLine(X1, Y, X2, Y, COLOR_GRID);
    }
}

/// @brief Draws dots (as part of a grid).
/// @param H The height of the grid.
/// @param W The width of the grid.
/// @param GridSize The size (spacing) of the grid.
static inline void DrawDots(uint16_t H, uint16_t W, uint16_t GridSize){
    for (uint16_t X = 0; X <= (W / GridSize) / 2; X++) {
        for (uint16_t Y = 0; Y <= (H / GridSize) / 2; Y++){
            DrawCircle((2 * X * GridSize) - (W / 2), (2 * Y * GridSize) - (H / 2), 2.0f, COLOR_GRID);
        }
    }
}

/// @brief Draws a grid.
/// @param GridSize Determines the size of the grid.
/// @param Type Determines the type of grid.
static inline void DrawGrid2D(uint16_t GridSize, GridType Type) {

    const uint16_t W = WINDOW_WIDTH;
    const uint16_t H = WINDOW_HEIGHT;

    switch(Type) {
        case(LINES): {
            DrawColumns(W, H, GridSize);
            DrawRows(W, H, GridSize);
            break;
        }
        case(DOTS): {
            DrawDots(W, H, GridSize);
            break;
        }
        case(DOTS_AND_LINES): {
            DrawColumns(W, H, GridSize);
            DrawRows(W, H, GridSize);
            DrawDots(W, H, GridSize);
            break;
        }
        case(NONE):
        default: {
            INFO("Unknown GridType '%u' passed to DrawGrid2D()\n", Type);
        }
    };

}

/// @brief Draws a transparent circle with an solid outline.
/// @param X The X coordinate of the circle.
/// @param Y The Y coordinate of the circle.
/// @param R The radius coordinate of the circle.
/// @param C The color coordinate of the circle.
static inline void DrawCircleOutline(int X, int Y, float R, Color C) {
    DrawCircle(X, Y, R, ColorDim(C, 0.3));
    DrawCircleLines(X, Y, R, C);
    DrawCircleLines(X, Y, R * 0.99f, C);
}

static inline void DrawAxis(){
    DrawLine(0, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT/2, COLOR_AXIS);
}

#endif