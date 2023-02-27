#include "SC16311.h"
#include "main.h"
#include "string.h"


uint8_t SegmentSelect[12] =
{
	//1,4,7,10,13,16,19,22,25,28,31
	31,28,25,22,19,16,13,10,7,4,1
};



uint8_t SC_Init(SPI_HandleTypeDef *Cspi)
{
	uint8_t Fdisplaydata[Arrey_Size];
	memset(Fdisplaydata,0,Arrey_Size*sizeof(Fdisplaydata[0]));
	HAL_SPI_MspDeInit(Cspi);
	HAL_SPI_MspInit(Cspi);
	HAL_GPIO_WritePin(SC16311_STB_GPIO,SC16311_STB_PIN,GPIO_PIN_SET);
	SC_Update_All(Cspi,SC_dig13_seg15_mode,SC_LCD_ON,SC_Set_PW_87_percent,0x00,Fdisplaydata,
		      sizeof(Fdisplaydata));
	return HAL_OK;
}
uint8_t SC_writecmd(SPI_HandleTypeDef *Cspi,uint8_t cmd)
{
	HAL_GPIO_WritePin(SC16311_STB_GPIO,SC16311_STB_PIN,GPIO_PIN_RESET);
	if(HAL_SPI_Transmit(Cspi,&cmd,sizeof(cmd),SC16311_TIMEOUT)!=HAL_OK)return HAL_ERROR;
	HAL_GPIO_WritePin(SC16311_STB_GPIO,SC16311_STB_PIN,GPIO_PIN_SET);
	return HAL_OK;
}
uint8_t SC_writedata_addrinc(SPI_HandleTypeDef *Cspi,uint8_t startaddr,uint8_t *data,uint8_t size)
{
  startaddr = startaddr | 0xC0;
	HAL_GPIO_WritePin(SC16311_STB_GPIO,SC16311_STB_PIN,GPIO_PIN_RESET);
	if(HAL_SPI_Transmit(Cspi,&startaddr,sizeof(startaddr),SC16311_TIMEOUT)!=HAL_OK)return HAL_ERROR;
	for(int i=0;i<size;i++)
	{
		if(HAL_SPI_Transmit(Cspi,&data[i],1,SC16311_TIMEOUT)!=HAL_OK)return HAL_ERROR;
	}
	
	HAL_GPIO_WritePin(SC16311_STB_GPIO,SC16311_STB_PIN,GPIO_PIN_SET);
	return HAL_OK;
}

uint8_t SC_Clear(SPI_HandleTypeDef *Cspi)
{
	uint8_t data[48];
	memset(data,0,Arrey_Size*sizeof(data[0]));
	SC_Update_All(Cspi,SC_dig13_seg15_mode,SC_LCD_ON,SC_Set_PW_87_percent,0x00,data,
		      sizeof(data));
	return HAL_OK;
}
uint8_t SC_Update_All(SPI_HandleTypeDef *Cspi,uint8_t SC_Display_Mode,uint8_t Display_ON_OFF,uint8_t Display_Dimming
	   ,uint8_t startaddr,uint8_t *data,uint8_t size)
{
			SC_writecmd(Cspi,SC_Display_Mode);
	    SC_writecmd(Cspi,0x40);
	    SC_writedata_addrinc(Cspi,0x00,data,Arrey_Size);
	    SC_writecmd(Cspi,(0x80|((Display_ON_OFF<<3)|Display_Dimming)));
	    return HAL_OK;
}


