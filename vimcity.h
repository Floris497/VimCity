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

struct s_game {
    t_map map;
    t_size screenSize;
}

struct s_map {
    field *field;
    t_size size;
}

struct s_point {
    Int64 x;
    Int64 y;
}
struct s_size {
    Uint64 width;
    Uint64 heigt:
}
struct s_rect {
    t_point origin;
    t_size size;
}


int gameLoop(SDL_Renderer *renderer);

#endif /* vimcity_h */
