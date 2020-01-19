//
//  utils.h
//  VimCity-xcode
//
//  Created by Floris Fredrikze on 19/01/2020.
//

#ifndef utils_h
#define utils_h

#include "vimcity.h"
#include "list.h"

Uint64 getFPS(t_list *list, size_t size);
char *getFPSText(t_list *list, size_t size);

#endif /* utils_h */
