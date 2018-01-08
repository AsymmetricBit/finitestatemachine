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

FSM_retval FSM_init(struct fsm *instance, int8_t start_state, int8_t start_event);
FSM_retval FSM_update(struct fsm *instance, int8_t *new_state);

int8_t FSM_get_current_state(const struct fsm *instance);

FSM_retval FSM_get_external_event(const struct fsm *instance, int8_t *event);
FSM_retval FSM_set_external_event(struct fsm *instance, int8_t event);

#endif /* INCLUDE_FSM_H */
