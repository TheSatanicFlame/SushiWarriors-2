#pragma once
#include "SushiManager.h" // Include the SushiManager class
#include "MouseHandler.h" // Include the MouseHandler class
#include "surface.h" // Include the Surface class
#include "template.h" // Include the template class
#include "SDL.h" // Include the SDL library


namespace Tmpl8 {

class Surface;
// Define the game state
enum class GameState {
	START,
	PLAYING,
	END
};
// Define the Game class
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; } // Set the target surface
	void Init(); // Initialize the game
	void Shutdown(); // Shutdown the game
	void Tick( float deltaTime ); // Update the game
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown(int button); // Detect mouse button presses
	void MouseMove(int x, int y) { mousex = x, mousey = y; } // Detect mouse movement
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
	void StartGame(); // Start the game
	void BackToMenu(); // Go back to the menu
	void EndGame(); // End the game
	int mousex, mousey; // mouse position
	void DrawStartScreen(Surface* screen); // Draw the start screen
	void DrawEndScreen(Surface* screen); // Draw the end screen
private:
	Surface* screen; // Pointer to the screen surface
	SushiManager sushiManager; // Sushi manager
	MouseHandler* mouseHandler; // Mouse handler
	float gameTimeRemaining = 180.0f; // 180 seconds total game time
	GameState currentState = GameState::START; // Initial game state
	Sprite* titleSprite = nullptr; // Title sprite
	Sprite* playButtonSprite = nullptr; // Play button sprite
	Sprite* backToMenuButtonSprite = nullptr; // Back to menu button sprite
	SDL_Rect playButtonRect; // Area for the play button
	SDL_Rect restartButtonRect; // Area for the restart button
};

}; // namespace Tmpl8