/*==============================================================================
 Project: Final 30 Product
 Due Date:    June 22, 2022
==============================================================================*/

#include "UBMP4.h"
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "PIC16F1459config.h"

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

//----------------- CUSTOM CHARACTERS --------------------------

unsigned char dinosaur1 [ ] = { 
    	0b00111,
	0b01010,
	0b01111,
	0b01110,
	0b01110,
	0b11110,
	0b01110,
	0b00011 
};

unsigned char dinosaur2 [ ] = { 
    	0b00111,
	0b01010,
	0b01111,
    	0b01110,
	0b01110,
	0b11110,
	0b01011,
	0b01100 
};

unsigned char cactus [ ] = { 
    	0b00100,
	0b10100,
	0b10100,
	0b10101,
	0b11101,
    	0b00111,
	0b00100,
	0b00100
};

unsigned char bird1 [ ] = { 
    	0b00000,
	0b00000,
	0b00000,
	0b01000,
	0b11111,
	0b00110,
	0b00110,
	0b00100 
};

unsigned char bird2 [ ] = {	
    	0b00000,
	0b00100,
	0b00110,
	0b01110,
	0b11111,
	0b00000,
	0b00000,
	0b00000 
};

unsigned char spaceship_bottom[] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b11000,
	0b01111,
	0b01111,
	0b11000
};

unsigned char spaceship_top[] = {
	0b11000,
	0b01111,
	0b01111,
	0b11000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};

unsigned char asteroid_bottom[] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b01110,
	0b01110,
	0b00000
};

unsigned char asteroid_top[] = {
	0b00000,
	0b01110,
	0b01110,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};

unsigned char laser_bottom[] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b10101,
	0b01010,
	0b00000
};

unsigned char laser_top[] = {
	0b00000,
	0b01010,
	0b10101,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};
//======================= SFX =====================================

void tone(unsigned char period)
{       
    if(period != 0)
    {
        for(unsigned char cycles = 50; cycles != 0; cycles--)
        {
            BEEPER = !BEEPER;
            for(unsigned int p = period; p != 0; p--);
        }
    }
}

            display_asteroid(int asteroid_x, asteroid_y)
            {
                if(asteroid_y < 3)
                {
                    lcd_SetCursor(asteroid_x + 64);
                }
                if(asteroid_y > 2)
                {
                    lcd_SetCursor(asteroid_x);
                }

                if(asteroid_y == 2 || asteroid_y == 4)
                {
                    lcd_data(2);
                }

                if(asteroid_y == 1 || asteroid_y == 3)
                {
                    lcd_data(3);
                }
            }
//======================= MAIN =====================================

int SW2count = 0;
bool jumping = false;
char jump_count = 0;
char animation_count = 0;
int x, y;
int speed_count = 0;
int speed = 3;
int loop_count = 0;
bool second_cactus = false;
char dino = 0;
bool dino_animation = false;
char bird = 3;
bool bird_animation = false;
char dino_pos = 64;
char cactus1_pos = 79;
char cactus2_pos = 80;
signed char bird_pos = 22;
bool dino_game = false;
bool defender_game = false;
bool game_1 = true;
int score = 0;
int random;
bool SW2Pressed = false;

