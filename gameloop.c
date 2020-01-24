//
//  gameloop.h
//
//
//  Created by Tim Trussner on 07/01/2020.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL.h>

#include "vimcity.h"
#include "utils.h"
#include "renderUtils.h"

SDL_Color colors[] = {
    {0x00, 0x00 , 0x00, 0xFF}, // black
    {0xFF, 0x00 , 0x00, 0xFF}, // red
    {0x00, 0xFF , 0x00, 0xFF}, // green
    {0x00, 0x00 , 0xFF, 0xFF}, // blue
};

void moveCursor(Game *gameState, int xDir, int yDir) {
    int w = gameState->map.width;
    int h = gameState->map.height;
    gameState->prevCursorX = gameState->cursorX;
    gameState->prevCursorY = gameState->cursorY;
    gameState->cursorX += xDir;
    gameState->cursorY += yDir;
    if(gameState->cursorX < 0) {
        gameState->cursorX = 0;
    }
    if(gameState->cursorY < 0) {
        gameState->cursorY = 0;
    }
    if(gameState->cursorX >= w) {
        gameState->cursorX = w-1;
    }
    if(gameState->cursorY >= h) {
        gameState->cursorY = h-1;
    }
    int cursorXDir = gameState->cursorX - gameState->prevCursorX;
    int cursorYDir = gameState->cursorY - gameState->prevCursorY;
    if(abs(cursorXDir) > abs(cursorYDir)) {
        cursorXDir = cursorXDir > 0 ? 1 : -1;
        cursorYDir = 0;
    } else {
        cursorXDir = 0; 
        cursorYDir = cursorYDir > 0 ? 1 : -1;
    }
    gameState->cursorXDir = cursorXDir;
    gameState->cursorYDir = cursorYDir;
}

//maps a direction to the vim direction keys (hjkl) = (1234) = (LEFT DOWN UP RIGHT)
int directionToVim(int xDir, int yDir) {
    if(xDir < 0) {
        return 0;
    }
    if(yDir > 0) {
        return 1;
    }
    if(yDir < 0) {
        return 2;
    }
    if(xDir > 0) {
        return 3;
    }
    return -1;
}

void buildRoad(Game *gameState) {
    int cursorX = gameState->cursorX;
    int cursorY = gameState->cursorY;
    int type = TILE_ROAD_LEFT + directionToVim(gameState->cursorXDir, gameState->cursorYDir);
    gameState->map.tiles[cursorX][cursorY].type = type;
}

int gameLoop(Screen *screen, Game *gameState) {
    SDL_Event e;
    bool keepRunning = true;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                keepRunning = false;
                break;
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym) {
                    case SDLK_h:
                    case SDLK_LEFT:
                       moveCursor(gameState, -1, 0); 
                       break;
                    case SDLK_j:
                    case SDLK_DOWN:
                       moveCursor(gameState, 0, 1); 
                       break;
                    case SDLK_k:
                    case SDLK_UP:
                       moveCursor(gameState, 0, -1); 
                       break;
                    case SDLK_l:
                    case SDLK_RIGHT:
                       moveCursor(gameState, 1, 0); 
                       break;
                    case SDLK_r:
                       buildRoad(gameState);
                    default:
                        ;
                }
                break;
        }

    }    
    draw(screen, gameState);
    return keepRunning;
}

void drawLineOnTile(SDL_Renderer *renderer, int x, int y, int xDir, int yDir, int tileSize) {
    int cx = x*tileSize + tileSize/2;
    int cy = y*tileSize + tileSize/2;
    int fromX = cx - xDir*tileSize/2;
    int fromY = cy - yDir*tileSize/2;
    int toX = cx + xDir*tileSize/2;
    int toY = cy + yDir*tileSize/2;
    drawArrow(renderer, fromX, fromY, toX, toY);
}

void drawRoad(SDL_Renderer *renderer, int x, int y, int xDir, int yDir, int tileSize) {
    SDL_Rect tileRect = {x * tileSize, y*tileSize, tileSize, tileSize};
    SDL_SetRenderDrawColor(renderer, 0x99, 0x99, 0x99, 0xFF);
    SDL_RenderFillRect(renderer, &tileRect);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    drawLineOnTile(renderer, x, y, xDir, yDir, tileSize);
}

int draw(Screen *screen, Game *gameState) {
    SDL_SetRenderDrawColor(screen->renderer, 0,0,0,0);
    SDL_RenderClear(screen->renderer);
    int w = gameState -> map.width;
    int h = gameState -> map.height;
    const int TILE_SIZE = 20;
   
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            int tileType = gameState -> map.tiles[i][j].type;
            switch(tileType) {
                case TILE_EMPTY: //nothing
                    break;
                case TILE_ROAD_LEFT: //road
                    drawRoad(screen->renderer, i, j, -1, 0, TILE_SIZE);
                    break;
                case TILE_ROAD_UP:
                    drawRoad(screen->renderer, i, j, 0, -1, TILE_SIZE);
                    break;
                case TILE_ROAD_DOWN:
                    drawRoad(screen->renderer, i, j, 0, 1, TILE_SIZE);
                    break;
                case TILE_ROAD_RIGHT:
                    drawRoad(screen->renderer, i, j, 1, 0,  TILE_SIZE);
                    break;
            };
        }
    }
    //draw cursor
    SDL_Rect cursorOutline = {gameState->cursorX *TILE_SIZE, gameState->cursorY * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    int cursorXDir = gameState->cursorXDir;
    int cursorYDir = gameState->cursorYDir;
    float cx = cursorOutline.x + cursorOutline.w/2;
    float cy = cursorOutline.y + cursorOutline.h/2;
    SDL_SetRenderDrawColor(screen->renderer, 0x99, 0x99, 0x99, 0xFF);
    SDL_RenderDrawRect(screen->renderer, &cursorOutline);
    drawArrow(screen->renderer, cx - cursorXDir*cursorOutline.w/2, cy - cursorYDir*cursorOutline.h/2,
            cx + cursorXDir*cursorOutline.w/2, cy + cursorYDir*cursorOutline.h/2);

#ifdef _WIN32
    SDL_Log("No FONTS in Windows..");
#else
    Text textureInfo;
    textureInfo.color = (SDL_Color){255,255,255,200};
    SDL_Texture *texture = createTextTexture(getFPSText(screen->FPSHistory, 60), screen, &textureInfo);
    SDL_RenderCopy(screen->renderer, texture, NULL, &textureInfo.rect);
    SDL_DestroyTexture(textureInfo.texture);
#endif
    SDL_RenderPresent(screen->renderer);

    return true;
}

void addCar(Game *gameState, int x, int y) {
    
}

void removeCar(Game *gameState) {
    
}



