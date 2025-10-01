
#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    float playerX = 100.0;
    float playerY = 800.0;
    float playerWidth = 50.0;
    float playerHeight = 50.0;
    float startX = 100.0;
    float startY = 800.0;

    float enemyX = 300.0;
    float enemyY = 200.0;
    float enemyWidth = 50.0;
    float enemyHeight = 50.0;


    float groundY = 500.0;
    float groundHeight = 100.0;
    float velocityX = 0.0;
    float velocityY = 0.0;
    float jumpPower = -400.0;
    float gravity = 980.0;
    
    bool isOnGround = false;
    float deathTimer = 0.5;






    InitWindow(screenWidth, screenHeight, "first-platformer");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float movementSpeed = 300.0;
        float deltaTime = GetFrameTime();


        if(IsKeyDown(KEY_LEFT)){
            playerX -= movementSpeed * deltaTime;
        }
        if(IsKeyDown(KEY_RIGHT)){
            playerX += movementSpeed * deltaTime;
        }




        if(IsKeyDown(KEY_SPACE)){
            playerY += jumpPower * deltaTime;
            isOnGround = false;
        }

        velocityY += gravity * deltaTime;

        playerX += velocityX * deltaTime;
        playerY += velocityY * deltaTime;



        if(playerX < 0){
            playerX = 0;
            velocityX = 0;
        }
        if(playerX + playerWidth > screenWidth){
            playerX = screenWidth - playerWidth;
            velocityX = 0;
        }
        if(playerY < 0){
            playerY = 0;
            velocityY = 0;
        }
        if(playerY + playerHeight > screenHeight - groundHeight){
            playerY = (screenHeight - groundHeight) - playerHeight;
            velocityY = 0;
            isOnGround = true;
        }
        else{
            isOnGround = false;
        }


        if(playerX < enemyX + enemyWidth && playerX + playerWidth > enemyWidth && playerY < enemyY + enemyHeight && playerHeight > enemyHeight + enemyY){
            playerX = startX;
        }
        





        


        BeginDrawing();

            ClearBackground(SKYBLUE);

            DrawRectangle(playerX,playerY,playerWidth,playerHeight,YELLOW);
            DrawRectangle(enemyX,enemyY,enemyWidth,enemyHeight,RED);

            DrawRectangle(0,groundY,screenWidth,groundHeight,GREEN);



            DrawText("Platformer", 400, 400, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();       
    

    
    return 0;
}