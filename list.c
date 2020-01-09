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
        list = mem + (sizeof(t_list) * i);
        list->next = (t_list *)(sizeof(t_list) * (i + 1));
    }
    
    list = mem + (sizeof(t_list) * size);
    list->next = (t_list *)mem;
    
    return (t_list *)mem;
}
