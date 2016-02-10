#include <inttypes.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "state.h"

uint8_t state;
void init(void);

int main(void) {
	exit(0);
}

void init(void) {
	state = STATE_START;
}