uint8_t SC_SendChar(SPI_HandleTypeDef *Cspi,uint8_t *databuffer,char input,uint8_t dignumber)
{
	if(dignumber <= 0)return HAL_ERROR;
  dignumber = dignumber + 2;
	if(input>='0' && input<='9')
	{
    switch(input)
		{
			case '0':  
				  databuffer[dignumber]=C|D|E;
	        databuffer[dignumber+1]=A|B|F;
			break;
			case '1':  
				  databuffer[dignumber]=C;
	        databuffer[dignumber+1]=B;
			break;
			case '2':  
				  databuffer[dignumber]=G1|G2|D|E;
	        databuffer[dignumber+1]=A|B;
			break;
			case '3':  
					databuffer[dignumber]=G1|G2|D|C;
	        databuffer[dignumber+1]=A|B;
			break;
			case '4':  
				  databuffer[dignumber]=C|G1|G2;
	        databuffer[dignumber+1]=B|F;
			break;
			case '5':  
				  databuffer[dignumber]=G1|G2|C|D;
	        databuffer[dignumber+1]=A|F;
			break;
			case '6':  
				  databuffer[dignumber]=G1|G2|D|C|E;
	        databuffer[dignumber+1]=A|F;
			break;
			case '7':  
					databuffer[dignumber]=C;
	        databuffer[dignumber+1]=A|B;
			break;
			case '8':  
				  databuffer[dignumber]=C|D|E|G1|G2;
	        databuffer[dignumber+1]=A|B|F;
			break;
			case '9':  
			    databuffer[dignumber]=C|D|G1|G2;
	        databuffer[dignumber+1]=A|B|F;
			break;
			
		}
	}
	else if((input>='A' && input<='Z')||(input == ' '))
	{
	  switch(input)
		 {
			case ' ':  
				  databuffer[dignumber]=0;
	        databuffer[dignumber+1]=0;
			break;			
			case 'A':  
				  databuffer[dignumber]=C|E|G1|G2;
	        databuffer[dignumber+1]=A|B|F;
			break;
			case 'B':  
				  databuffer[dignumber]=C|D|E|G1|G2;
	        databuffer[dignumber+1]=F;
			break;
			case 'C':  
				  databuffer[dignumber]=D|E;
	        databuffer[dignumber+1]=F|A;
			break;
			case 'D':  
				  databuffer[dignumber]=C|D|E|G1|G2;
	        databuffer[dignumber+1]=B;
			break;
			case 'E':  
				  databuffer[dignumber]=D|E|G1|G2;
	        databuffer[dignumber+1]=F|A;
			break;
			case 'F':  
				  databuffer[dignumber]=E|G1|G2;
	        databuffer[dignumber+1]=F|A;
			break;
			case 'G':  
				  databuffer[dignumber]=E|D|G2|C;
	        databuffer[dignumber+1]=F|A;
			break;
			case 'H':  
				  databuffer[dignumber]=C|E|G1|G2;
	        databuffer[dignumber+1]=B|F;
			break;
			case 'I':  
				  databuffer[dignumber]=D|L;
	        databuffer[dignumber+1]=A|I;
			break;
			case 'J':  
				  databuffer[dignumber]=D|K|C;
	        databuffer[dignumber+1]=B;
			break;
			case 'K':  
			    databuffer[dignumber]=E|M|G1;
	        databuffer[dignumber+1]=J|F;
			break;
			case 'L':  
				  databuffer[dignumber]=D|E;
	        databuffer[dignumber+1]=F;
			break;
			case 'M':  
				  databuffer[dignumber]=E|C;
	        databuffer[dignumber+1]=F|B|J|H;
			break;
			case 'N':  
				  databuffer[dignumber]=E|C|M;
	        databuffer[dignumber+1]=F|B|H;
			break;
			case 'O':  
				  databuffer[dignumber]=C|D|E;
	        databuffer[dignumber+1]=A|B|F;
			break;
			case 'P':  
				  databuffer[dignumber]=E|G1|G2;
	        databuffer[dignumber+1]=F|A|B;
			break;
			case 'Q':  
				  databuffer[dignumber]=M|G1|G2;
	        databuffer[dignumber+1]=F|A|B;
			break;
			case 'R':  
				  databuffer[dignumber]=E|G1|G2|M;
	        databuffer[dignumber+1]=F|A|B;
			break;
			case 'S':  
				  databuffer[dignumber]=C|D|G1|G2;
	        databuffer[dignumber+1]=A|F;
			break;
			case 'T':  
				  databuffer[dignumber]=L;
	        databuffer[dignumber+1]=A|I|B|F;
			break;
			case 'U':  
				  databuffer[dignumber]=C|D|E;
	        databuffer[dignumber+1]=B|F;
			break;
			case 'V':  
				  databuffer[dignumber]=E|K;
	        databuffer[dignumber+1]=F|J;
			break;
			case 'W':  
				  databuffer[dignumber]=C|K|M|E;
	        databuffer[dignumber+1]=B|F;
			break;
			case 'X':  
				  databuffer[dignumber]=K|M;
	        databuffer[dignumber+1]=H|J;
			break;
			case 'Y':  
				  databuffer[dignumber]=C|D|G1|G2;
	        databuffer[dignumber+1]=B|F;
			break;
			case 'Z':  
				  databuffer[dignumber]=D|K;
	        databuffer[dignumber+1]=A|J;
			break;
		}
		
	}
	else
		{
		  switch(input)
		   {
				case ':':  
				  databuffer[dignumber]=K;
	        databuffer[dignumber+1]=H;
			   break;
			 }
		}			 
		
		
	
	return HAL_OK;
}



