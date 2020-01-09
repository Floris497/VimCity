//
//  vimcity.h
//  
//
//  Created by Floris Fredrikze on 07/01/2020.
//

#ifndef vimcity_h
#define vimcity_h

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct s_color t_color;

struct s_color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

int gameLoop(SDL_Renderer *renderer);

#endif /* vimcity_h */
