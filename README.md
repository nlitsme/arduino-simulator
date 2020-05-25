Arduino Simulator Framework
===========================

This is a small wrapper I use to be able to debug arduino code locally on my laptop.

This Framework is not intended as a full arduino emulator, it will do the minimal work
to make code compile and link. It will probably not even work.

Currently some SPI stuff works, some of the FastLED stuff works, some of the SdFat stuff works.

There is one major code incompatibility with the arduino environment: This simulator needs your code
to follow the normal `C++` rules for declaration order. Meaning: you will have to declare or define
a function before you use it.


Host Platform
=============

The `Makefile` currently only knows how to find the arduino files on MacOS, I have
not yet investigated where the arduino code and files live on Linux or Windows systems.


How to use
==========

build a `SampleProject`:

    make SampleProject


If you want to build `MyProject`, which uses systemlibrary `XYZ` and installed library `KLM`, you can build it like this:

    USEDLIBS=KLM SYSLIBS=XYZ  make  MyProject

When either KLM or XYZ has .cpp files which need to be linked to your project, you will have
to extend the `Makefile`, like i did with the `arduino-fat` library.


Example
=======

    make fastleddemo
    ./fastleddemo


Configuration
=============

Adding `CFLAGS=-DVERBOSE` will add output for `delay` and `loop`. Add this as an environment variable before callling make, like this:

    CFLAGS=-DVERBOSE make MyProject


AUTHOR
======

Willem Hengeveld <itsme@xs4all.nl>


