// sushi.cpp
#include "sushi.h"

namespace Tmpl8 {

    void Sushi::Update(float deltaTime) { // Update the sushi
        // Move the sushi down by increasing its y position based on the speed
        position.y += speed * deltaTime / 1000; // deltaTime is in milliseconds, so divide by 1000 to get seconds
    }

    void Sushi::Draw(Surface* screen) { // Draw the sushi
        if (sprite != nullptr) { // If the sprite is not null
            sprite->Draw(screen, static_cast<int>(position.x), static_cast<int>(position.y)); // Draw the sprite at the sushi's position
        }
    }

    vec2 Sushi::GetPosition() const { // Get the sushi's position
        return position;
    }

    Sprite* Sushi::GetSprite() const { // Get the sushi's sprite
        return sprite;
    }

    


} // namespace Tmpl8