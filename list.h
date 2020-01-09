//
//  list.h
//  
//
//  Created by Floris Fredrikze on 09/01/2020.
//

#ifndef list_h
#define list_h

typedef struct s_list t_list;

struct s_list {
    void *value;
    t_list *next;
};

t_list *circularList(size_t size);

#endif /* list_h */
