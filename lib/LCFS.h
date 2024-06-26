#ifndef LCFS_H
#define LCFS_H
#include "queue.h"
#include "process.h"
#include <stdlib.h>

/**
 * determine which is the current process to be processed. 
 * @param running_process the prevously running process
 * @result a pointer to the new running process (if something changed) or to the previously running process
 */
process *LCFS_tick(process * running_process);

/**
 * Do everything you have to at startup in this function. It is called once.
 * @result 0 if everything was fine. Any other number if there was an error.
 */
int LCFS_startup();

/**
 * Handle new arrivals
 * @param arriving_process A pointer to a new arriving process
 * @param running_process A pointer to previously running process
 * @result A pointer to the new active (running) process (if that changed) or to the previously running process
 */
process *LCFS_new_arrival(process * arriving_process,
			  process * running_process);

/**
 * is called once after the all processes were handled. In case you want to cleanup something
 */
void LCFS_finish();
#endif				//LCFS_H
