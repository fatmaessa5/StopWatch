#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "SSD_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"

void SSD_voidInit(SSD_st* Copy_pstSSDInfo)
{
	DIO_voidSetPortDirection(Copy_pstSSDInfo->SSD_Port, OUTPUT);
}
void SSD_voidSetNumber(u8 Copy_u8Number, SSD_st* Copy_pstSSDInfo) {

	u8 Localu8_NumbersArray[10] = { ZERO, ONE, TWO, THREE, FOUR, FIVE,
	SIX, SEVEN, EIGHT, NINE };

	if (Copy_u8Number >= MINIMUM_ALLOWED_NUMBER && Copy_u8Number <= MAXIMUN_ALLOWED_NUMBER) {
		if (Copy_pstSSDInfo->SSD_ComType == COMMON_ANODE) {

			DIO_voidSetSpecificPortValue(Copy_pstSSDInfo->SSD_Port,
					~Localu8_NumbersArray[Copy_u8Number]);
		}
		else if (Copy_pstSSDInfo->SSD_ComType == COMMON_CATHODE) {

			DIO_voidSetSpecificPortValue(Copy_pstSSDInfo->SSD_Port,
					Localu8_NumbersArray[Copy_u8Number]);
		}
	}

}

