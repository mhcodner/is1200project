#include <pic32mx.h>
#include <stdint.h>

#include "mipslab.h"
#include "motor.h"
#include "sound.h"

#define forever for (;;)
#define PASSWORD_LENGTH 4
#define TMR2PERIOD ((80000000 / 256) / 10)

int getbtns();
int getswitches();
int debug_mode();
void init();
void display_btn();
void unlock();
void fail_message();
unsigned rand();

unsigned short lfsr = 0xACE1u;
unsigned bit;

int main() {
	init();
	int i;
	//Robin mode is activated if any of the switches is on
	int password[PASSWORD_LENGTH] = { 1, 2, 4, 8 }; // can not contain 0
	if (fun_mode()) {
		for (i = 0; i < PASSWORD_LENGTH; i++){
			password[i] = (int)(rand() % 7) + 1;
		}
	}
	int inputs = 0;
	forever {
		int btn = getbtns();
		int previous = btn;
		if (debug_mode()) {
			display_string(1, itoaconv(password[inputs]));
			display_string(2, itoaconv(inputs));
		}
		else {
			display_string(1, "");
			display_string(2, "");
		}
		display_btn(btn);
		MOTOR_spin();

		while ((btn = getbtns()) == previous); // Waits until change of state

		if (btn != 0 && btn == password[inputs]) {
			inputs++;
			btnpress(btn);
		}
		else if (btn != 0 && btn != password[inputs]) {
			inputs = 0;
			fail_message();
		}

		if (inputs == PASSWORD_LENGTH) {
			inputs = 0;
			unlock();
		}
	}
	return 0;
}

void fail_message() {
	if (fun_mode()){
		char* message = "Rip! BS!";
		display_string(0, message);
		display_update();
		soundfailR();
	}
	else {
		char* message = "Sorry try again!";
		display_string(0, message);
		display_update();
		soundfail();	
	}
}


void unlock() {
	if (fun_mode()){
		char* message = "IS LIT FAAAAM!";
		display_string(0, message);
		display_update();
		soundunlockR();
	}
	else{
		char* message = "Congratulations!";
		display_string(0, message);
		display_update();
		soundunlock();
	}
}

void display_btn(int btn) {
	char* buttons = itoaconv(btn);
	display_string(3, buttons);
	display_update();
}

void init() {
	/* Set up peripheral bus clock */
	/* OSCCONbits.PBDIV = 1; */
	OSCCONCLR = 0x100000; /* clear PBDIV bit 1 */
	OSCCONSET = 0x080000; /* set PBDIV bit 0 */

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	// Enable the buttons and switches as inputs
	TRISDSET = (0xFF << 4);
	TRISFSET = 2;

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
	SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

	// Timer 2 setup
	PR2 = TMR2PERIOD;
	T2CONSET = 0x70; // setting the prescale
	TMR2 = 0; // reset timer to 0
	T2CONSET = 0x8000; // turn timer on, set bit 15 to 1

	display_init();
	MOTOR_init();
	SOUND_init();
}

int getbtns(){
	delay();
	// Return an integer representation of the buttons currently pressed
	return ((PORTD >> 4) & 0xE) | ((PORTF >> 1) & 1);
}

int fun_mode() {
	return getswitches() & 1;
}

int debug_mode() {
	return getswitches() & 0x8;
}

int getswitches(){
	return (PORTD >> 8) & 0xF;
}

unsigned rand() {
	bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
	return lfsr =  (lfsr >> 1) | (bit << 15);
}
