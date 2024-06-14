#include "../lib/SRTN.h"
#include "queue_extended.h"

static queue_object *SRTN_queue;
//You can add more global variables here

process *SRTN_tick(process *running_process)
{
	// print_queue(PRIOP_queue);
	if (running_process == NULL || running_process->time_left == 0)
		running_process = queue_pop(SRTN_queue);

	if (running_process != NULL)
		running_process->time_left--;

	return running_process;
}

int SRTN_startup()
{
	SRTN_queue = new_queue();
	if (SRTN_queue == NULL)
		return 1;
	return 0;
}

process *SRTN_new_arrival(process *arriving_process, process *running_process)
{
	if (arriving_process != NULL)
	{
		if (running_process == NULL || arriving_process->time_left < running_process->time_left)
		{
			process *swap = running_process;
			running_process = arriving_process;
			arriving_process = swap;
		}

		if (arriving_process != NULL)
			queue_insert_remaining_time(arriving_process, SRTN_queue);
	}
	return running_process;
}

void SRTN_finish()
{
	free_queue(SRTN_queue);
}
