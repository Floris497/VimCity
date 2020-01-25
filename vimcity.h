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
typedef enum TileType TileType;

enum e_tileType
{
    TILE_EMPTY,
    TILE_ROAD_LEFT,
    TILE_ROAD_DOWN,
    TILE_ROAD_UP,
    TILE_ROAD_RIGHT,
};

typedef struct Game Game;
typedef struct Map Map;
typedef struct Tile Tile;
typedef struct Text Text;
typedef struct Screen Screen;
typedef struct Car Car;

struct Text {
    SDL_Color color;
    SDL_Texture *texture;
    SDL_Rect rect;
};

struct Screen {
    int width; 
    int height;
    SDL_Renderer *renderer;
    long double timePerFrame;
    TTF_Font *font;
    t_list *FPSHistory;
};

struct Car {
    //discrete position
    int x;
    int y;
    //continuous position for animation
    float fx;
    float fy;
};

struct Tile {
    int type;
    Car *car;
};

struct Map {
    Tile **tiles;
    int width;
    int height;
};

struct Game {
    Map map;
    long tick;
    int cursorX;
    int cursorY;
    int prevCursorX;
    int prevCursorY;
    int cursorXDir;
    int cursorYDir;

    int nCars;
    Car *carList;
};

void moveCursor(Game*, int, int);

void init_game(Game *gameState);

void gameTick(Game *gameState);

int draw(Screen *screen, Game *gameState);

int gameLoop(Screen* screen, Game *gameState);

void buildRoad(Game *gameState);

SDL_Texture *createTextTexture( const char* string, Screen *screenState, Text *textureInfo);

void addCar(Game *gameState, int x, int y);

void removeCar(Game *gameState);

#endif /* vimcity_h */
