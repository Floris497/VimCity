//
//  init.c
//  VimCity-xcode
//
//  Created by Floris Fredrikze on 19/01/2020.
//

#include <stdlib.h>

#include "init.h"
#include "list.h"

void init_graphics(t_screen *screenState)
{
    screenState->width = 1280;
    screenState->height = 720;
    screenState->renderer = NULL;
    screenState->timePerFrame = (SDL_GetPerformanceFrequency()/60.0);
    screenState->FPSHistory = circularList(10);
#ifdef _WIN32
    screenState->font = TTF_OpenFont("C:/Users/MacBook Air/Desktop/UbuntuMono-R.ttf", 20);
#elif BUNDLE
    screenState->font = TTF_OpenFont("UbuntuMono-R.ttf", 20);
#else
    screenState->font = TTF_OpenFont("./assets/fonts/UbuntuMono-R.ttf", 20);
#endif

}

void init_game(t_game *gameState) {
    int w = 80;
    int h = 20;
    gameState->map.field = (int **)malloc(w * sizeof(int*));
    for(int i = 0; i < w; i++) {
        gameState -> map.field[i] = (int *) malloc(h * sizeof(int));
        for(int j = 0; j < h; j++) {
            gameState->map.field[i][j] = rand()%4;
        }
    }
    gameState->map.width = w;
    gameState->map.height = h;
}
