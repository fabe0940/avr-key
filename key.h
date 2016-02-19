#ifndef _KEY_H_
#define _KEY_H_

#include <inttypes.h>
#include "io.h"

#define ROW2 0
#define ROW3 1
#define COL1 2
#define ROW4 3
#define COL2 4
#define COL3 5
#define COL4 6
#define ROW1 7

void keyInit(void);
char getKey(void);

#endif /* _KEY_H_ */
