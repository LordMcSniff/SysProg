#include "../lib/RR.h"

static queue_object *RR_queue;
static int RR_quantum = 0;
static unsigned int remaining = 0;

process *RR_tick(process *running_process)
{

	// handle process swaping
	if (running_process == NULL || running_process->time_left <= 0)
	{
		remaining = RR_quantum;
		running_process = queue_poll(RR_queue);
	}
	else if (remaining <= 0)
	{
		queue_add(running_process, RR_queue);
		remaining = RR_quantum;
		running_process = queue_poll(RR_queue);
	}

	if (running_process != NULL)
		running_process->time_left--;

	remaining--;

	return running_process;
}

int RR_startup(int quantum)
{
	if (quantum <= 0)
		return 1;

	RR_quantum = quantum;
	RR_queue = new_queue();

	if (RR_queue == NULL)
		return 1;

	return 0;
}

process *RR_new_arrival(process *arriving_process, process *running_process)
{
	if (arriving_process != NULL)
	{
		queue_add(arriving_process, RR_queue);
	}
	return running_process;
}

void RR_finish()
{
	free_queue(RR_queue);
}
