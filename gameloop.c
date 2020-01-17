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
    int w = 20;
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

int gameLoop(SDL_Renderer *renderer, t_game *gameState) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return false;
        }
    }    
    
    draw(renderer, gameState);
    
    return true;
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
            
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0x00);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
    
    return true;
}
