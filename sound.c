#include <pic32mx.h>
#include "sound.h"

void SOUND_init() {

}

void SOUND_beep(int freq, int length) {

}
void soundfail(){
 SOUND_beep (200, 2);
 SOUND_beep (400, 1);
 SOUND_beep (200, 2);
 SOUND_beep (400, 1);
}
void soundunlock(){                     //#Mary had a little lamb
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
