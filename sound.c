#include <pic32mx.h>
#include "sound.h"

void SOUND_init() {

}

void SOUND_beep(int freq, int length) {

}
// Plays in case of a fail
void soundfail(){
 SOUND_beep (200, 2);
 SOUND_beep (400, 1);
 SOUND_beep (200, 2);
 SOUND_beep (400, 1);
}
void soundunlock(){                     //Plays during the unluck#Mary had a little lamb
 SOUND_beep (659.25,2); //e
 SOUND_beep (587.33,2); //d
 SOUND_beep (554.00,2); //c
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
//Outputs different sound for different button combos, we can adjust frequencies later.
void btnpress (int getbtns){
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
}
