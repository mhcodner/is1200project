#include <pic32mx.h>
#include <stdint.h>

#include "mipslab.h"
#include "motor.h"
#include "sound.h"

#define forever for (;;)
#define PASSWORD_LENGTH 4

int getbtns();
void init();
void display_btn();
void unlock();
void fail_message();

int main() {
	init();

	int password[PASSWORD_LENGTH] = { 1, 2, 4, 8 }; // can not contain 0
	int inputs = 0;

	forever {
		int btn = getbtns();
		int previous = btn;
		display_btn(btn);

		while ((btn = getbtns()) == previous); // Waits until change of state

		if (btn != 0 && btn == password[inputs]) {
			inputs++;
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
	char* message = "Sorry try again!";
	display_string(0, message);
	display_update();
}

void unlock() {
	char* message = "Congratulations!";
	display_string(0, message);
	display_update();
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

	display_init();
	MOTOR_init();
	SOUND_init();
}

int getbtns(){
	// Return an integer representation of the buttons currently pressed
	return ((PORTD >> 4) & 0xE) | ((PORTF >> 1) & 1);
}
