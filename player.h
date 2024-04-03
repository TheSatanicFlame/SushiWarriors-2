// player.h
#pragma once
#include "surface.h"
#include "template.h"
#include "sushi.h"

namespace Tmpl8 {

    class Player {
    public:
        Player();

        void Move(float deltaTime);
        void Draw(Surface* screen);
        vec2 GetPosition() const { return position; }

        //speed controlls
        void SetSpeed(float newSpeed);
        void ResetSpeed() { speed = 0.2f; }
        float GetSpeed() { return speed; }

        // New methods to set sprites from outside
        void SetSprite(Sprite* sprite);
        void SetSpriteLeft(Sprite* spriteLeft);
        void SetSpriteRight(Sprite* spriteRight);
        void SetSpriteIdle(Sprite* spriteIdle);
        bool CollidesWith(const Sushi& sushi);
        void Update(float deltaTime);


    private:
        vec2 position;
        float width = 64, height = 64;
        int orientation;
        bool idle;
        float speed = 0.2f; // Default speed
        float originalSpeed = 0.2f; // Store the original speed for restoration
        float speedTimer = 0.0f; // Timer to track speed restoration


        // Store sprite pointers instead of static instances
        Sprite* spriteLeft;
        Sprite* spriteRight;
        Sprite* spriteIdle;

    };

} // namespace Tmpl8