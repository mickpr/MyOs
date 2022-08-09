#ifndef _SYSCLK_H
#define _SYSCLK_H

#include <inttypes.h>

#define TASKS 2


//typedef void (*callback)();
typedef struct {
	uint32_t delay;
	void (*handler)();
	uint32_t counter;
} t_process;

void init_sysclk();
void process_add(uint8_t task, void * handler, uint32_t delay);
#endif
