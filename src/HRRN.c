#include "../lib/HRRN.h"
#include "queue_extended.h"

static queue_object *HRRN_queue;
unsigned int tick = 0;
//You can add more global variables and structs here

process *HRRN_tick(process *running_process)
{
	// print_queue(HRRN_queue);
	if (running_process == NULL || running_process->time_left == 0)
		running_process = queue_pop_highest_response_ratio(HRRN_queue, tick++);

	if (running_process != NULL)
		running_process->time_left--;

	return running_process;
}

int HRRN_startup()
{
	HRRN_queue = new_queue();
	if (HRRN_queue == NULL)
		return 1;
	return 0;
}

process *HRRN_new_arrival(process *arriving_process, process *running_process)
{
	if (arriving_process != NULL)
		queue_add(arriving_process, HRRN_queue);

	return running_process;
}

void HRRN_finish()
{
	free_queue(HRRN_queue);
}
