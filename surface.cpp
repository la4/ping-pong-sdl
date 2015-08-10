#include "surface.h"


GameSurface::GameSurface()
{

}

SDL_Surface* GameSurface::load(char *file)
{
    SDL_Surface *surfTemp = NULL;
    SDL_Surface *surfReturn = NULL;

    if((surfTemp = SDL_LoadBMP(file)) == NULL)
    {
        return 0;
    }

    surfReturn = SDL_DisplayFormat(surfTemp);
    SDL_FreeSurface(surfTemp);


    return surfReturn;
}

bool GameSurface::draw(SDL_Surface *surfDest, SDL_Surface *surfSrc, int x, int y)
{
    if(surfDest == NULL || surfSrc == NULL)
    {
        return false;
    }

    SDL_Rect destR; //Blit requres a rectangle

    destR.x = x;
    destR.y = y;

    SDL_BlitSurface(surfSrc, NULL, surfDest, &destR);

    return true;
}

bool GameSurface::draw(SDL_Surface *surfDest, SDL_Surface *surfSrc, int x, int y, int x2, int y2, int w, int h)
{
    if(surfDest == NULL || surfSrc == NULL)
    {
        return false;
    }

    SDL_Rect destR;
    SDL_Rect srcR;

    destR.x = x;
    destR.y = y;

    srcR.x = x2;
    srcR.y = y2;
    srcR.w = w;
    srcR.h = h;

    SDL_BlitSurface(surfSrc, &srcR, surfDest, &destR);
    return true;
}


bool GameSurface::makeTransparent(SDL_Surface *surfDest, int r, int g, int b)
{
    if(surfDest == NULL)
    {
        return false;
    }

    SDL_SetColorKey(surfDest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(surfDest->format, r, g, b));

    return true;
}
