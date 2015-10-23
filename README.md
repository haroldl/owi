OWI Edge robot arm control via USB
==================================

This project provides APIs to control an OWI Edge robot arm using
C or Python.

Python Quickstart
-----------------

Use `setup.py` to build and install the library:

    python setup.py install

Then try it out!

    $ python
    >>> import owiedge
    >>> owiedge.init()
    >>> owiedge.light_on()
    >>> owiedge.light_off()
    >>> owiedge.light_toggle()
    >>> owiedge.light_toggle()
    >>> owiedge.base_left(1.5)
    >>> owiedge.base_left(0.5)
    >>> owiedge.base_right(2)
    >>> owiedge.shutdown()

owi command line program
-

Use `./owi` to run the program.

     m | m | m | m | m5
     1 | 2 | 3 | 4 |----
    ---+---+---+---+
     e | r | t | y | i o p
     d | f | g | h |
     c | v | b | n | l     <- light toggle on/off
