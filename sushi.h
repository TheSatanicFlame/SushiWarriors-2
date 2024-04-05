#pragma once
#include "template.h" // Include template.h for the template class
#include "surface.h" // Include surface.h for the Surface class

namespace Tmpl8 {

    enum SushiType {DEFAULT, SPEED_UP, SPEED_DOWN, SPEED_RESET, SCORE }; // Enum for sushi types

    class Sushi { // Sushi class
    public:
        Sushi(SushiType type, vec2 position, Sprite* sprite, int points)
            : type(type), position(position), sprite(sprite), points(points) {} // Constructor

        void Update(float deltaTime); // Update the sushi
        void Draw(Surface* screen); // Draw the sushi
        SushiType GetType() const { return type; } // Get the sushi type
        int GetPoints() const { return points; } // Get the points this sushi awards
        vec2 GetPosition() const; // Get the sushi's position
        Sprite* GetSprite() const; // Get the sushi's sprite

    private:
        SushiType type; // Sushi type
        vec2 position; // Position of the sushi
        Sprite* sprite; // Sprite of the sushi
        int points; // Points this sushi awards
        float speed = 100.0f; // Movement speed in pixels per second
    };

} // namespace Tmpl8
