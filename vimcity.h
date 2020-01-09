//
//  vimcity.h
//  
//
//  Created by Floris Fredrikze on 07/01/2020.
//

#ifndef vimcity_h
#define vimcity_h

// for types
#include <SDL_stdinc.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct s_color t_color;
typedef struct s_game t_game;
typedef struct s_map t_map;

typedef struct s_point t_point;
typedef struct s_size t_size;
typedef struct s_rect t_rect;

struct s_color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

struct s_point {
    Sint64 x;
    Sint64 y;
};

struct s_size {
    Uint64 width;
    Uint64 height;
};

struct s_rect {
    t_point origin;
    t_size size;
};

struct s_map {
    int *field;
    t_size size;
};

struct s_game {
    t_map map;
    t_size screenSize;
};

int gameLoop(SDL_Renderer *renderer, t_game gameState);

#endif /* vimcity_h */
