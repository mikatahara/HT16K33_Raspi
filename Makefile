ht16k33 : Wiringpi_HT16K33.o main.o
	gcc -o ht16k33 main.o Wiringpi_HT16K33.o -lwiringPi

Wiringpi_HT16K33.o : Wiringpi_HT16K33.cpp Wiringpi_HT16K33.h
	gcc -o Wiringpi_HT16K33.o -c Wiringpi_HT16K33.cpp

main.o : main.cpp Wiringpi_HT16K33.h
	gcc -o main.o -c main.cpp
