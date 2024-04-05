#include "game.h" // Game class and game logic
#include "surface.h" // Surface class for rendering
#include "template.h" // Template utilities
#include "animation.h" // Animation and AnimatedSprite classes
#include "Player.h" // Player class for player-related functionality
#include "MouseHandler.h" // MouseHandler class for mouse interaction
#include "SushiManager.h" // SushiManager class for managing sushi objects
#include "ScoreSystem.h" // ScoreSystem class for tracking and displaying score
#include <windows.h> // Windows-specific headers for system calls
#include <iostream> // Standard I/O
#include <vector> // Standard vector container
#include <cstring> // C-style string functions
#include <string> // C++ string class
#include <cstdlib> // Standard library for rand(), srand()
#include <ctime>   // Time functions

namespace Tmpl8
{

    // Player sprites for different states
    Sprite* playerSpriteRight = new Sprite(new Surface("assets/run.png"), 4);
    Sprite* playerSpriteLeft = new Sprite(new Surface("assets/run-left.png"), 4);
    Sprite* playerSpriteIdle = new Sprite(new Surface("assets/idle.png"), 5);
    Sprite MouseCursor(new Surface("assets/pointer.png"), 1);
    Sprite* scorePrefixSprite = new Sprite(new Surface("assets/score.png"), 1);

    // Array for digit sprites (0-9, plus a colon for displaying time)
    Sprite* digitSprites[11];

    // Draws a single digit on a surface with scaling
    void DrawDigitScaled(Surface* surface, int digit, int posX, int posY, int width, int height) {
        if (digit >= 0 && digit < 10) {
            digitSprites[digit]->DrawScaled(posX, posY, width, height, surface);
        }
    }

    // Renders game time in minutes:seconds format
    void DrawGameTimer(Surface* surface, int gameTimeSeconds, int posX, int posY) {
        float scaleFactor = 0.4f; // Scale factor for size adjustment
        int minutes = gameTimeSeconds / 60;
        int seconds = gameTimeSeconds % 60;

        int originalDigitWidth = 64; // Original width of digit sprites
        int originalDigitHeight = 64; // Original height of digit sprites
        int scaledWidth = static_cast<int>(originalDigitWidth * scaleFactor);
        int scaledHeight = static_cast<int>(originalDigitHeight * scaleFactor);
        int spacing = 0; // Spacing between characters

        // Drawing minutes and colon
        DrawDigitScaled(surface, minutes / 10, posX, posY, scaledWidth, scaledHeight);
        DrawDigitScaled(surface, minutes % 10, posX + scaledWidth + spacing, posY, scaledWidth, scaledHeight);
        digitSprites[10]->DrawScaled(posX + 2 * (scaledWidth + spacing), posY, scaledWidth, scaledHeight, surface);

        // Drawing seconds
        DrawDigitScaled(surface, seconds / 10, posX + 2 * (scaledWidth + spacing) + scaledWidth, posY, scaledWidth, scaledHeight);
        DrawDigitScaled(surface, seconds % 10, posX + 3 * (scaledWidth + spacing) + scaledWidth, posY, scaledWidth, scaledHeight);
    }

    // Draws the current score on the surface
    void DrawScore(Surface* surface, int score, int posX, int posY) {
        scorePrefixSprite->Draw(surface, posX, posY); // Drawing "Score: " prefix
        posX += scorePrefixSprite->GetWidth() + 10; // Adjust position for digits

        float scaleFactor = 0.4f; // Digit scaling factor
        int scaledWidth = static_cast<int>(64 * scaleFactor); // Scaled width for digits
        int scaledHeight = static_cast<int>(64 * scaleFactor); // Scaled height for digits
        int spacing = -5; // Spacing between digits

        std::string scoreStr = std::to_string(score);
        for (char digit : scoreStr) {
            int digitIndex = digit - '0'; // Convert character to integer index
            digitSprites[digitIndex]->DrawScaled(posX, posY, scaledWidth, scaledHeight, surface);
            posX += scaledWidth + spacing; // Adjust position for next digit
        }
    }

