// sushi.h
#pragma once
#include "template.h"
#include "surface.h"

namespace Tmpl8 {

    enum SushiType { SPEED_UP, SPEED_DOWN, SPEED_RESET, SCORE };

    class Sushi {
    public:
        Sushi(SushiType type, vec2 position, Sprite* sprite, int points)
            : type(type), position(position), sprite(sprite), points(points) {}

        void Update(float deltaTime);
        void Draw(Surface* screen);
        SushiType GetType() const { return type; }
        int GetPoints() const { return points; }
        vec2 GetPosition() const;
        Sprite* GetSprite() const;

    private:
        SushiType type;
        vec2 position;
        Sprite* sprite;
        int points; // Points this sushi awards
        float speed = 100.0f; // Movement speed in pixels per second
    };

} // namespace Tmpl8
