// Player.cpp
#include "player.h"
#include "windows.h"
#include "sushi.h"

namespace Tmpl8 {

    Player::Player() : position(400 - 32, 360), speed(0.2f), orientation(0), idle(true),
        spriteLeft(nullptr), spriteRight(nullptr), spriteIdle(nullptr) {}

    void Player::Move(float deltaTime) {
        // Implementation remains the same...
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

    bool Player::CollidesWith(const Sushi& sushi) {
        // Simple bounding box collision detection
        // Assuming Player class has position, width, and height members
        vec2 sushiPos = sushi.GetPosition();
        Sprite* sushiSprite = sushi.GetSprite();
        int sushiWidth = sushiSprite->GetWidth();
        int sushiHeight = sushiSprite->GetHeight();

        bool collisionX = position.x + width >= sushiPos.x && sushiPos.x + sushiWidth >= position.x;
        bool collisionY = position.y + height >= sushiPos.y && sushiPos.y + sushiHeight >= position.y;

        return collisionX && collisionY;
    }

    void Player::Draw(Surface* screen) {
        // Updated to use sprite pointers
        // Make sure to check if the pointers are not null
        if (spriteLeft && spriteRight && spriteIdle) {
            if (idle) {
				spriteIdle->Draw(screen, position.x, position.y);
			}
            else {
                if (orientation == 0) {
					spriteRight->Draw(screen, position.x, position.y);
				}
                else {
					spriteLeft->Draw(screen, position.x, position.y);
				}
			}
		}
    }



    // Implement the new methods
    void Player::SetSprite(Sprite* sprite) { /* Assign to the appropriate member variable */ }
    void Player::SetSpriteLeft(Sprite* spriteLeft) { this->spriteLeft = spriteLeft; }
    void Player::SetSpriteRight(Sprite* spriteRight) { this->spriteRight = spriteRight; }
    void Player::SetSpriteIdle(Sprite* spriteIdle) { this->spriteIdle = spriteIdle; }

} // namespace Tmpl8