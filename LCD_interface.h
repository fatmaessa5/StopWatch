#ifndef  LCD_INTERFACE_H
#define  LCD_INTERFACE_H


#define LCD_ROW0   0
#define LCD_ROW1   1
#define MAX_SIZE 1000

#define LCD_COULUMN0   0
#define LCD_COULUMN1   1
#define LCD_COULUMN2   2
#define LCD_COULUMN3   3
#define LCD_COULUMN4   4
#define LCD_COULUMN5   5
#define LCD_COULUMN6   6
#define LCD_COULUMN7   7
#define LCD_COULUMN8   8
#define LCD_COULUMN9   9
#define LCD_COULUMN10  10
#define LCD_COULUMN11  11
#define LCD_COULUMN12  12
#define LCD_COULUMN13  13
#define LCD_COULUMN14  14
#define LCD_COULUMN15  15


void LCD_voidSendInit(void);
void LCD_voidSendData(u8 Copy_u8Data);
void LCD_voidSendCommand(u8 Copy_u8Command);
void LCD_voidGoToXY(u8 Copy_u8XPosition, u8 Copy_u8YPosition);
void LCD_voidSendString(u8 * Copy_pu8String, u8 Copy_u8XPosition, u8 Copy_u8YPosition);
void LCD_voidSENDString(const char* Copy_pcString);
void LCD_voidSendCustomCharacter(u8 * Copy_pu8CharacterArray, u8 Copy_u8XPosition, u8 Copy_u8YPosition, u8 Copy_u8PatternNumber);
void LCD_voidWriteNumber(u32 Copy_u32num, u8 Copy_u8XPos,u8 Copy_u8Ypos);
void LCD_voidClear(void);
#endif
