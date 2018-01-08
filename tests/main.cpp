#include <iostream>
#include "gtest/gtest.h"

#include "fsm.h"
#include "simple_fsm.h"

TEST(Initialization, simple) {

	extern struct fsm fsm_simple;
	FSM_retval ret;
	int8_t state;

	ret = FSM_init(&fsm_simple, STATE_init, EVENT_ok);
	EXPECT_EQ(ret, 0);

	ret = FSM_update(&fsm_simple, &state);
	EXPECT_EQ(state, STATE_one);
	EXPECT_EQ(ret, FSM_ok);

	ret = FSM_update(&fsm_simple, &state);
	EXPECT_EQ(state, STATE_two);
	EXPECT_EQ(ret, FSM_ok);

	ret = FSM_update(&fsm_simple, &state);
	EXPECT_EQ(state, STATE_shutdown);
	EXPECT_EQ(ret, FSM_ok);
}
