/*==============================================================================
 Project: Final 30 Product
 Date:    May 16, 2021
==============================================================================*/

//-------------------------- BUILD FOR 16F1459  ---------------------------------
// PIC16F1459 Configuration Bit Settings
// 'C' source line config statements
#include <xc.h>
#include "UBMP4.h"
#include "stdbool.h"

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)
// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config CPUDIV = NOCLKDIV// CPU System Clock Selection Bit (NO CPU system divide)
#pragma config USBLSCLK = 48MHz // USB Low SPeed Clock Selection bit (System clock expects 48 MHz, FS/LS USB CLKENs divide-by is set to 8.)
#pragma config PLLMULT = 3x     // PLL Multipler Selection Bit (3x Output Frequency Selected)
#pragma config PLLEN = ENABLED  // PLL Enable Bit (3x or 4x PLL Enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#define _XTAL_FREQ 4000000      // 4MHz for now
#define SW1         PORTAbits.RA3   // S1/Reset pushbutton input
#define SW2         PORTBbits.RB4   // Pushbutton SW2 input
#define SW3         PORTBbits.RB5   // Pushbutton SW3 input
#define SW4         PORTBbits.RB6   // Pushbutton SW4 input
#define SW5         PORTBbits.RB7   // Pushbutton SW5 input


// Enable ADC and switch the input mux to the specified channel (use channel
// constants defined in UBMP4.h header file - eg. ANQ1).

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
// Enable ADC and switch the input mux to the specified channel (use channel
// constants defined in UBMP4.h header file - eg. ANQ1).

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

//--------------------- CUSTOM CHARACTERS -------------------------

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

//======================= MAIN =====================================
unsigned char dinosaur1 [ ] = { 0b00111,
	                            0b01010,
	                            0b01111,
	                            0b01110,
	                            0b01110,
	                            0b11110,
	                            0b01010,
	                            0b01111 } ;

unsigned char dinosaur2 [ ] = { 0b00111,
	                            0b01010,
	                            0b01111,
	                            0b01110,
	                            0b01110,
	                            0b11110,
	                            0b01011,
	                            0b01100 } ;

unsigned char cactus [ ] = { 0b00100,
	                         0b10100,
	                         0b10100,
	                         0b10101,
	                         0b11101,
	                         0b00111,
	                         0b00100,
	                         0b00100} ; // Cactus

unsigned char bird1 [ ] = {	0b00000,
	                        0b00000,
	                        0b00000,
	                        0b01000,
	                        0b11111,
	                        0b00110,
	                        0b00110,
	                        0b00100 } ; // bird sprite 1

unsigned char bird2 [ ] = {	0b00000,
	                        0b00100,
	                        0b00110,
	                        0b01110,
	                        0b11111,
	                        0b00000,
	                        0b00000,
	                        0b00000 } ; // bird sprite 2
bool jumping = false;
char jump_count = 0;
char animation_count = 0;
int x, y;
char dino = 0;
char bird = 3;
bool bird_animation = false;
char dino_pos = 64;
char cactus1_pos = 79;
signed char bird_pos = 22;
void main (void)
{
    unsigned char i;
    
    initIO();               // init the chip IO
    __delay_ms(300);        // power up delay for LCD - adjust as necessary
    lcd_init();             // init the LCD
    CreateCustomCharacter(dinosaur1,0);
    CreateCustomCharacter(dinosaur2,1);
    CreateCustomCharacter(cactus,2);
    CreateCustomCharacter(bird1,3);
    CreateCustomCharacter(bird2,4);

    while(1)
    {
        x = ADC_read_channel(ANH1);
        y = ADC_read_channel(ANH2);

        // Animations
        if(bird_animation == true)
        {
            bird = 3;
        }
        if(bird_animation == false)
        {
            bird = 4;
        }
        animation_count += 1;
        if(animation_count == 4)
        {
            bird_animation = !bird_animation;
            animation_count = 0;
        }

        // Obstacle movement
        
        cactus1_pos -= 1;
        bird_pos -= 1;

        if(cactus1_pos < 63)
        {
            cactus1_pos = 79;
        }

        if(bird_pos < 0)
        {
            bird_pos = 16;
        }

        // Dino jumping
        if(y < 100 && jumping == false)
        {
            jumping = true;
        }
        if(jumping == true)
        {
            dino_pos = 0;
            jump_count += 1;
            if(jump_count == 10)
            {
                jumping = false;
                jump_count = 0;
                dino_pos = 63;
            }
        }

        // Hit detection and game over
        if(cactus1_pos == dino_pos || bird_pos == dino_pos)
        {
           lcd_cmd(0x01);
           lcd_SetCursor(0);
           lcd_WriteStr("Game Over");
           break;
        }

        // Update LCD
        lcd_cmd(0x01);
        lcd_SetCursor(dino_pos);
        lcd_data(dino);
        lcd_SetCursor(cactus1_pos);
        lcd_data(2);
        lcd_SetCursor(bird_pos);
        lcd_data(bird);

        if(SW1 == 0)
        {
            lcd_cmd(0x01);
            __delay_ms(300);
            lcd_init();
            RESET();
        }

        __delay_ms(100);
    }
}