/*
 * Wiringpi_HT16K33.cpp
 * Modified for Trinket 0by MikataHara
 * 2024.10.26
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "Wiringpi_HT16K33.h"

static uint8_t LEDNum[10][8] = {
    {//"0"
     0b11100000,
     0b10100000,
     0b10100000,
     0b10100000,
     0b10100000,
     0b10100000,
     0b11100000,
     0b00000000},
    {//"1"
     0b00100000,
     0b00100000,
     0b00100000,
     0b00100000,
     0b00100000,
     0b00100000,
     0b00100000,
     0b00000000},
    {//"2"
     0b11100000,
     0b00100000,
     0b00100000,
     0b11100000,
     0b10000000,
     0b10000000,
     0b11100000,
     0b00000000},
    {//"3"
     0b11100000,
     0b00100000,
     0b00100000,
     0b11100000,
     0b00100000,
     0b00100000,
     0b11100000,
     0b00000000},
    {//"4"
     0b10100000,
     0b10100000,
     0b10100000,
     0b11100000,
     0b00100000,
     0b00100000,
     0b00100000,
     0b00000000},
    {//"5"
     0b11100000,
     0b10000000,
     0b10000000,
     0b11100000,
     0b00100000,
     0b00100000,
     0b11100000,
     0b00000000},
    {//"6"
     0b11100000,
     0b10000000,
     0b10000000,
     0b11100000,
     0b10100000,
     0b10100000,
     0b11100000,
     0b00000000},
    {//"7"
     0b11100000,
     0b10100000,
     0b10100000,
     0b00100000,
     0b00100000,
     0b00100000,
     0b00100000,
     0b00000000},
    {//"8"
     0b11100000,
     0b10100000,
     0b10100000,
     0b11100000,
     0b10100000,
     0b10100000,
     0b11100000,
     0b00000000},
    {//"8"
     0b11100000,
     0b10100000,
     0b10100000,
     0b11100000,
     0b00100000,
     0b00100000,
     0b11100000,
     0b00000000},
};

static uint8_t LEDNumS[10][8] = {
    {//"0"
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000},
    {//"1"
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000010},
    {//"2"
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000011},
    {//"3"
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000001,
     0b00000011},
    {//"4"
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000001,
     0b00000001,
     0b00000011},
    {//"5"
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000011},
    {//"6"
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000011},
    {//"7"
     0b00000000,
     0b00000000,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000011},
    {//"8"
     0b00000000,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000011},
    {//"8"
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000001,
     0b00000011},
};

static uint8_t Alloff[8] = {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000
};

/* val : 輝度（0x0〜0xF） */
Wiringpi_HT16K33::Wiringpi_HT16K33(uint8_t val)
{
  _i2caddr = wiringPiI2CSetup(HT16K33_I2CADDR_DEFAULT);

  // オシレータを有効化
  wiringPiI2CWrite(_i2caddr, 0x21);       // 0x21: システムオシレータON

  // 表示点灯
  wiringPiI2CWrite(_i2caddr, 0x81);       // 0x81: 表示ON、ブリンクなし

  // 輝度設定
  wiringPiI2CWrite(_i2caddr, 0xE0 | val); // 0xE0 + 輝度（0x0〜0xF）
  return;
}

void Wiringpi_HT16K33::write(uint8_t val)
{
  wiringPiI2CWrite(_i2caddr, val);
}

void Wiringpi_HT16K33::write8(uint8_t reg, uint8_t val)
{
  wiringPiI2CWriteReg8(_i2caddr, reg, val);
}

uint8_t Wiringpi_HT16K33::read8(uint8_t reg)
{
  uint16_t result = wiringPiI2CReadReg8(_i2caddr, reg);
  return result;
}

void Wiringpi_HT16K33::allClear()
{
	for(uint8_t i=0; i<16; i+=2){
		write8(i,   0x00);
		write8(i+1, 0x00);
	}
}

void Wiringpi_HT16K33::allRed()
{
	for(uint8_t i=0; i<16; i+=2){
		write8(i,   0x00);
		write8(i+1, 0xFF);
	}
}

void Wiringpi_HT16K33::allGreen()
{
	for(uint8_t i=0; i<16; i+=2){
		write8(i,   0xFF);
		write8(i+1, 0x00);
	}
}

void Wiringpi_HT16K33::allOrange()
{
	for(uint8_t i=0; i<16; i+=2){
		write8(i,   0xFF);
		write8(i+1, 0xFF);
	}
}

//**********************ＬＥＤドライバ　HT16K33　8X8データ送信*******************
void Wiringpi_HT16K33::DisplayOutput(uint8_t *GndDot, uint8_t *RndDot)
{
  uint8_t i,j;
  for(i=0,j=0; i<16; i+=2,j++){
		write8(i,   GndDot[j]);
		write8(i+1, RndDot[j]);
	}
}

//**********************　回転　*******************
void Wiringpi_HT16K33::RotateMatrix(uint8_t *Buf1, uint8_t *Buf2){
  uint8_t i,j,bt;
  uint8_t Mask=0b00000001;

  memset((uint8_t*)Buf2,0,8);
  for(i=0; i<8; i++){
    for(j=0; j<8; j++){
      bt = (Buf1[i]>>j)&Mask;
      Buf2[j] = Buf2[j] | (bt<<i);
    }
  }
}


//**********************　２桁表示　***************
void Wiringpi_HT16K33::DispNum(uint8_t num){
  uint8_t Buf1[8],Buf2[8];
  uint8_t n10 = (int8_t)(num/10.)%10;
  uint8_t n1 = num%10;

  for(uint8_t i=0; i<8; i++){
    Buf1[i] = LEDNum[n10][i] | (LEDNum[n1][i]>>4);
  }
  RotateMatrix(Buf1,Buf2);
  DisplayOutput(Buf2,Alloff);
}
