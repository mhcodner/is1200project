#include <pic32mx.h>
#include "motor.h"

void MOTOR_init() {
	ODCDSET = 3; // Bits 0 & 1 of port D to enable open drain
	TRISDCLR = 3; // Set bits 0 & 1 to 0 for output
}

void MOTOR_spin() {
	LATD = 2; // Set bit 1 to go high, bit 0 to 0 for ground
}

void MOTOR_stop() {
	LATD = 0; // Clear LATD to ground the open drain
}