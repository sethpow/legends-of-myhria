#include <unistd.h>
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "Button.h"
#include "Character.h"
#include "Dummy.h"
#include "Enemy.h"
#include "Prop.h"
#include "Powerup.h"
#include "WindowDetails.h"


int main()
{
    // window
    WindowDetails window{800, 600};

    Vector2 circlePosition = { (float)window.getWindowWidth() / 2, (float)window.getWindowHeight() / 2 };
    bool drawCircle = false;

    // map
    Texture2D ptrMap = LoadTexture("assets/map_tileset/ptr.png");
    Vector2 mapPos = { 0.0, 0.0 };
    const float mapScale = 2.0;

    // character
    Character knight{window.getWindowWidth(), window.getWindowHeight()};

    Enemy goblin1{
        Vector2{1000.f, 450.f},
        LoadTexture("assets/characters/goblin_idle_spritesheet.png"),
        LoadTexture("assets/characters/goblin_run_spritesheet.png"),
        500.0f
    };
    Enemy goblin2{
        Vector2{250.f, 50.f},
        LoadTexture("assets/characters/goblin_idle_spritesheet.png"),
        LoadTexture("assets/characters/goblin_run_spritesheet.png"),
        500.0f
    };
    Enemy goblin3{
        Vector2{750.f, 750.f},
        LoadTexture("assets/characters/goblin_idle_spritesheet.png"),
        LoadTexture("assets/characters/goblin_run_spritesheet.png"),
        500.0f
    };

    // enemies
    Enemy* enemies[3] = {&goblin1, &goblin2, &goblin3};

    // set player as enemy target
    for (Enemy* enemy : enemies)
    {
        enemy->setTarget(&knight);
        enemy->setRadius(30.0f);
    }

    // props
    Prop prop1{Vector2{0.f, 0.f}, LoadTexture("assets/tilesets/Rock.png")};
    Prop props[3] = {
        Prop{Vector2{600.f, 300.f}, LoadTexture("assets/tilesets/Rock.png")},
        Prop{Vector2{1050.f, 550.f}, LoadTexture("assets/tilesets/Rock.png")},
        Prop{Vector2{750.f, 750.f}, LoadTexture("assets/tilesets/Rock.png")}
    };

    // powerups
    Powerup GoldCoin{Vector2{1000.f, 300.f}, LoadTexture("assets/tilesets/GoldCoin.png")};
    Powerup RedCoin{Vector2{400.f, 750.f}, LoadTexture("assets/tilesets/RedCoin.png")};

    // dummy
    Dummy dpsDummy{Vector2{500.f, 200.f}, LoadTexture("assets/npc/targetDummy/target_dummy_dps.png")};
    Dummy healDummy{Vector2{500.f, 400.f}, LoadTexture("assets/npc/targetDummy/target_dummy_heal.png")};


    SetTargetFPS(60);

    // double currentTime = GetTime(); // Get the current time
    // double startTime = 0.0f;
    bool isInMenu = true;
    bool isInControls = false;
    bool isInInstructions = false;
    bool isCreatingChar = false;
    bool isInPTR = false;
    bool isInGameMenu = false;
    bool isInGame = false;
    bool isPaused = false;
    float showPausedText = 180.0;

    // buttons
    Button PTRButton(100, 200, 200, 50, "PTR");
    Button loadGameMenuButton(400, 200, 200, 50, "New/Load Game");
    Button newGameButton(550, 450, 200, 50, "New Game");
    Button createButton(550, 550, 200, 50, "Create Character");
    Button loadGameButton(550, 160, 200, 50, "Load Game");
    Button controlsButton(100, 300, 200, 50, "Controls");
    Button instructionsButton(400, 300, 200, 50, "Instructions");
    Button backButton(100, 550, 200, 50, "Back");

    while(!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F1))
        {
            window.ToggleFullScreenWindow(window.getWindowWidth(), window.getWindowHeight());
        }
        if(isInMenu)
        {
            if(PTRButton.IsClicked())
            {
                isInMenu = false;
                isInControls = false;
                isInInstructions = false;
                isCreatingChar = false;
                isInPTR = true;
                isInGameMenu = false;
                isInGame = false;
                isPaused = false;
            }
            if(loadGameMenuButton.IsClicked())
            {
                isInMenu = false;
                isInControls = false;
                isInInstructions = false;
                isCreatingChar = false;
                isInPTR = false;
                isInGameMenu = true;
                isInGame = false;
                isPaused = false;
            }
            if (controlsButton.IsClicked())
            {
                isInMenu = false;
                isInControls = true;
                isInInstructions = false;
                isCreatingChar = false;
                isInPTR = false;
                isInGame = false;
                isInGameMenu = false;
                isPaused = false;
            }
            if (instructionsButton.IsClicked())
            {
                isInMenu = false;
                isInControls = false;
                isInInstructions = true;
                isCreatingChar = false;
                isInPTR = false;
                isInGame = false;
                isInGameMenu = false;
                isPaused = false;
            }
        }
        else
        {
            if(backButton.IsClicked()) isInMenu = true;
            if(IsKeyPressed(KEY_P)) isPaused = !isPaused;
        }

        BeginDrawing();
        if(isInMenu)
        {
            ClearBackground(BLACK);
            DrawText("Legends of Myhria", 25, 100, 75, RAYWHITE);
            PTRButton.Draw();
            loadGameMenuButton.Draw();
            controlsButton.Draw();
            instructionsButton.Draw();
            DrawText("F1 - Toggle Fullscreen", 100, 450, 40, RAYWHITE);
            DrawText("ESC - Quit Game", 100, 550, 40, RAYWHITE);
        }
        else if (isInGameMenu)
        {
            ClearBackground(BLACK);
            DrawText("Select Save File", 25, 50, 75, RAYWHITE);
            DrawText("=================", 25, 100, 75, RAYWHITE);
            DrawText("|| Save 1 - ***", 25, 150, 75, RAYWHITE);
            DrawText("|| Empty", 25, 250, 75, RAYWHITE);
            DrawText("|| Empty", 25, 350, 75, RAYWHITE);
            newGameButton.Draw();
            loadGameButton.Draw();
            backButton.Draw();
            if (newGameButton.IsClicked())
            {
                isInMenu = false;
                isInControls = false;
                isInInstructions = false;
                isCreatingChar = true;
                isInPTR = false;
                isInGameMenu = false;
                isInGame = false;
                isPaused = false;
            }
            if (loadGameButton.IsClicked())
            {
                isInMenu = false;
                isInControls = false;
                isInInstructions = false;
                isCreatingChar = false;
                isInPTR = false;
                isInGameMenu = false;
                isInGame = true;
                isPaused = false;
            }
        }
        else if(isCreatingChar)
        {
            ClearBackground(BLACK);
            DrawText("Character Creation", 25, 50, 75, RAYWHITE);
            DrawText("===================", 25, 100, 75, RAYWHITE);
            DrawText("|| Name: _________", 25, 150, 75, RAYWHITE);
            DrawText("||", 25, 200, 75, RAYWHITE);
            DrawText("||", 25, 250, 75, RAYWHITE);
            DrawText("||", 25, 300, 75, RAYWHITE);
            DrawText("||", 25, 350, 75, RAYWHITE);
            DrawText("||", 25, 400, 75, RAYWHITE);
            DrawText("||       <        >", 25, 450, 75, RAYWHITE);
            createButton.Draw();
            backButton.Draw();
            if (createButton.IsClicked())
            {
                isInMenu = false;
                isInControls = false;
                isInInstructions = false;
                isCreatingChar = false;
                isInPTR = false;
                isInGameMenu = false;
                isInGame = true;
                isPaused = false;
            }
        }
        else if(isInControls)
        {
            ClearBackground(BLACK);
            DrawText("Controls", 25, 50, 75, RAYWHITE);
            DrawText("WASD/Arrows - Move", 100, 150, 40, RAYWHITE);
            DrawText("Left Click - Ability 1", 100, 200, 40, RAYWHITE);
            DrawText("Right Click - Ability 2", 100, 250, 40, RAYWHITE);
            DrawText("Middle Click - Ability 3", 100, 300, 40, RAYWHITE);
            DrawText("Tab - Racial Ability", 100, 350, 40, RAYWHITE);
            DrawText("Space - Shield", 100, 400, 40, RAYWHITE);
            backButton.Draw();
        }
        else if(isInInstructions)
        {
            ClearBackground(BLACK);
            DrawText("Instructions", 25, 50, 75, RAYWHITE);
            backButton.Draw();
        }
        else
        {
            if(!isPaused)
            {
                if (isInGame)
                {
                    ClearBackground(WHITE);

                    mapPos = Vector2Scale(
                        knight.getWorldPos(),
                        -1.0f // -10 superspeed, 1 flips controls, 10 flips & superspeed
                    );

                    // draw map
                    DrawTextureEx(
                        ptrMap,
                        mapPos,
                        0.0, // rotate map
                        2.0, // increase map scale
                        WHITE
                    );

                    // draw props
                    prop1.Render(knight.getWorldPos());
                    for (Prop prop : props)
                    {
                        prop.Render(knight.getWorldPos());
                    }

                    if (!knight.getAlive())
                    {
                        DrawText("Game Over", 300, 300, 30, RED);
                        EndDrawing();
                        continue;
                    }
                    else if (!goblin1.getAlive() && !goblin2.getAlive() && !goblin3.getAlive())
                    {
                        DrawText("You Win!", 300, 300, 30, GREEN);
                        EndDrawing();
                        continue;
                    }
                    else
                    {
                        // draw health
                        std::string knightsHealthText = "Health: ";
                        knightsHealthText.append(std::to_string(knight.getHealth()), 0, 4);
                        float characterHealth = knight.getHealth();
                        Rectangle healthBar{20, 50, 100, 20}; // position and size of health bar
                        Rectangle healthBarBackground{20, 50, 100, 20}; // position and size of health bar
                        float healthPercentage = characterHealth / 100; // example health percentage (80%)
                        Color healthColor = GREEN; // example health color
                        DrawRectangle(healthBarBackground.x, healthBarBackground.y, healthBarBackground.width, healthBarBackground.height, RED);
                        DrawRectangle(healthBar.x, healthBar.y, healthBar.width * healthPercentage, healthBar.height, healthColor);
                        DrawText(knightsHealthText.c_str(), 20, 20, 20, BLACK);

                        // draw knight score
                        std::string knightScoreText = "Score: ";
                        knightScoreText.append(std::to_string(knight.getScore()), 0, 4);
                        DrawText(knightScoreText.c_str(), 200, 20, 20, BLACK);


                        // draw enemy health in top right
                        std::string enemyHealthText = "Goblin 1: ";
                        enemyHealthText.append(std::to_string(goblin1.getHealth()), 0, 4);
                        float enemyHealth = goblin1.getHealth();
                        Rectangle eHealthBar{600, 50, 100, 20}; // position and size of health bar
                        Rectangle eHealthBarBackground{600, 50, 100, 20}; // position and size of health bar
                        float eHealthPercentage = enemyHealth / 500; // example health percentage (80%)
                        Color eHealthColor = GREEN; // example health color
                        DrawRectangle(eHealthBarBackground.x, eHealthBarBackground.y, eHealthBarBackground.width, eHealthBarBackground.height, RED);
                        DrawRectangle(eHealthBar.x, eHealthBar.y, eHealthBar.width * eHealthPercentage, eHealthBar.height, eHealthColor);
                        DrawText(enemyHealthText.c_str(), 600, 20, 20, BLACK);

                        std::string enemyHealthText2 = "Goblin 2: ";
                        enemyHealthText2.append(std::to_string(goblin2.getHealth()), 0, 4);
                        float enemyHealth2 = goblin2.getHealth();
                        Rectangle eHealthBar2{600, 100, 100, 20}; // position and size of health bar
                        Rectangle eHealthBarBackground2{600, 100, 100, 20}; // position and size of health bar
                        float eHealthPercentage2 = enemyHealth2 / 500; // example health percentage (80%)
                        Color eHealthColor2 = GREEN; // example health color
                        DrawRectangle(eHealthBarBackground2.x, eHealthBarBackground2.y, eHealthBarBackground2.width, eHealthBarBackground2.height, RED);
                        DrawRectangle(eHealthBar2.x, eHealthBar2.y, eHealthBar2.width * eHealthPercentage2, eHealthBar2.height, eHealthColor2);
                        DrawText(enemyHealthText2.c_str(), 600, 100, 20, BLACK);

                        std::string enemyHealthText3 = "Goblin 3: ";
                        enemyHealthText3.append(std::to_string(goblin3.getHealth()), 0, 4);
                        float enemyHealth3 = goblin3.getHealth();
                        Rectangle eHealthBar3{600, 150, 100, 20}; // position and size of health bar
                        Rectangle eHealthBarBackground3{600, 150, 100, 20}; // position and size of health bar
                        float eHealthPercentage3 = enemyHealth3 / 500; // example health percentage (80%)
                        Color eHealthColor3 = GREEN; // example health color
                        DrawRectangle(eHealthBarBackground3.x, eHealthBarBackground3.y, eHealthBarBackground3.width, eHealthBarBackground3.height, RED);
                        DrawRectangle(eHealthBar3.x, eHealthBar3.y, eHealthBar3.width * eHealthPercentage3, eHealthBar3.height, eHealthColor3);
                        DrawText(enemyHealthText3.c_str(), 600, 150, 20, BLACK);
                    }

                    // draw character
                    knight.tick(GetFrameTime());

                    // out of bounds
                    if (knight.getWorldPos().x < 0.0 ||
                        knight.getWorldPos().y < 0.0 ||
                        knight.getWorldPos().x + window.getWindowWidth() > ptrMap.width * mapScale || 
                        knight.getWorldPos().y + window.getWindowHeight() > ptrMap.height * mapScale)
                    {
                        // if hitting wall, reset worldPos to last frame
                        knight.undoMovement();
                    }
                    for (Prop prop : props)
                    {
                        // collision
                        if (
                            CheckCollisionRecs(
                                knight.getCollisionRec(),
                                prop.getCollisionRec(knight.getWorldPos())
                            )
                        )
                        {
                            knight.undoMovement();
                        }
                    }

                    // draw enemies
                    for (Enemy* enemy : enemies)
                    {
                        enemy->tick(GetFrameTime());
                    }

                    // shield on spacebar
                    if (IsKeyDown(KEY_SPACE))
                    {
                        // Activate shield
                        // Add shield logic here
                        knight.drawShield(true);
                    }
                    else
                    {
                        knight.drawShield(false);
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        {
                            // check weapon collision
                            for (Enemy* enemy : enemies)
                            {
                                if (CheckCollisionRecs(knight.getWeaponCollisionRec(), enemy->getCollisionRec()))
                                {
                                    enemy->takeDamage(knight.getWeaponDamage());
                                }
                                // check if enemy is dead
                                if (enemy->getHealth() <= 0)
                                {
                                    enemy->setAlive(false);
                                    knight.setScore(knight.getScore() + 1);
                                }
                            }
                            DrawText("Ability 1", window.GetDisplayWidth()/3, 50, 25, RAYWHITE);
                        }
                        // else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
                        else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
                        {
                            // draw knight healing animation
                            DrawText("Ability 2", window.GetDisplayWidth()/3, 50, 25, RAYWHITE);
                            knight.drawHealing(true);
                        }
                        else if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON))
                        {
                            DrawText("Ability 3", window.GetDisplayWidth()/3, 50, 25, RAYWHITE);
                        }
                        else if (IsKeyPressed(KEY_TAB))
                        {
                            DrawText("Racial Ability", window.GetDisplayWidth()/3, 50, 25, RAYWHITE);
                        }

                        if (showPausedText > 0.0)
                        {
                            showPausedText -= 1;
                            DrawText("P - Pause Game", window.GetDisplayWidth()/3, 50, 25, RAYWHITE);
                        }
                    }

                }
                else if (isInPTR)
                {
                    ClearBackground(RED);

                    mapPos = Vector2Scale(
                        knight.getWorldPos(),
                        -1.0f // -10 superspeed, 1 flips controls, 10 flips & superspeed
                    );

                    // draw map
                    DrawTextureEx(
                        ptrMap,
                        mapPos,
                        0.0, // rotate map
                        2.0, // increase map scale
                        RED
                    );

                    // draw powerups
                    GoldCoin.Render(knight.getWorldPos());
                    RedCoin.Render(knight.getWorldPos());

                    // draw dummies
                    dpsDummy.Render(knight.getWorldPos());
                    healDummy.Render(knight.getWorldPos());

                    // if (!knight.getAlive())
                    // {
                    //     DrawText("Game Over", 300, 300, 30, RED);
                    //     EndDrawing();
                    //     continue;
                    // }
                    
                    // if knights health is 1, stop taking more damage
                    if (knight.getHealth() == 1)
                    {
                        DrawText("GO HEAL YOURSELF", 300, 300, 30, RED);
                        knight.setHealth(5);
                    }
                    else
                    {
                        // draw health
                        std::string knightsHealthText = "Health: ";
                        knightsHealthText.append(std::to_string(knight.getHealth()), 0, 4);
                        float characterHealth = knight.getHealth();
                        Rectangle healthBar{20, 50, 100, 20}; // position and size of health bar
                        Rectangle healthBarBackground{20, 50, 100, 20}; // position and size of health bar
                        float healthPercentage = characterHealth / 100; // example health percentage (80%)
                        Color healthColor = GREEN; // example health color
                        DrawRectangle(healthBarBackground.x, healthBarBackground.y, healthBarBackground.width, healthBarBackground.height, RED);
                        DrawRectangle(healthBar.x, healthBar.y, healthBar.width * healthPercentage, healthBar.height, healthColor);
                        DrawText(knightsHealthText.c_str(), 20, 20, 20, BLACK);

                        // draw enemy health in top right
                        std::string enemyHealthText = "Blue Dummy: ";
                        enemyHealthText.append(std::to_string(healDummy.getHealth()), 0, 4);
                        float enemyHealth = healDummy.getHealth();
                        Rectangle eHealthBar{600, 50, 100, 20}; // position and size of health bar
                        Rectangle eHealthBarBackground{600, 50, 100, 20}; // position and size of health bar
                        float eHealthPercentage = enemyHealth / 100; // example health percentage (80%)
                        Color eHealthColor = BLUE; // example health color
                        DrawRectangle(eHealthBarBackground.x, eHealthBarBackground.y, eHealthBarBackground.width, eHealthBarBackground.height, RED);
                        DrawRectangle(eHealthBar.x, eHealthBar.y, eHealthBar.width * eHealthPercentage, eHealthBar.height, eHealthColor);
                        DrawText(enemyHealthText.c_str(), 600, 20, 20, BLACK);
                    }

                    // draw character
                    knight.tick(GetFrameTime());
                    if (IsKeyDown(KEY_ONE))
                    {
                        DrawText("1 PRESSED", window.GetDisplayWidth()/3, 50, 25, RAYWHITE);
                        drawCircle = true;
                        circlePosition = GetMousePosition();
                    }
                    if (IsKeyReleased(KEY_TWO))
                    {
                        drawCircle = false;
                    }
                    if (drawCircle)
                    {
                        DrawCircleV(circlePosition, 30, RED);
                    }

                    // // out of bounds
                    // if (knight.getWorldPos().x < 0.0 ||
                    //     knight.getWorldPos().y < 0.0 ||
                    //     knight.getWorldPos().x + window.getWindowWidth() > ptrMap.width * mapScale || 
                    //     knight.getWorldPos().y + window.getWindowHeight() > ptrMap.height * mapScale)
                    // {
                    //     // if hitting wall, reset worldPos to last frame
                    //     knight.undoMovement();
                    // }
                    // for (Prop prop : props)
                    // {
                    //     // collision
                    //     if (
                    //         CheckCollisionRecs(
                    //             knight.getCollisionRec(),
                    //             prop.getCollisionRec(knight.getWorldPos())
                    //         )
                    //     )
                    //     {
                    //         knight.undoMovement();
                    //     }
                    // }

                    // check collision with coin
                    if (CheckCollisionRecs(knight.getCollisionRec(), GoldCoin.getCollisionRec(knight.getWorldPos())))
                    {
                        knight.setScale(2.0f);
                        knight.setSpeed(10.0f);
                        knight.setWeaponDamage(5.0f);
                        GoldCoin.removePowerup();
                    }

                    // check collision with coin
                    if (CheckCollisionRecs(knight.getCollisionRec(), RedCoin.getCollisionRec(knight.getWorldPos())))
                    {
                        knight.setScale(8.0f);
                        knight.setSpeed(2.5f);
                        knight.setWeaponDamage(25.0f);
                        RedCoin.removePowerup();
                    }

                    // check collision with dummy
                    if (CheckCollisionRecs(knight.getCollisionRec(), dpsDummy.getCollisionRec(knight.getWorldPos())))
                    {
                        // damage knight
                        knight.takeDamage(dpsDummy.getDps());
                    }

                    // shield on spacebar
                    if (IsKeyDown(KEY_SPACE))
                    {
                        // Activate shield
                        // Add shield logic here
                        knight.drawShield(true);
                    }
                    else
                    {
                        knight.drawShield(false);
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        {
                            // check weapon collision with heal
                            if (CheckCollisionRecs(knight.getCollisionRec(), healDummy.getCollisionRec(knight.getWorldPos())))
                            {
                                // damage dummy
                                healDummy.takeDamage(knight.getWeaponDamage());
                            }
                            if (healDummy.getHealth() <= 0.0f)
                            {
                                while (healDummy.getHealth() != 100.0f)
                                {
                                    healDummy.setHealth(healDummy.getHealth() + 0.5f);
                                }
                            }
                            DrawText("Ability 1", window.GetDisplayWidth()/3, 50, 25, RAYWHITE);
                        }
                        // else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
                        else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
                        {
                            // draw knight healing animation
                            DrawText("Ability 2", window.GetDisplayWidth()/3, 50, 25, RAYWHITE);
                            knight.drawHealing(true);
                        }
                        else if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON))
                        {
                            DrawText("Ability 3", window.GetDisplayWidth()/3, 50, 25, RAYWHITE);
                        }
                        else if (IsKeyPressed(KEY_TAB))
                        {
                            DrawText("Racial Ability", window.GetDisplayWidth()/3, 50, 25, RAYWHITE);
                        }
                        if (showPausedText > 0.0)
                        {
                            showPausedText -= 1;
                            DrawText("P - Pause Game", window.GetDisplayWidth()/3, 50, 25, RAYWHITE);
                        }
                    }
                }
            }
            else
            {
                DrawRectangle(window.GetDisplayWidth()/5, window.GetDisplayHeight()/5, window.GetDisplayWidth()/2, window.GetDisplayHeight()/2, LIGHTGRAY);
                DrawText("Paused", window.GetDisplayWidth()/5, window.GetDisplayHeight()/5, 75, RAYWHITE);
                DrawText("BACKSPACE - Return to Menu", 100, 550, 40, RAYWHITE);
                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    isInMenu = true;
                    isInControls = false;
                    isInInstructions = false;
                    isCreatingChar = false;
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
