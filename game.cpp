#include "game.h"
#include "surface.h"
#include "template.h"
#include "animation.h"
#include <windows.h>
#include <iostream>
#include <vector>

namespace Tmpl8
{
    Sprite playerSpriteRight(new Surface("assets/run.png"), 4);

    Sprite PlayerSpriteLeft(new Surface("assets/run-left.png"), 4);

    Sprite PlayerSpriteIdle(new Surface("assets/idle.png"), 5);

    Sprite MouseCursor(new Surface("assets/pointer.png"), 1);
    
    
    
    class Player
    {
    public:

        Player() {
			position = vec2(400 - 32, 360);
			speed = 0.2;
		}

        void Move(float deltaTime) {
            if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41)) {
                position.x -= speed * deltaTime;
                if (position.x < 0) {
					position.x = 0;
				}

                //make sprite face left
                orientation = 1;
                idle = false;
                
            }
            else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44)) {
                position.x += speed * deltaTime;
                if (position.x > 800 - 64) {
                    position.x = 800 - 64;
                }

                //make sprite face right
                orientation = 0;
                idle = false;
			}
             else {
				idle = true;
			}
        }

        void Draw(Surface* screen) {
            if (idle) {
                PlayerSpriteIdle.Draw(screen, position.x, position.y);

            } else {
                if (orientation == 0) {
                    playerSpriteRight.Draw(screen, position.x, position.y);
                }
                else {
                    PlayerSpriteLeft.Draw(screen, position.x, position.y);
                }
            }
            
		}
        
    private:
        vec2 position;
		float speed;
        int orientation;
        bool idle;
    };


    std::vector<AnimatedSprite> animatedSprites;

    float x = 400, y = 256;

    Player player = Player();

    void Game::Init() {
        animatedSprites.push_back(AnimatedSprite(&playerSpriteRight, 4, 100));
        animatedSprites.push_back(AnimatedSprite(&PlayerSpriteLeft, 4, 100));
        animatedSprites.push_back(AnimatedSprite(&PlayerSpriteIdle, 5, 120));
    }



    void Game::Shutdown() {}
    
    Sprite background (new Surface("assets/background-export.png"), 1);
    

    void Game::Tick(float deltaTime)
    {
        background.Draw(screen, ((800 / 2) - 519), ((512 / 2) - 680));
        screen->Plot((int)x, (int)y, 0xffffff);
        player.Move(deltaTime);
        player.Draw(screen);
        for (auto& animatedSprite : animatedSprites) {
            animatedSprite.Update(deltaTime);

        }
        MouseCursor.DrawScaled(mousex, mousey, 32, 32, screen);
    }
};