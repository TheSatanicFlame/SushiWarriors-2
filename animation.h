#pragma once // Prevents multiple inclusions of this header file in a single compilation.
#include "surface.h" // Includes the definition for the Surface class, used here for drawing.

namespace Tmpl8 {

    // This class represents an animation, holding its properties like frame count and speed.
    class Animation {
    public:
        int frameCount; // Total number of frames in the animation sequence.
        float animationTimeLeft; // Remaining time (in seconds) before transitioning to the next frame.
        float animationSpeed; // Duration of each frame in seconds.
        int currentFrame; // The current frame being displayed in the animation sequence.

        // Initializes a new instance of the Animation class with specified frame count and speed.
        Animation(int frames, float speed);
        // Processes the animation frame updates based on the elapsed time since the last frame update.
        void Update(float deltaTime);
    };

    // This class associates a sprite (2D image) with an animation sequence, enabling animated sprites.
    class AnimatedSprite {
    public:
        Sprite* sprite; // Pointer to the sprite object that will be animated.
        Animation animation; // Animation object that controls the frame sequence and speed for the sprite.

        // Constructs an AnimatedSprite with a linked sprite object, number of frames, and animation speed.
        AnimatedSprite(Sprite* spr, int frames, float speed);
        // Updates the sprite's frame according to the animation, based on elapsed time.
        void Update(float deltaTime);
    };

} // namespace Tmpl8