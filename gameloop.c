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
#include "utils.h"

t_color colors[] = {
    {0x00, 0x00 , 0x00, 0xFF}, // black
    {0xFF, 0x00 , 0x00, 0xFF}, // red
    {0x00, 0xFF , 0x00, 0xFF}, // green
    {0x00, 0x00 , 0xFF, 0xFF}, // blue
};

void moveCursor(t_game *gameState, int xDir, int yDir) {
    int w = gameState->map.width;
    int h = gameState->map.height;
    gameState->cursorX += xDir;
    gameState->cursorY += yDir;
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
        gameState->cursorY = h-1;
    }
}

int gameLoop(t_screen *screen, t_game *gameState) {
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
    draw(screen, gameState);
    return keepRunning;
}

int draw(t_screen *screen, t_game *gameState) {
    SDL_SetRenderDrawColor(screen->renderer, 0,0,0,0);
    SDL_RenderClear(screen->renderer);
    int w = gameState -> map.width;
    int h = gameState -> map.height;
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            int val = gameState -> map.field[i][j];
            SDL_Rect rect = {i*CELL_SIZE, j*CELL_SIZE, CELL_SIZE, CELL_SIZE};
            t_color color = colors[val];
            
            SDL_SetRenderDrawColor(screen->renderer, color.r, color.g, color.b, 0xFF);
            SDL_RenderFillRect(screen->renderer, &rect);
        }
    }

    //draw cursor
    SDL_Rect cursorOutline = {gameState->cursorX *CELL_SIZE, gameState->cursorY * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_SetRenderDrawColor(screen->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(screen->renderer, &cursorOutline);


#ifdef _WIN32
    SDL_Log("No FONTS in Windows..");
#else
    t_text textureInfo;
    textureInfo.color = (SDL_Color){255,255,255,200};
    SDL_Texture *texture = createTextTexture(getFPSText(screen->FPSHistory, 60), screen, &textureInfo);
    SDL_RenderCopy(screen->renderer, texture, NULL, &textureInfo.rect);
    SDL_DestroyTexture(textureInfo.texture);
#endif
    SDL_RenderPresent(screen->renderer);

    return true;
}
