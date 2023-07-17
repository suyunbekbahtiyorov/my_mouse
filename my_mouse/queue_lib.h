
#ifndef QUEUE_LIB_H
#define QUEUE_LIB_H

typedef struct s_locator { // to handle coordinate and step
    unsigned x, y;
} locator;

typedef struct s_linked_list {
    locator* loc;
    unsigned num_step;
    struct s_linked_list* next;
} linked_list;

struct queue {
    linked_list* data ;
    void (*const push_back) (linked_list**, linked_list*); // add last
    void (*const pop) (linked_list**); // remove first
    linked_list* (*const front) (linked_list*); //get first  queue
    bool (*const is_empty) (linked_list**);
} ;

extern const struct QueueClass {
    struct queue  (*New)();
} Queue;

#endif // QUEUE_LIB_H