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
        void SetSpeed(float speed) { this->speed = speed; }
        void resetSpeed() { speed = 0.2f; }

        // New methods to set sprites from outside
        void SetSprite(Sprite* sprite);
        void SetSpriteLeft(Sprite* spriteLeft);
        void SetSpriteRight(Sprite* spriteRight);
        void SetSpriteIdle(Sprite* spriteIdle);
        bool CollidesWith(const Sushi& sushi);


    private:
        vec2 position;
        float width = 64, height = 64;
        float speed;
        int orientation;
        bool idle;


        // Store sprite pointers instead of static instances
        Sprite* spriteLeft;
        Sprite* spriteRight;
        Sprite* spriteIdle;

    };

} // namespace Tmpl8