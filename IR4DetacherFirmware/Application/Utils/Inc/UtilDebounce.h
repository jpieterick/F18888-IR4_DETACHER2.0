/*
 * UtilDebounce.h
 *
 *  Created on: Aug 14, 2023
 *      Author: jpieterick
 */

#ifndef _UTIL_DEBOUNCE_H_
#define _UTIL_DEBOUNCE_H_

#include <stdbool.h>
#include "pindefs.h"

void UtilDebounceReadAndDebounceInputs(void);
bool UtilDebounceCheckPinState(enum pin_id pinId,bool state2BeChecked);

#endif /* _UTIL_DEBOUNCE_H_ */
