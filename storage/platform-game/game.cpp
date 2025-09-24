#include "raylib.h"

int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "My First Raylib Game!");
    
    // Game variables
    Vector2 ballPosition = { screenWidth/2, screenHeight/2 };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    int ballRadius = 20;
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;
        
        // Bounce off walls
        if (ballPosition.x >= (screenWidth - ballRadius) || ballPosition.x <= ballRadius) {
            ballSpeed.x *= -1.0f;
        }
        if (ballPosition.y >= (screenHeight - ballRadius) || ballPosition.y <= ballRadius) {
            ballSpeed.y *= -1.0f;
        }
        
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawCircleV(ballPosition, ballRadius, MAROON);
        DrawText("My First Game!", 10, 10, 20, DARKGRAY);
        DrawFPS(10, 40);
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}