void main(void)
{
    unsigned char i;
    
    initIO();               // init the chip IO
    __delay_ms(300);        // power up delay for LCD - adjust as necessary
    lcd_init();             // init the LCD

    lcd_SetCursor(3);
    lcd_WriteStr("UBMP4 Game");
    lcd_SetCursor(68);
    lcd_WriteStr("Console!");

    while(1)
    {
        y = ADC_read_channel(ANH2);

        if(SW2 == 0 && SW2Pressed == false)
        {
           if(SW2count < 255 )
           {
               SW2count += 1;
           }
           tone(10);
           SW2Pressed = true;
        }

        if(SW2 == 1)
        {
           SW2Pressed = false;
        }

        if(SW2count == 1)
        {
            lcd_cmd(0x01);
            lcd_WriteStr("Dinosaur Game<");
            lcd_SetCursor(63);
            lcd_WriteStr("Defender");
            game_1 = true;
            SW2count += 1;
        }

        
        if(y < 100)
        {
            lcd_cmd(0x01);
            lcd_SetCursor(0);
            lcd_WriteStr("Dinosaur Game<");
            lcd_SetCursor(63);
            lcd_WriteStr("Defender");
            game_1 = true;
        }

        if(y > 250)
        {
            lcd_cmd(0x01);
            lcd_SetCursor(0);
            lcd_WriteStr("Dinosaur Game");
            lcd_SetCursor(63);
            lcd_WriteStr("Defender<");
            game_1 = false;
        }

        if(SW2count == 3 && game_1 == true)
        {   
            SW2count += 5;
            dino_game = true;
        }

        if(SW2count == 3 && game_1 == false)
        {
            SW2count += 5;
            defender_game = true;
        }

        // Dinosaur game
        if(dino_game == true)
        {
        CreateCustomCharacter(dinosaur1,0);
        CreateCustomCharacter(dinosaur2,1);
        CreateCustomCharacter(cactus,2);
        CreateCustomCharacter(bird1,3);
        CreateCustomCharacter(bird2,4);

        while(dino_game == true)
        {
            time_t t;
            srand((unsigned) time(&t));
            random = rand();

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

            if(dino_animation == true)
            {
                dino = 0;
            }

            if(dino_animation == false)
            {
                dino = 1;
            }

            animation_count += 1;

            if(animation_count == 4)
            {
                bird_animation = !bird_animation;
                dino_animation = !dino_animation;
                animation_count = 0;
            }

            // Obstacle movement

            speed_count += 1;
            loop_count += 1;

            if(loop_count == 100)
            {
                speed = 2;
            }

            if(loop_count == 206)
            {
                speed = 1;
            }

            if(loop_count == 300)
            {
                second_cactus = true;
            }

            if(speed_count == speed)
            {
                cactus1_pos -= 1;
                bird_pos -= 1;
                speed_count = 0;
            }

            if(second_cactus == true)
            {
                cactus2_pos = cactus1_pos + 2;
            }

            if(cactus1_pos < 63)
            {
                cactus1_pos = 79 + (random % 5);
                score += 1;
            } 

            if(bird_pos < 0)
            {
                bird_pos = 16 + (random % 5);
                score += 1;
            }

            // Dino jumping
            if(y < 100 && jumping == false)
            {
                jumping = true;
                tone(100);                                
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

            // Update LCD
            lcd_cmd(0x01);
            lcd_SetCursor(dino_pos);
            lcd_data(dino);
            lcd_SetCursor(cactus1_pos);
            lcd_data(2);
            lcd_SetCursor(cactus2_pos);
            lcd_data(2);
            lcd_SetCursor(bird_pos);
            lcd_data(bird);

            // Hit detection and game over
            if(cactus1_pos == dino_pos || bird_pos == dino_pos || cactus2_pos == dino_pos)
            {
                lcd_cmd(0x01);
                lcd_SetCursor(0);
                lcd_WriteStr("Game Over");
                lcd_SetCursor(63);
                lcd_WriteStr("Score: ");
                char str[6];
                sprintf(str, "%d", score);
                lcd_WriteStr(str);
                __delay_ms(1000);
                dino_game = false;
            }

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


        if(defender_game == true)
        {
            CreateCustomCharacter(spaceship_top,0);
            CreateCustomCharacter(spaceship_bottom,1);
            CreateCustomCharacter(asteroid_top,2);
            CreateCustomCharacter(asteroid_bottom,3);
            CreateCustomCharacter(laser_top,4);
            CreateCustomCharacter(laser_bottom,5);

            int spaceship_x = 0;
            int spaceship_y = 4;
            int asteroid1_x = 15;
            int asteroid1_y = 4;
            int laser_x;
            int laser_y;
            int laser_count = 0;

            while(defender_game == true)
            {

                // Spaceship Movement
                asteroid1_x -= 1;

                if(asteroid1_x < 0)
                {
                    asteroid1_x = 15;
                }

                if(laser_count == 0 && SW2 == 0)
                {
                    laser_count = 1;
                }

                if(laser_count > 0)
                {
                    if(laser_count == 1)
                    {
                        laser_x = spaceship_x;
                        laser_y = spaceship_y;
                        laser_count = 2;
                    }

                    if(laser_count > 1)
                    {
                        laser_x += 1;
                        if(laser_x > 16)
                        {
                            laser_count = 0;
                        }
                    }
                }

                x = ADC_read_channel(ANH1);
                y = ADC_read_channel(ANH2);

                if(y < 100 && spaceship_y < 4)
                {
                    spaceship_y += 1;
                }

                if(y > 200 && spaceship_y > 1)
                {
                    spaceship_y -= 1;
                }
                
                if(x > 200 && spaceship_x < 15)
                {
                    spaceship_x += 1;
                }

                if(x < 50 && spaceship_x > 0)
                {
                    spaceship_x -= 1;
                }

                // Update LCD
                lcd_cmd(0x01);

                if(spaceship_y < 3)
                {
                    lcd_SetCursor(spaceship_x + 64);
                }
                if(spaceship_y > 2)
                {
                    lcd_SetCursor(spaceship_x);
                }

                if(spaceship_y == 2 || spaceship_y == 4)
                {
                    lcd_data(0);
                }

                if(spaceship_y == 1 || spaceship_y == 3)
                {
                    lcd_data(1);
                }

                if(laser_y < 3)
                {
                    lcd_SetCursor(laser_x + 64);
                }
                if(laser_y > 2)
                {
                    lcd_SetCursor(laser_x);
                }

                if(laser_y == 2 || laser_y == 4)
                {
                    lcd_data(4);
                }

                if(laser_y == 1 || laser_y == 3)
                {
                    lcd_data(5);
                }

                display_asteroid(asteroid1_x, asteroid1_y);
                
                 
                if(SW1 == 0)
                {
                    lcd_cmd(0x01);
                    __delay_ms(300);
                    lcd_init();
                    RESET();
                }
                __delay_ms(150);
                
            }
        }

        if(SW1 == 0)
        {
            lcd_cmd(0x01);
            __delay_ms(300);
            lcd_init();
            RESET();
        }
    }
}

