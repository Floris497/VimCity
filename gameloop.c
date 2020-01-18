//
//  gameloop.h
//
//
//  Created by Tim Trussner on 07/01/2020.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL.h>

#include "vimcity.h"

t_color colors[] = {
    {0x00, 0x00 , 0x00, 0xFF}, // black
    {0xFF, 0x00 , 0x00, 0xFF}, // red
    {0x00, 0xFF , 0x00, 0xFF}, // green
    {0x00, 0x00 , 0xFF, 0xFF}, // blue
};

void init_game(t_game *gameState) {
    int w = 80;
    int h = 20; 
    gameState -> map.field = (int **)malloc(w * sizeof(int*));
    for(int i = 0; i < w; i++) {
        gameState -> map.field[i] = (int *) malloc(h * sizeof(int));
        for(int j = 0; j < h; j++) {
            gameState->map.field[i][j] = rand()%4;
        }
    }
    gameState -> map.width = w;
    gameState -> map.height = h;
}

void moveCursor(t_game *gameState, int xDir, int yDir) {
    SDL_Log("cursor moved in direction (%d, %d)", xDir, yDir);
    int w = gameState->map.width;
    int h = gameState->map.height;
    gameState->cursorX+=xDir;
    gameState->cursorY+=yDir;
    if(gameState->cursorX < 0) {
        gameState->cursorX = 0;
    }
    if(gameState->cursorY < 0) {
        gameState->cursorY = 0;
    }
    if(gameState->cursorX >= w) {
        gameState->cursorX = w-1;
    }
    if(gameState->cursorY >= h) {
        gameState->cursorX = h-1;
    }
}

int gameLoop(SDL_Renderer *renderer, t_game *gameState) {
    SDL_Event e;
    bool keepRunning = true;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                keepRunning = false;
                break;
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym) {
                    case SDLK_h:
                       moveCursor(gameState, -1, 0); 
                       break;
                    case SDLK_j:
                       moveCursor(gameState, 0, 1); 
                       break;
                    case SDLK_k:
                       moveCursor(gameState, 0, -1); 
                       break;
                    case SDLK_l:
                       moveCursor(gameState, 1, 0); 
                       break;
                }
        }

    }    
    draw(renderer, gameState);
    return keepRunning;
}

int draw(SDL_Renderer *renderer, t_game *gameState) {
    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);
    int w = gameState -> map.width;
    int h = gameState -> map.height;
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            int val = gameState -> map.field[i][j];
            SDL_Rect rect = {i*CELL_SIZE, j*CELL_SIZE, CELL_SIZE, CELL_SIZE};
            t_color color = colors[val];
            
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    //draw cursor
    SDL_Rect cursorOutline = {gameState->cursorX *CELL_SIZE, gameState->cursorY * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &cursorOutline);

    SDL_RenderPresent(renderer);
    
    return true;
}
