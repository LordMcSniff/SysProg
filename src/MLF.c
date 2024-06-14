#include "../lib/MLF.h"
#include "queue_extended.h"
#include <stdio.h>

#define MLF_LEVELS 4

static queue_object *MLF_queues[MLF_LEVELS];
// You can add more global variables here
//  since whe have no pow function, so just use a lookup
static unsigned short quantums[] = {1, 2, 4, 8, 16, 32, 64, 128}; // this limits the MLF Levels to 8 but idgaf
static unsigned int remaining = 0;

process *MLF_level_tick(process *running_process, short level)
{
	if (running_process == NULL || remaining <= 0)
	{
		queue_insert_priority(running_process, MLF_queues[level + 1]); // level 4 will be hindered, by the quantum never being smaller than the time_left
		running_process = queue_pop(MLF_queues[level]);

		if (level >= MLF_LEVELS - 1)
		{
			if (running_process != NULL)
				remaining = running_process->time_left;
		}
		else
		{
			remaining = quantums[level];
		}
	}

	remaining--;

	return running_process;
}

process *MLF_tick(process *running_process)
{
	if (running_process == NULL || running_process->time_left <= 0)
	{
		running_process = NULL;
		remaining = -1;
	}

	for (int i = 0; i < MLF_LEVELS; i++)
	{
		running_process = MLF_level_tick(running_process, i);
		if (running_process != NULL)
			break;
	}

	if (running_process != NULL)
		running_process->time_left--;

	return running_process;
}

int MLF_startup()
{
	for (int i = 0; i < MLF_LEVELS; i++)
	{
		MLF_queues[i] = new_queue();
		if (MLF_queues[i] == NULL) // normally you would have to handle freeing these now
			return 1;
	}
	return 0;
}

process *MLF_new_arrival(process *arriving_process, process *running_process)
{
	if (arriving_process != NULL)
		queue_insert_priority(arriving_process, MLF_queues[0]);

	return running_process;
}

void MLF_finish()
{
	for (int i = 0; i < MLF_LEVELS; i++)
		free_queue(MLF_queues[i]);
}
