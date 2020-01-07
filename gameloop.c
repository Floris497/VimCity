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

const int CELL_SIZE = 5;

typedef struct s_color t_color;

struct s_color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

t_color colors[] = {
    {0,0,0,255},
    {255, 0, 0, 255},
    {0,255, 0, 255},
    {0,0,255,255}
};

int gameLoop(SDL_Window *window, SDL_Renderer *renderer) {
    int w = 80;
    int h = 60;
    int grid[w * h];
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            grid[i + j * w] = rand()%4; 
        }
    }
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return false;
        }
    }    

    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            int val = grid[i+j*w];
            SDL_Rect rect = {i*CELL_SIZE, j*CELL_SIZE, CELL_SIZE, CELL_SIZE};
            t_color color = colors[val];
            
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0x00);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
    return 1;
}
