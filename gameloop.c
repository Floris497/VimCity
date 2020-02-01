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

//moves the cursor and handles all extra logic, like orienting to the right direction before moving
void moveCursor(Game *gameState, int xDir, int yDir) {
    int w = gameState->map.width;
    int h = gameState->map.height;
    
    if(xDir!=gameState->cursorXDir || yDir!=gameState->cursorYDir) {
        gameState->cursorXDir = xDir;
        gameState->cursorYDir = yDir;
    } else {
        gameState->cursorX+=xDir; 
        gameState->cursorY+=yDir; 
    }

    if(gameState->cursorX < 0)
        gameState->cursorX = 0;
    if(gameState->cursorY < 0)
        gameState->cursorY = 0;
    if(gameState->cursorX >= w)
        gameState->cursorX = w-1;
    if(gameState->cursorY >= h)
        gameState->cursorY = h-1;
}

void centerCamera(Screen *screen, Game *gameState) {
    int screenW = screen->width;
    int screenH = screen->height;
    int tileSize = gameState->tileSize;
    int widthInTiles = screenW/tileSize;
    int heightInTiles = screenH/tileSize;
    int cx = gameState->cursorX - widthInTiles/2;
    int cy = gameState->cursorY - heightInTiles/2;
    screen->cameraX = cx < 0 ? 0 : cx; 
    screen->cameraY = cy < 0 ? 0 : cy;
    SDL_Log("centering camera");
}

//maps a direction to the vim direction keys (hjkl) = (1234) = (LEFT DOWN UP RIGHT)
int directionToVim(int xDir, int yDir) {
    if(xDir < 0) { return 0; }
    if(yDir > 0) { return 1; }
    if(yDir < 0) { return 2; }
    if(xDir > 0) { return 3; }
    return -1;
}

void vimToDirection(int vimCode, int *xDir, int *yDir) {
    switch(vimCode) {
        case 0:
            (*xDir) = -1;
            (*yDir) = 0;
            break;
        case 1:
            (*xDir) = 0;
            (*yDir) = 1;
            break;
        case 2:
            (*xDir) = 0;
            (*yDir) = -1;
            break;
        case 3:
            (*xDir) = 1;
            (*yDir) = 0;
            break;
    }
}

void buildRoad(Screen *screen, Game *gameState) {
    int cursorX = gameState->cursorX;
    int cursorY = gameState->cursorY;
    int vimDir = directionToVim(gameState->cursorXDir, gameState->cursorYDir);
    int type = kTileRoadLeft + vimDir;
    gameState->map.tiles[cursorX][cursorY].type = type;
    if(random()%10 == 0) {
        addCar(gameState, cursorX, cursorY);
    }
    moveCursor(gameState, gameState->cursorXDir, gameState->cursorYDir);
}

void buildHouse(Screen *screen, Game *gameState) {
    int cursorX = gameState->cursorX;
    int cursorY = gameState->cursorY;
    int type = kTileHouseSmall;
    gameState->map.tiles[cursorX][cursorY].type = type;
}

InputAction getAction(SDL_Keycode key) {
    InputAction action = kActionNothing;
    switch(key) {
        case SDLK_h:
        case SDLK_LEFT:
           action = kActionLeft;
           break;
        case SDLK_j:
        case SDLK_DOWN:
           action = kActionDown;
           break;
        case SDLK_k:
        case SDLK_UP:
           action = kActionUp;
           break;
        case SDLK_l:
        case SDLK_RIGHT:
           action = kActionRight;
           break;
        case SDLK_r:
           action = kActionBuildRoad;
           break;
        case SDLK_c:
           action = kActionBuildCar;
           break;
        case SDLK_z:
           action = kActionCenterCamera;
           break;
        case SDLK_b:
           action = kActionBuildHouse;
           break;
        default:
			action = kActionNothing;
    }
    return action;
}

void actionTriggered(Game *gameState, InputAction action, bool down) {
    if(down) {
        gameState->actionDownTicks[action] = 1;
    } else {
        gameState->actionDownTicks[action] = -1;
    }
}

void updateInput(Screen *screen, Game *gameState) {
    for(int i = 0; i < kActionLast; i++) {
        //update actin
        if((gameState->actionDownTicks[i] > 15 && gameState->actionDownTicks[i]%2==0) || gameState->actionDownTicks[i]==1) {
            switch(i) {
                case kActionLeft:
                    moveCursor(gameState, -1, 0);
                    break;
                case kActionDown:
                    moveCursor(gameState, 0, 1);
                    break;
                case kActionUp:
                    moveCursor(gameState, 0, -1);
                    break;
                case kActionRight:
                    moveCursor(gameState, 1, 0);
                    break;
                case kActionBuildRoad:
                    buildRoad(screen, gameState);
                    break;
                case kActionCenterCamera:
                    centerCamera(screen, gameState);
                    break;
                case kActionBuildHouse:
                    buildHouse(screen, gameState);
                    break;
                default:
                    ;
            }
        }
        //count
        if(gameState->actionDownTicks[i] > 0) {
            gameState->actionDownTicks[i]++;
        }
    }
}

