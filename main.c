//
//  main.c
//
//
//  Created by Floris Fredrikze on 07/01/2020.
//

#include <stdio.h>
#include <stdbool.h>

#include "vimcity.h"
#include "list.h"
#include "init.h"

int main(int argc, char* args[]) {
    SDL_Window      *window = NULL;
    t_game          gameState = {};
    t_screen        screenState = {};

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL not loaded");
    } if (TTF_Init()) {
        SDL_Log("SDL_ttf not loaded");
    } else {

        // init Graphics
        init_graphics(&screenState);

        //Create window
        window = SDL_CreateWindow("VimCity Pre Alpha 0.0.0",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  screenState.width,
                                  screenState.height,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

        if (window == NULL) {
            SDL_Log("could not make window");
        } else {
            int w,h;
            SDL_GetWindowSize(window, &w, &h);

            screenState.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

            long double delta;
            Uint64 now, taken;
            bool ret = true;
            init_game(&gameState);
            while (ret) {
                now = SDL_GetPerformanceCounter();

                // run game loop
                ret = gameLoop(&screenState, &gameState);

                taken = SDL_GetPerformanceCounter() - now;
                delta = round(screenState.timePerFrame - taken) / (SDL_GetPerformanceFrequency() / 1000);
                if (delta > 0) { SDL_Delay(round(delta)); }
                taken = SDL_GetPerformanceCounter() - now;
                screenState.FPSHistory->value = (void *)taken;
                screenState.FPSHistory = screenState.FPSHistory->next;
            }
            SDL_DestroyWindow(window);
        }

        SDL_DestroyRenderer(screenState.renderer);
        TTF_CloseFont(screenState.font);
        SDL_Quit();
        SDL_Log("einde");
    }
    return 0;
}
