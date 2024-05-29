#include <keyboardDriver.h>
#include <videoDriver.h>
#include <stdint.h>
#include <time.h>

static void int_20();
static void int_21();

void irqDispatcher(uint64_t irq) {
	//printNoColor("irqDispatcher start");
	switch (irq) {
		case 0:
			int_20();
			break;
		case 1:
			int_21();
			break;
	}
	return;
}

void int_20() {
	timerHandler();
	//printNoColor("timerTickworking");
}

void int_21() {
	keyboardHandler();
	//printNoColor("keyboardworking");
}
