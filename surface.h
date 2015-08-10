#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED

#include <SDL/SDL.h>
#include <vector>

class GameSurface {
public:
    GameSurface();

public:
    static SDL_Surface *load(char *file);

    static bool draw(SDL_Surface *surfDest, SDL_Surface *surfSrc, int x, int y);

    static bool draw(SDL_Surface *surfDest, SDL_Surface *surfSrc, int x, int y, int x2, int y2, int w, int h);

    static bool makeTransparent(SDL_Surface *surfDest, int r, int g, int b);

};

#endif // SURFACE_H_INCLUDED
