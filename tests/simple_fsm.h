#ifndef INCLUDE_SIMPLE_FSM_H_
#define INCLUDE_SIMPLE_FSM_H_

#include "fsm.h"

enum EVENTS_simple {
	EVENT_ok,
	EVENT_fail
};

enum STATES_simple {
	STATE_init,
	STATE_one,
	STATE_two,
	STATE_shutdown
};


#endif /* INCLUDE_SIMPLE_FSM_H_ */
