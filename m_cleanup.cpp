#include "application.h"

void GameMain::mainCleanup()
{

    SDL_FreeSurface(displaySurface);
    SDL_FreeSurface(mapSurface);
    SDL_FreeSurface(menuBack);
    SDL_FreeSurface(menuLevels);
    SDL_FreeSurface(bScore);
    SDL_FreeSurface(pScore);

    for(int i = 0; i < GameEntity::entityList.size(); i++)
    {
        if(!GameEntity::entityList[i]) continue;

        GameEntity::entityList[i]->cleanup();
    }

    GameEntity::entityList.clear();

    SDL_Quit();
}
