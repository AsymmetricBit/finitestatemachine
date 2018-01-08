/* Copyright (C) 2017-2018 Andre Eggert - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GPLv3 license. The full license text can
 * be found in the LICENSE file.
 *
 * If you have not received the LICENSE file,
 * please write to: andre@droidperception.com,
 * or visit :
 * https://github.com/AsymmetricBit/finitestatemachine/
 */

#ifndef INCLUDE_FSM_H
#define INCLUDE_FSM_H

#include "stdint.h"

#define FSM_EXTERNAL_EVENT_NONE (-1)

enum FSM_retval
{
  FSM_error = -3,
  FSM_busy = -2,
  FSM_bad_input = -1,
  FSM_ok = 0,
};

struct fsm_transition;

struct fsm
{
  int8_t external_event;
  int8_t current_state;
  int8_t current_event;
  uint16_t fsm_size;
  void *priv;
  void (*init_func)(struct fsm *instance);
  void (*update_func)(struct fsm *instance);
  const struct fsm_transition *transit_matrix;
};

struct fsm_transition
{
  int8_t state;
  int8_t event;
  int8_t next_state;
  int8_t (*func)(struct fsm *instance);
};

/**
 * @brief Initialize the state machine given by \c instance.
 * This must be called before \c FSM_update can be used.
 * @param[in,out] instance - FSM instance
 * @param[in] starte_state - State that \c instance will be initialized to.
 * @param[in] starte_event - Event that \c instance will be initialized to.
 */
FSM_retval FSM_init(struct fsm *instance, int8_t start_state, int8_t start_event);

/**
 * @brief Update the state machine state. This will trigger a state
 * change that depends on the internal state and given event
 * @param[in,out] instance - FSM instance
 * @return FSM_error - If there is no state defined for the current event transition.
 */
FSM_retval FSM_update(struct fsm *instance, int8_t *new_state);

/**
 * @brief Return the current state of the FSM
 * @param[in,out] instance - FSM instance
 * @return FSM state
 */
int8_t FSM_get_current_state(const struct fsm *instance);

/**
 * @brief Returns the currently set external event.
 * @param[in,out] instance - FSM instance
 * @param[out] event - external event
 */

FSM_retval FSM_get_external_event(const struct fsm *instance, int8_t *event);

/**
 * @brief Set an external event that will be used on the next possible transition.
 * @param[in,out] instance - FSM instance
 * @param[out] event - external event
 */

FSM_retval FSM_set_external_event(struct fsm *instance, int8_t event);

#endif /* INCLUDE_FSM_H */
