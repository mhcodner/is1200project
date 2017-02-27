#include <pic32mx.h>
#include "sound.h"

#define TMR3PERIOD ((80000000 / 256) / 10)
#define T3CON PIC32_R(0x0A00)
#define T3CONSET PIC32_R(0x0A08)
#define TMR3 PIC32_R(0x0A10)
#define PR3 PIC32_R(0x0A20)

void SOUND_init() {
	OC1CON = 0b01110;    				// set output compare 1 module to PMW mode
	T3CONSET = 0x8000;      			// start the timer 15th bit
	OC1CON |= 0x8000;    				// turn on output compare 1 module 
}
// makes the sound
void SOUND_beep(double freq, int length) {
	if (freq == 0){
		PR3 = 0;
		OC1CON = 0x000E;    			// turn on output compare 1 module 
	}
	PR3 = ((80000000 / 64)) / freq;
	
// not sure if this works, and still gotta learn how to make it buzz for a certain time.
// shall we do it like in lab 3 with time out count?
}

// Plays in case of a fail
void soundfail(){
	SOUND_beep (200, 2);
	SOUND_beep (400, 1);
	SOUND_beep (200, 2);
	SOUND_beep (400, 1);
}
void soundfailR(){                      //Wah Wah Waaaah
	SOUND_beep (659.25,2);
	SOUND_beep (622.25,2);
	SOUND_beep (587.33,2);
	SOUND_beep (554.37,4);
}
void soundunlock(){                     //Plays during the unlock #Mary had a little lamb
	SOUND_beep (659.25,2); //e
	SOUND_beep (587.33,2); //d
	SOUND_beep (523.23,2); //c
	SOUND_beep (587.33,2);
	SOUND_beep (659.25,2);
	SOUND_beep (659.25,2);
	SOUND_beep (659.25,2);
	SOUND_beep (587.33,2);
	SOUND_beep (587.33,2);
	SOUND_beep (587.33,2);
	SOUND_beep (659.25,2);
	SOUND_beep (659.25,2);
	SOUND_beep (659.25,2);
}

void soundunlockR() {                  // Starwars theme?
	SOUND_beep (659.25,2);
	SOUND_beep (587.33,2);
	SOUND_beep (659.25,2);
	SOUND_beep (587.33,2);
	SOUND_beep (659.25,2);
	SOUND_beep (987.77,2);
	SOUND_beep (587.33,2);
	SOUND_beep (523.23,2);
	SOUND_beep (880.00,2);
	SOUND_beep (523.23,2);
}
//Outputs different sound for different button combos, we can adjust frequencies later.
void btnpress (int getbtns) {
	switch (getbtns){
		case 1:
			SOUND_beep (159.25,2);
			break;
		case 2:
			SOUND_beep (259.25,2);
			break;
		case 3:
			SOUND_beep (359.25,2);
			break;
		case 4:
			SOUND_beep (459.25,2);
			break;
		case 5:
			SOUND_beep (559.25,2);
			break;
		case 6:
			SOUND_beep (659.25,2);
			break;
		case 7:
			SOUND_beep (759.25,2);
			break;
	}
}
