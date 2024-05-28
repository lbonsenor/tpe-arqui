#ifndef _INTERRUPTIONS_H_
#define _INTERRUPTIONS_H_

#include <stdint.h>

void _cli(void);
void _sti8(void);
void _hlt(void);
void _sti(void);

void picMasterMask(uint8_t mask);
void picSlaveMask(uint8_t mask);

#endif