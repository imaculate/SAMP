CC=g++
CCFLAGS=-std=c++11

samp:  Audio.o  iterator.o Driver.o 
	$(CC) $(CCFLAGS) Driver.o Audio.o iterator.o Matrix.h   -o samp
   

Audio.o : Audio.cpp Audio.h iterator.o 
	$(CC) $(CCFLAGS) -o Audio.o -c Audio.cpp 

iterator.o : iterator.cpp 
	$(CC) $(CCFLAGS) -o iterator.o -c iterator.cpp

Driver.o : Driver.cpp 
	$(CC) $(CCFLAGS) -o Driver.o -c Driver.cpp

test: Tests.o 
	$(CC) Tests.o Audio.o iterator.o  -o test


Tests.o: Tests.cpp
	$(CC) $(CCFLAGS) -o Tests.o -c Tests.cpp 

clean:
	rm -rf *.o