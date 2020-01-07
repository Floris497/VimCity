#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

int gameLoop(SDL_Window *window, SDL_Surface *screenSurface) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
        SDL_UpdateWindowSurface( window );
        if (e.type == SDL_QUIT) {
            return false;
        }
        return true;
    }
}
