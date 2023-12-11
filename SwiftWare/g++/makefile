#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# $Id: makefile,v 1.1.1.1 2010/07/13 17:33:54 swift Exp $
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# RCS Log:
#
# $Log: makefile,v $
# Revision 1.1.1.1  2010/07/13 17:33:54  swift
# This distribution contains the source code for the Float Mission Simulator
# used to simulate, debug, and test float firmware.
#
# Revision 1.3  2008/07/14 16:59:28  swift
# Modifications for use with Fedora.
#
# Revision 1.2  2006/11/11 18:59:17  swift
# Added targets to make symbolic links.
#
# Revision 1.1  2006/11/11 18:43:06  swift
# Added G++ functionality to the project for energy budget model.
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.SUFFIXES:
.DEFAULT:
.PRECIOUS: %.o
.PHONY: all test fresh clean force

SHELL=/bin/csh
libDir      = ../..#
libName     = g++#

# construct a list of all source files in source directory
srcFiles = $(wildcard *.cpp *.cc *.c)

# construct a list of base names
baseNames = $(basename $(notdir $(srcFiles)))

# construct a list of object file names
objFiles = $(addsuffix .o, $(baseNames))

# construct a list of symbolic links
symFiles = GetOpt.oop SmplStat.oop Vec.oop

all: $(symFiles) $(objFiles)
	ar rvu $(libDir)/lib$(libName).a $(objFiles)
	ranlib $(libDir)/lib$(libName).a
	@echo done making files in $(lib) ...

test:
	@echo libDir    = $(libDir)
	@echo baseNames = $(baseNames)
	@echo srcFiles  = $(srcFiles)
	@echo objFiles  = $(objFiles)

fresh: clean all

clean: force
	- rm -f $(objFiles) $(libDir)/lib$(libName).a

%.o:  %.cpp
	gcc -m32 -x c++ -D$(shell echo $*.cpp|tr a-z. A-Z_) -c -ggdb -I./{.,../c}/ -Wall -o $@ $<

%.o:  %.cc 
	gcc -m32 -x c++ -c -ggdb -I./ -Wall -o $@ $<

%.o:  %.c
	gcc -m32 -x c -c -ggdb -I./ -I../c/ -Wall -Wmissing-prototypes -o $@ $<

GetOpt.oop:
	ln -s GetOpt.{cpp,oop}

SmplStat.oop:
	ln -s SmplStat.{cpp,oop}

Vec.oop:
	ln -s Vec.{cpp,oop}
