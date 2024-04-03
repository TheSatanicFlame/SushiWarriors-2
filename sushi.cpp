// sushi.cpp
#include "sushi.h"

namespace Tmpl8 {

    void Sushi::Update(float deltaTime) {
        // Move the sushi down by increasing its y position based on the speed
        position.y += speed * deltaTime / 1000;
    }

    void Sushi::Draw(Surface* screen) {
        if (sprite != nullptr) {
            sprite->Draw(screen, static_cast<int>(position.x), static_cast<int>(position.y));
        }
    }

    vec2 Sushi::GetPosition() const {
        return position;
    }

    Sprite* Sushi::GetSprite() const {
        return sprite;
    }

    


} // namespace Tmpl8