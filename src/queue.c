#include "../lib/queue.h"
#include <stdlib.h>
#include <stdio.h>

int queue_add(void *new_object, queue_object *queue)
{
	if (queue == NULL)
		return 1;

	queue_object *tail = queue->next;

	queue->next = calloc(1, sizeof(queue_object));
	queue->next->next = tail;
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
	second_last->next = NULL;
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

// ########### CUSTOM ###########
#include "../lib/process.h"

void print_queue(queue_object *queue)
{
	printf("\n >>> QUEUE: %p <<< \n", queue);

	while (queue != NULL)
	{
		process *p = (process *)(queue->object);
		char pid = (p != NULL) ? p->id : '0';
		printf(" | %p, %p, %c |\n", queue, queue->object, pid);

		queue = queue->next;
	}
	printf("\n");
}
int queue_push(void *new_object, queue_object *queue)
{
	queue_add(new_object, queue);
}

void *queue_pop(queue_object *queue)
{
	if (queue == NULL)
		return NULL;
	if (queue->next == NULL)
		return NULL;

	queue_object *tail = queue->next->next;
	void *item = queue->next->object;

	free(queue->next);
	queue->next = tail;
	return item;
}

// ########### END CUSTOM ###########