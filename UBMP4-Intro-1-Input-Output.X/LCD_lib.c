#include "UBMP4.h"
#include "LCD_lib.h"
#include "PIC16F1459config.h"
#include <xc.h>

//---------------------INIT IO -----------------------------------
void initIO(void){
    OSCCON = 0b00110100;  // Internal oscillator = 4MHz (for now)
    TRISC=0b00000011;
    PORTC=0b00000000;
    ANSELC=0b00000011;
    TRISB=0b11110000;
    WPUB=0b11110000;
    PORTB=0b00000000;
    ANSELB=0b00000000;
    TRISA=0b00001111;
    PORTA=0b00100000;
    ANSELA=0b00000000;
}

//--------------------- STROBE LCD ---------------------------
// Pulses E line on LCD to write
int strobeLCD(void)
{
    LCD_ENout = 1;
    __delay_us(2);     // Added a little here
    LCD_ENout = 0; 
}

//--------------------- WRITE 8 BIT DATA TO LCD  -----------------
// Assumes LCD is ready and RS is set to correct value
// LCD data bus is RC4-RC7
// Enable cycle time is a side effect of execution time - faster clocks
// may require a specific delay.
void writeLCD(unsigned char dat)
{
    lcd_port &= 0x0f;               // get current port, clear upper bits
    lcd_port |= (dat & 0xf0);       // combine w/upper nibble, leave lower same
    strobeLCD();

    lcd_port &= 0x0f;               // get current port, clear upper bits
    lcd_port |= ((dat <<4) & (0xf0)); // combine w/lower nibble, leave lower port same
    strobeLCD();
    __delay_ms(2);                // wait for display to process
}

//-------------------- WRITE LCD COMMAND  -------------------------
// Write cmd to LCD with RS=0
// Assumes E is low and display is NOT busy
void lcd_cmd (unsigned char cmd)
{
    LCD_RSout = 0;       // select command register
    writeLCD(cmd);
}

//---------------------- WRITE LCD DATA  --------------------------
// Write dat to LCD with RS=1
// Assumes E is low and display is NOT busy
void lcd_data (unsigned char dat)
{
    LCD_RSout = 1;       // select data register
    writeLCD(dat);
}

//--------------------- CREATE CUSTOM CHARACTER -------------------------
void CreateCustomCharacter (unsigned char *Pattern, const char Location)
{ 
    int i=0; 
    lcd_cmd (0x40+(Location*8));     //Send the Address of CGRAM
    for (i=0; i<8; i++)
    lcd_data (Pattern [ i ] );         //Pass the bytes of pattern on LCD 
}

//-------------------- RESET/CONFIGURE LCD  -------------------------
// Delays are generous, trim when able
void lcd_init(void)
{
    lcd_port &= 0x0f;   // clear upper bits of LCD port
    lcd_port |= 0x30;   // direct data to LCD DB7-4
    LCD_RSout = 0;
    strobeLCD();        // write 3h, wait 10ms
    __delay_ms(10);
    strobeLCD();        // write 3h, wait..
    __delay_ms(10);
     strobeLCD();       // write 3h
    __delay_ms(10);

   lcd_port &= 0x0f;    // clear upper bits of LCD port
   lcd_port |= 0x20;    // direct data to LCD DB7-4
   strobeLCD();         // write 2h
   __delay_ms(10);

    lcd_cmd(0x28);       // Funciton Set: 4-bit mode - 2 line - 5x7 font.
    lcd_cmd(0x01);       // Clear LCD
    lcd_cmd(0x06);       // Automatic Increment - No Display shift.
    lcd_cmd(0x0c);       // Cursor off
    lcd_cmd(0x80);       // Address DDRAM with 0 offset 80h.
}

//----------------------- WRITE STRING TO LCD  ---------------------
// Writes null terminated string to LCD from ROM
void lcd_WriteStr(const unsigned char *c)
{
    while(*c != '\0'){
        lcd_data(*c);
        c++;
    }
}

//--------------------  SETS CURSOR ANYWHERE IN DISPLAY MEMORY  ---------
// Valid locations are 0-79 decimal.  This doesn't check for valid location
void lcd_SetCursor(unsigned char loc)
{
    lcd_cmd(loc | 0x80);        // form and send 'set DDRAM address' cmd
}

//----------------- CANNED LINE COMMANDS  -------------------------
// For a 2 line display
void lcd_LINE1(void)
{
    lcd_SetCursor(lcdLINE1);
}

void lcd_LINE2(void)
{
    lcd_SetCursor(lcdLINE2);
}
