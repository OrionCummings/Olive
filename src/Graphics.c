#include "Graphics.h"

Animation ZoomAnimation;
float CurrentZoom = 1.0;
float PreviousZoom = 1.0;

Animation DragAnimation;


Animation PanAnimation;


void InitZoomAnimation(double (*EasingFunction)(double t)) {
    ZoomAnimation = AnimationNew(EasingFunction);
}

void InitDragAnimation(double (*EasingFunction)(double t)) {
    DragAnimation = AnimationNew(EasingFunction);
}

void InitPanAnimation(double (*EasingFunction)(double t)) {
    PanAnimation = AnimationNew(EasingFunction);
}

void UpdateZoom(Camera2D* C){

    // THIS WHOLE ZOOM THING NEEDS TO BE REWORKED.
    // WHEN A ZOOM IS DETECTED, DISABLE FUTURE ZOOMS UNTIL
    // THE CURRENT ZOOM IS COMPLETE!

    // Figure out the animation direction
    // CurrentZoom = C.zoom;
    // float ZoomDelta = CurrentZoom - PreviousZoom;

    // AnimationDirection Dir;
    // if (ZoomDelta > 0) {
    //     Dir = FORWARD;
    // } else if (ZoomDelta < 0) {
    //     Dir = BACKWARD;
    // }

    // printf("%u --> %u = %u\t%u\t%s\n", CurrentZoom, PreviousZoom, ZoomDelta, Dir, (Dir == FORWARD)? "FORWARD" : "BACKWARD");

    // // If we have zoomed
    // float MouseWheelMovement = GetMouseWheelMove();
    // bool MouseWheelMoved = (bool)MouseWheelMovement;
    // if (MouseWheelMoved && AnimationInactive(ZoomAnimation)) {
        
    //     // printf("Animation starting\n");

    //     // Start the animation
    //     AnimationStart(&ZoomAnimation, Dir);
    // }
    
    // // If the animation is active
    // if (AnimationActive(ZoomAnimation)) {

    //     // printf("Animation active\n");

    //     // Step the animation
    //     AnimationStep(&ZoomAnimation, Dir);
    //     // AnimationPrint(ZoomAnimation);

    //     // Actually update the zoom
    //     // C.zoom = CurrentZoom * (float)(ZoomAnimation.Time) * Dir;
    //     // printf("%.2f, %.2f\n", (float)(ZoomAnimation.Time), C.zoom);
    // }

    // // Save the previous zoom
    // PreviousZoom = CurrentZoom;

    // if (Dir == FORWARD){
    //     printf("%.2f --[%.2f]--> %.2f\n", PreviousZoom, C.zoom, CurrentZoom);
    // } else {
    //     printf("%.2f <--[%.2f]-- %.2f\n", PreviousZoom, C.zoom, CurrentZoom);
    // }

    // OLD: Perform the zoom
    C->zoom += (GetMouseWheelMove() * 0.05f);

    // Clamp the zoom
    if (C->zoom > 3.0f){
        C->zoom = 3.0f;
    } else if (C->zoom < 0.1f){
        C->zoom = 0.1f;
    }
}

void UpdateDrag(Camera2D* C){

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

        // Get the difference between the clicked and the current position
        Vector2 Delta = GetMouseDelta();

        // Scale delta based on the current camera zoom
        Delta = Vector2Scale(Delta, -1.0f/C->zoom);

        // Update the camera center
        C->target = Vector2Add(C->target, Delta);
    }
}

void UpdatePan(Camera2D* C) {

    // Check for a double click
    Vector2 TouchPosition = { 0.0f, 0.0f };
    if (DoubleClick(200, &TouchPosition)) {
        printf("Double click!\n");

        // TODO: Fix!
        C->target = (Vector2) {
            TouchPosition.x - (WINDOW_WIDTH/2) * C->zoom, 
            TouchPosition.y - (WINDOW_HEIGHT/2) * C->zoom
            };
    }

}