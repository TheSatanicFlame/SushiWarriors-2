#pragma once
#include "SushiManager.h"
#include "MouseHandler.h"
#include "surface.h"

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove(int x, int y) { mousex = x, mousey = y; }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
	int mousex, mousey; // mouse position
private:
	Surface* screen;
	SushiManager sushiManager;
	MouseHandler* mouseHandler;
	float gameTimeRemaining = 180.0f; // 180 seconds total game time
};

}; // namespace Tmpl8