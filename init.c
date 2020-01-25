//
//  init.c
//  VimCity-xcode
//
//  Created by Floris Fredrikze on 19/01/2020.
//

#include <stdlib.h>

#include "init.h"
#include "list.h"

void init_graphics(Screen *screenState)
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

void createRoad(Game *gameState, int fromX, int fromY, int xDir, int yDir, int length) {
    int type = directionToVim(xDir, yDir) + TILE_ROAD_LEFT;
    for(int i = 0; i < length; i++) {
        int x = fromX + xDir*i;
        int y = fromY + yDir*i;
        gameState->map.tiles[x][y].type = type;
        if(rand()%8 == 0) {
            addCar(gameState, x, y);
        }
    }
}

void init_game(Game *gameState) {
    //input
    gameState->actionDownTicks = (int *)malloc(sizeof(int) * kActionLast);
    for(int i = 0; i < kActionLast; i++) {
        gameState->actionDownTicks[i] = -1;
    }
    int w = 60;
    int h = 30;
    gameState->map.tiles = (Tile **)malloc(w * sizeof(Tile*));
    for(int i = 0; i < w; i++) {
        gameState -> map.tiles[i] = (Tile *) malloc(h * sizeof(Tile));
        for(int j = 0; j < h; j++) {
            gameState->map.tiles[i][j].type = 0;
            gameState->map.tiles[i][j].car = NULL;
        }
    }
    gameState->map.width = w;
    gameState->map.height = h;
    gameState->cursorX = 0;
    gameState->cursorY = 0;
    gameState->prevCursorX = 0;
    gameState->prevCursorY = 0;
    gameState->cursorXDir = 1;
    gameState->cursorYDir = 0;
    createRoad(gameState, 0, 0, 0, 1, h);
    createRoad(gameState, 0, h-1, 1, 0, w);
    createRoad(gameState, w-1, h-1, 0, -1, h);
    createRoad(gameState, w-1, 0, -1, 0, w);
    createRoad(gameState, w/2, h-1, 0, -1, h);
    createRoad(gameState, w-1, h/2, -1, 0, w);
}
