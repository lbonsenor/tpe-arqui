#include <eliminator.h>
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3
#define SPEED 5

char p1Keys[4] = {'w', 'a', 's', 'd'};
char p2Keys[4] = {'i','j', 'k', 'l'};

char p1Dir = DOWN;
char p2Dir = UP;

uint32_t p1Color = 0xFF0000;
uint32_t p2Color = 0x00FF00;

uint64_t p1Coord[2] = {0,0};    // pxCoord is a coordinate to center
uint64_t p2Coord[2] = {0,0};

void changeDir(char c){
    switch (c)
    {
        case 'w':   p1Dir = UP;
                    break;
        case 'a':   p1Dir = LEFT;
                    break;
        case 's':   p1Dir = DOWN;
                    break;
        case 'd':   p1Dir = RIGHT;
                    break;
        case 'i':   p2Dir = UP;
                    break;
        case 'j':   p2Dir = LEFT;
                    break;
        case 'k':   p2Dir = DOWN;
                    break;
        case 'l':   p2Dir = RIGHT;
                    break;
        default:    break;
    }
}

void move(){
    switch (p1Dir)
    {
    case UP:    p1Coord[1]--;
                break;
    case LEFT:  p1Coord[0]--;
                break;
    case DOWN:  p1Coord[1]++;
                break;
    case RIGHT: p1Coord[0]++;
                break;
    default:    break;
    }

    switch (p2Dir)
    {
    case UP:    p2Coord[1]--;
                break;
    case LEFT:  p2Coord[0]--;
                break;
    case DOWN:  p2Coord[1]++;
                break;
    case RIGHT: p2Coord[0]++;
                break;
    default:    break;
    }
}

void play1(){
    int counter = 0; // This counter is going to serve as a form of time checking for in-game velocity, it is unnecesary to make a syscall
    int lost = 0;
}
void play2(){
    int counter = 0; // This counter is going to serve as a form of time checking for in-game velocity, it is unnecesary to make a syscall
    int lost = 0;    // 1 if Player 1 Lost, 2 if Player 2 Lost
}