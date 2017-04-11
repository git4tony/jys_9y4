# build mfm383c executable when user executes "make"
LIBS=-lmodbus

jys: jys.o
	$(CC) $(LDFLAGS) $(LIBS) main.o -o jys
jys.o: main.c
	$(CC) -c $(CFLAGS) main.c

# remove object files and executable when user executes "make clean"
clean:
	rm *.o jys
