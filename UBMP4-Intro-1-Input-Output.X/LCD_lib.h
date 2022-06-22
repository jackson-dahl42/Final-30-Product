/*==============================================================================
 File: LCD_lib.h
 Date: June 22, 2022
 
 This file contains function prototypes from the LCD_lib.c file. There is also
 a defeneition of the LATC data bus. On the microchip RC7-4 is used for the data
 transfer to the LCD. The RC3 and RC2 are used for RS and EN on the LCD.
==============================================================================*/


//---------------------IO DEFINITIONS  --------------------------
// These are for the 1459 - 1787 uses same..
#define lcd_port  LATC        // write to LAT, read from PORT
// RC7-4 is the LCD 4 bit databus
#define LCD_RSout LATC2     // moved from ICSP
#define LCD_ENout LATC3
// RC0,RC1 reserved for ICSP DEBUG

//-------------------- DISPLAY SETTINGS  ---------------------
// Define some display settings.  These could be defined as complete
// commands as well..
#define lcdLINE1 0x00       // where line 1 begins
#define lcdLINE2 0x40       // where line 2 begins

// Function Prototypes

void initIO(void);

int strobeLCD(void);

void writeLCD(unsigned char dat);

void lcd_cmd (unsigned char cmd);

void lcd_data (unsigned char dat);

void CreateCustomCharacter (unsigned char *Pattern, const char Location);

void lcd_init(void);

void lcd_WriteStr(const unsigned char *c);

void lcd_SetCursor(unsigned char loc);

void lcd_LINE1(void);

void lcd_LINE2(void);
