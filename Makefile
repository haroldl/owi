# sudo apt-get install libusb-1.0-0-dev

CFLAGS = -Wall

owi: owi.o libowi.o
	gcc owi.o libowi.o -o owi -lusb-1.0 -lncurses

%.o: %.c
	gcc $< $(CFLAGS) -c -o $@

clean:
	-rm -f owi owi.o libowi.o
