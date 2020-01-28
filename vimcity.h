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


// Enums
typedef enum TileType TileType;
typedef enum InputAction InputAction;

enum TileType
{
    kTileEmpty,
    kTileRoadLeft,
    kTileRoadDown,
    kTileRoadUp,
    kTileRoadRight,
};

enum InputAction
{
    kActionNothing,
    kActionLeft,
    kActionDown,
    kActionUp,
    kActionRight,
    kActionBuildRoad,
    kActionBuildCar,
    kActionLast,
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
    int cameraX;
    int cameraY;
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
    int *actionDownTicks;
    Map map;
    long tick;
    int cursorX;
    int cursorY;
    int cursorXDir;
    int cursorYDir;
    int tileSize;

    int nCars;
    Car *carList;
};

void moveCursor(Game* gameState, int x, int y);

void init_game(Game *gameState);

void gameTick(Game *gameState);

int draw(Screen *screen, Game *gameState);

int gameLoop(Screen* screen, Game *gameState);

void buildRoad(Game *gameState);

SDL_Texture *createTextTexture(const char* string, Screen *screenState, Text *textureInfo);

void addCar(Game *gameState, int x, int y);

void removeCar(Game *gameState);

int directionToVim(int xDir, int yDir);

InputAction getAction(SDL_Keycode key);

void actionTriggered(Game *gameState, InputAction action, bool down);

void updateInput(Game *gameState);

#endif /* vimcity_h */
