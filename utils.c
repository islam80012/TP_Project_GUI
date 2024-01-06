#include "utils.h"

float Lerp(float start, float end, float t) {
    return start + t * (end - start);
}
/*void WaitTime(double seconds) {
    double startTime = GetTime();
    while ((GetTime() - startTime) < seconds) {
        // Allow the window to be closed during the delay
        if (WindowShouldClose()) {
            CloseWindow();
            exit(0);
        }
        // Let Raylib handle the frame rate
        SetTargetFPS(60);
        BeginDrawing();
        EndDrawing();
    }
} */