    std::vector<AnimatedSprite> animatedSprites; // Container for animated sprites

    float x = 400, y = 256; // Player initial position

    ScoreSystem scoreSystem; // Score system instance

    Player player = Player(); // Player instance

    // Starts the game, setting initial game state
    void Game::StartGame() {
        currentState = GameState::PLAYING;
        gameTimeRemaining = 180.0f; // Game duration in seconds
        scoreSystem.ResetScore();
        player.ResetPlayer();
    }

    // Ends the current game session
    void Game::EndGame() {
        sushiManager.ClearSushi();
        currentState = GameState::END;
        // Actions to perform at game end
    }

    // Returns to the game menu
    void Game::BackToMenu() {
        currentState = GameState::START;
        // Reset game state for new session
    }

    // Draws the game's start screen
    void Game::DrawStartScreen(Surface* surface) {
        if (titleSprite) {
            int titleX = (ScreenWidth - 320) / 2; // Center title
            int titleMarginTop = 50; // Margin from top
            titleSprite->Draw(surface, titleX, titleMarginTop);
        }

        if (playButtonSprite) {
            int playButtonX = (ScreenWidth - 64) / 2; // Center play button
            int playButtonMarginBottom = 100; // Margin from bottom
            int playButtonY = ScreenHeight - 64 - playButtonMarginBottom; // Apply margin
            playButtonSprite->Draw(surface, playButtonX, playButtonY);
        }
    }

    // Draws the game's end screen
    void Game::DrawEndScreen(Surface* surface) {
        if (titleSprite) {
            int titleX = (ScreenWidth - 320) / 2; // Center title
            int titleY = 50; // Margin from top
            titleSprite->Draw(surface, titleX, titleY);
        }

        if (backToMenuButtonSprite) {
            backToMenuButtonSprite->Draw(surface, playButtonRect.x, playButtonRect.y);
        }

        int scoreX = (ScreenWidth - (10 * 64 * 0.4f)) / 2; // Approximate centering for score
        int scoreY = 200; // Position below title
        DrawScore(surface, scoreSystem.GetScore(), scoreX, scoreY);
    }


    // Responds to mouse button clicks within the game window.
    void Game::MouseDown(int button) {
        // Check if the left mouse button was clicked.
        if (button == 1) {
            // Determine the game's current state to decide the next action.
            switch (currentState) {
            case GameState::START:
                // In the START state, check if the click is within the play button's area.
                // If so, initiate game start.
                if (mousex >= playButtonRect.x && mousex <= (playButtonRect.x + playButtonRect.w) &&
                    mousey >= playButtonRect.y && mousey <= (playButtonRect.y + playButtonRect.h)) {
                    StartGame();
                }
                break;
            case GameState::END:
                // In the END state, check if the click is within the restart button's area.
                // If so, reset the game to its initial state or menu.
                if (mousex >= restartButtonRect.x && mousex <= (restartButtonRect.x + restartButtonRect.w) &&
                    mousey >= restartButtonRect.y && mousey <= (restartButtonRect.y + restartButtonRect.h)) {
                    BackToMenu();
                }
                break;
                // GameState::PLAYING does not need mouse interaction handling here.
            }
        }
    }


