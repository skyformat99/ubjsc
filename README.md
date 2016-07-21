What it is
==========

Ubjsc is a port to C of my pure 100% Python-3.x library for dealing with [UBJSON](http://ubjson.org/) format.

Someday I will prepare some mature docs of how to build it. Till then, be prepared to deal with dragons here.

For now, the library uses [cmake](https://cmake.org/).

Known to work on:
- GCC @ debian amd64.

Obviously because of the very alpha status of this library, it may work everywhere else.

What is contained
=================

So...

* include/ - obviously includes. You want to use them in your code, especially include/ubjs.h.
* src/ - sources. Surely not commented and magic.
* test/ - in-house unittest framework and related unittests that cover >=95% of the sources.
  By its nature, this is also the best source of examples how to use the code. Just ignore all asserts
  and you see the common flow.
* ptrie/ - in-house library for dealing with patricia tries. This is used by ubjson objects code.

Upgrading
=========

Not enough versions yet.

Contact
=======

* Tomasz Sieprawski <tomasz@sieprawski.eu>

