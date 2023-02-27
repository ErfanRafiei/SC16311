#ifndef _SC16311_H_
#define _SC16311_H_

#include "stdint.h"
#include "main.h"

#define SC16311_TIMEOUT 500
#define SC16311_STB_GPIO  GPIOA
#define SC16311_STB_PIN GPIO_PIN_4
#define Arrey_Size 37

//buffer Address
#define C   (1<<5)
#define D   (1<<0)
#define E   (1<<1)
#define G1  (1<<7)
#define G2  (1<<6)
#define K   (1<<2)
#define L   (1<<3)
#define M   (1<<4)
//buffer Address buffer + 1
#define A   (1<<5)
#define B   (1<<4)
#define F   (1<<0)
#define H   (1<<1)
#define I   (1<<2)
#define J   (1<<3)
#define S   (1<<6)


#define Segment1   1
#define Segment2   4
#define Segment3   7
#define Segment4   10
#define Segment5   13
#define Segment6   16
#define Segment7   19
#define Segment8   22
#define Segment9   25
#define Segment10  28
#define Segment11  31

#define Section1  -2
#define Section2  34

uint8_t SC_writecmd(SPI_HandleTypeDef *Cspi,uint8_t cmd);
uint8_t SC_Init(SPI_HandleTypeDef *Cspi);
uint8_t SC_writedata_addrinc(SPI_HandleTypeDef *Cspi,uint8_t startaddr,uint8_t *data,uint8_t size);
uint8_t SC_Update_All(SPI_HandleTypeDef *Cspi,uint8_t SC_Display_Mode,uint8_t Display_ON_OFF,
            uint8_t Display_Dimming,uint8_t startaddr,uint8_t *data,uint8_t size);
uint8_t SC_SendChar(SPI_HandleTypeDef *Cspi,uint8_t *databuffer,char input,uint8_t dignumber);
uint8_t SC_SendStr(SPI_HandleTypeDef *Cspi,uint8_t *databuffer,char *str,uint8_t Start_dignumber);
uint8_t SC_SendMovingStr(SPI_HandleTypeDef *Cspi,uint8_t *databuffer
   ,char *str,uint16_t delay,uint8_t startsegment,uint8_t Effect_MODE);
uint8_t SC_Clear(SPI_HandleTypeDef *Cspi);
uint8_t SC_read_key(SPI_HandleTypeDef *Cspi);
uint8_t SC_read_SW(SPI_HandleTypeDef *Cspi);

#define SC_dig8_seg20_mode 0
#define SC_dig9_seg19_mode 0x08
#define SC_dig10_seg18_mode 0x09
#define SC_dig11_seg17_mode 0x0A
#define SC_dig12_seg16_mode 0x0B
#define SC_dig13_seg15_mode 0x0C
#define SC_dig14_seg14_mode 0x0D
#define SC_dig15_seg13_mode 0x0E
#define SC_dig16_seg12_mode 0x0F
				
#define SC_Set_PW_6_percent 0
#define SC_Set_PW_12_percent 1
#define SC_Set_PW_25_percent 2
#define SC_Set_PW_62_percent 3
#define SC_Set_PW_68_percent 4
#define SC_Set_PW_75_percent 5
#define SC_Set_PW_81_percent 6
#define SC_Set_PW_87_percent 7
				
#define SC_LCD_ON 1
#define SC_LCD_OFF 0


#define Effect_MODE_1 1
#define Effect_MODE_2 0










#endif


