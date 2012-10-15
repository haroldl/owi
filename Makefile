# sudo apt-get install libusb-1.0-0-dev

CFLAGS = -Wall

all: owi owitest morse

owi: owi.o libowi.o
	gcc owi.o libowi.o -o owi -lusb-1.0 -lncurses

owitest: owitest.o libowi.o
	gcc owitest.o libowi.o -o owitest -lusb-1.0

morse: morse.o libowi.o
	gcc morse.o libowi.o -o morse -lusb-1.0

%.o: %.c
	gcc $< $(CFLAGS) -c -o $@

clean:
	-rm -f owi owi.o libowi.o owitest owitest.o
