#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


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
		printf("blijkbaar kan de window wel gemaakt worden.");
            screenSurface = SDL_GetWindowSurface(window);
            bool quit = false;                                      
            SDL_Event e;                                            
            while (!quit) {                                         
		    printf("in event loop");
                while (SDL_PollEvent(&e)) {      
                    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
                    SDL_UpdateWindowSurface( window );                   
                    if (e.type == SDL_QUIT) {                       
                        quit = true;                                
                    }                                               
                }                                                   
            }        

            SDL_DestroyWindow(window);

            SDL_Quit();
        }
	printf("einde\n");
    return 0;
    }
}
