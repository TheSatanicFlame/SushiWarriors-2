#pragma once
#include "SushiManager.h"
#include "MouseHandler.h"
#include "surface.h"
#include "template.h"
#include "SDL.h"


namespace Tmpl8 {

class Surface;

enum class GameState {
	START,
	PLAYING,
	END
};

class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown(int button);
	void MouseMove(int x, int y) { mousex = x, mousey = y; }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
	void StartGame();
	void BackToMenu();
	void EndGame();
	int mousex, mousey; // mouse position
	void DrawStartScreen(Surface* screen);
	void DrawEndScreen(Surface* screen);
private:
	Surface* screen;
	SushiManager sushiManager;
	MouseHandler* mouseHandler;
	float gameTimeRemaining = 180.0f; // 180 seconds total game time
	GameState currentState = GameState::START; // Initial game state
	Sprite* titleSprite = nullptr;
	Sprite* playButtonSprite = nullptr;
	Sprite* backToMenuButtonSprite = nullptr;
	SDL_Rect playButtonRect; // Area for the play button
	SDL_Rect restartButtonRect; // Area for the restart button
};

}; // namespace Tmpl8