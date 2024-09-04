#include "Input.h"

bool DoubleClick(uint16_t Interval, Vector2* TouchPosition) {

    if (TouchPosition == NULL) ERROR("Touch position null!");

    int CurrentGesture = GetGestureDetected();
    *TouchPosition = GetTouchPosition(0);
    Rectangle TouchArea = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    if (CheckCollisionPointRec(*TouchPosition, TouchArea) && (CurrentGesture != GESTURE_NONE))
        if (CurrentGesture == GESTURE_DOUBLETAP)
            return true;

    return (
        CheckCollisionPointRec
        (*TouchPosition, TouchArea) &&
        (CurrentGesture != GESTURE_NONE) &&
        (CurrentGesture == GESTURE_DOUBLETAP)
        )? true : false;
}