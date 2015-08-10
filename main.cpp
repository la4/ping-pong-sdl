#include "application.h"

GameMain::GameMain()
{
    //System
    running = true;
    gameStatus = SF_MENU;
    gameLevel = 1;

    pScoreNum = 0;
    bScoreNum = 0;

    //Surfaces
    displaySurface = NULL;
    mapSurface = NULL;
    menuBack = NULL;
    menuLevels = NULL;
    bScore = NULL;
    pScore = NULL;

    //Enteties loop variables
    ballOldTime = 0;
    ballFrameRate = 0;
    for(int i = 0; i < PARTNUM; i++)
        isFree[i] = false;

    setRandBallX();
    ballVectorY = 2;
    do
    {
        windVector = 0.01 * (rand() % 180) - 0.9;

    }   while(windVector < 0.1 && windVector > -0.1);
    windOldTime = 0;
    windFrameRate = 5;
    ballVectorX += windVector;

    pRacketFrameRate = 3;
    pRacketOldTime = 0;

    bRacketFrameRate = 3;
    bRacketOldTime = 0;
    botDelay = false;

    racketStep = 2;

    roundOver = true;
    predictedX = WWIDTH / 2;

    lKeyStatus = false;
    rKeyStatus = false;
    priorityKey = false;
}

float GameMain::predictBallX() // Returns a place where the center of the ball will be
{
    botDelay = true;
    float absCoord = ((ball.y - RACKHEIGHT) / (ballVectorY * -1)) * ballVectorX; //Ball shift if no walls
     if(absCoord >= 0) //If shift right
     {
         if(WWIDTH - ball.x - BALLSIZE >= absCoord) //If no wall
         {
             return ball.x + absCoord + BALLSIZE / 2;
         }
         else
         {
             if(((int)(absCoord - (WWIDTH - ball.x - BALLSIZE)) / (WWIDTH - BALLSIZE)) % 2 == 0)
             {
                return WWIDTH - BALLSIZE - ((int)(absCoord - (WWIDTH - ball.x - BALLSIZE))) % (WWIDTH - BALLSIZE) + BALLSIZE / 2;
             }
             else
             {
                 return (int)(absCoord - (WWIDTH - ball.x - BALLSIZE)) % (WWIDTH - BALLSIZE) + BALLSIZE / 2;
             }
         }
     }
     else
     {
         absCoord = abs(absCoord);
         if(ball.x  - absCoord > 0)
         {
             return ball.x - absCoord + BALLSIZE / 2;
         }
         else
         {
             if((((int)(absCoord - ball.x)) / (WWIDTH - BALLSIZE)) % 2 == 0)
             {
                 return ((int)(absCoord - ball.x)) % (WWIDTH - BALLSIZE) + BALLSIZE / 2;
             }
             else
             {
                 return WWIDTH - BALLSIZE - ((int)(absCoord - ball.x)) % (WWIDTH - BALLSIZE) + BALLSIZE / 2;
             }
         }
     }

}

void GameMain::setRandBallX()
{

    ballVectorX = 0.01 * (rand() % 120) - 0.6;
}

int GameMain::execute()
{
    if(mainInit() == false)
    {
        return -1;
    }

    SDL_Event event;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            processEvent(&event);
        }

        mainLoop();
        mainRender();
    }

    mainCleanup();
    return 0;
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    GameMain theApp;

    return theApp.execute();
}
