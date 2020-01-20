//
//  list.c
//  
//
//  Created by Floris Fredrikze on 09/01/2020.
//

#include <stdlib.h>
#include "list.h"

t_list *circularList(size_t size) {
    void *mem = malloc(size * sizeof(t_list));
    
    t_list *list;
    
    for (size_t i = 0; i < size; i++) {
        list = &((t_list *)mem)[i];
        list->next = &list[1];
        list->value = (int *)16;
    }
    
    list = &((t_list *)mem)[size - 1];
    list->next = (t_list *)mem;
    
    return (t_list *)mem;
}
