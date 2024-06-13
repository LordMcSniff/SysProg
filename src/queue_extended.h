
#ifndef QUEUE_H

// custom functions should be included after queue.h
#include "../lib/queue.h"

#endif

#ifdef QUEUE_H
#ifndef QUEUE_EXTENDED_H
#define QUEUE_EXTENDED_H

void print_queue(queue_object *queue);

int queue_push(void *new_object, queue_object *queue);

void *queue_pop(queue_object *queue);

#endif // QUEUE_EXTENDED_H
#endif // QUEUE_H
