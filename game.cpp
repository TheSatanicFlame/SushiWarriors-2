#include "game.h"
#include "surface.h"
#include "template.h"
#include "animation.h"
#include "Player.h" 
#include "MouseHandler.h"
#include "SushiManager.h"
#include "ScoreSystem.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdlib> // For srand() and rand()
#include <ctime>   // For time()

namespace Tmpl8
{

    Sprite* playerSpriteRight = new Sprite(new Surface("assets/run.png"), 4);
    Sprite* playerSpriteLeft = new Sprite(new Surface("assets/run-left.png"), 4);
    Sprite* playerSpriteIdle = new Sprite(new Surface("assets/idle.png"), 5);
    Sprite MouseCursor(new Surface("assets/pointer.png"), 1);
    Sprite* scorePrefixSprite = new Sprite(new Surface("assets/score.png"), 1);

    Sprite* digitSprites[11];

    void DrawDigitScaled(Surface* surface, int digit, int posX, int posY, int width, int height) {
        if (digit >= 0 && digit < 10) {
            digitSprites[digit]->DrawScaled(posX, posY, width, height, surface);
        }
    }

    void DrawGameTimer(Surface* surface, int gameTimeSeconds, int posX, int posY) {
        float scaleFactor = 0.4f; // Adjust as needed
        int minutes = gameTimeSeconds / 60;
        int seconds = gameTimeSeconds % 60;

        int originalDigitWidth = 64; // Original width of each digit sprite
        int originalDigitHeight = 64; // Original height of each digit sprite
        int scaledWidth = static_cast<int>(originalDigitWidth * scaleFactor);
        int scaledHeight = static_cast<int>(originalDigitHeight * scaleFactor);
        int spacing = 0; // Adjust as needed

        // Use DrawScaled for drawing minutes
        DrawDigitScaled(surface, minutes / 10, posX, posY, scaledWidth, scaledHeight);
        DrawDigitScaled(surface, minutes % 10, posX + scaledWidth + spacing, posY, scaledWidth, scaledHeight);

        // Draw colon with scaling
        digitSprites[10]->DrawScaled(posX + 2 * (scaledWidth + spacing), posY, scaledWidth, scaledHeight, surface);

        // Use DrawScaled for drawing seconds
        DrawDigitScaled(surface, seconds / 10, posX + 2 * (scaledWidth + spacing) + scaledWidth, posY, scaledWidth, scaledHeight);
        DrawDigitScaled(surface, seconds % 10, posX + 3 * (scaledWidth + spacing) + scaledWidth, posY, scaledWidth, scaledHeight);
    }

    void DrawScore(Surface* surface, int score, int posX, int posY) {
        // Assuming scorePrefixSprite is already loaded somewhere else and not resized here
        scorePrefixSprite->Draw(surface, posX, posY); // Draw the "Score: " prefix without scaling
        posX += scorePrefixSprite->GetWidth() + 10; // Move X position right after the prefix sprite with some spacing

        float scaleFactor = 0.4f; // Scaling factor for digits
        // Assuming original dimensions for digit sprites are known (64x64 in this case)
        int scaledWidth = static_cast<int>(64 * scaleFactor); // Calculate scaled width for digits
        int scaledHeight = static_cast<int>(64 * scaleFactor); // Calculate scaled height for digits
        int spacing = -5; // Spacing between scaled digits

        std::string scoreStr = std::to_string(score);
        for (char digit : scoreStr) {
            int digitIndex = digit - '0'; // Convert char to int index
            // Draw each digit scaled using the DrawScaled method
            digitSprites[digitIndex]->DrawScaled(posX, posY, scaledWidth, scaledHeight, surface);
            posX += scaledWidth + spacing; // Move to the next digit position with added spacing
        }
    }



    

    


    std::vector<AnimatedSprite> animatedSprites;

    float x = 400, y = 256;

    ScoreSystem scoreSystem;

    Player player = Player();

    void Game::StartGame() {
        currentState = GameState::PLAYING;
        gameTimeRemaining = 180.0f; // Reset game time
        scoreSystem.ResetScore(); // Reset the score
        player.ResetPlayer(); // Reset the player position and speed
    }

    void Game::EndGame() {
        currentState = GameState::END;
        // Here you can handle anything that should happen when the game ends,
        // like stopping the game loop or displaying the end screen.
    }

    void Game::BackToMenu() {
		currentState = GameState::START;
		// Reset any game state or variables to start a new game
	}

    void Game::DrawStartScreen(Surface* surface) {
        if (titleSprite) {
            int titleX = (ScreenWidth - 320) / 2; // Center horizontally
            int titleMarginTop = 50; // Increased top margin for title
            titleSprite->Draw(surface, titleX, titleMarginTop);
        }

        if (playButtonSprite) {
            int playButtonX = (ScreenWidth - 64) / 2; // Center horizontally
            int playButtonMarginBottom = 100; // Increased bottom margin for play button
            int playButtonY = ScreenHeight - 64 - playButtonMarginBottom; // Apply the bottom margin
            playButtonSprite->Draw(surface, playButtonX, playButtonY);
        }
    }

