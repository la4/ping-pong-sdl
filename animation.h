#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <SDL/SDL.h>

class GameAnimation {
private:
    int currentFrame;
    int frameInc;

    long oldTime;

public:
    int frameRate; //Milliseconds
    int maxFrames;
    bool oscillate;

    GameAnimation();
    void onAnimate();

    void setFrameRate(int rate);
    void setCurrentFrame(int frame);
    int getCurrentFrame();
};

#endif // ANIMATION_H_INCLUDED
