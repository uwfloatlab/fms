#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# $Id: makefile,v 1.1.1.1 2010/07/13 17:33:54 swift Exp $
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Copyright (C) 2001 Dana Swift.   Written by Dana Swift.
#  
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

.DEFAULT:
.SUFFIXES:
.PHONY: force
.PRECIOUS: %.o
SHELL=/bin/csh

binFiles := fms fmsRossSea fmsRossSeaIce
srcFiles := ApexSbe.cpp HydroObs.cpp MessageLogger.cpp PistonSensor.cpp \
            PSensorEmulator.cpp ParaSight.cpp SpyStream.cpp
objFiles := $(subst .cpp,.o, $(srcFiles)) SpyStreamLexer.o

all: swiftware headers $(binFiles)
	@echo Done making all...

fms: fms.o $(objFiles)
	gcc -m32 -ggdb $? -L. -lm -lstdc++ -lSwiftWare -lSwiftWare++ -lg++ -lfl -lSwiftWare -o $@ 

fmsRossSea: fmsRossSea.o $(objFiles)
	gcc -m32 -ggdb $? -L. -lm -lstdc++ -lSwiftWare -lSwiftWare++ -lg++ -lfl -lSwiftWare -o $@ 

fmsRossSeaIce: fmsRossSeaIce.o $(objFiles)
	gcc -m32 -ggdb $? -L. -lm -lstdc++ -lSwiftWare -lSwiftWare++ -lg++ -lfl -lSwiftWare -o $@ 

clean: clean-swiftware force
	-rm -f $(binFiles) $(addsuffix .o,$(binFiles)) $(objFiles) {fms,fmsRossSea,fmsRossSeaIce}{,.o} 

%.o: %.c
	gcc -m32 -D$(shell echo $*.c|tr a-z.- A-Z__) -Dpersistent="" -c -x c -I{.,SwiftWare/c} -ggdb \
       -Wall -Wmissing-prototypes -Wno-format-overflow $< -o $@

%.o: %.cpp
	gcc -m32 -D$(shell echo $*.cpp|tr a-z.- A-Z__) -c -x c++ -ggdb -I{.,SwiftWare/{c,c++,g++}} \
       -Wall -Wno-format-overflow $*.cpp -o $*.o 

headers: $(hdrFiles)

%.h: %.c 
	../bin/swh D=$(shell echo $*.h|tr a-z.- A-Z__) if=$< of=$@

symfiles: $(symFiles)

$(symFiles):
	-ln -s ../lib/$@

swiftware: force
	-cd SwiftWare/c; make
	-cd SwiftWare/c++; make
	-cd SwiftWare/g++; make
	-cd SwiftWare/src; make

clean-swiftware: force
	-cd SwiftWare/c; make clean
	-cd SwiftWare/c++; make clean
	-cd SwiftWare/g++; make clean
	-cd SwiftWare/src; make clean

%.cpp: %.l
	flex -s -i -o$*.cpp $*.l

SpyStreamLexer.l: SpyStream.cpp
	pac x SpyStream.cpp SpyStreamLexer.l

SpyStreamLexer.o: SpyStreamLexer.cpp
	gcc -m32 -DSPYSTREAMLEXER_CPP -c -x c++ -ggdb -I{.,SwiftWare/{c,c++,g++}} \
       -Wall -Wno-unused-function SpyStreamLexer.cpp -o SpyStreamLexer.o 
