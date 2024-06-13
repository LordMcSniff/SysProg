
#ifndef QUEUE_H

// custom functions should be included after queue.h
#include "../lib/queue.h"

#endif

#ifndef QUEUE_EXTENDED_H
#define QUEUE_EXTENDED_H

inline int queue_push(void *new_object, queue_object *queue) { queue_add(new_object, queue); };

void *queue_pop(queue_object *queue);

#endif // QUEUE_H
