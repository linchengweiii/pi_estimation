CC = g++
CFLAGS = -g -Wall -O3 -std=c++17

pi: main.o
	$(CC) main.o -o pi

main.o: PIDigitEstimator.h ArgumentParser.h main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f pi *.o
