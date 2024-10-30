/* Adafruit 8x8 Bi-Color LED Matrix DEMO */
/*
 * main.cpp
 * Released under the MIT license
 * Copyright (c) 2024 MikataHara
 * 2024.10.26
 */

#include <stdio.h>
#include <stdint.h>

#include "Wiringpi_HT16K33.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

/* Initial Dot Matrix */
uint8_t GrnDor[8]={		//Green Horizontal Line
	0b11111111,
	0b11111111,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};

uint8_t RndDor[8]={		//Red Horizontal Line
	0b00000000,
	0b11111111,
	0b11111111,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};

uint8_t GrnDor2[8]={	//Green Vertical Line
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000
};

uint8_t RndDor2[8]={	//Red Vertical Line
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000
};

/* Rotate v down */
static void shiftdown(uint8_t *Buf)
{
	uint8_t i,tmp;
	tmp = Buf[7];
	for(i=7; i>0; i--){
		Buf[i] = Buf[i-1];
	}
	Buf[0] = tmp;
}

/* Rotate shift up */
static void shiftup(uint8_t *Buf)
{
	uint8_t i,tmp;
	tmp = Buf[0];
	for(i=0; i<7; i++){
		Buf[i] = Buf[i+1];
	}
	Buf[7] = tmp;
}

/* Rotate shift right */
static void shiftright(uint8_t *Buf)
{
	uint8_t i,tmp;
	for(i=0; i<8; i++){
		tmp = Buf[i]&0x01;
		Buf[i] >>= 1;
		Buf[i] |= (tmp<<7);
	}
}

/* Rotate shift left */
static void shiftleft(uint8_t *Buf)
{
	uint8_t i,tmp;
	for(i=0; i<8; i++){
		tmp = Buf[i]&0x80;
		Buf[i] <<= 1;
		Buf[i] |= (tmp>>7);
	}
}

/* Demonstration for 8x8 BiColor LED Matrix */
int main()
{
	Wiringpi_HT16K33 ht16k33(5);

	uint8_t Dotr1[8], Dotr2[8];

	for(uint8_t i=0;i<22; i++){
		ht16k33.RotateMatrix(GrnDor,Dotr1);
		ht16k33.RotateMatrix(RndDor,Dotr2);
		ht16k33.DisplayOutput(Dotr1,Dotr2);
		delay(250);
		shiftdown(GrnDor);
		shiftdown(RndDor);
	}

	shiftup(GrnDor);
	shiftup(RndDor);

	for(uint8_t i=0;i<22; i++){
		ht16k33.RotateMatrix(GrnDor,Dotr1);
		ht16k33.RotateMatrix(RndDor,Dotr2);
		ht16k33.DisplayOutput(Dotr1,Dotr2);
		delay(250);
		shiftup(GrnDor);
		shiftup(RndDor);
	}

	delay(500);
	ht16k33.allClear();
	delay(500);

	for(uint8_t i=0;i<22; i++){
		ht16k33.RotateMatrix(GrnDor2,Dotr1);
		ht16k33.RotateMatrix(RndDor2,Dotr2);
		ht16k33.DisplayOutput(Dotr1,Dotr2);
		delay(250);
		shiftright(GrnDor2);
		shiftright(RndDor2);
	}

	shiftleft(GrnDor2);
	shiftleft(RndDor2);

	for(uint8_t i=0;i<22; i++){
		ht16k33.RotateMatrix(GrnDor2,Dotr1);
		ht16k33.RotateMatrix(RndDor2,Dotr2);
		ht16k33.DisplayOutput(Dotr1,Dotr2);
		delay(250);
		shiftleft(GrnDor2);
		shiftleft(RndDor2);
	}

	delay(500);
	ht16k33.allClear();
	delay(500);

	for(uint8_t i=0;i<100; i++){
		ht16k33.DispNum(i);
		delay(100);
	}

	delay(500);
	ht16k33.allClear();

}
