#include "animation.h" // Include the class declarations

namespace Tmpl8 {

    // Constructs an Animation with a specified number of frames and speed
    Animation::Animation(int frames, float speed)
        : frameCount(frames), animationTimeLeft(speed), animationSpeed(speed), currentFrame(0) {}

    // Updates the animation frame based on the elapsed time (deltaTime)
    void Animation::Update(float deltaTime) {
        animationTimeLeft -= deltaTime;
        while (animationTimeLeft <= 0.0) {
            currentFrame = (currentFrame + 1) % frameCount; // Loop the animation
            animationTimeLeft += animationSpeed; // Reset the timer
        }
    }

    // Constructs an AnimatedSprite with a given sprite, frame count, and speed
    AnimatedSprite::AnimatedSprite(Sprite* spr, int frames, float speed)
        : sprite(spr), animation(frames, speed) {}

    // Updates the sprite's animation
    void AnimatedSprite::Update(float deltaTime) {
        animation.Update(deltaTime); // Update the animation frame
        sprite->SetFrame(animation.currentFrame); // Update the sprite to the current frame
    }

} // namespace Tmpl8