uint8_t SC_SendStr(SPI_HandleTypeDef *Cspi,uint8_t *databuffer,char *str,uint8_t Start_dignumber)
{
	if(Start_dignumber+strlen(str)>11)return HAL_ERROR;
	for(int i=strlen(str);i>=0;i--)
	{
	 	  SC_SendChar(Cspi,databuffer,str[i],SegmentSelect[Start_dignumber+i]);
	}
	return HAL_OK;
}

uint8_t SC_SendMovingStr(SPI_HandleTypeDef *Cspi,uint8_t *databuffer
   ,char *str,uint16_t delay,uint8_t startsegment,uint8_t Effect_MODE)
{
	uint8_t temp;
	if(Effect_MODE)
	{
    if(startsegment+strlen(str)>11)return HAL_ERROR;
	  for(int i=0;i<(startsegment+strlen(str));i++)
	  {
	    temp=databuffer[0];
	    databuffer[(startsegment+i)]=databuffer[(startsegment+i)+1];
	    databuffer[startsegment+strlen(str)]=temp;
	  	
	    SC_SendChar(Cspi,databuffer,str[strlen(str)-i],SegmentSelect[startsegment+strlen(str)-i]);
	  	SC_SendChar(Cspi,databuffer,' ',SegmentSelect[startsegment+(strlen(str)-i)+1]);
	  	
	    SC_Update_All(Cspi,SC_dig13_seg15_mode,SC_LCD_ON,SC_Set_PW_87_percent,0x00,databuffer,
	        sizeof(databuffer));
	  	HAL_Delay(delay);
	  }
	}
	else
	{
	  for(int i=0;i<(startsegment+strlen(str));i++)
	  {
			
	    temp=databuffer[0];
	    databuffer[(startsegment+i)]=databuffer[(startsegment+i)+1];
	    databuffer[startsegment+strlen(str)]=temp;
	  	
	    SC_SendChar(Cspi,databuffer,str[strlen(str)-i],SegmentSelect[startsegment+strlen(str)-i]);
	  	SC_SendChar(Cspi,databuffer,' ',SegmentSelect[startsegment+(strlen(str)-i)+2]);

	    SC_Update_All(Cspi,SC_dig13_seg15_mode,SC_LCD_ON,SC_Set_PW_87_percent,0x00,databuffer,
	        sizeof(databuffer));
	  	HAL_Delay(delay);
	  }

	}
	return HAL_OK;
}


uint8_t SC_read_key(SPI_HandleTypeDef *Cspi)
{
	uint8_t keydata[1],cmd=0x42;
	HAL_GPIO_WritePin(SC16311_STB_GPIO,SC16311_STB_PIN,GPIO_PIN_RESET);
	HAL_SPI_Transmit(Cspi,&cmd,sizeof(cmd),SC16311_TIMEOUT);
	__NOP();__NOP();__NOP();
	HAL_SPI_Receive(Cspi,keydata,sizeof(keydata),SC16311_TIMEOUT);
	HAL_GPIO_WritePin(SC16311_STB_GPIO,SC16311_STB_PIN,GPIO_PIN_SET);
	return *keydata;
}

uint8_t SC_read_SW(SPI_HandleTypeDef *Cspi)
{
	uint8_t swdata[1],cmd=0x43;
	HAL_GPIO_WritePin(SC16311_STB_GPIO,SC16311_STB_PIN,GPIO_PIN_RESET);
	HAL_SPI_Transmit(Cspi,&cmd,sizeof(cmd),SC16311_TIMEOUT);
	__NOP();__NOP();__NOP();
	HAL_SPI_Receive(Cspi,swdata,sizeof(swdata),SC16311_TIMEOUT);
	HAL_GPIO_WritePin(SC16311_STB_GPIO,SC16311_STB_PIN,GPIO_PIN_SET);
	return *swdata;
}












