#pragma once // Ensures the file is included only once during compilation
#include "surface.h" // Include the Surface class definition

namespace Tmpl8 {

    // Defines an animation sequence
    class Animation {
    public:
        int frameCount; // Number of frames in the animation
        float animationTimeLeft; // Time left until the next frame
        float animationSpeed; // Speed of the animation
        int currentFrame; // Index of the current frame

        // Constructor
        Animation(int frames, float speed);
        // Updates the animation based on delta time
        void Update(float deltaTime);
    };

    // Connects a Sprite with an Animation, allowing the sprite to be animated
    class AnimatedSprite {
    public:
        Sprite* sprite; // Pointer to the sprite
        Animation animation; // The animation controlling the sprite's frames

        // Constructor
        AnimatedSprite(Sprite* spr, int frames, float speed);
        // Updates the animation and the sprite's current frame
        void Update(float deltaTime);
    };

} // namespace Tmpl8