int gameLoop(Screen *screen, Game *gameState) {
    SDL_Event e;
    bool keepRunning = true;
    InputAction action;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                keepRunning = false;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                action = getAction(e.key.keysym.sym);
                actionTriggered(gameState, action, e.type==SDL_KEYDOWN);
        }
    } 
    updateInput(screen, gameState);
    gameTick(gameState);
    draw(screen, gameState);
    return keepRunning;
}

bool isInBounds(Game *gameState, int x, int y) {
    return x >= 0 && y >= 0 && x < gameState->map.width && y < gameState->map.height;
}

//assumes that tiles are in the direct neighbourhood
bool canDrive(Game *gameState, int fromX, int fromY, int toX, int toY) {
    if(isInBounds(gameState, toX, toY)) {
        Tile *tile = &(gameState->map.tiles[toX][toY]);
        if(tile->type >= kTileRoadLeft && tile->type <= kTileRoadRight) {
            int toXDir = 0;
            int toYDir = 0;
            int fromXDir = 0;
            int fromYDir = 0;
            int vimCode = tile->type-kTileRoadLeft;
            vimToDirection(vimCode, &toXDir, &toYDir);
            vimCode = gameState->map.tiles[fromX][fromY].type - kTileRoadLeft;
            vimToDirection(vimCode, &fromXDir, &fromYDir);
            int dx = toX-fromX;
            int dy = toY-fromY;
            if((toXDir == dx && toYDir == dy)) {
                return tile->car==NULL;
            } else if(fromXDir== dx && fromYDir == dy 
                    && fromXDir*toXDir + fromYDir*toYDir >= 0) {
                return tile->car==NULL;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
       return false; 
    }
}

void gameTick(Game *gameState) {
    if(gameState->tick%5==0) {
        for(int i = 0; i < gameState->nCars; i++) {
            Car *car = &gameState->carList[i];
            Tile *tile = &gameState->map.tiles[car->x][car->y];
            if(random() % 100) {
                int carXDir = 0;
                int carYDir = 0;
                vimToDirection(tile->type-kTileRoadLeft, &carXDir, &carYDir);
                //Explore the neighbourhood and choose a direction
                int leftX = car->x + carYDir;
                int leftY = car->y - carXDir;
                int forwardX = car->x + carXDir;
                int forwardY = car->y + carYDir;
                int rightX = car->x - carYDir;
                int rightY = car->y + carXDir;
                bool canMoveLeft = canDrive(gameState, car->x, car->y, leftX, leftY);
                bool canMoveRight = canDrive(gameState, car->x, car->y, rightX, rightY);
                bool canMoveForward = canDrive(gameState, car->x, car->y, forwardX, forwardY);
                //hacky way to choose a random possible direction
                int sum = canMoveLeft + canMoveRight + canMoveForward;
                if(sum > 0) {
                    int chooseDir = random() % sum;
                    int counter = 0;
                    int toX = 0;
                    int toY = 0;
                    counter+=canMoveLeft;
                    if(counter > chooseDir) {
                        toX = leftX;
                        toY = leftY;
                    } else {
                        counter+=canMoveRight;
                        if(counter > chooseDir) {
                            toX = rightX;
                            toY = rightY;
                        } else {
                            toX = forwardX;
                            toY = forwardY;
                        }
                    }
                    gameState->map.tiles[toX][toY].car = car;
                    tile->car = NULL; 
                    car->x = toX;
                    car->y = toY;
                }
            } else {
                removeCar(gameState, i);
            }
        }
    }
    gameState->tick++;
}


void drawLineOnTile(SDL_Renderer *renderer, 
        int x, 
        int y, 
        int xDir, 
        int yDir, 
        int tileSize) {
    int cx = x*tileSize + tileSize/2;
    int cy = y*tileSize + tileSize/2;
    int fromX = cx - xDir*tileSize/2;
    int fromY = cy - yDir*tileSize/2;
    int toX = cx + xDir*tileSize/2;
    int toY = cy + yDir*tileSize/2;
    drawArrow(renderer, fromX, fromY, toX, toY);
}

void drawRoad(SDL_Renderer *renderer, 
        Game *gameState, 
        int x, 
        int y, 
        int xDir, 
        int yDir, 
        int tileSize) {

    SDL_Rect tileRect = {x * tileSize, y*tileSize, tileSize, tileSize};
    SDL_SetRenderDrawColor(renderer, 0x99, 0x99, 0x99, 0xFF);
    SDL_RenderFillRect(renderer, &tileRect);
    if(gameState->map.tiles[x][y].car!=NULL) {
        SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0xFF, 0xFF);
    } else {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    drawLineOnTile(renderer, x, y, xDir, yDir, tileSize);
}

int draw(Screen *screen, Game *gameState) {
    SDL_SetRenderDrawColor(screen->renderer, 0,0,0,0);
    SDL_RenderClear(screen->renderer);
    int w = gameState -> map.width;
    int h = gameState -> map.height;
    int tileSize = gameState->tileSize;
   
    int screenWidthInTiles = screen->width/tileSize;
    int screenHeightInTiles = screen->height/tileSize;
    int fromX = screen->cameraX;
    int fromY = screen->cameraY;
    int toX = fromX + screenWidthInTiles;
    int toY = fromY + screenHeightInTiles;
    int cameraX = screen->cameraX;
    int cameraY = screen->cameraY;
    if(toX > w) {
        toX = w;
    }
    if(toY > h) {
        toY = h;
    }
    for(int x = fromX; x < toX; x++) {
        for(int y = fromY; y < toY; y++) {
            int tileType = gameState -> map.tiles[x][y].type;
            switch(tileType) {
                case kTileEmpty: //nothing
                    break;
                case kTileRoadLeft: //road
                    drawRoad(screen->renderer, 
                            gameState, 
                            x-cameraX, 
                            y-cameraY, 
                            -1, 
                            0, tileSize);
                    break;
                case kTileRoadUp:
                    drawRoad(screen->renderer, 
                            gameState, 
                            x-cameraX, 
                            y-cameraY, 
                            0, 
                            -1, 
                            tileSize);
                    break;
                case kTileRoadDown:
                    drawRoad(screen->renderer, 
                            gameState, 
                            x-cameraX, 
                            y-cameraY, 
                            0, 
                            1, 
                            tileSize);
                    break;
                case kTileRoadRight:
                    drawRoad(screen->renderer, 
                            gameState, 
                            x-cameraX, 
                            y-cameraY, 
                            1, 
                            0, 
                            tileSize);
                    break;
            };
        }
    }
    //draw cars
    for(int i = 0; i < gameState->nCars; i++) {
        Car *car = &gameState->carList[i];
        int carScreenX = (-cameraX + car->x) * tileSize + tileSize/2-5;
        int carScreenY = (-cameraY + car->y) * tileSize + tileSize/2-5;
        SDL_SetRenderDrawColor(screen->renderer, 0xFF, 0,0,0xFF); 
        SDL_Rect carRect = {carScreenX, carScreenY, 10, 10};
        SDL_RenderFillRect(screen->renderer, &carRect);
    }

    //draw cursor
    int cursorX = gameState->cursorX*tileSize - screen->cameraX * tileSize;
    int cursorY = gameState->cursorY*tileSize - screen->cameraY * tileSize;
    SDL_Rect cursorOutline = {cursorX, cursorY, tileSize, tileSize};
    int cursorXDir = gameState->cursorXDir;
    int cursorYDir = gameState->cursorYDir;
    float cx = cursorOutline.x + cursorOutline.w/2;
    float cy = cursorOutline.y + cursorOutline.h/2;
    SDL_SetRenderDrawColor(screen->renderer, 0x99, 0x99, 0xFF, 0xFF);
    SDL_RenderDrawRect(screen->renderer, &cursorOutline);
    drawArrow(screen->renderer, 
            cx - cursorXDir*cursorOutline.w/2, 
            cy - cursorYDir*cursorOutline.h/2,
            cx + cursorXDir*cursorOutline.w/2, 
            cy + cursorYDir*cursorOutline.h/2);

#ifdef _WIN32
    SDL_Log("No FONTS in Windows..");
#else
    Text textureInfo;
    textureInfo.color = (SDL_Color){255,255,255,200};
    SDL_Texture *texture = createTextTexture(getFPSText(screen->FPSHistory, 60), 
            screen, 
            &textureInfo);
    SDL_RenderCopy(screen->renderer, 
            texture, 
            NULL, 
            &textureInfo.rect);
    SDL_DestroyTexture(textureInfo.texture);
#endif
    SDL_RenderPresent(screen->renderer);

    return true;
}

void addCar(Game *gameState, int x, int y) {
    Car *carList = (Car *)malloc(sizeof(Car) * (gameState->nCars+1));
    if(gameState->nCars !=0 ) {
        memcpy(carList, gameState->carList, sizeof(Car)*gameState->nCars);
    }
    carList[gameState->nCars].x = x;
    carList[gameState->nCars].y = y;
    gameState->map.tiles[x][y].car = &carList[gameState->nCars];
    gameState->nCars++;
    gameState->carList = carList;
}

void removeCar(Game *gameState, int carIdx) {
    Car *newCarList = (Car *)malloc(sizeof(Car) * (gameState->nCars-1));
    for(int i = 0; i < gameState->nCars-1; i++) {
        int idx = i < carIdx ? i : i+1;
        newCarList[i] = gameState->carList[idx];    
    } 
    Car *car = &gameState->carList[carIdx];
    Tile *tile = &gameState->map.tiles[car->x][car->y];
    tile->car=NULL;
    free(gameState->carList);
    gameState->carList = newCarList;
    --gameState->nCars;
}



