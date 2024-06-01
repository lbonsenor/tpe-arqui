// Soundcode source: https://wiki.osdev.org/PC_Speaker

#include <lib.h>
#include <time.h>
#include <sound.h>

extern void outb(uint32_t param1, uint32_t param2);
extern uint8_t inb(uint16_t param1);

// Play sound using built in speaker
void play_sound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
    // Sets the sound frequence
 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (Div));
 	outb(0x42, (uint8_t) (Div >> 8));
 
    // Plays the sound in the speakers
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
}
 
// Makes it stop
void nosound() {
 	uint8_t tmp = inb(0x61) & 0xFC;
 	outb(0x61, tmp);
}
 
// Makes a beep
void beep() {
 	 play_sound(1000);
 	 timer_wait(10);
 	 nosound();
 }

void playNoteSound(int freq, int duration, int wait) {
    play_sound(freq);
    timer_wait(duration);
    nosound();
    timer_wait(wait);
 }

void playMelody() {
	playNoteSound(DO,10,0);
	playNoteSound(RE,10,0);
	playNoteSound(MI,10,0);
	playNoteSound(SOL,10,0);
	playNoteSound(SOL,10,0);

	playNoteSound(MI,10,0);
	playNoteSound(RE,10,0);
	playNoteSound(DO,10,0);
	playNoteSound(RE,10,0);
	playNoteSound(MI,10,0);
	timer_wait(10);
	
	playNoteSound(DO,10,0);
	playNoteSound(RE,10,0);
	playNoteSound(MI,10,0);
	playNoteSound(SI,10,0);
	playNoteSound(DO2,10,1);

	playNoteSound(DO2,10,1);
	playNoteSound(SI,10,0);
	playNoteSound(LA,10,0);
	playNoteSound(SOL,10,0);
	playNoteSound(LA,10,0);
	playNoteSound(LA,10,0);
	playNoteSound(SOL,10,0);
	timer_wait(10);

	playNoteSound(DO,10,0);
	playNoteSound(RE,10,0);
	playNoteSound(MI,10,0);
	playNoteSound(SOL,10,0);
	playNoteSound(SOL,10,0);

	playNoteSound(MI,10,0);
	playNoteSound(RE,10,0);
	playNoteSound(DO,10,0);
	playNoteSound(RE,10,0);
	playNoteSound(DO,10,0);
	timer_wait(10);

	playNoteSound(DO,10,0);
	playNoteSound(RE,10,0);
	playNoteSound(MI,10,0);
	playNoteSound(SOL,10,0);

	playNoteSound(SOL,10,0);
	playNoteSound(FA,10,0);
	playNoteSound(FA,10,0);
	playNoteSound(MI,10,0);

	playNoteSound(DO2,10,1);
	playNoteSound(MI,10,0);
	playNoteSound(MI,10,0);
	playNoteSound(RE,10,0);
}