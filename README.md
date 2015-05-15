Author: Imaculate Mosha

Date: 13th May 2015
Name: Simple Audio Manipulation Program (SAMP)


Description: 
This assignment is written to in responce to answer assignment 5 question. It reads audio files into 
classes and performs required operations using iterators and c++ algorithms in conjuction with functors and lambdas. 

Instructions: Extract the tar file. Navigate to the destination folder from the command line. 
Enter make

Run( samp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName] [<ops>] Soundfile [SoundFile2] )
where ops are:
 -add s1 s2
-cut r1 r2
-radd r1 r2 s1 s2
-cat s1 s2
 -v r1 r2
 -rev s1
 -rms s1
 -norm r1 r2
 -fadein n
 -fadeout n
 As provided in the instructions

eg( samp -r 44100 -b 8 -c 2 -o cutfile -cut 10 500 countdown40sec_44100_signed_8bit_stereo.raw)

For unit testing :
compile with (make test)
run with (test)
 
	 

List of files: 

Audio.h -header file for HuffmanTree class.
Audio.cpp -defines HuffmanTree class methods .
Driver.cpp -driver file for the program
Makefile - used to run the program.


 