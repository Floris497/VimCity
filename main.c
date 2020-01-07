#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

gameLoop(SDL_Window *window, SDL_Surface *screenSurface);

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    
    if(SDL_Init( SDL_INIT_VIDEO) < 0) {
        printf("SDL not loaded");
    } else {
        //Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL) {
            printf("could not make window");
        } else {
            screenSurface = SDL_GetWindowSurface(window);
            bool quit = false;
            while (!quit) {
                quit = !gameLoop(window, screenSurface);
            }
            
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
        printf("einde\n");
        return 0;
    }
}

