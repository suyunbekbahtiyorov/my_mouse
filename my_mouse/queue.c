
#include "lib.h"

void push_back(linked_list** self, linked_list* new_link)
{
    if (*self == NULL)
        *self = new_link;
    else
    {
        linked_list* lastNode = *self;
        while (lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }
        lastNode->next = new_link;
    }
}

void pop(linked_list** self)
{
    if (*self == NULL) return;
    linked_list* temp = *self;
    *self = (*self)->next;
    free(temp);
}

linked_list* front(linked_list* self)
{
    return self;
}

bool is_empty(linked_list** self)
{
    return (*self == NULL);
}

linked_list* new_linked_list(unsigned x, unsigned y, unsigned num_step)
{
    linked_list* buff = (linked_list*)malloc(sizeof(linked_list));
    buff->loc = (locator*)malloc(sizeof(locator));
    buff->loc->x = x;
    buff->loc->y = y;
    buff->num_step = num_step;
    buff->next = NULL;
    return buff;
}

struct queue New()
{
    return (struct queue){
        .data = NULL,
        .push_back = &push_back,
        .pop = &pop,
        .front = &front,
        .is_empty = &is_empty,
    };
}

const struct QueueClass Queue = {.New = &New};