    void Game::DrawEndScreen(Surface* surface) {
        // Draw the title at the top with a margin
        if (titleSprite) {
            int titleX = (ScreenWidth - 320) / 2; // Center horizontally
            int titleY = 50; // Top margin
            titleSprite->Draw(surface, titleX, titleY);
        }

        // Draw the "Back to Menu" button in the play button's position
        if (backToMenuButtonSprite) { // Assuming the same sprite for simplicity; replace with backToMenuButtonSprite if different
            backToMenuButtonSprite->Draw(surface, playButtonRect.x, playButtonRect.y);
        }

        int scoreX = (ScreenWidth - (10 * 64 * 0.4f)) / 2; // This is an approximation for centering. Adjust as needed.
        int scoreY = 200; // Position the score below the title. Adjust as needed.
        DrawScore(surface, scoreSystem.GetScore(), scoreX, scoreY);
    }


    void Game::MouseDown(int button) {
        // Assuming button 1 is the left mouse button
        if (button == 1) { // SDL_BUTTON_LEFT
            switch (currentState) {
            case GameState::START:
                if (mousex >= playButtonRect.x && mousex <= (playButtonRect.x + playButtonRect.w) &&
                    mousey >= playButtonRect.y && mousey <= (playButtonRect.y + playButtonRect.h)) {
                    StartGame();
                }
                break;
            case GameState::END:
                if (mousex >= restartButtonRect.x && mousex <= (restartButtonRect.x + restartButtonRect.w) &&
                    mousey >= restartButtonRect.y && mousey <= (restartButtonRect.y + restartButtonRect.h)) {
                    BackToMenu(); // or Init() to restart everything from scratch
                }
                break;
                // No need to handle GameState::PLAYING here unless you have UI elements in this state
            }
        }
    }

    void Game::Init() {
        srand(static_cast<unsigned int>(time(nullptr)));

        // Existing initialization code...
        player.SetSpriteLeft(playerSpriteLeft);
        player.SetSpriteRight(playerSpriteRight);
        player.SetSpriteIdle(playerSpriteIdle);

        mouseHandler = new MouseHandler(screen);

        animatedSprites.push_back(AnimatedSprite(playerSpriteRight, 4, 150));
        animatedSprites.push_back(AnimatedSprite(playerSpriteLeft, 4, 150));
        animatedSprites.push_back(AnimatedSprite(playerSpriteIdle, 5, 150));

        titleSprite = new Sprite(new Surface("assets/title.png"), 1);
        playButtonSprite = new Sprite(new Surface("assets/play.png"), 1);
        backToMenuButtonSprite = new Sprite(new Surface("assets/back.png"), 1); // Load your back button sprite

        // Set up play button rectangle for click detection
        int playButtonMarginBottom = 100; // Must match the margin used in DrawStartScreen
        playButtonRect = { (ScreenWidth - 64) / 2, ScreenHeight - 64 - playButtonMarginBottom, 64, 64 };
        restartButtonRect = { (ScreenWidth - 64) / 2, ScreenHeight - 64 - playButtonMarginBottom, 64, 64 };

        // Load digit sprites
        for (int i = 0; i < 10; ++i) {
            std::string filePath = "assets/digit/" + std::to_string(i) + ".png";
            std::vector<char> filePathCStr(filePath.c_str(), filePath.c_str() + filePath.size() + 1); // +1 for null terminator
            Surface* digitSurface = new Surface(&filePathCStr[0]); // Convert to char* and load the image
            digitSprites[i] = new Sprite(digitSurface, 1); // Assume each digit is a single frame
        }

        // Load colon sprite
        std::string colonPath = "assets/digit/semicolon.png";
        std::vector<char> colonPathCStr(colonPath.c_str(), colonPath.c_str() + colonPath.size() + 1); // +1 for null terminator
        Surface* colonSurface = new Surface(&colonPathCStr[0]);
        digitSprites[10] = new Sprite(colonSurface, 1); // Colon sprite is also a single frame
    }



    void Game::Shutdown() {}
    
    Sprite background (new Surface("assets/background-export.png"), 1);


    

    void Game::Tick(float deltaTime)
    {
        if (gameTimeRemaining > 0) {
            gameTimeRemaining -= deltaTime / 1000;
            if (gameTimeRemaining < 0) gameTimeRemaining = 0; // Prevent it from going negative
        }

        int currentScore = scoreSystem.GetScore();

        //std::cout << "DeltaTime: " << deltaTime << ", GameTimeRemaining: " << gameTimeRemaining << std::endl;

        background.Draw(screen, ((800 / 2) - 519), ((512 / 2) - 680));
        screen->Plot((int)x, (int)y, 0xffffff);

        switch (currentState) {
        case GameState::START:
            // Handle start state, e.g., display start screen
            DrawStartScreen(screen);
            mouseHandler->DrawCursor(mousex, mousey);
            break;
        case GameState::PLAYING:
            // Existing gameplay logic here
            // Wrap the gameplay logic with the PLAYING state check
            player.Move(deltaTime);
            player.Draw(screen);
            for (auto& animatedSprite : animatedSprites) {
                animatedSprite.Update(deltaTime);

            }
            sushiManager.Update(deltaTime, gameTimeRemaining);
            sushiManager.UpdateSushi(deltaTime);
            sushiManager.DrawSushi(screen);
            sushiManager.CheckCollisions(player);
            
            DrawScore(screen, currentScore, 10, 10);
            DrawGameTimer(screen, static_cast<int>(gameTimeRemaining), 650, 10);
            player.Update(deltaTime);
            if (gameTimeRemaining <= 0) {
                EndGame();
            }
            // Additional gameplay handling...
            break;
        case GameState::END:
            // Handle end state, e.g., display end screen and score
            DrawEndScreen(screen);
            mouseHandler->DrawCursor(mousex, mousey);
            break;
        }
        

    }
};