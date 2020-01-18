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
#define CELL_SIZE 20

typedef struct s_color t_color;

typedef struct s_game t_game;
typedef struct s_map t_map;

typedef struct s_screen t_screen;
struct s_screen {
    int width; 
    int height;
    SDL_Renderer *renderer;
};

struct s_color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

struct s_map {
    int **field;
    int width;
    int height;
};

struct s_game {
    t_map map;
    int cursorX;
    int cursorY;
};

void moveCursor(t_game*, int, int);

void init_game(t_game *gameState);

int draw(t_screen *screen, t_game *gameState);

int gameLoop(t_screen* screen, t_game *gameState);

#endif /* vimcity_h */
