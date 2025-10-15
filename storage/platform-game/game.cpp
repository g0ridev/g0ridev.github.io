
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

    float enemyX = 500.0;
    float enemyY = 450.0;
    float enemyWidth = 20.0;
    float enemyHeight = 20.0;

    // death screen (triggers when player touches enemy square, and display exit or restart.)
    bool isPlayerDead = false;
    


    float velocityX = 0.0;
    float velocityY = 0.0;
    float jumpPower = -800.0;
    float gravity = 980.0;
    
    bool isOnGround = false;


    const int TILE_SIZE = 32;
    const int LEVEL_WIDTH = 25;
    const int LEVEL_HEIGHT = 19;

    int levelMap[LEVEL_HEIGHT][LEVEL_WIDTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1},
        {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1},
        {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };


    



    InitWindow(screenWidth, screenHeight, "first-platformer");
    

    Texture2D tileset =  LoadTexture("tileset_full.png");
    Texture2D background = LoadTexture("blue-sky.jpg");
    Texture2D background2 = LoadTexture("death-screen.jpg");
    Texture2D knight = LoadTexture("knight.png");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float movementSpeed = 300.0;
        float deltaTime = GetFrameTime();
        // Apply gravity first
        velocityY += gravity * deltaTime;

        // Move player
        playerX += velocityX * deltaTime;
        playerY += velocityY * deltaTime;

        // Reset ground state
        isOnGround = false;

        // Check collisions with tiles
        for(int y = 0; y < LEVEL_HEIGHT; y++){
            for(int x = 0; x < LEVEL_WIDTH; x++){  // FIXED: was LEVEL_HEIGHT
                if(levelMap[y][x] == 1){
                    Rectangle tileRect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                    Rectangle playerRect = {playerX, playerY, playerWidth, playerHeight};

                    if(CheckCollisionRecs(playerRect, tileRect)){
                        // Calculate overlap on each axis
                        float overlapX = 0;
                        float overlapY = 0;
                        
                        // Calculate which side has less overlap (that's the collision side)
                        float leftOverlap = (playerX + playerWidth) - tileRect.x;
                        float rightOverlap = (tileRect.x + TILE_SIZE) - playerX;
                        float topOverlap = (playerY + playerHeight) - tileRect.y;
                        float bottomOverlap = (tileRect.y + TILE_SIZE) - playerY;
                        
                        // Find minimum overlap
                        float minOverlap = leftOverlap;
                        int collisionSide = 0; // 0=left, 1=right, 2=top, 3=bottom
                        
                        if(rightOverlap < minOverlap){
                            minOverlap = rightOverlap;
                            collisionSide = 1;
                        }
                        if(topOverlap < minOverlap){
                            minOverlap = topOverlap;
                            collisionSide = 2;
                        }
                        if(bottomOverlap < minOverlap){
                            minOverlap = bottomOverlap;
                            collisionSide = 3;
                        }
                        
                        // Resolve collision based on side
                        if(collisionSide == 0){ // Hit left side of tile
                            playerX = tileRect.x - playerWidth;
                            velocityX = 0;
                        }
                        else if(collisionSide == 1){ // Hit right side of tile
                            playerX = tileRect.x + TILE_SIZE;
                            velocityX = 0;
                        }
                        else if(collisionSide == 2){ // Hit top of tile (landing)
                            playerY = tileRect.y - playerHeight;
                            velocityY = 0;
                            isOnGround = true;
                        }
                        else if(collisionSide == 3){ // Hit bottom of tile (bonk head)
                            playerY = tileRect.y + TILE_SIZE;
                            velocityY = 0;
                        }
                    }
                }
            }
        }


        if(IsKeyDown(KEY_LEFT)){
            playerX -= movementSpeed * deltaTime;
        }
        if(IsKeyDown(KEY_RIGHT)){
            playerX += movementSpeed * deltaTime;
        }




        if(IsKeyDown(KEY_SPACE) && isOnGround){
            velocityY = jumpPower;
        }





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
        if(playerY + playerHeight > screenHeight){
            playerY = screenHeight - playerHeight;
            velocityY = 0;
            isOnGround = true;
        }
        else{
            isOnGround = false;
        }


            if(playerX < enemyX + enemyWidth && 
            playerX + playerWidth > enemyX &&
            playerY < enemyY + enemyHeight && 
            playerY + playerHeight > enemyY){  // Changed < to >
                playerX = 100.0;
                playerY = 400.0; 
                velocityX = 0.0;
                velocityY = 0.0;
                isPlayerDead = true;
            }

                    





        


        BeginDrawing();





            if(isPlayerDead == true){
                DrawTexturePro(background2, 
                (Rectangle){0, 0, (float)background2.width, (float)background2.height},
                (Rectangle){0, 0, screenWidth, screenHeight},
                (Vector2){0, 0}, 0.0f, WHITE);
                DrawText("You Died!", screenWidth/2 - 100, screenHeight/2 - 100,40 , RED);
                DrawText("Press Enter to Restart.", screenWidth/2 - 250, screenHeight/2 - 50,40 , RED);
                DrawText("Press Escape to exit.", screenWidth/2 - 250, screenHeight/2,40 , RED);

                if(IsKeyDown(KEY_ENTER)){
                    isPlayerDead = false;
                }
            }
            else{
        
            DrawTexturePro(background, 
            (Rectangle){0, 0, (float)background.width, (float)background.height},
            (Rectangle){0, 0, screenWidth, screenHeight},
            (Vector2){0, 0}, 0.0f, WHITE);



            if(!isOnGround){
                Rectangle sourceRec = {64, 2, 35, 35};
                Rectangle destRec = {playerX - 45, playerY - 70, playerWidth*3, playerHeight*3};  
                DrawTexturePro(knight, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);


            }
            else{
            Rectangle sourceRec = {0, 0, 35, 35};
            Rectangle destRec = {playerX - 45, playerY - 70, playerWidth*3, playerHeight*3};  
            DrawTexturePro(knight, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);

            }
            
            DrawRectangle(playerX,playerY,playerWidth,playerHeight,RED);
            DrawRectangle(enemyX,enemyY,enemyWidth,enemyHeight,RED);

            for(int y = 0; y < LEVEL_HEIGHT; y++){
                for(int x = 0; x < LEVEL_WIDTH; x++){
                    if(levelMap[y][x] == 1){
                        Rectangle sourceRec = {0, 0, TILE_SIZE, TILE_SIZE};  // Which tile in tileset
                        Rectangle destRec = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                        DrawTexturePro(tileset, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);

                    }
                }
            }


            }




        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(background2); 
    UnloadTexture(knight);
    UnloadTexture(tileset);
    CloseWindow();      
    
    

    
    return 0;
}