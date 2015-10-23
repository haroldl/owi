OWI Edge robot arm control via USB
==================================

This project provides APIs to control an OWI Edge robot arm using
C or Python.

Python Quickstart
-----------------

Use `setup.py` to build and install the library:

    python setup.py install

Then try it out!

    >>> import owi
    >>> owi.init()
    >>>

owi command line program
-

Use `./owi` to run the program.

     m | m | m | m | m5
     1 | 2 | 3 | 4 |----
    ---+---+---+---+
     e | r | t | y | i o p
     d | f | g | h |
     c | v | b | n | l     <- light toggle on/off
