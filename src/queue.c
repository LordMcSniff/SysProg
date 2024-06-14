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
#include "queue_extended.h"

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
	return queue_add(new_object, queue);
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

int queue_insert_priority(void *new_object, queue_object *queue)
{
	if (queue == NULL)
		return 1;

	queue_object *second_last = queue;

	while (second_last->next != NULL && ((process *)(second_last->next->object))->priority >= ((process *)new_object)->priority)
		second_last = second_last->next;

	return queue_add(new_object, second_last);
}

int queue_insert_remaining_time(void *new_object, queue_object *queue)
{
	if (queue == NULL)
		return 1;

	queue_object *second_last = queue;

	while (second_last->next != NULL && ((process *)(second_last->next->object))->time_left <= ((process *)new_object)->time_left)
		second_last = second_last->next;

	return queue_add(new_object, second_last);
}
unsigned int calc_response_ratio(void *object, unsigned int tick)
{
	process *p = (process *)object;
	if (p == NULL)
		return -1;

	return (tick - p->start_time) / p->time_left;
}

void *queue_pop_highest_response_ratio(queue_object *queue, int tick)
{
	if (queue == NULL)
		return NULL;

	queue_object *q = queue;
	unsigned int tracking_rr = -1;

	while (queue->next != NULL)
	{
		unsigned int current_rr = calc_response_ratio(queue->next->object, tick);
		if (current_rr > tracking_rr)
		{
			// save queue link of the tracking highest rr
			q = queue;
			tracking_rr = current_rr;
		}

		queue = queue->next;
	}

	return queue_poll(q);
}

// ########### END CUSTOM ###########