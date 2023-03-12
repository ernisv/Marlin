#ifndef __STEPPER_H
#define __STEPPER_H

#include <stdint.h> // uint8_t

uint_fast8_t stepper_event(struct timer *t);

uint8_t klipper_stepper_active();

#endif // stepper.h
