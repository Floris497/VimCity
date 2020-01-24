//
//  text.c
//  VimCity
//
//  Created by Floris Fredrikze on 18/01/2020.
//

#include <stdio.h>
#include <stdbool.h>

#include "vimcity.h"

SDL_Texture *createTextTexture( const char* string, Screen *screenState, Text *textureInfo)
{
    SDL_Color color = { 255, 255, 255 , 0};
    SDL_Surface *surface = TTF_RenderUTF8_Blended(screenState->font, string, color);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(screenState->renderer, surface);
    textureInfo->texture = texture;

    SDL_QueryTexture(texture,
                     NULL,
                     NULL,
                     &textureInfo->rect.w,
                     &textureInfo->rect.h);

    textureInfo->rect.x = screenState->width - textureInfo->rect.w - 10;
    textureInfo->rect.y = 10;

    SDL_FreeSurface(surface);
    return texture;
}
