#include "animation.h" // Including the header file for the Animation and AnimatedSprite classes.

namespace Tmpl8 {

    // Constructor for the Animation class. It sets up an animation with a defined number of frames and animation speed.
    Animation::Animation(int frames, float speed)
        : frameCount(frames), animationTimeLeft(speed), animationSpeed(speed), currentFrame(0) {}

    // This function updates the current frame of an animation based on the time passed since the last update.
    void Animation::Update(float deltaTime) {
        animationTimeLeft -= deltaTime; // Decrease time left by deltaTime.
        while (animationTimeLeft <= 0.0) {
            currentFrame = (currentFrame + 1) % frameCount; // Move to the next frame, or loop back to the start if at the end.
            animationTimeLeft += animationSpeed; // Reset the time left for the next frame change.
        }
    }

    // Constructor for the AnimatedSprite class. It associates a sprite with an animation.
    AnimatedSprite::AnimatedSprite(Sprite* spr, int frames, float speed)
        : sprite(spr), animation(frames, speed) {}

    // This function updates the animation for the sprite based on the elapsed time.
    void AnimatedSprite::Update(float deltaTime) {
        animation.Update(deltaTime); // Call the update function of the animation object.
        sprite->SetFrame(animation.currentFrame); // Set the sprite's current frame to match the animation's current frame.
    }

} // namespace Tmpl8
