#include "raylib.h"
#include "parson.h"
#include <stdlib.h>

typedef struct {
    int width;
    int height;
    int tileSize;
    float playerStartX;
    float playerStartY;
    int** tiles;
    int enemyCount;
    Rectangle* enemies;
} Level;

Level LoadLevelFromJSON(const char* filename) {
    Level level = {0};
    
    JSON_Value* root_value = json_parse_file(filename);
    if (root_value == NULL) {
        TraceLog(LOG_ERROR, "Failed to load level: %s", filename);
        return level;
    }
    
    JSON_Object* root = json_value_get_object(root_value);
    
    // Load basic properties
    level.width = (int)json_object_get_number(root, "width");
    level.height = (int)json_object_get_number(root, "height");
    level.tileSize = (int)json_object_get_number(root, "tileSize");
    
    // Load player start position
    JSON_Object* playerStart = json_object_get_object(root, "playerStart");
    level.playerStartX = (float)json_object_get_number(playerStart, "x");
    level.playerStartY = (float)json_object_get_number(playerStart, "y");
    
    // Load tiles
    JSON_Array* tilesArray = json_object_get_array(root, "tiles");
    level.tiles = (int**)malloc(level.height * sizeof(int*));
    
    for (int y = 0; y < level.height; y++) {
        level.tiles[y] = (int*)malloc(level.width * sizeof(int));
        JSON_Array* row = json_array_get_array(tilesArray, y);
        
        for (int x = 0; x < level.width; x++) {
            level.tiles[y][x] = (int)json_array_get_number(row, x);
        }
    }
    
    // Load enemies
    JSON_Array* enemiesArray = json_object_get_array(root, "enemies");
    level.enemyCount = (int)json_array_get_count(enemiesArray);
    level.enemies = (Rectangle*)malloc(level.enemyCount * sizeof(Rectangle));
    
    for (int i = 0; i < level.enemyCount; i++) {
        JSON_Object* enemy = json_array_get_object(enemiesArray, i);
        level.enemies[i].x = (float)json_object_get_number(enemy, "x");
        level.enemies[i].y = (float)json_object_get_number(enemy, "y");
        level.enemies[i].width = (float)json_object_get_number(enemy, "width");
        level.enemies[i].height = (float)json_object_get_number(enemy, "height");
    }
    
    json_value_free(root_value);
    return level;
}

void UnloadLevel(Level* level) {
    if (level->tiles != NULL) {
        for (int y = 0; y < level->height; y++) {
            free(level->tiles[y]);
        }
        free(level->tiles);
        level->tiles = NULL;
    }
    
    if (level->enemies != NULL) {
        free(level->enemies);
        level->enemies = NULL;
    }
}

































