/*
 * helpers.h
 *
 *  Created on: May 22, 2023
 *  Author: Ibrahim Mohamed
 */

#ifndef HELPERS_H_
#define HELPERS_H_

#include "Std_Types.h"

enum doorLockingState{
    DOOR_LOCKED,
    DOOR_UNLOCKED
};



/**	----------------------  Functions ---------------------- **/

void unlockDoor(enum doorLockingState *LockingState);
void lockDoor(enum doorLockingState *LockingState);
void blinkHazardLights(void);


#endif /* HELPERS_H_ */
