#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>

#include "queue_lib.h"
#include "mouse_lib.h"

#define START  '1' // declare start character
#define TARGET '2' // declare target character


typedef struct start_target {   // mark start and target location 
    unsigned start[2];          // 0th index is 'y', 1th index is 'x'
    unsigned target[2];         //
} start_target;

linked_list* new_linked_list(unsigned x, unsigned y, unsigned num_step);

char* readline(int);

start_target* parser(int, struct binary_matrix*, struct char_matrix*);

#endif // LIB_H