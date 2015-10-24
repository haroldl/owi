OWI Edge robot arm control via USB
==================================

This project provides APIs to control an OWI Edge robot arm using
C or Python.

If you need to stop the robot arm right away, just unplug the USB
cable from your computer.

Python Quickstart
-----------------

Use `setup.py` to build and install the library:

    python setup.py install

Then try it out!

    $ python
    >>> import owi
    >>> owi.init()
    >>> owi.light_on()
    >>> owi.light_off()
    >>> owi.light_toggle()
    >>> owi.light_toggle()
    >>> owi.base_left(1.5)
    >>> owi.base_left(0.5)
    >>> owi.base_right(2)
    >>> owi.shutdown()

owi command line program
-

Build the tool via `make`. You'll need `libusb-1.0` and
the headers installed for this to work. On Ubuntu you can
get this installed via

    sudo apt-get install libusb-1.0-0-dev

Use `./owi` to run the program.

There are three keys per motor: forward/stop/reverse.

     m | m | m | m |   m5
     1 | 2 | 3 | 4 | (base)
    ---+---+---+---+-----------
     e | r | t | y | i o p
     d | f | g | h |   l     <- light on/off
     c | v | b | n |

Writing your own C code
-

See `libowi.h` for the available functions.
