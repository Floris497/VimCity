//
//  init.h
//  VimCity-xcode
//
//  Created by Floris Fredrikze on 19/01/2020.
//

#ifndef init_h
#define init_h

#include <SDL.h>
#include <SDL_ttf.h>

#include "vimcity.h"

void init_graphics(t_screen *screenState);
void init_game(t_game *gameState);

#endif /* init_h */
