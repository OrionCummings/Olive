#pragma once
#ifndef H_GRAPHICS
#define H_GRAPHICS

#include <raylib.h>
#include <raymath.h>
#include "Animation.h"
#include "Constants.h"
#include "Helpers.h"

/// @brief Initialize the zoom animation.
/// @param EasingFunction The easing function to use.
void InitZoomAnimation(double (*EasingFunction)(double t));

/// @brief Initialize the drag animation.
/// @param EasingFunction The easing function to use.
void InitDragAnimation(double (*EasingFunction)(double t));

/// @brief Initialize the pan animation.
/// @param EasingFunction The easing function to use.
void InitPanAnimation(double (*EasingFunction)(double t));

/// @brief Handles updating the camera zoom.
/// @param C The camera to zoom.
void UpdateZoom(Camera2D* C);

/// @brief Handles updating the camera dragging.
/// @param C The camera to drag.
void UpdateDrag(Camera2D* C);

/// @brief Handles updating the camera panning.
/// @param C The camera to pan.
void UpdatePan(Camera2D* C);

#endif