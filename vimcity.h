//
//  vimcity.h
//  
//
//  Created by Floris Fredrikze on 07/01/2020.
//

#ifndef vimcity_h
#define vimcity_h

// for types
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_stdinc.h>
#include "list.h"

#define CELL_SIZE 20

typedef struct s_color t_color;

typedef struct s_game t_game;
typedef struct s_map t_map;

typedef struct s_text t_text;
typedef struct s_screen t_screen;

struct s_text {
    SDL_Color color;
    SDL_Texture *texture;
    SDL_Rect rect;
};

struct s_screen {
    int width; 
    int height;
    SDL_Renderer *renderer;
    long double timePerFrame;
    TTF_Font *font;
    t_list *FPSHistory;
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

SDL_Texture *createTextTexture( const char* string, t_screen *screenState, t_text *textureInfo);

#endif /* vimcity_h */
