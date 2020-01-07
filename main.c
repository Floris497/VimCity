//
//  main.c
//
//
//  Created by Floris Fredrikze on 07/01/2020.
//

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int gameLoop(SDL_Window *window, SDL_Renderer *renderer);

#define FRAME_DURATION (SDL_GetPerformanceFrequency()/60)

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;

    long double duration = (SDL_GetPerformanceFrequency()/60.0);

    if(SDL_Init( SDL_INIT_VIDEO) < 0) {
        printf("SDL not loaded");
    } else {
        //Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        if(window == NULL) {
            printf("could not make window");
        } else {
                        
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

            bool quit = false;

            long double delta;
            Uint64 now, end, taken;
            while (!quit) {
                now = SDL_GetPerformanceCounter();
                quit = !gameLoop(window, renderer);
                end = SDL_GetPerformanceCounter();
                taken = end - now;
                delta = round(duration - taken) / (SDL_GetPerformanceFrequency() / 1000);
                SDL_Log("Taken: %llu, %Lf\n", taken / SDL_GetPerformanceFrequency(), delta);
                if (delta > 0)
                    SDL_Delay(round(delta));
            }

            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
        printf("einde\n");
        return 0;
    }
}
