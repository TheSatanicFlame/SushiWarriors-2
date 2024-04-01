#include "game.h"
#include "surface.h"
#include "template.h"
#include <windows.h>
#include <iostream>
#include <vector>

namespace Tmpl8
{
    Sprite playerSpriteRight(new Surface("assets/run.png"), 4);

    Sprite PlayerSpriteLeft(new Surface("assets/run-left.png"), 4);

    Sprite PlayerSpriteIdle(new Surface("assets/idle.png"), 5);
    
    
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

                //make sprite face left
                orientation = 1;
                idle = false;
                
            }
            else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44)) {
                position.x += speed * deltaTime;

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

    class Animation {
    public:
        int frameCount;
        float animationTimeLeft;
        float animationSpeed;
        int currentFrame;

        Animation(int frames, float speed) : frameCount(frames), animationTimeLeft(speed), animationSpeed(speed), currentFrame(0) {}

        void Update(float deltaTime) {
            animationTimeLeft -= deltaTime;
            while (animationTimeLeft <= 0.0) {
                currentFrame = (currentFrame + 1) % frameCount;
                animationTimeLeft += animationSpeed;
            }
        }
    };
    
    class AnimatedSprite {
    public:
        Sprite* sprite;
        Animation animation;

        AnimatedSprite(Sprite* spr, int frames, float speed) : sprite(spr), animation(frames, speed) {}

        void Update(float deltaTime) {
            animation.Update(deltaTime);
            // Set animation frame for the sprite
            sprite->SetFrame(animation.currentFrame);
        }
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
    
    int FrameCounterWalking = 0;
    int FrameCounterIdle = 0;
    int TickCounter = 0;

    void Game::Tick(float deltaTime)
    {
        background.Draw(screen, ((800 / 2) - 519), ((512 / 2) - 680));
        screen->Line(mousex, 0, mousex, 511, 0xff0000);
        screen->Line(0, mousey, 799, mousey, 0xff0000);
        float dx = x - mousex, dy = y - mousey;
        float dist = sqrtf(dx * dx + dy * dy);
        if (dist < 50)
            x += dx / dist, y += dy / dist;
        screen->Plot((int)x, (int)y, 0xffffff);
        player.Move(deltaTime);
        player.Draw(screen);
        TickCounter++;
        for (auto& animatedSprite : animatedSprites) {
            animatedSprite.Update(deltaTime);
        }
    }
};