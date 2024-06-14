#include "../lib/PRIOP.h"
#include "queue_extended.h"
#include <stdio.h>

static queue_object *PRIOP_queue;
//You can add more global variables here

process *PRIOP_tick(process *running_process)
{
	// print_queue(PRIOP_queue);
	if (running_process == NULL || running_process->time_left == 0)
		running_process = queue_pop(PRIOP_queue);

	if (running_process != NULL)
		running_process->time_left--;

	return running_process;
}

int PRIOP_startup()
{
	PRIOP_queue = new_queue();
	if (PRIOP_queue == NULL)
		return 1;
	return 0;
}

process *PRIOP_new_arrival(process *arriving_process, process *running_process)
{
	if (arriving_process != NULL)
	{
		if (running_process == NULL || arriving_process->priority > running_process->priority)
		{
			process *swap = running_process;
			running_process = arriving_process;
			arriving_process = swap;
		}

		if (arriving_process != NULL)
			queue_insert_priority(arriving_process, PRIOP_queue);
	}
	return running_process;
}

void PRIOP_finish()
{
	free_queue(PRIOP_queue);
}
