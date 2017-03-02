#include <pic32mx.h>
#include "sound.h"

void SOUND_init() {
	OC1CON = 0b01110;    				// set output compare 1 module to PWM mode
	T3CONSET = 0x8000;      			// start the timer 15th bit
	OC1CON |= 0x8000;    				// turn on output compare 1 module 
	OC1RS = PR3 / 2;         			// set duty cycle 
}

// makes the sound
void SOUND_beep(int freq, int length) {
	if (freq == 0){
		PR3 = 0;
		OC1CON = 0xE;    				// turn on output compare 1 module 
	}
	else {
		OC1CON |= 0x8000;
	}
	int tempo = 8;
	PR3 = ((80000000 / 64)) / freq;
	OC1RS = PR3 / 2;
	soundlength(tempo / length);
}

// Plays in case of a fail
void soundfail(){
	SOUND_beep (175, 1);
	SOUND_beep (87, 1);
	SOUND_beep (175, 1);
	SOUND_beep (87, 1);
	SOUND_beep (0, 1);
}

void soundfailR(){                      //Wah Wah Waaaah
	SOUND_beep (165,2);
	SOUND_beep (156,2);
	SOUND_beep (147,2);
	SOUND_beep (138,1);
	SOUND_beep (0, 1);
}

void soundunlock(){                     //Plays during the unlock #Mary had a little lamb
	SOUND_beep (165,1); //e
	SOUND_beep (147,1); //d
	SOUND_beep (131,1); //c
	SOUND_beep (147,1);
	SOUND_beep (165,1);
	SOUND_beep (165,1);
	SOUND_beep (165,1);
	SOUND_beep (147,1);
	SOUND_beep (147,1);
	SOUND_beep (147,1);
	SOUND_beep (165,1);
	SOUND_beep (165,1);
	SOUND_beep (165,1);
	SOUND_beep (0, 1);
}

void soundunlockR() {                  // Starwars theme?
	SOUND_beep (165,1);
	SOUND_beep (147,1);
	SOUND_beep (165,1);
	SOUND_beep (147,1);
	SOUND_beep (165,1);
	SOUND_beep (247,1);
	SOUND_beep (147,1);
	SOUND_beep (131,1);
	SOUND_beep (220,1);
	SOUND_beep (131,1);
	SOUND_beep (0, 1);
}

// Defines how long the sound is played for
void soundlength (int tempo){
	int i = 0;
	while(1){
		if(IFS(0) & 0x100){   // if flag of Timer 2 is on (every 100ms)
			i++;
			IFSCLR(0) = 0x100;  // clear flag
		}
		if(i == tempo){
			break;
		}
	}
}

//Outputs different sound for different button combos, we can adjust frequencies later.
void btnpress (int getbtns) {
	switch (getbtns){
		case 1:                           //Starts at E and goes up (case 2 is f)
			SOUND_beep (82,1);
			SOUND_beep (0, 1);
			break;
		case 2:
			SOUND_beep (87,1);
			SOUND_beep (0, 1);
			break;
		case 3:
			SOUND_beep (92,1);
			SOUND_beep (0, 1);
			break;
		case 4:
			SOUND_beep (98,1);
			SOUND_beep (0, 1);
			break;
		case 5:
			SOUND_beep (104,1);
			SOUND_beep (0, 1);
			break;
		case 6:
			SOUND_beep (110,1);
			SOUND_beep (0, 1);
			break;
		case 7:
			SOUND_beep (117,1);
			SOUND_beep (0, 1);
			break;
		case 8:
			SOUND_beep (123,1);
			SOUND_beep (0, 1);
			break;
		case 9:
			SOUND_beep (131,1);
			SOUND_beep (0, 1);
			break;
		case 10:
			SOUND_beep (147,1);
			SOUND_beep (0, 1);
			break;
		case 11:
			SOUND_beep (165,1);
			SOUND_beep (0, 1);
			break;
		case 12:
			SOUND_beep (175,1);
			SOUND_beep (0, 1);
			break;
		case 13:
			SOUND_beep (185,1);
			SOUND_beep (0, 1);
			break;
		case 14:
			SOUND_beep (196,1);
			SOUND_beep (0, 1);
			break;
		case 15:
			SOUND_beep (220,1);
			SOUND_beep (0, 1);
			break;
	}
}

