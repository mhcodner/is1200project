#include <pic32mx.h>
#include "motor.h"

void MOTOR_init() {
	OC2CONSET = 0x8021;
	OC2R = PR2 / 2;
}

void MOTOR_spin() {
	OC2CONSET = 0x8000;
}

void MOTOR_stop() {
	OC2CONCLR = 0x8000;
}