int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    // Load level
    Level currentLevel = LoadLevelFromJSON("level1.json");
    
    if (currentLevel.tiles == NULL) {
        TraceLog(LOG_ERROR, "Failed to load level!");
        return 1;
    }

    float playerX = currentLevel.playerStartX;
    float playerY = currentLevel.playerStartY;
    float playerWidth = 50.0;
    float playerHeight = 50.0;

    bool isPlayerDead = false;
    int PlayerLives = 3;
    int currentLevelNumber = 1;

    bool playerWin = false;

    float velocityX = 0.0;
    float velocityY = 0.0;
    float jumpPower = -600.0;
    float gravity = 980.0;
    
    bool isOnGround = false;

    InitWindow(screenWidth, screenHeight, "first-platformer");
    
    Texture2D coins = LoadTexture("coin.png");
    Texture2D spikes = LoadTexture("spike.png");
    Texture2D tileset = LoadTexture("tileset_full.png");
    Texture2D background = LoadTexture("afternoon-sky.jpg");
    Texture2D background2 = LoadTexture("death-screen.jpg");
    Texture2D background3 = LoadTexture("blue-sky.jpg");
    Texture2D knight = LoadTexture("knight.png");

    SetTargetFPS(60);

    while (!WindowShouldClose())
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
        for(int y = 0; y < currentLevel.height; y++){
            for(int x = 0; x < currentLevel.width; x++){
                if(currentLevel.tiles[y][x] == 1){
                    Rectangle tileRect = {
                        x * currentLevel.tileSize, 
                        y * currentLevel.tileSize, 
                        (float)currentLevel.tileSize, 
                        (float)currentLevel.tileSize
                    };
                    Rectangle playerRect = {playerX, playerY, playerWidth, playerHeight};

            

                    if(CheckCollisionRecs(playerRect, tileRect)){
                        // Calculate overlap on each axis
                        float leftOverlap = (playerX + playerWidth) - tileRect.x;
                        float rightOverlap = (tileRect.x + currentLevel.tileSize) - playerX;
                        float topOverlap = (playerY + playerHeight) - tileRect.y;
                        float bottomOverlap = (tileRect.y + currentLevel.tileSize) - playerY;
                        
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
                            playerX = tileRect.x + currentLevel.tileSize;
                            velocityX = 0;
                        }
                        else if(collisionSide == 2){ // Hit top of tile (landing)
                            playerY = tileRect.y - playerHeight;
                            velocityY = 0;
                            isOnGround = true;
                        }
                        else if(collisionSide == 3){ // Hit bottom of tile (bonk head)
                            playerY = tileRect.y + currentLevel.tileSize;
                            velocityY = 0;
                        }
                    }
                }
            }
        }

        // Movement controls
        if(IsKeyDown(KEY_LEFT)){
            playerX -= movementSpeed * deltaTime;
        }
        if(IsKeyDown(KEY_RIGHT)){
            playerX += movementSpeed * deltaTime;
        }

        // Jump
        if(IsKeyPressed(KEY_SPACE) && isOnGround){
            velocityY = jumpPower;
        }

        // Screen boundaries
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
        }

        // Check collision with all enemies
        for(int i = 0; i < currentLevel.enemyCount; i++){
            Rectangle enemyRect = currentLevel.enemies[i];
            Rectangle playerRect = {playerX, playerY, playerWidth, playerHeight};
            
            if(CheckCollisionRecs(playerRect, enemyRect)){
                playerX = currentLevel.playerStartX;
                playerY = currentLevel.playerStartY; 
                velocityX = 0.0;
                velocityY = 0.0;
                isPlayerDead = true;
            }
        }

        BeginDrawing();
        Rectangle playerRect = {playerX, playerY, playerWidth, playerHeight};

        if(isPlayerDead == true){
            DrawTexturePro(background2, 
                (Rectangle){0, 0, (float)background2.width, (float)background2.height},
                (Rectangle){0, 0, screenWidth, screenHeight},
                (Vector2){0, 0}, 0.0f, WHITE);
            DrawText("You Died!", screenWidth/2 - 100, screenHeight/2 - 100, 40, RED);
            DrawText("Press Enter to Restart.", screenWidth/2 - 250, screenHeight/2 - 50, 40, RED);

            if(IsKeyPressed(KEY_ENTER)){
                playerX = currentLevel.playerStartX;
                playerY = currentLevel.playerStartY;
                velocityX = 0;
                velocityY = 0;
                PlayerLives = 3;
                isPlayerDead = false;
            }
        }
        else if(playerWin == true){
            DrawTexturePro(background3, 
                (Rectangle){0, 0, (float)background3.width, (float)background3.height},
                (Rectangle){0, 0, screenWidth, screenHeight},
                (Vector2){0, 0}, 0.0f, WHITE);
            DrawText("You Won!", screenWidth/2 - 100, screenHeight/2 - 100, 40, BLUE);
            DrawText("Press Enter to Restart.", screenWidth/2 - 250, screenHeight/2 - 50, 40, BLUE);

            if(IsKeyPressed(KEY_ENTER)){
                playerX = currentLevel.playerStartX;
                playerY = currentLevel.playerStartY;
                velocityX = 0;
                velocityY = 0;
                PlayerLives = 3;
                isPlayerDead = false;
                playerWin = false;
                
            }
        }
        else {
            DrawTexturePro(background, 
                (Rectangle){0, 0, (float)background.width, (float)background.height},
                (Rectangle){0, 0, screenWidth, screenHeight},
                (Vector2){0, 0}, 0.0f, WHITE);

            // Draw player
            if(!isOnGround){
                Rectangle sourceRec = {64, 2, 35, 35};
                Rectangle destRec = {playerX - 45, playerY - 70, playerWidth*3, playerHeight*3};  
                DrawTexturePro(knight, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);
            }
            else {
                Rectangle sourceRec = {0, 0, 35, 35};
                Rectangle destRec = {playerX - 45, playerY - 70, playerWidth*3, playerHeight*3};  
                DrawTexturePro(knight, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);
            }
            
            DrawRectangle(playerX, playerY, playerWidth, playerHeight, BLANK);

            // Draw enemies
            for(int i = 0; i < currentLevel.enemyCount; i++){
                DrawRectangle(
                    currentLevel.enemies[i].x,
                    currentLevel.enemies[i].y,
                    currentLevel.enemies[i].width,
                    currentLevel.enemies[i].height,
                    RED
                );
            }

            // Draw tiles
            for(int y = 0; y < currentLevel.height; y++){
                for(int x = 0; x < currentLevel.width; x++){
                    if(currentLevel.tiles[y][x] == 1){
                        Rectangle sourceRec = {0, 0, (float)currentLevel.tileSize, (float)currentLevel.tileSize};
                        Rectangle destRec = {
                            x * currentLevel.tileSize, 
                            y * currentLevel.tileSize, 
                            (float)currentLevel.tileSize, 
                            (float)currentLevel.tileSize
                        };
                        DrawTexturePro(tileset, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);
                    }
                    if(currentLevel.tiles[y][x] == 2){
                        // Calculate width of one spike (total width divided by 4 variants)
                        float spikeWidth = (float)spikes.width / 4.0f;
                        float spikeHeight = (float)spikes.height;
                        
                        // Grab the FIRST spike variant (index 0)
                        // Change the 0 to 1, 2, or 3 for different spike variants
                        Rectangle sourceRec = {0 * spikeWidth, 0, spikeWidth, spikeHeight};
                        Rectangle destRec = {
                            x * currentLevel.tileSize, 
                            y * currentLevel.tileSize, 
                            (float)currentLevel.tileSize, 
                            (float)currentLevel.tileSize
                        };
                        DrawTexturePro(spikes, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);

                        if(CheckCollisionRecs(playerRect, destRec)){
                            PlayerLives--;

                            if(PlayerLives <= 0){
                                isPlayerDead = true;
                            }
                            else{
                                playerX = currentLevel.playerStartX;
                                playerY = currentLevel.playerStartY;
                                velocityX = 0.0;
                                velocityY = 0.0;
                            }
                        }

                        
                    }

                    //draw coins

                    if(currentLevel.tiles[y][x] == 3){
                        float coinWidth = (float)coins.width / 12.0f;
                        float coinHeight = (float)coins.height;
                        
                        // Grab the FIRST spike variant (index 0)
                        // Change the 0 to 1, 2, or 3 for different spike variants
                        Rectangle sourceRec = {0 * coinWidth, 0, coinWidth, coinHeight};
                        Rectangle destRec = {
                            x * currentLevel.tileSize, 
                            y * currentLevel.tileSize, 
                            (float)currentLevel.tileSize, 
                            (float)currentLevel.tileSize
                        };
                        DrawTexturePro(coins, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);

                        if(CheckCollisionRecs(playerRect, destRec)){
                            playerWin = true;

                        }

                        
                    }
                }
            }

            // Level indicator
            DrawText(TextFormat("Level %d", currentLevelNumber), 10, 10, 20, WHITE);
            DrawText(TextFormat("Lives: %d", PlayerLives), 10, 40, 20, YELLOW);

        }

        EndDrawing();
    }

    UnloadLevel(&currentLevel);
    UnloadTexture(background);
    UnloadTexture(background2); 
    UnloadTexture(background3);
    UnloadTexture(knight);
    UnloadTexture(spikes);
    UnloadTexture(tileset);
    UnloadTexture(coins);
    CloseWindow();
    
    return 0;
}