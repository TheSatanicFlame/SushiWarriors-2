// Player.cpp
#include "player.h"
#include "windows.h"
#include "sushi.h"

namespace Tmpl8 {

    Player::Player() : position(400 - 32, 360), speed(0.2f), orientation(0), idle(true),
        spriteLeft(nullptr), spriteRight(nullptr), spriteIdle(nullptr) {} // Initialize the sprite pointers to null

    void Player::Move(float deltaTime) { 
        // handle player movement
        // Move the player to the left
        if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41)) {
            position.x -= speed * deltaTime;
            if (position.x < 0) {
                position.x = 0;
            }

            //make sprite face left
            orientation = 1;
            idle = false;

        }
        // Move the player to the right
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
        // Check if the player's bounding box intersects with the sushi's bounding box
        vec2 sushiPos = sushi.GetPosition();
        Sprite* sushiSprite = sushi.GetSprite();
        int sushiWidth = sushiSprite->GetWidth();
        int sushiHeight = sushiSprite->GetHeight();

        bool collisionX = position.x + width >= sushiPos.x && sushiPos.x + sushiWidth >= position.x;
        bool collisionY = position.y + height >= sushiPos.y && sushiPos.y + sushiHeight >= position.y;

        return collisionX && collisionY;
    }

    void Player::Draw(Surface* screen) {
        // Draw the player sprite
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

    void Player::Update(float deltaTime) {
        // Update the player's position
        if (speedTimer > 0) {
            speedTimer -= deltaTime / 1000;
            if (speedTimer <= 0) {
                SetSpeed(originalSpeed); // Restore original speed when timer expires
            }
        }
    }

    void Player::ResetPlayer()
    {
        // Reset the player's position and speed
        position = vec2(400 - 32, 360);
		speed = 0.2f;
		orientation = 0;
		idle = true;
    }

    void Player::SetSpeed(float newSpeed) {
        // Set the player's speed
        speed = newSpeed;
        if (newSpeed != originalSpeed) {
            speedTimer = 10.0f; // Start countdown to reset speed if it's a temporary change
        }
        else {
            speedTimer = 0.0f; // Cancel timer if setting to original speed
        }
    }



    // Implement the new methods
    void Player::SetSprite(Sprite* sprite) { /* Assign to the appropriate member variable */ }
    void Player::SetSpriteLeft(Sprite* spriteLeft) { this->spriteLeft = spriteLeft; }
    void Player::SetSpriteRight(Sprite* spriteRight) { this->spriteRight = spriteRight; }
    void Player::SetSpriteIdle(Sprite* spriteIdle) { this->spriteIdle = spriteIdle; }

} // namespace Tmpl8