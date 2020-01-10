//
//  main.c
//
//
//  Created by Floris Fredrikze on 07/01/2020.
//

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "vimcity.h"
#include "list.h"

//int main(int argc, char* args[])
int main(void) {
    SDL_Window      *window   = NULL;
    SDL_Renderer    *renderer = NULL;
    t_game          gameState = {};

    long double duration = (SDL_GetPerformanceFrequency()/60.0);

    t_list *list = circularList(10);
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL not loaded");
    } else {
        //Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        if(window == NULL) {
            printf("could not make window");
        } else {
            int w,h;
            SDL_GetWindowSize(window, &w, &h);
            gameState.screenSize.width = w;
            gameState.screenSize.height = h;
                        
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

            long double delta;
            Uint64 now, end, taken;
            bool ret = true;
            while (ret) {
                now = SDL_GetPerformanceCounter();
                ret = gameLoop(renderer, &gameState);
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
