#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>

//Frecuency table, taken from https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEgs4ia4Rd7FI71hw910jjOkROUdr9jSI57eebJ7q1CI9ib1p8WXOi9gvwtGYc_V-cDuALghLxkufDOqc2twadxB4S42259NsnxWIGBdnOxQz11iohkT0YIPphWLie47ADNzfhh3dvrt0AU/s1600/FRECUENCIA_NOTAS_MUSICALES.jpg
#define DO 261
#define RE 293
#define MI 329
#define FA 349
#define FASharp 370
#define SOL 392
#define LA 440
#define SI 493

#define DO2 523
#define RE2 587
#define MI2 659
#define FA2 698
#define SOL2 784
#define LA2 880
#define SI2 987
#define DO3 1046

static void play_sound(uint32_t nFrequence);
static void nosound();

void beep(/* int freq, int duration */);

void playNoteSound(int freq, int duration, int waitAfter);

void playMelody();
void nosound();


#endif /* SOUND_H */