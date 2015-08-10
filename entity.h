#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <vector>
#include "animation.h"
#include "surface.h"

class GameEntity{
public:
    GameEntity();
    virtual ~GameEntity();

protected:
    GameAnimation animControl;
    SDL_Surface *surfEntity;

public:
    static std::vector <GameEntity*> entityList;

    float x;
    float y;

    bool isRender;

    int width;
    int height;

    int animState;

public:
    virtual bool load(char *file, int width, int height, int maxFrames);

    virtual bool load(char *file, int width, int height, int maxFrames, bool oscillate);

    virtual bool load(char *file, int width, int height, int maxFrames, bool oscillate, int frameRate);

    virtual void loop();

    virtual void render(SDL_Surface *displaySurface);

    virtual void cleanup();

};

#endif // ENTITY_H_INCLUDED
