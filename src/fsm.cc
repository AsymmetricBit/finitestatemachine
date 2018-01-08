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

#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include "fsm.h"

FSM_retval FSM_init(struct fsm *instance, int8_t start_state, int8_t start_event)
{
  instance->current_event = start_event;
  instance->current_state = start_state;

  assert(instance->transit_matrix != NULL);
  assert(instance->fsm_size > 0);

  if (instance->init_func != NULL)
    instance->init_func(instance);

  return FSM_ok;
}

int8_t FSM_get_current_state(const struct fsm *instance)
{
  int8_t ret = -1;

  if (instance != NULL)
    ret = instance->current_state;

  return ret;
}

FSM_retval FSM_get_external_event(const struct fsm *instance, int8_t *event)
{
  *event = instance->external_event;
  return FSM_ok;
}

FSM_retval FSM_set_external_event(struct fsm *instance, int8_t event)
{
  if (instance->external_event == FSM_EXTERNAL_EVENT_NONE || event == FSM_EXTERNAL_EVENT_NONE)
    instance->external_event = event;
  else
    return FSM_busy;

  return FSM_ok;
}

static FSM_retval FSM_get_next_state(const struct fsm *instance, int8_t cur_state, int8_t event, int8_t *next_state)
{
  uint16_t i;

  for (i = 0; i < instance->fsm_size; i++)
  {

    if (instance->transit_matrix[i].state == cur_state && instance->transit_matrix[i].event == event)
    {
      *next_state = i;
      return FSM_ok;
    }
  }

  return FSM_error;
}

FSM_retval FSM_update(struct fsm *instance, int8_t *new_state)
{
  int8_t temp_event = -1;
  int8_t idx = -1;
  FSM_retval ret;

  if (FSM_get_external_event(instance, &temp_event) > 0)
  {
    ret = FSM_get_next_state(instance, instance->current_state, temp_event, &idx);

    if (ret < 0)
      ret = FSM_get_next_state(instance, instance->current_state, instance->current_event, &idx);
    else
      FSM_set_external_event(instance, FSM_EXTERNAL_EVENT_NONE);

  } else
  {
    ret = FSM_get_next_state(instance, instance->current_state, instance->current_event, &idx);
  }

  if (idx < 0)
    return FSM_error;

  if (instance->transit_matrix[idx].func != NULL)
    temp_event = instance->transit_matrix[idx].func(instance);

  instance->current_event = temp_event;
  instance->current_state = instance->transit_matrix[idx].next_state;

  if (instance->update_func != NULL)
    instance->update_func(instance);

  *new_state = instance->current_state;
  return FSM_ok;
}
