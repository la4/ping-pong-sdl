#include "application.h"

void GameMain::mainRender()
{
    if(gameStatus == SF_MENU)
    {
        GameSurface::draw(displaySurface, menuBack, 0, 0);
        for(int i = 0; i < 5; i++)
        {
            GameSurface::draw(displaySurface, menuLevels, 100 + i * 100 + i * 50, WHEIGHT / 2 + 10, 0, i * 100, 100, 100);
        }
    }
    else
    {
        GameSurface::draw(displaySurface, mapSurface, 0, 0);
        GameSurface::draw(displaySurface, pScore, 423, 567, 0, 30 * pScoreNum, 18, 30);
        GameSurface::draw(displaySurface, bScore, 459, 567, 0, 30 * bScoreNum, 18, 30);
    }


    for(int i = 0; i < GameEntity::entityList.size(); i++)
    {
        if(!GameEntity::entityList[i]) continue;

        GameEntity::entityList[i]->render(displaySurface);
    }

    SDL_Flip(displaySurface);
}

