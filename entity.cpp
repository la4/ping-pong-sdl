#include "entity.h"

std::vector <GameEntity*> GameEntity::entityList; //статическа€ переменна€, требовала объ€влени€

GameEntity::GameEntity()
{
    surfEntity = NULL;

    x = y = 0.0f;

    width = height = 0;
    animState = 0;
    isRender = false;
}

GameEntity::~GameEntity()
{
}

bool GameEntity::load(char *file, int width, int height, int maxFrames)
{
    if((surfEntity = GameSurface::load(file)) == NULL)
    {
        return false;
    }

    GameSurface::makeTransparent(surfEntity, 255, 0, 255);
    this->width = width; //this - указатель на объект, который вызвал функцию
    this->height = height;

    animControl.maxFrames = maxFrames;

    return true;
}

bool GameEntity::load(char *file, int width, int height, int maxFrames, bool oscillate)
{
    if((surfEntity = GameSurface::load(file)) == NULL)
    {
        return false;
    }

    animControl.oscillate = oscillate;

    GameSurface::makeTransparent(surfEntity, 255, 0, 255);
    this->width = width; //this - указатель на объект, который вызвал функцию
    this->height = height;

    animControl.maxFrames = maxFrames;

    return true;
}


bool GameEntity::load(char *file, int width, int height, int maxFrames, bool oscillate, int frameRate)
{
    if((surfEntity = GameSurface::load(file)) == NULL)
    {
        return false;
    }

    animControl.oscillate = oscillate;
    animControl.frameRate = frameRate;

    GameSurface::makeTransparent(surfEntity, 255, 0, 255);
    this->width = width; //this - указатель на объект, который вызвал функцию
    this->height = height;

    animControl.maxFrames = maxFrames;

    return true;
}

void GameEntity::loop()
{
    animControl.onAnimate();
}

void GameEntity::render(SDL_Surface *displaySurface)
{
    if(surfEntity == NULL || displaySurface == NULL || !isRender) return;

    GameSurface::draw(displaySurface, surfEntity, x, y, animState * width, animControl.getCurrentFrame() * height, width, height);
}

void GameEntity::cleanup()
{
    if(surfEntity)
    {
        SDL_FreeSurface(surfEntity);
    }

    surfEntity = NULL;
}

