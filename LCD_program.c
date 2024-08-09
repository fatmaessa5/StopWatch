#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_privte.h"
#include "LCD_config.h"

#include <util/delay.h>

void LCD_voidSendCommand(u8 Copy_u8Command)
{
	/*SET THE RS PIN TO BE LOW 0:FOR COMMAND*/
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,LOW);
	/*SET THE RW PIN TO BE LOW 0:FOR WRITE*/
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,LOW);
	/*set the port value to be command */
    DIO_voidSetPortSpecificValue(LCD_DATA_PORT,Copy_u8Command);
	/* SET THE ENABLE PIN TO BE HIGH*/
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,HIGH);
	/*wait for 2msec*/
	_delay_ms(2);
	/* SET THE ENABLE PIN TO BE LOW*/
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,LOW);
	
}
void LCD_voidSendData(u8 Copy_u8Data)
{
	/*SET THE RS PIN TO BE LOW 0:FOR COMMAND*/
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,HIGH);
	/*SET THE RW PIN TO BE LOW 0:FOR READ*/
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,LOW);
	/*set the port value to be command */
    DIO_voidSetPortSpecificValue(LCD_DATA_PORT,Copy_u8Data);
	/* SET THE ENABLE PIN TO BE HIGH*/
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,HIGH);
	/*wait for 2msec*/
	_delay_ms(2);
	/* SET THE ENABLE PIN TO BE LOW*/
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,LOW);
}
void LCD_voidInit(void)
{
	/* set the data port to be output */
	DIO_voidSetPortDirection(LCD_DATA_PORT,OUTPUT);
	
	/* set the control pins  to be output */
    DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_RS_PIN,OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_RW_PIN,OUTPUT);
    DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_EN_PIN,OUTPUT);
 
	
	/* wait for more than 30ms */
	_delay_ms(40);
	/* send the function send command :n=1=> 2-lines, f:0=>5*8 dotes*/
	LCD_voidSendCommand(0x38);
	/* send the function send command :D=1=>DSPLAY, C:1=>VISIBLE , B:1=>BLINK*/
	LCD_voidSendCommand(0x0F);
	/* send the DISPLAY CLEAR command */
	LCD_voidSendCommand(0x01);
	
}
void LCD_voidGoToXY(u8 Copy_u8XPosition, u8 Copy_u8YPosition)
{
	u8 Local_u8Address = 0;
	//check if we are in the first Row//
	if(Copy_u8XPosition == LCD_ROW0)
	{                      
		Local_u8Address = Copy_u8YPosition;
	}
	//check if we are in the second Row//
	else if(Copy_u8XPosition == LCD_ROW1)
	{
		Local_u8Address = DDRAM_OFFSET + Copy_u8YPosition;
	}
	// SET BIT NUM 7 TO BE 1
	SET_BIT(Local_u8Address, 7);
	// SEND THE COMMAND TO LCD
	LCD_voidSendCommand(Local_u8Address);
		
}
void LCD_voidSendString(u8 * Copy_pu8String, u8 Copy_u8XPosition, u8 Copy_u8YPosition)
{
	LCD_voidGoToXY(Copy_u8XPosition, Copy_u8YPosition);
	u8 Local_u8Index =0;
	u8 Local_u8Line0 =0;
	while(Copy_pu8String != '\0' &&((Copy_u8XPosition *16)+(Local_u8Index +Copy_u8YPosition)) <32)
	{
		if(((Copy_u8XPosition *16)+(Local_u8Index +Copy_u8YPosition)) <16)
		{
			LCD_voidSendData(Copy_pu8String[Local_u8Index]);
			Local_u8Index++;
		}
		else if(((Copy_u8XPosition *16)+(Local_u8Index +Copy_u8YPosition)) == 16&& Local_u8Line0 ==0)
		{
		   LCD_voidGoToXY(1,0);
		   Local_u8Line0++;
		}
		else if(((Copy_u8XPosition *16)+(Local_u8Index +Copy_u8YPosition)) <32 && Local_u8Line0 ==1 )
		{
			LCD_voidSendData(Copy_pu8String[Local_u8Index]);
			Local_u8Index++;
		}
	}	
}
/*
void LCD_voidSENDString(const char* Copy_pcString)
{
  u8 Local_u8Counter=0;
  while(Copy_pcString[Local_u8Counter]!='\0')
  {
	  LCD_voidSendData(Copy_pcString[Local_u8Counter]);
	  Local_u8Counter++;
  }
}
*/
void LCD_voidSendCustomCharacter(u8 * Copy_pu8CharacterArray, u8 Copy_u8XPosition, u8 Copy_u8YPosition, u8 Copy_u8PatternNumber)
{
	u8 Local_u8LoopCounter;
	u8 Local_u8CGRAMAddress = 0;
	// Calculate the CGRAMADDRESS byte = pattern number*8//
	Local_u8CGRAMAddress = Copy_u8PatternNumber *8;
	//set  bit num 6//
	SET_BIT(Local_u8CGRAMAddress, 6);
	//send the command to lcd//
	LCD_voidSendCommand(Local_u8CGRAMAddress);
	
	//loop on the character array to send it to lcd//
	for(Local_u8LoopCounter=0; Local_u8LoopCounter<8; Local_u8LoopCounter++)
	{
		//send abyte from the charater array
		LCD_voidSendData(Copy_pu8CharacterArray[Local_u8LoopCounter]);
	}
	// send the ddram address command
	LCD_voidGoToXY(Copy_u8XPosition,Copy_u8YPosition);
	// display the pattern
	LCD_voidSendData(Copy_u8PatternNumber);
}   


void LCD_voidWriteNumber(u32 Copy_u32num, u8 Copy_u8XPos,u8 Copy_u8Ypos)
{
	u8 Local_Digit=0;
  u8 Local_Counter=0;


   u8 Digits[MAX_SIZE];
	while(Copy_u32num>0)
	{
		Local_Digit=Copy_u32num%10;
		Digits[Local_Counter]=Local_Digit;
		Local_Counter++;

		Copy_u32num/=10;
	}

	 u8 Local_Iterator;
	 u8 Local_Iterator2=Local_Counter-1;

    for(Local_Iterator=0;Local_Iterator<Local_Counter ; Local_Iterator++)
	{
		 LCD_voidGoToXY(Copy_u8XPos,Copy_u8Ypos+Local_Iterator2);
		 u8 Data=Digits[Local_Iterator]+48;
		 LCD_voidSendData(Data);
		 Local_Iterator2--;

	}
}

void LCD_voidClear(void)
{
	 LCD_voidSendCommand(0b00000001);
}




