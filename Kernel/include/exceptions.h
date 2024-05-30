#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <stdint.h>

void exceptionDispatcher(int exception, uint64_t registers[17]);

#endif