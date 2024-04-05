#pragma once
#include "surface.h" // Surface class
#include "template.h" // Tmpl8 class
#include "sushi.h" // Sushi class

namespace Tmpl8 {

    class Player {
    public:
        Player(); // Constructor

        void Move(float deltaTime); // Move the player
        void Draw(Surface* screen); // Draw the player
        vec2 GetPosition() const { return position; } // Get the player's position

        //speed controlls
        void SetSpeed(float newSpeed); // Set the player's speed
        void ResetSpeed() { speed = 0.2f; } // Reset the player's speed
        float GetSpeed() { return speed; } // Get the player's speed

        // New methods to set sprites from outside
        void SetSprite(Sprite* sprite); // Set the player's sprite
        void SetSpriteLeft(Sprite* spriteLeft); // Set the player's sprite when moving left
        void SetSpriteRight(Sprite* spriteRight); // Set the player's sprite when moving right
        void SetSpriteIdle(Sprite* spriteIdle); // Set the player's sprite when idle
        bool CollidesWith(const Sushi& sushi); // Check if the player collides with a sushi
        void Update(float deltaTime); // Update the player
        void ResetPlayer(); // Reset the player


    private:
        vec2 position; // Player's position
        float width = 64, height = 64; // Player's width and height
        int orientation; // Player's orientation
        bool idle; // Player's idle state
        float speed = 0.2f; // Default speed
        float originalSpeed = 0.2f; // Store the original speed for restoration
        float speedTimer = 0.0f; // Timer to track speed restoration


        // Store sprite pointers instead of static instances
        Sprite* spriteLeft; // Sprite when moving left
        Sprite* spriteRight; // Sprite when moving right
        Sprite* spriteIdle; // Sprite when idle

    };

} // namespace Tmpl8