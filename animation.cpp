#include "animation.h"

GameAnimation::GameAnimation() {
    currentFrame = 0;
    maxFrames = 0;
    frameInc = 1;

    frameRate = 100; //Milliseconds
    oldTime = 0;

    oscillate = false;
}

void GameAnimation::onAnimate() {
    if(oldTime + frameRate > SDL_GetTicks()) return;

    oldTime = SDL_GetTicks();

    currentFrame += frameInc;

    if(oscillate)
    {
        if(frameInc > 0)
        {
            if(currentFrame >= maxFrames - 1)
            {
                frameInc = -frameInc;
            }
        }
        else
        {
            if(currentFrame <= 0)
            {
                frameInc = -frameInc;
            }
        }
    }
    else
    {
        if(currentFrame >= maxFrames)
        {
            currentFrame = 0;
        }
    }
}

void GameAnimation::setFrameRate(int rate) {
    frameRate = rate;
}

void GameAnimation::setCurrentFrame(int frame) {
    if(frame < 0 || frame >= maxFrames) return;

    currentFrame = frame;
}

int GameAnimation::getCurrentFrame() {
    return currentFrame;
}
