.SUFFIXES : .cu .cu_dbg_o .c_dbg_o .cpp_dbg_o .cu_rel_o .c_rel_o .cpp_rel_o .cubin

CXX        := g++
CC         := gcc
LINK       := g++ 

# flags for C++ compiler:
CFLAGS		= -g -Wall 
SRCDIR			= .
INCFLAGS		= 	

# libraries to link with:
LIBPATH = 
LDFLAGS = -lGL -lGLU -lglut -lm
OBJFILES = main.o 

# ***********************************************************************************
all:	main

main:	$(OBJFILES)
	@echo "Linking ...."
	$(LINK)  $(CFLAG) $(CPPFLAGS) $(LIBPATH) $(OBJFILES) $(LDFLAGS) -o main
	
.c.o:	$*.h
	@echo "Compiling C code ...."
	$(CXX) -o $*.o -c $(CFLAGS) $(DEFFLAGS) $(INCFLAGS) $*.c

.cpp.o:	$*.h
	@echo "Compiling C++ code ...."
	$(CXX) -o $*.o -c $(CFLAGS)  $(DEFFLAGS) $(INCFLAGS) $*.cpp


clean:	
	@echo "Clearing ..."
	rm -f *.o *.bck core *~ main


