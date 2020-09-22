#CAESAR CIPHER ANALYSER

caesarAnalyser.out: main.o header.h decryptShift.o roundN.o
	g++ -o caesarAnalyser.out main.o header.h decryptShift.o roundN.o

main.o: main.o header.h decryptShift.o roundN.o
	g++ -c main.cpp

decryptShift.o: decryptShift.cpp header.h 
	g++ -c decryptShift.cpp

roundN.o: roundN.cpp header.h 
	g++ -c roundN.cpp

clean:
	rm *.o caesarAnalyser.out
