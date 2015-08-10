#include "application.h"

void GameMain::processEvent(SDL_Event *event)
{
    GameEvent::processEvent(event);
}

void GameMain::exitApp()
{
    running = false;
}

void GameMain::keyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
    {
    case SDLK_ESCAPE:
        {
            exitApp();
            break;
        }
    case SDLK_LEFT:
        {
            if(gameStatus != SF_RUNNING) break;

            priorityKey = false;
            lKeyStatus = true;
            break;
        }
    case SDLK_RIGHT:
        {
            if(gameStatus != SF_RUNNING) break;

            priorityKey = true;;
            rKeyStatus = true;
            break;
        }
    }
}

void GameMain::keyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
    {
    case SDLK_LEFT:
        {
            if(gameStatus != SF_RUNNING) break;
            lKeyStatus = false;
            break;
        }
    case SDLK_RIGHT:
        {
            if(gameStatus != SF_RUNNING) break;
            rKeyStatus = false;
            break;
        }
    }
}

void GameMain::lButtonUp(int mX, int mY)
{
    if(gameStatus != SF_MENU) return;


    if(mY >= WHEIGHT / 2 + 10 && mY <= WHEIGHT / 2 + 110)
    {
        for(int i = 0; i < 5; i++)
        {
            if(mX >= 100 + i * 100 + i * 50 && mX <= 100 + (i + 1) * 100 + i * 50)
            {
                gameStatus = SF_RUNNING;
                gameLevel = i + 1;
                ballFrameRate = 8 - i * 2;

                if(gameLevel == 5)
                {
                    ballFrameRate = 1;
                }
                for(int i = 0; i < PARTNUM; i++)
                {
                    particles[i].isRender = true;
                }

                playerRacket.isRender = true;
                botRacket.isRender = true;
                ball.isRender = true;
                break;
            }

        }

    }
}
