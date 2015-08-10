#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <SDL/SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "surface.h"
#include "event.h"
#include "animation.h"
#include "entity.h"
#include "define.h"


class GameMain : public GameEvent {
private:
    //System variables
    bool running;
    int gameLevel; //Not used
    int pScoreNum;
    int bScoreNum;
    int gameStatus; 
    enum{SF_MENU, SF_RUNNING, SF_WIN, SF_LOST}; //For game status (SF - status flag)

    //Creating surfaces
    SDL_Surface *displaySurface;
    SDL_Surface *mapSurface;
    SDL_Surface *menuBack;
    SDL_Surface *menuLevels;
    SDL_Surface *pScore;
    SDL_Surface *bScore;

    //Creating enteties
    GameEntity playerRacket;
    GameEntity botRacket;
    GameEntity ball;
    GameEntity gameOver;
    GameEntity gameWin;
    GameEntity particles[PARTNUM];

    int ballOldTime;
    int ballFrameRate;

    bool isFree[PARTNUM];
    float ballVectorX;
    float ballVectorY;
    float windVector;

    int windOldTime;
    int windFrameRate;

    int pRacketOldTime;
    int pRacketFrameRate;

    int bRacketOldTime;
    int bRacketFrameRate;
    bool botDelay;

    int racketStep;

    int predictedX;

    bool roundOver;

    bool lKeyStatus;
    bool rKeyStatus;
    bool priorityKey; //false - left, true - right

public:
    GameMain();

    //Main functions
    int execute();

    bool mainInit();

    void mainLoop();

    void mainRender();

    void mainCleanup();

    float predictBallX();

    void setRandBallX();

    void exitApp();

    //Event functions prototypes
    void processEvent(SDL_Event *event);

    void keyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

    void keyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

    void lButtonUp(int mX, int mY);
};

#endif // APPLICATION_H_INCLUDED
