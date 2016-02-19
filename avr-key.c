#include <inttypes.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "io.h"
#include "key.h"
#include "state.h"

#define SIZE 4

uint8_t state;
char pass[SIZE] = { '1', '2', '3', '4' };
void init(void);

int main(void) {
	uint8_t i;
	uint8_t valid;
	char in[SIZE];

	init();

	while(1) {
		switch(state) {
			case STATE_START:
				io_out(PORT_B, ~0x80);
				in[0] = getKey();
				state = STATE_PRESS_ONE;
				break;
			case STATE_PRESS_ONE:
				io_out(PORT_B, ~0x01);
				in[1] = getKey();
				state = STATE_PRESS_TWO;
				break;
			case STATE_PRESS_TWO:
				io_out(PORT_B, ~0x03);
				in[2] = getKey();
				state = STATE_PRESS_THREE;
				break;
			case STATE_PRESS_THREE:
				io_out(PORT_B, ~0x07);
				in[3] = getKey();
				state = STATE_CHECK;
				break;
			case STATE_CHECK:
				io_out(PORT_B, ~0x0F);
				for (i = 0, valid = 1; valid && i < SIZE; i++) {
					valid &= (in[i] == pass[i]);
				}
				state = valid ? STATE_UNLOCK : STATE_LOCK;
				break;
			case STATE_LOCK:
				io_out(PORT_B, 0xFF);
				state = STATE_LOCK;
				break;
			case STATE_UNLOCK:
				io_out(PORT_B, 0x00);
				state = STATE_UNLOCK;
				break;
		}
	}

	exit(0);
}

void init(void) {
	keyInit();
	state = STATE_START;

	return;
}
