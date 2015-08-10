#include "application.h"

void GameMain::mainLoop()
{
    //--------------BALL ANIMATION CALCULATIONS--------------
    if(gameStatus > SF_MENU && (ballOldTime + ballFrameRate <= SDL_GetTicks()))
    {
        if(ballVectorX > 4) ballVectorX = 4;
        if(ballVectorX < -4) ballVectorX = -4;

        //Checking collision with player racket
        if(ball.y + ballVectorY + BALLSIZE > WHEIGHT - BORDERHEIGHT - RACKHEIGHT && (ball.x + BALLSIZE >= playerRacket.x && ball.x <= playerRacket.x + RACKWIDTH))
        {
            ballVectorY *= -1;
            if(!priorityKey)
            {
                if(lKeyStatus) ballVectorX -= 1.25;
                else if(rKeyStatus) ballVectorX += 1.25;
            }
            else
            {
                if(rKeyStatus) ballVectorX += 1.25;
                else if(lKeyStatus) ballVectorX -= 1.25;
            }
            ball.y = WHEIGHT - BORDERHEIGHT - BALLSIZE - RACKHEIGHT;
            predictedX = predictBallX();
        }
        //end

        //Checking collision with -DOWN SIDE-
        if(gameStatus == SF_RUNNING && (ball.y + ballVectorY + BALLSIZE > WHEIGHT - BORDERHEIGHT))
        {
            if(++bScoreNum < 9)
            {
                ballVectorY = 2;

                ball.x = (WWIDTH - BALLSIZE) / 2;
                ball.y =  RACKHEIGHT - ballVectorY;

                setRandBallX();

                do
                {
                    windVector = 0.01 * (rand() % 180) - 0.9;
                }   while(windVector < 0.1 && windVector > -0.1);

                predictedX = WWIDTH / 2;
                playerRacket.x = WWIDTH / 2 - RACKWIDTH / 2;
                botRacket.x = WWIDTH / 2 - RACKWIDTH / 2;
                botDelay = true;

                roundOver = true;
            }
            else
            {
                gameOver.isRender = true;
                gameStatus = SF_LOST;

                if(ballFrameRate >= 4)
                {
                    ballFrameRate /= 4;
                }
                else
                {
                    ballVectorX *= 2;
                    ballVectorY *= 2;
                }
            }
        }
        //end

        //Checking collision with -BOT RACKET-
        if((ball.y + ballVectorY) < RACKHEIGHT && ball.x + BALLSIZE >= botRacket.x && ball.x <= botRacket.x + RACKWIDTH)
        {
            ballVectorY *= -1;
            ball.y = RACKHEIGHT;

            if(rand() % 2)
            {
                predictedX = WWIDTH / 2;
            }
        }
        //end

        //Checking collision with -UPPER SIDE-
        if(gameStatus == SF_RUNNING && (ball.y + ballVectorY) < 0)
        {
            if(++pScoreNum < 9)
            {
                ballVectorY = -2;
                ball.x = (WWIDTH - BALLSIZE) / 2;
                ball.y =  WHEIGHT - RACKHEIGHT - BORDERHEIGHT - BALLSIZE - ballVectorY;


                botDelay = true;

                do
                {
                    windVector = 0.01 * (rand() % 180) - 0.9;
                }   while(windVector < 0.1 && windVector > -0.1);


                setRandBallX();

                predictedX = predictBallX();
                playerRacket.x = WWIDTH / 2 - RACKWIDTH / 2;
                botRacket.x = WWIDTH / 2 - RACKWIDTH / 2;

                roundOver = true;
            }
            else
            {
                gameWin.isRender = true;
                gameStatus = SF_WIN;

                if(ballFrameRate >= 4)
                {
                    ballFrameRate /= 4;
                }
                else
                {
                    ballVectorX *= 2;
                    ballVectorY *= 2;
                }
            }
        }
        //end

        //Checking collision with -VERTICAL SIDES-
        if((ball.x + ballVectorX) < 0 || (ball.x + ballVectorX + BALLSIZE) >= WWIDTH)
        {
            ballVectorX *= -1;
        }
        //end

        //Reversing the ball when lost
        if(ball.y + ballVectorY + BALLSIZE > WHEIGHT - BORDERHEIGHT || (ball.y + ballVectorY) < 0)
        {
            ballVectorY *= -1;
        }

        ball.x += ballVectorX;
        ball.y += ballVectorY;

        if(roundOver) //Stopping animations
        {
            ballOldTime = SDL_GetTicks() + 1500;
            pRacketOldTime = SDL_GetTicks() + 1500;
            bRacketOldTime = SDL_GetTicks() + 1500;
            roundOver = false;
        }
        else ballOldTime = SDL_GetTicks();
    }
    //*****************END of BALL ANIMATION CALCULATIONS*****************




    //---------------pRacket ANIMATION CALCULATIONS---------------
    if(gameStatus == SF_RUNNING && (pRacketOldTime + pRacketFrameRate <= SDL_GetTicks()))
    {
        if(!priorityKey)
        {
            if(lKeyStatus) playerRacket.x -= racketStep;
            else if(rKeyStatus) playerRacket.x += racketStep;
        }
        else
        {
            if(rKeyStatus) playerRacket.x += racketStep;
            else if(lKeyStatus) playerRacket.x -= racketStep;
        }


        //playerRacket.x += pRacketVectorX;

        if(playerRacket.x < 0) playerRacket.x = 0;

        if(playerRacket.x > WWIDTH - RACKWIDTH) playerRacket.x = WWIDTH - RACKWIDTH;

        pRacketOldTime = SDL_GetTicks();
    }
    //*************END of pRacket ANIMATION CALCULATIONS************

    //---------------WIND AND PARTICLES animation---------------
    if(gameStatus >= SF_RUNNING && (windOldTime + windFrameRate <= SDL_GetTicks()))
    {
        if(!(rand() % 600))
        {
            ballVectorX -= windVector;

            if(rand() % 2)
            {
                if(windVector < 0.9)
                    windVector += 0.15;
            }
            else
            {
                if(windVector > -0.9)
                    windVector -= 0.15;
            }
            if(windVector < 0.2 && windVector >= 0)
            {
                windVector = -0.4;
            }
            if(windVector > -0.2 && windVector < 0)
            {
                windVector = 0.4;
            }

            ballVectorX += windVector;
            if(ballVectorY < 0)
            {
                predictedX = predictBallX();
            }
        }

        for(int i = 0; i < PARTNUM; i++)
        {
            if(!isFree[i])
            {
                particles[i].x += windVector;
                if(particles[i].x < 0 || particles[i].x > WWIDTH)
                {
                    isFree[i] = true;
                    particles[i].x = 2 * WWIDTH;
                }
            }
        }

        for(int i = 0; i < PARTNUM; i++)
        {
            if(windVector && !(rand() % 700))
            {
                while(i < PARTNUM && !isFree[i])
                {
                    i++;
                }
                isFree[i] = false;
                particles[i].y = rand() % (WHEIGHT - BORDERHEIGHT);
                if(windVector > 0) particles[i].x = 0;
                else particles[i].x = WWIDTH - 1;
            }
        }

        for(int i = 0; i < PARTNUM; i++)
        {
            if(!isFree[i])
            {
                particles[i].x += windVector;
            }

        }
        windOldTime = SDL_GetTicks();
    }
    //*************END of WIND AND PARTICLES animation************


    //------------------BOT RACKET BEHAVIOUR------------------

    int botDelayTime = 0;
    switch (gameLevel)
    {
    case 1:
        {
            botDelayTime = 1050 + rand() % 300;
            break;
        }
    case 2:
        {
            botDelayTime = 580 + rand() % 250;
            break;
        }
    case 3:
        {
            botDelayTime = 250 + rand() % 70;
            break;
        }
    case 4:
        {
            botDelayTime = 80 + rand() % 50;
            racketStep = 4;
            break;
        }
    case 5:
        {
            botDelayTime = 30 + rand() % 20;
            racketStep = 5;
            break;
        }
    }
    if(gameStatus == SF_RUNNING && (bRacketOldTime + bRacketFrameRate + botDelay * botDelayTime <= SDL_GetTicks()))
    {
        botDelay = false;

        if(abs(botRacket.x + RACKWIDTH / 2 - predictedX) < racketStep)
        {
            botRacket.x = predictedX - RACKWIDTH / 2;
        }
        else
        {
            if(botRacket.x + RACKWIDTH / 2 < predictedX)
                botRacket.x += racketStep;
            else
                botRacket.x -= racketStep;
        }

        //Check if outside the window
        if(botRacket.x < 0) botRacket.x = 0;

        if(botRacket.x > WWIDTH - RACKWIDTH) botRacket.x = WWIDTH - RACKWIDTH;
        //end

        bRacketOldTime = SDL_GetTicks();
    }
    //***************END OF BOT RACKET BEHAVIOUR***************


    //--------------ENTETIES ANIMATION PROCESSING---------------
    if(gameStatus >= SF_RUNNING)
    {
        for(int i = 0; i < GameEntity::entityList.size(); i++)
        {
            GameEntity::entityList[i]->loop();
        }
    }
	//************END OF ENTETIES ANIMATION PROCESSING**********
}