    // Initializes the game, setting up sprites, the game state, and other initial settings.
    void Game::Init() {
        srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator.

        // Assign predefined sprites to the player character for different states.
        player.SetSpriteLeft(playerSpriteLeft);
        player.SetSpriteRight(playerSpriteRight);
        player.SetSpriteIdle(playerSpriteIdle);

        // Initialize the mouse handler for cursor interaction.
        mouseHandler = new MouseHandler(screen);

        // Populate the animatedSprites vector with sprites for animation.
        animatedSprites.push_back(AnimatedSprite(playerSpriteRight, 4, 150));
        animatedSprites.push_back(AnimatedSprite(playerSpriteLeft, 4, 150));
        animatedSprites.push_back(AnimatedSprite(playerSpriteIdle, 5, 150));

        // Load sprites for UI components like the title and play button.
        titleSprite = new Sprite(new Surface("assets/title.png"), 1);
        playButtonSprite = new Sprite(new Surface("assets/play.png"), 1);
        backToMenuButtonSprite = new Sprite(new Surface("assets/back.png"), 1);

        // Define interactive areas for the UI, specifically for the play and restart buttons.
        int playButtonMarginBottom = 100; // Set the bottom margin for the play button.
        playButtonRect = { (ScreenWidth - 64) / 2, ScreenHeight - 64 - playButtonMarginBottom, 64, 64 };
        restartButtonRect = { (ScreenWidth - 64) / 2, ScreenHeight - 64 - playButtonMarginBottom, 64, 64 };

        // Load digit sprites for use in score display and timer.
        for (int i = 0; i < 10; ++i) {
            std::string filePath = "assets/digit/" + std::to_string(i) + ".png";
            std::vector<char> filePathCStr(filePath.c_str(), filePath.c_str() + filePath.size() + 1);
            Surface* digitSurface = new Surface(&filePathCStr[0]);
            digitSprites[i] = new Sprite(digitSurface, 1);
        }

        // Load the sprite for the colon character, used in displaying time.
        std::string colonPath = "assets/digit/semicolon.png";
        std::vector<char> colonPathCStr(colonPath.c_str(), colonPath.c_str() + colonPath.size() + 1);
        Surface* colonSurface = new Surface(&colonPathCStr[0]);
        digitSprites[10] = new Sprite(colonSurface, 1);
    }

    // Cleans up and releases resources when the game is closing.
    void Game::Shutdown() {
        // This function would include cleanup logic, but is not needed.
    }

    Sprite background (new Surface("assets/background-export.png"), 1);

    void Game::Tick(float deltaTime)
    {
        // Calculate the time remaining in the game session.
        if (gameTimeRemaining > 0) {
            gameTimeRemaining -= deltaTime / 1000;
            if (gameTimeRemaining < 0) gameTimeRemaining = 0; // Prevent it from going negative
        }

        // Get the current score from the score system.
        int currentScore = scoreSystem.GetScore();

        // Draw the game background
        background.Draw(screen, ((800 / 2) - 519), ((512 / 2) - 680));

        // Handle game state-specific logic
        switch (currentState) {
        case GameState::START:
            // Handle start state, e.g., display start screen
            DrawStartScreen(screen);
            mouseHandler->DrawCursor(mousex, mousey);
            break;
        case GameState::PLAYING:
            // Existing gameplay logic here
            // Wrap the gameplay logic with the PLAYING state check
            // Make sure to update and draw the player, sushi, and other game elements
            player.Move(deltaTime);
            player.Draw(screen);
            for (auto& animatedSprite : animatedSprites) {
                animatedSprite.Update(deltaTime);

            }
            sushiManager.Update(deltaTime, gameTimeRemaining);
            sushiManager.UpdateSushi(deltaTime);
            sushiManager.DrawSushi(screen);
            sushiManager.CheckCollisions(player);
            
            // Draw the score and game timer
            DrawScore(screen, currentScore, 10, 10);
            DrawGameTimer(screen, static_cast<int>(gameTimeRemaining), 650, 10);
            player.Update(deltaTime);
            // Check if the game time has run out, and end the game if so.
            if (gameTimeRemaining <= 0) {
                EndGame();
            }
            break;
        case GameState::END:
            // Handle end state, e.g., display end screen and score
            DrawEndScreen(screen);
            mouseHandler->DrawCursor(mousex, mousey);
            break;
        }
        

    }
};