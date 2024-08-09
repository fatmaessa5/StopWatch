#include "../../LIB/STD_TYPES.h"

#include "../../LIB/BIT_MATH.h"

#include "TIMERS_interface.h"
#include "TIMERS_private.h"
#include "TIMERS_config.h"
void (*Global_pvCTCFunction)(void)=NULL;
void (*Global_pvICUFunction)(void)=NULL;
void (*Global_pvTimer1OvfFunction)(void)=NULL;




void TIMERS_voidTimer0Init(void)
{

  #if TIMER0_MODE==CTC
    CLR_BIT(TCCR0,TCCR0_WGM00);
    SET_BIT(TCCR0,TCCR0_WGM01);

  #if TIMER0_CTC_MODE==NORMAL
      CLR_BIT(TCCR0,TCCR0_COM00);
      CLR_BIT(TCCR0,TCCR0_COM01);

  #endif

#elif TIMER0_MODE==FAST_PWM
      SET_BIT(TCCR0,TCCR0_WGM00);
      SET_BIT(TCCR0,TCCR0_WGM01);

#if FAST_PWM_MODE==CLEAR_ON_COMPARE_SET_AT_TOP
      CLR_BIT(TCCR0,TCCR0_COM00);
      SET_BIT(TCCR0,TCCR0_COM01);
#endif



#endif



#if TIMER0_PRESCALLER==DIVIDE_BY_1
    SET_BIT(TCCR0,TCCR0_CS00);
    CLR_BIT(TCCR0,TCCR0_CS01);
    CLR_BIT(TCCR0,TCCR0_CS02);

#elif TIMER0_PRESCALLER==DIVIDE_BY_8
    CLR_BIT(TCCR0,TCCR0_CS00);
    SET_BIT(TCCR0,TCCR0_CS01);
    CLR_BIT(TCCR0,TCCR0_CS02);
#elif  TIMER0_PRESCALLER==DIVIDE_BY_64
    SET_BIT(TCCR0,TCCR0_CS00);
    SET_BIT(TCCR0,TCCR0_CS01);
    CLR_BIT(TCCR0,TCCR0_CS02);


#endif



#if TIMER0_COMPARE_MATCH_INTERRUPT_ENABLE==ENABLE

    SET_BIT(TIMSK,TIMSK_OCIE0);

#elif TIMER0_COMPARE_MATCH_INTERRUPT_ENABLE==DISABLE

    CLR_BIT(TIMSK,TIMSK_OCIE0);
#endif



}


void TIMERS_voidTimer0SetCompareMatchValue(u8 Copy_u8CompareMatchValue)
{
	OCR0=Copy_u8CompareMatchValue;
}


void TIMERS_voidTimer0SetPreLoadValue(u8 Copy_u8PreLoadValue)
{
	TCNT0=Copy_u8PreLoadValue;
}




void TIMERS_voidTimer0CTCSetCallBackFunction(void (*Copy_pvCTCFunction)(void))
{
	Global_pvCTCFunction =Copy_pvCTCFunction;
}




void __vector_9 (void)  __attribute__((signal));
void __vector_9 (void)
{
	if(Global_pvTimer1OvfFunction!=NULL)
	{
		Global_pvTimer1OvfFunction();
	}
	else
	{
		/*Do Nothing*/
	}


}



