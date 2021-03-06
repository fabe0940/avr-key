CC := avr-gcc
CFLAGS := -mmcu=atmega32 -O0
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))
APPLICATION_NAME := avr-key
DEV := /dev/ttyS0

.PHONY : all clean rebuild

all : $(APPLICATION_NAME)

install : $(APPLICATION_NAME)
	avrdude -y -p atmega32 -P $(DEV) -c stk500v2 \
		-U flash:w:$(APPLICATION_NAME).hex:i

$(APPLICATION_NAME) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	objcopy -S -O ihex $(APPLICATION_NAME) $(APPLICATION_NAME).hex

%.o : %.c
	$(CC) $(CFLAGS) -c $<

avr-key.c : key.h io.h state.h
key.c : key.h
io.c : io.h

clean :
	\rm -f $(APPLICATION_NAME) $(APPLICATION_NAME).hex $(OBJ)

rebuild :
	make clean
	make all
