#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H

#define COMMON_ANODE           0
#define COMMON_CATHODE         1
#define MINIMUM_ALLOWED_NUMBER 0
#define MAXIMUN_ALLOWED_NUMBER 9
//you donot need to set port direction
typedef struct
{
	u8 SSD_Port;
	u8 SSD_ComType;//CommonCathode ,CommonAnode
}SSD_st;

void SSD_voidInit(SSD_st* Copy_pstSSDInfo);

void SSD_voidSetNumber(u8 Copy_u8Number, SSD_st* Copy_pstSSDInfo);


#endif
