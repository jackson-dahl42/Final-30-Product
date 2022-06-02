/*==============================================================================
 Project: Intro-1-Input-Output
 Date:    May 16, 2021
 
 This example UBMP4 input and output program demonstrates pushbutton input, LED
 (bit) output, port latch (byte) output, time delay functions, and simple 'if'
 condition structures.
 
 Additional program analysis and programming activities demonstrate byte output,
 logical condition operators AND and OR, using delay functions to create sound,
 and simulated start-stop button functionality.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP4.h"           // Include UBMP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// The main function is required, and the program begins executing from here.

int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    // Code in this while loop runs repeatedly.
    while(1)
	{
        
        // If SW2 is pressed, make a flashy light pattern


        // Add code for your Program Analysis and Programming Activities here:

        if(SW2 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(500);
        }

        if(SW3 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(700);
        }

        if(SW4 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(900);
        }

        if(SW5 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(1100);
        }
        

        if(SW1 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(1000);
            RESET();
        }

        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(1000);
            LED1 = 1;
            __delay_ms(100);
            LED1 = 0;
            __delay_ms(100);
            LED1 = 1;
            RESET();
        }
    }
}

/* Learn More - Program Analysis Activities
 * 
 * 1. How many times do the LEDs flash if SW2 is quickly pressed and released?
 *    Do the LEDs keep flashing when SW2 is held? Look at the program and
 *    explain why this happens when SW2 is held.

 *    Answer: The LEDs flash once if SW2 is quickly pressed and released. The LEDs keep flashing when SW2 is held.
 *    When SW2 is held its value is equal to 0 and this triggers the if statement to run its code. This code
 *    includes the LEDs turning on with a 100 ms delay and then turning off in with a 100 ms delay. The machine
 *    runs the code from top to bottom. When the button is held the value of the SW2 is 0 so it keeps running the code
 *    because it is inside the while loop and the code is repeated.
 * 
 * 2. Explain the difference between the statements: LED3 = 0; and LED3 = 1;

 *    Answer: LED3 = 0; means turn the light off while LED3 = 1; means turn the light on.
 * 
 * 3. What voltage do you expect the microcontroller to output to LED D3 when
 *    the statement LED3 = 0; runs? What voltage do you expect the output to be
 *    when the statement LED3 = 1; runs?
 *
 *    Answer: I excpect the voltage of the microcontroller to LED3 to be 0 when the statement  LED3 = 0; runs. I excpect the voltge
 *    of the microcontroller to  the LED3 would be 2.9 V or between 1.8 and 3.3 V if the statement LED3 = 1; runs.
 * 
 *    You can confirm the output voltage with a voltmeter if you have access
 *    to one. If you tried that, did the voltage match your prediction?
 * 
 * 4. The statement 'if(SW2 == 0)' uses two equal signs, while the statement
 *    'LED3 = 1;' uses a single equal sign. What operation is performed by one
 *    equal sign? What operation is performed by two equal signs?
 *
 *    Answer: The operation that one equal sign does is assign a value to a variable. The operation performed by two equal signs is a boolean operator.
 *    When the the two values on both sides of the two equal signs are the same the boolean operator says the statement is true and runs the code.
 *    It does false for everything else.
 * 
 * 5. The following program code includes instructions that write to the PORTC
 *    output latches directly. Try it by copying and pasting this code below
 *    the existing SW2 'if' structure, at the location shown by the comment.

        if(SW3 == 0)
        {
            LATC = 0b00000000;
            __delay_ms(100);
            LATC = 0b11110000;
            __delay_ms(100);
        }

 *    What happens when pushbutton SW3 is pressed? Identify at least one
 *    advantage and one disadvantage of controlling the LEDs using 'LATC' writes
 *    rather than through individual 'LEDn = x;' statements.
 *
 *    Answer: Multiple lights will turn on. Perhaps you could use this to save writing by activating multiple lights wiht one statement.
 *    One disadvantage is that you can't controll the individual LED with this statement.
 * 
 * 6. Next, compare the operation of 'if' and 'while' structures to simulate
 *    momentary buttons. Replace the code you added in 5, above, with this code:

        // Momentary button using if structure
        if(SW3 == 0)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

        // Momentary button using while structure
        while(SW4 == 0)
        {
            LED5 = 1;
        }
        LED5 = 0;

 *    First, try pressing and releasing SW3 and SW4 one at a time.
 * 
 *    Next, press and hold SW3 while pressing and releasing SW4. Does it work
 *    as expected?
 * 
 *    Next, try press and holding SW4 while pressing and releasing SW3. Does it
 *    work as expected? Explain the difference in operation between the 'if' and
 *    'while' structures making up the momentary button code.
 *
 *    Answer: When the code in the while loop is running the if statements are ignored. You cna think that the computer runs code from top to bottom. When 
 *    The code enters a while loop it runs the code top to bottom, but when it reaches the bottom it gets sent back to the top of the while loop. Because
 *    the computer only runs the code in the while loop while it is activated the computer ignores the if statement. THis means the functionality of, the 
 *    if statement will stop when the while loop is running.
 * 
 * 7. Let's explore logical conditions using 'if' statements. Replace the code
 *    added in 6, above, with this nested if code to make a logical AND
 *    condition that will light LED D4 only if both SW3 and SW4 are pressed:

        // Nested if 'AND' code
        if(SW3 == 0)
        {
            if(SW4 == 0)
            {
                LED4 = 1;
            }
            else
            {
                LED4 = 0;
            }
        }
        else
        {
            LED4 = 0;
        }

 *    Test the code to ensure it works as expected. Does the order of the if
 *    conditions matter? (eg. swap the conditional checks for SW3 and SW4)
 *
 *    Answer: You have to press both of the buttons in order to activate the conditions.
 *    The order doesn't matter, you press SW4 then SW3 or SW3 and then SW4.
 * 
 * 8. Next, replace the code from 7 with the following code which implements a
 *    logical AND conditional operator composed of two ampersands '&&':
 
        // Conditional 'AND' code
        if(SW3 == 0 && SW4 == 0)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

 *    Does '&&' work the same way as the nested if structures? Can you think of
 *    at least one advantage of using a logical conditional operator instead of
 *    nested if structures?
 *
 *    Answer: The '&&' works the same way a sthe nested if structures. One advantage of using a logical operator is that is takes up less writing then nested brackets.
 *    also it might make it easier to read code. ex. if(x>y && w>v && z>a) if this was a nested bracket it would be harder to understand,
 * 
 * 9. Replace the double ampersand '&&' with double vertical bars '||)' to make
 *    a logical OR conditional operator. Your code should look like this:
  
        // Conditional 'OR' code
        if(SW3 == 0 || SW4 == 0)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

 *    Describe the conditions under which LED4 turns on.
 *    
 *     Answer: The LED4 will turn on if SW3 is pressed or if SW4 is pressed or if both SW3 and SW4 are pressed.
 * 
 * Programming Activities
 * 
 * 1. The statement '__delay_ms(100);' creates a 100ms delay. Try changing one
 *    or more of the delay values in the program to 500ms and see what happens.
 * 
 *    Can the delay be made even longer? Try 1000 ms. How big can the delay be
 *    before MPLAB-X produces an error message? (Hint: can you think of a fast
 *    and efficient way of guessing an unknown number?)
 *    
 *    Answer: Yes, the delay can be made longer. The maximum delay is 4205 ms.
 * 
 * 2. The '__delay_ms();' function only accepts integers as delay values. To
 *    make delays shorter than 1ms, specify a delay in microseconds using the
 *    '__delay_us();' function. You won't be able to see such short LED flashes
 *    with your eyes, but you could measure them using an oscilloscope, or hear
 *    them if they are used to turn the piezo beeper on and off. Try this code:
 
        // Make a tone while SW5 is held
        if(SW5 == 0)
        {
            BEEPER = 1;
            __delay_us(567);
            BEEPER = 0;
            __delay_us(567);
        }

 *    Try changing the delay values in both of the __delay_us(); functions.
 *    Does the pitch of the tone increase or decrease if the delay value is
 *    made smaller?
 *
 *    Answer: When the delay is decreased the pitch increases, but when teh delay increases th epitch decreases.
 * 
 * 3. This code demonstrates a more compact way of toggling the beeper output
 *    using a logical NOT operator '!'. Replace the code above, with this code:
 
        // Make a tone while SW5 is held
        if(SW5 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(567);
        }

 *    One difference between this code and the code in 2, above, is the state
 *    of the BEEPER pin when SW5 is released. What state will the BEEPER output
 *    be in after this code runs? While one advantage of this method is smaller
 *    code, can you think of one or more disadvantages based on its output when
 *    the button is released?
 *
 *    Answer: the beeper will beep and then stop. You cannot control the delay of the beeper shutting off.
 * 
 * 4. Using modified versions of the original SW2 'if' structure, create a
 *    program that makes a unique LED flashing pattern for each pushbutton.
 * 
 *    Test each of your flashing patterns. Describe what happens when more than
 *    one button is held. Do all of the patterns try to flash the LEDs at the
 *    same time, or sequentially? Explain why this is.

//Program for different light patterns for each button.

        if(SW3 == 0)
        {
           LED3 = 1;
           LED5 = 1;
           __delay_ms(100);
           LED3 = 0;
           LED5 = 0;
           __delay_ms(100);
           LED4 = 1;
           LED6 = 1;
           __delay_ms(100);
           LED4 = 0;
           LED6 = 0;
           __delay_ms(100);
        }

        if(SW4 == 0)
        {
            LED3 = 1;
            LED4 = 1;
            LED5 = 1;
            LED6 = 1;
            __delay_ms(100);
            LED3 = 0;
            LED4 = 0;
            LED5 = 0;
            LED6 = 0;
            __delay_ms(100);
        }
        
        if(SW5 == 0)
        {
            LED6 = 1;
            __delay_ms(100);
            LED5 = 1;
            __delay_ms(100);
            LED4 = 1;
            __delay_ms(100);
            LED3 = 1;
            __delay_ms(100);
            LED6 = 0;
            __delay_ms(100);
            LED5 = 0;
            __delay_ms(100);
            LED4 = 0;
            __delay_ms(100);
            LED3 = 0;
            __delay_ms(100);
        }

        if(SW2 == 0)
        {
            LED3 = 1;
            __delay_ms(100);
            LED4 = 1;
            __delay_ms(100);
            LED5 = 1;
            __delay_ms(100);
            LED6 = 1;
            __delay_ms(100);
            LED3 = 0;
            __delay_ms(100);
            LED4 = 0;
            __delay_ms(100);
            LED5 = 0;
            __delay_ms(100);
            LED6 = 0;
            __delay_ms(100);
        }

        if(SW1 == 0)
        {
            LED1 = 1;
            __delay_ms(100);
            LED1 = 0;
            __delay_ms(100);
            LED1 = 1;
            RESET();
        }
        Answer: When I run the program that I made the individual programs work fine. However when I press all the buttons at once they don't all activate at the same time.
        The computer seem to take turns between the programs from top to bottom. It will run all of the code as if it were on giant if statment because all of the conditions are met.
        The computer doesn't run everything at once because it reads down the text. The delay function also helps make this apparent.


 * 
 * 5. Create a program that makes a different tone for each pushbutton.
 * 
 *    Test each tone by pressing each button individually. Next, press two or
 *    more buttons at the same time. Describe what the tone waveform would look
 *    like when more than one button is held.

 Answer: when more than one button is held the tone wave form would look like a composition of the two waves.

//Program for different tone for each button.
        if(SW2 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(500);
        }

        if(SW3 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(700);
        }

        if(SW4 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(900);
        }

        if(SW5 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(1100);
        }
        

        if(SW1 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(1000);
            RESET();
        }
 * 
 * 6. Use individual 'if' structures to simulate 'Start' and 'Stop' buttons for
 *    an industrial machine. LED D4 should turn on when SW3 is pressed, stay on
 *    even after SW3 is released, and turn off when SW4 is pressed. Test your
 *    program to make sure it works.

        if(SW3 == 0)
        {
            LED4 = 1;
        }
        if(SW4 == 0)
        {
            LED4 = 0;
        }
 * 
 * 7. Running your program from 6, above, describe what happens when both SW3
 *    and SW4 are pressed. Does LED D4 stay on? If so, how does the brightness
 *    of LED D4 compare between its normal on state following SW3 being pressed
 *    to this new state when both SW3 and SW4 are bing held? Can you explain
 *    why it changes?
      Answer: When both SW3 and SW4 are pressed LED D4 stays on. The brightness of the LED is less than when SW4 is not being pressed.
      It probably is less bright because the device is continuesly shutting it off and turning it off when it reads the code from top to bottom.
 * 
 * 8. As you can imagine, an industrial machine that is able to turn on even
 *    while its 'Stop' button is pressed represents a significant safety hazard.
 *    Using a logical conditional operator, modify the start-stop program from
 *    activity 5 to make it safer. SW3 should only turn on LED D4 if SW4 is
 *    released.
        if(SW3 == 0 && SW4 == 1)
        {
            LED4 = 1;
        }
        if(SW4 == 0)
        {
            LED4 = 0;
        }
 * 
 * 9. LED D1 is normally used to indicate that a program is running, but it can
 *    be controlled by your program as well. If you take a look at the UBMP4
 *    schematic, you will see that LED D1's cathode (or negative) pin is
 *    connected to the microcontroller instead of the anode (positive) pin as
 *    with the other LEDs. This means that you need to make D1's output a zero
 *    to turn D1 on. Try it! Make a program that controls or flashes LED D1.
 
   if(SW3 == 0)
   {
       LED1 = 0;
       __delay__ms(100);

       LED1 = 0;
       __delay__ms(100);

       LED1 = 1;
       __delay__ms(100);

       LED1 = 0;
       __delay__ms(100);
   }

 *
 *
 *
 *
 *
 *
 */
