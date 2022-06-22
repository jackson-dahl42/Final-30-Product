/*==============================================================================
 File: UBMP4.c
 Date: May 16, 2021
 
 UBMP4 (PIC16F1459) hardware initialization functions
 
 Initialization functions to configure the PIC16F1459 oscillator and on-board
 UBMP4 devices. Include UMBP4.h in your main program to call these functions.
==============================================================================*/

#include    "xc.h"              // XC compiler general include file

#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP4.h"           // Include UBMP4 constant symbol definitions

// TODO Initialize oscillator, ports and other PIC/UBMP hardware features here:

// Configure ADC for 8-bit conversion from on-board phototransistor Q1 (AN7).
void ADC_config(void)
{
    LATC = 0b00000000;          // Clear Port C latches before configuring PORTC
    // Configure RC3 for analog input. Enable additional or other inputs below:
    TRISCbits.TRISC3 = 1;       // Disable individual output drivers (TRISx.bit = 1)
    ANSELC = 0b00001000;        // Enable individual analog inputs (ANSELx.bit = 1)
    // General ADC setup and configuration
    ADCON0 = 0b00011100;        // Set channel to AN7, leave A/D converter off
    ADCON1 = 0b01100000;        // Left justified result, FOSC/64 clock, +VDD ref
    ADCON2 = 0b00000000;        // Auto-conversion trigger disabled
}

// Enable ADC and switch the input mux to the specified channel (use channel
// constants defined in UBMP4.h header file - eg. ANQ1).
void ADC_select_channel(unsigned char channel)
{
    ADON = 1;                   // Turn the A-D converter on
    ADCON0 = (ADCON0 & 0b10000011); // Clear channel select (CHS) bits by ANDing
    ADCON0 = (ADCON0 | channel);	// Set channel by ORing with channel const.
}

// Convert currently selected channel and return 8-bit conversion result.
unsigned char ADC_read(void)
{
    GO = 1;                     // Start the conversion by setting Go/~Done bit
	while(GO)                   // Wait for the conversion to finish (GO==0)
        ;                       // Terminate the empty while loop
    return (ADRESH);            // Return the MSB (upper 8-bits) of the result
}

// Enable ADC, switch to specified channel, and return 8-bit conversion result.
// Use channel constants defined in UBMP4.h header file (eg. ANQ1).
unsigned char ADC_read_channel(unsigned char channel)
{
    ADON = 1;                   // Turn the A-D converter on
    ADCON0 = (ADCON0 & 0b10000011); // Clear channel select (CHS) bits by ANDing
    ADCON0 = (ADCON0 | channel);	// Set channel by ORing with chan. constant
    __delay_us(5);              // Allow input to settle (charges internal cap.)
    GO = 1;                     // Start the conversion by setting Go/~Done bit
	while(GO)                   // Wait for the conversion to finish (GO==0)
        ;                       // Terminate the empty while loop
    ADON = 0;                   // Turn the A-D converter off
    return (ADRESH);            // Return the MSB (upper 8-bits) of the result
}

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
