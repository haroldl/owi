# sudo apt-get install libusb-1.0-0-dev
owi: owi.c
	gcc owi.c -o owi -lusb-1.0 -lncurses

clean:
	-rm -f owi
