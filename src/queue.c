#include "../lib/queue.h"
#include <stdlib.h>
#include <stdio.h>

int queue_add(void *new_object, queue_object *queue)
{
	if (queue == NULL)
		return 1;

	queue_object *last = queue->next;

	queue->next = calloc(1, sizeof(queue_object));
	queue->next->next = last;
	queue->next->object = new_object;
	return 0;
}

void *queue_poll(queue_object *queue)
{
	if (queue == NULL)
		return NULL;

	queue_object *second_last = queue;
	if (second_last->next == NULL)
		return NULL;

	while (second_last->next->next != NULL)
		second_last = second_last->next;

	void *item = second_last->next->object;
	free(second_last->next);
	return item;
}

queue_object *new_queue()
{
	return calloc(1, sizeof(queue_object));
}

void free_queue(queue_object *queue)
{
	while (queue != NULL)
	{
		queue_object *next = queue->next;
		free(queue);
		queue = next;
	}
}

void *queue_peek(queue_object *queue)
{
	if (queue == NULL)
		return NULL;

	if (queue->next == NULL)
		return NULL;

	return queue->next->object;
}
