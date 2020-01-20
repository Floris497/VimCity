//
//  utils.c
//  VimCity-xcode
//
//  Created by Floris Fredrikze on 19/01/2020.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

Uint64 getFPS(t_list *list, size_t size)
{
    Uint64 duration = 0;

    for (size_t len = 0; len < size; len++)
    {
        duration += (Uint64)list->value;
        list = list->next;
    }

    return (SDL_GetPerformanceFrequency() / (duration / size));
}

char *getFPSText(t_list *list, size_t size)
{
    Uint64 fps = getFPS(list, size);
    char *str = malloc(log(fps) * (sizeof(char) + 1 + 1 + strlen("FPS: ")));

    sprintf(str, "FPS: %llu", fps);
    return str;
}
