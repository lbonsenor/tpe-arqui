#include"music.h"
#include "libSysCalls.h"

void errorSound() {
    /* version 1
    make_sound(440,5,1); //6
    make_sound(349,5,1); //4
    make_sound(329,5,1); //3 */
    //version 2
    make_sound(261,5,0);
    make_sound(329,5,0);
    make_sound(195,5,0);
    make_sound(130,5,0);
}

void playDragonMelody() {
    /*
    make_sound(391,10,0); //5
    make_sound(391,10,1);

    make_sound(329,10,0); //3
    make_sound(349,7,0);  //4
    make_sound(391,7,0);  
    make_sound(440,7,1);  //6 

    make_sound(391,10,0); 
    make_sound(349,10,0);
    make_sound(329,10,0);
    make_sound(293,10,2); //2

    make_sound(329,10,0);
    make_sound(329,10,1); 

    make_sound(261,10,0); //1
    make_sound(293,7,0);
    make_sound(329,7,0);
    make_sound(349,7,0);

    make_sound(329,10,0);
    make_sound(293,7,0);
    make_sound(261,7,0); 
    make_sound(246,7,3); //7 

    make_sound(246,7,3);
    make_sound(246,7,3);*/
    // Chau cancion de dragonB :(
    
    //W Mario
    make_sound(659,5,1);
    make_sound(659,5,1);
    make_sound(659,5,1);
    make_sound(523,5,1);
    make_sound(659,5,1);
    make_sound(783,5,2);
}

void playWahWahWah() {
    make_sound(195,10,2);
    make_sound(184,10,2);
    make_sound(174,10,2);
    make_sound(146,6,0);
    make_sound(138,6,0);
    make_sound(146,6,0);
    make_sound(138,6,0);
    make_sound(146,6,0);
}