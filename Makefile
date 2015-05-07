CC=g++
CCFLAGS=-std=c++11

samp:   Driver.o 
	$(CC) $(CCFLAGS) Driver.o  -o samp
   




Driver.o : Driver.cpp Audio.h Audio.cpp
	$(CC) $(CCFLAGS) -o Driver.o -c Driver.cpp

test: Tests.o 
	$(CC) Tests.o Audio.o iterator.o  -o test


Tests.o: Tests.cpp
	$(CC) $(CCFLAGS) -o Tests.o -c Tests.cpp 

clean:
	rm -rf *.o