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
#include <stdbool.h>

//define tile types
#define TILE_EMPTY 0
#define TILE_ROAD_LEFT 1
#define TILE_ROAD_DOWN 2
#define TILE_ROAD_UP 3
#define TILE_ROAD_RIGHT 4

typedef struct s_game t_game;
typedef struct s_map t_map;
typedef struct s_tile t_tile;
typedef struct s_text t_text;
typedef struct s_screen t_screen;
typedef struct s_car t_car;
typedef struct s_color t_color;

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

struct s_car {
    //discrete position
    int x;
    int y;
    //continuous position for animation
    float fx;
    float fy;
};

struct s_tile {
    int type;
    t_car *car;
};

struct s_map {
    t_tile **tiles;
    int width;
    int height;
};

struct s_game {
    t_map map;
    int cursorX;
    int cursorY;
    int prevCursorX;
    int prevCursorY;
    int cursorXDir;
    int cursorYDir;

    int nCars;
    t_car *carList;
};

void moveCursor(t_game*, int, int);

void init_game(t_game *gameState);

int draw(t_screen *screen, t_game *gameState);

int gameLoop(t_screen* screen, t_game *gameState);

void buildRoad(t_game *gameState);

SDL_Texture *createTextTexture( const char* string, t_screen *screenState, t_text *textureInfo);

void addCar(t_game *gameState, int x, int y);

void removeCar(t_game *gameState);

#endif /* vimcity_h */
