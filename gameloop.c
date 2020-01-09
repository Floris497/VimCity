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

const int CELL_SIZE = 20;

t_color colors[] = {
    {0x00, 0x00 , 0x00, 0xFF}, // black
    {0xFF, 0x00 , 0x00, 0xFF}, // red
    {0x00, 0xFF , 0x00, 0xFF}, // green
    {0x00, 0x00 , 0xFF, 0xFF}, // blue
};

int draw(SDL_Renderer *renderer, t_game gameState);

int gameLoop(SDL_Renderer *renderer, t_game gameState) {

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return false;
        }
    }    
    
    draw(renderer, gameState);
    
    return true;
}

int draw(SDL_Renderer *renderer, t_game gameState) {
    int w = gameState.screenSize.width / CELL_SIZE;
    int h = gameState.screenSize.height / CELL_SIZE;

    int grid[w][h];
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            grid[i][j] = rand()%4;
        }
    }
    
    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            int val = grid[i][j];
            SDL_Rect rect = {i*CELL_SIZE, j*CELL_SIZE, CELL_SIZE, CELL_SIZE};
            t_color color = colors[val];
            
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0x00);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
    
    return true;
}
