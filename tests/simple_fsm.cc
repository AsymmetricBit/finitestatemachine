#include <stddef.h>
#include "simple_fsm.h"

int8_t func_state_one(struct fsm *instance);
int8_t func_state_two(struct fsm *instance);

const struct fsm_transition fsm_simple_transit[] = {
		{STATE_init, EVENT_ok, STATE_one, func_state_one},
		{STATE_one, EVENT_ok, STATE_two, func_state_two},
		{STATE_two, EVENT_ok, STATE_shutdown, func_state_two},
};


int8_t func_state_one(struct fsm *instance)
{
	return EVENT_ok;
}

int8_t func_state_two(struct fsm *instance)
{
	return EVENT_ok;
}

int8_t func_state_shutdown(struct fsm *instance)
{
	return EVENT_ok;
}

struct fsm fsm_simple = {
		FSM_EXTERNAL_EVENT_NONE,
		-1,
		-1,
		sizeof(fsm_simple_transit)/sizeof(struct fsm_transition),
		NULL,
		NULL,
		NULL,
		fsm_simple_transit,
};
