/*==============================================================================
 File: UBMP4.h
 Date: May 16, 2021
 
 UBMP4 (PIC16F1459) symbolic constant definitions
 
 I/O pin definitions section:
 Inputs read port registers (eg. RC0), and outputs write to port latches
 (eg. LATC0). Use this file to create unique symbolic names for each input
 and output device connected to the I/O pins of the PIC16F1459 in the UBMP4.
 
 ADC input channel definitions section:
 Definitions representing ADCON0 channel select (CHS) bit for the ADC channels
 available on the UMBP4.
 
 Function prototypes section:
 Functions in the UBMP4.c file need to be defined before use in the main user
 program. This header file contains the function prototype definitions for the
 functions in the UBMP4.c file.
==============================================================================*/

// TODO - Add/modify user constant definitions for UBMP hardware here.

// ADC (A-D converter) input channel definitions for read_ADC() function
#define AN4         0b00010000      // A-D converter channel 4 input
#define ANH1        0b00010000      // External H1 header analogue input (Ch4))
#define AN5         0b00010100      // A-D converter channel 5 input
#define ANH2        0b00010100      // External H2 header analogue input (Ch5)
#define AN6         0b00011000      // A-D converter channel 6 input
#define ANH3        0b00011000      // External H3 header analogue input (Ch6)
#define AN7         0b00011100      // A-D converter channel 7 input
#define ANH4        0b00011100      // External H4 header analogue input (Ch7)
#define ANQ1        0b00011100      // Q1 phototransistor A-D input (Ch7)
#define AN8         0b00100000      // A-D converter channel 8 input
#define ANH7        0b00100000      // External H7 header analogue input (Ch8)
#define AN9         0b00100100      // A-D converter channel 9 input
#define ANH8        0b00100100      // External H8 header analogue input (Ch9)
#define AN10        0b00101000      // A-D converter channel 10 input (SW2)
#define AN11        0b00101100      // A-D converter channel 11 input (SW3)
#define ANTIM       0b01110100      // On-die temperature indicator module input

// Clock frequency for delay macros and simulation
#define _XTAL_FREQ  48000000        // Set clock frequency for time delays

// Prototypes for UBMP4.c functions:

/**
 * Function: void OSC_config(void)
 * 
 * Configure oscillator for 48 MHz operation (required for USB bootloader).
 */
void OSC_config(void);

/**
 * Function: void UBMP4_config(void)
 * 
 * Configure hardware ports and peripherals for on-board UBMP4 I/O devices.
 */
void UBMP4_config(void);

/**
 * Function: void ADC_config(void)
 * 
 * Configure ADC for 8-bit conversion from on-board phototransistor Q1 (AN7).
 */
void ADC_config(void);

/**
 * Function: void ADC_select_channel(unsigned char channel)
 * 
 * Enable ADC and switch input mux to specified channel based on the channel
 * constants defined above.
 * 
 * Example usage: ADC_select_channel(ANTIM);
 */
void ADC_select_channel(unsigned char);

/**
 * Function: unsigned char ADC_read(void)
 * 
 * Convert currently selected channel and return 8-bit conversion result.
 * 
 * Example usage: light_level = ADC_read();
 */
unsigned char ADC_read(void);

/**
 * Function: unsigned char ADC_read_channel(unsigned char channel)
 * 
 * Enable ADC, switch to the channel specified by channel constants defined
 * above, and return the 8-bit conversion result.
 * 
 * Example usage: light_level = ADC_read_channel(ANQ1);
 */
unsigned char ADC_read_channel(unsigned char);

// TODO - Add additional function prototypes for new functions in UBMP4.c here.

#define SW1         PORTAbits.RA3   // S1/Reset pushbutton input
#define SW2         PORTBbits.RB4   // Pushbutton SW2 input
#define BEEPER      LATAbits.LATA4  // Piezo beeper (LS1) output

void tone(unsigned char period);
