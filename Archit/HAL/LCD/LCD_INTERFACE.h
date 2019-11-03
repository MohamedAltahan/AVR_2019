
/********************************************/
/* Author   : MOHAMED ALTAHAN               */
/* Date     : 5 sep 2019                    */
/* Version  : V1                            */
/********************************************/

#ifndef LCD_INTERFACE_H_ 
#define LCD_INTERFACE_H_ 


/************* define the port and pins ************/
#define LCD_DATA_PORT     DIO_PORTA
#define RS                PIN2
#define EN                PIN3
#define D4                PIN4
#define D5                PIN5
#define D6                PIN6
#define D7                PIN7

/************* function prototypes ************/
void LCD_vidInit();
void LCD_vidClear();

void LCD_vidWriteCmd(u8 Cpy_u8Cmd);
void LCD_vidWriteData(u8 Cpy_u8Data);

void LCD_vidWriteChar(u8 Cpy_u8Data);
void LCD_vidWriteString(  u8 * Ptr_u8String);

void LCD_vidDelay_ms(u16 Cpy_u16Ticks);
void LCD_vidDelay_us(u16 Cpy_u16Ticks);

void LCD_vidShiftLeft();
void LCD_vidShiftRight();

// (first row ,first column) = (0,0)
void LCD_vidGoTo(u8 Cpy_u8Row , u8 Cpy_u8Column);


#endif
