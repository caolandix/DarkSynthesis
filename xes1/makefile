##
##	ES1 Makefile 
##
FILE_EXT = 
##
EXEC=		xes1
##
CC = gcc
##
##      C compiler.  Normally cc; is scc on Unicos.
#
#  This program needs libtk.a, libtcl.a, libXpm.a, and libXG20.a.
LIBDIRS = -L/usr/local/lib/xgrafix -L/usr/local/lib -L/usr/X11R6/lib
##
CFLAGS= -O2
##
##      Flags used for compiling.  -O for optimization, which is optional.
##	If the X11 include files are not located in /usr/include/X11, you
##	must specify the directory as a flag prefixed by -I.  For instance, 
##	if the include files for X11 are located in /usr/local/include, the 
##	flag -I/usr/local/include must also be passed.
##
LIBS  = $(LIBDIRS) -lXGC250 -ltk -ltcl -lXpm -lX11 -lm -ldl
##
##      Libraries and their directories used in loading.  Normal is -lm and -lX11
##	for the Math and X11 libraries, which is NOT optional.  On Unicos, -lnet
##	is also used.  If the X11 libraries are not located in /usr/lib/X11, you
##	must also specify the directory as a flag prefixed by -L.  For instance,
##	if the include files for X11 are located in /usr/local/lib, the flag
##	-L/usr/local/lib must also be passed.  On Sun, use -Bstatic to avoid
##	problems with differing versions of OS.  Man cc for more information on flags.
##
##
ES1OBJ=	fft.o es1.o set.o init.o move.o accel.o fields.o initwin.o 

all:	$(ES1OBJ) $(EXEC)

.c.o:	es1.h
	$(CC) -c $(CFLAGS) $*.c

$(EXEC):	$(ES1OBJ)
		$(CC) $(CFLAGS) -o $(EXEC) $(ES1OBJ) $(LIBS)

clean:
	@rm *.o *~
