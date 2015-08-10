#include "application.h"

bool GameMain::mainInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;

    //-----------------------SURFACES-----------------------
    if((displaySurface = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) return false;

    if((menuBack = GameSurface::load("./gfx/menu_background.bmp")) == NULL) return false;

    if((mapSurface = GameSurface::load("./gfx/map.bmp")) == NULL) return false;

    if((menuLevels = GameSurface::load("./gfx/menu_numbers.bmp")) == NULL) return false;

    if((pScore = GameSurface::load("./gfx/numbers_orange.bmp")) == NULL) return false;

    if((bScore = GameSurface::load("./gfx/numbers_red.bmp")) == NULL) return false;

    GameSurface::makeTransparent(pScore, 255, 0, 255);
    GameSurface::makeTransparent(bScore, 255, 0, 255);

    //-----------------------ENTETIES-----------------------

    //Player racket initialization
    if(playerRacket.load("./gfx/player_racket.bmp", RACKWIDTH, RACKHEIGHT, 1) == false) return false;
    playerRacket.x = (WWIDTH - RACKWIDTH) / 2;
    playerRacket.y = WHEIGHT - BORDERHEIGHT - RACKHEIGHT;

    //Bot racket initialization
    if(botRacket.load("./gfx/bot_racket.bmp", RACKWIDTH, RACKHEIGHT, 1) == false) return false;
    botRacket.x = (WWIDTH - RACKWIDTH) / 2;
    botRacket.y = 0;

    //Ball initialization
    if(ball.load("./gfx/ballmac.bmp", BALLSIZE, BALLSIZE, 10, true, 100) == false) return false;
    ball.x = (WWIDTH - BALLSIZE) / 2 - ballVectorX;
    ball.y =  RACKHEIGHT - ballVectorY;

    //GameOver initialization
    if(gameOver.load("./gfx/gameover.bmp", GAMEOVERW, GAMEOVERH, 9, true, 150) == false) return false;
    gameOver.x = (WWIDTH - GAMEOVERW) / 2;
    gameOver.y = (WHEIGHT - GAMEOVERH) / 2;

    //GameWin initialization
    if(gameWin.load("./gfx/gamewin.bmp", GAMEOVERW, GAMEOVERH, 9, true, 150) == false) return false;
    gameWin.x = (WWIDTH - GAMEOVERW) / 2;
    gameWin.y = (WHEIGHT - GAMEOVERH) / 2;

    //PARTNUM particles initialization
    for(int i = 0; i < PARTNUM; i += 2)
    {
        if(particles[i].load("./gfx/wind_particle1.bmp", 4, 4, 1) == false) return false;
        particles[i].x = rand() % (WWIDTH);
        particles[i].y = rand() % (WHEIGHT - BORDERHEIGHT);
    }
    for(int i = 1; i < PARTNUM; i += 2)
    {
        if(particles[i].load("./gfx/wind_particle2.bmp", 4, 2, 1) == false) return false;
        particles[i].x = WWIDTH + 3;
        particles[i].y = 0;
    }

    //Pushing to entities vector
    for(int i = 0; i < PARTNUM; i++)
    {
        GameEntity::entityList.push_back(&particles[i]);
        particles[i].isRender = false;
    }
    GameEntity::entityList.push_back(&gameOver);
    GameEntity::entityList.push_back(&gameWin);
    GameEntity::entityList.push_back(&ball);
    GameEntity::entityList.push_back(&playerRacket);
    GameEntity::entityList.push_back(&botRacket);
    return true;
}
