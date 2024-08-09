#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"

#include"../MCAL/DIO/DIO_interface.h"

#include"../MCAL/TIMERS/TIMERS_interface.h"
#include"../MCAL/GIE/GIE_interface.h"
#include"../HAL/SSD/SSD_interface.h"

#include<util/delay.h>

u8 Global_u8Number = 9;
void ChangeNum(void);

void main(void)
{
	DIO_voidSetPinDirection(PORTB,PIN6,OUTPUT);
	DIO_voidSetPinValue(PORTB,PIN6,OUTPUT);


   SSD_st s1={PORTA,COMMON_ANODE};

	TIMERS_voidTimer0Init();
	TIMERS_voidTimer0SetCompareMatchValue(250);
	TIMERS_voidTimer0CTCSetCallBackFunction(&ChangeNum);
	  SSD_voidInit(&s1);
	 DIO_voidSetPinDirection(PORTD,PIN1,OUTPUT);


  GIE_voidEnableGlobalInterrupt();




    while(1)
    {
        if(Global_u8Number>=0&&Global_u8Number<=9)
      SSD_voidSetNumber(Global_u8Number,&s1);
        if(Global_u8Number==0)
        {

        	 DIO_voidSetPinValue(PORTD,PIN1,HIGH);
        }
    }

}
void ChangeNum(void)
{     static u16 Local_counter=0;
        Local_counter++;
        if(Local_counter==4000&&Global_u8Number>0)
        {
        	 Global_u8Number--;
        	 Local_counter=0;
        }

}

