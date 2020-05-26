#
# This builds the arduino project name specified as the make target
# using the arduino simulator framework.
#
-include Makefile.local

# These paths are specific to MacOS, you may need to change them
# to something else to make this work under linux or windows
PROJECTSDIR=$(HOME)/Documents/Arduino/
ARDUINOAPP=$(firstword $(wildcard $(HOME)/Applications/Arduino.app /Applications/Arduino.app))
HARDWAREDIR=$(ARDUINOAPP)/Contents/Java/hardware
AVRTOOLS=$(HARDWAREDIR)/tools/avr
AVRBASE=$(HARDWAREDIR)/arduino/avr

SYSLIBS+=SPI
USEDLIBS+=SdFat

CFLAGS+=-O0 -g -std=c++17
CFLAGS+=-I .
CFLAGS+=$(foreach i,$(SYSLIBS),-I $(AVRBASE)/libraries/$i/src)
CFLAGS+=$(foreach i,$(USEDLIBS),-I $(PROJECTSDIR)/libraries/$i/src)
CFLAGS+=-include Arduino.h
CFLAGS+=-DARDUINO=10607

LIBTOOL=libtool

default:
	echo Specify an arduino project as make argument to build it using the simulator code.

libarduino-simulator.a:  arduino.o arduino-spi.o $(if $(USEFATLIB),libarduino-fatlib.a,arduino-fat.o)
	$(LIBTOOL) -o $@ $^

%: %.o  libarduino-simulator.a
	$(CXX) -o $@ $(filter-out %.a,$^)  $(LDFLAGS) -L. -larduino-simulator

%.o: $(PROJECTSDIR)/%
	$(CXX) -c $(CFLAGS) -x c++ $^/$(notdir $^).ino  -o $@
%.o: examples/%
	$(CXX) -c $(CFLAGS) -x c++ $^/$(notdir $^).ino  -o $@


%.o: %.cpp
	$(CXX) -c $(CFLAGS) $^  -o $@


FATDIR=$(PROJECTSDIR)/libraries/SdFat/src
libarduino-fatlib.a: FatFile.o FatVolume.o SdSpiCard.o FatFileSFN.o FatFileLFN.o
	$(LIBTOOL) -o $@ $^

%.o: $(FATDIR)/FatLib/%.cpp
	$(CXX) -c $(CFLAGS) $^  -o $@
%.o: $(FATDIR)/SdCard/%.cpp
	$(CXX) -c $(CFLAGS) $^  -o $@

clean::
	$(RM) $(wildcard *.o *.a)
