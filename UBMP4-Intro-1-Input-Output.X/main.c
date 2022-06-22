/*==============================================================================
 File: main.c
 Project: Final 30 Product
 Date: June 22, 2022
 
 This file is the main file for my UBMP4 game console. It contains the code for
 the title menu of the game, the dinosaur game, and the defender game.
==============================================================================*/
// Header files
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "UBMP4.h"
#include <time.h>
#include "PIC16F1459config.h"
#include "LCD_lib.h"
#include "dino_game.h"
#include "defender_game.h"

// This is a function for the defender game. It simply takes in the asteroid's x and y coordinates and
// displays it on the LCD. I used this function to make the code shorter, but I could also make other functions
// at a later time for other things, such as the hit detection for the asteroid.

void display_asteroid(int asteroid_x, asteroid_y)
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
       cd_data(3);
    }
}  

//======================= MAIN =====================================
// These are variables for checking when switch 2 is pressed.
int SW2count = 0;
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
    // This is the main while loop that runs the game.
    while(game_console == true)
    {
        // This reads the input from the joystick.
        y = ADC_read_channel(ANH2);
      
        // This is a switch counter so that a game starts after 2 presses of the button.
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

        // This is the game select screen. This is what it defaults to when you press
        // the switch button.
        if(SW2count == 1)
        {
            lcd_cmd(0x01);
            lcd_WriteStr("Dinosaur Game<");
            lcd_SetCursor(63);
            lcd_WriteStr("Defender");
            game_1 = true;
            SW2count += 1;
        }

        // If the joystick is up then it sets the game to game one, which was the dinosaur game.
        if(y < 100)
        {
            lcd_cmd(0x01);
            lcd_SetCursor(0);
            lcd_WriteStr("Dinosaur Game<");
            lcd_SetCursor(63);
            lcd_WriteStr("Defender");
            game_1 = true;
        }
        
        // If the joystick is down then it sets the game one to false, which results in the defender game.
        if(y > 250)
        {
            lcd_cmd(0x01);
            lcd_SetCursor(0);
            lcd_WriteStr("Dinosaur Game");
            lcd_SetCursor(63);
            lcd_WriteStr("Defender<");
            game_1 = false;
        }
        
        // This code runs after you pick a game with a joystick and select the switch.
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
        // These functions create the custom characters. the variable are the character sprites found in the dino_game.h file.
        // The number in the function is where the character is stored in CG-RAM which is character generated RAM.
        // The CG-RAM can only store 8 custom characters at a time. Luckily I didn't need that many sprites to make my game.
         
        CreateCustomCharacter(dinosaur1,0);
        CreateCustomCharacter(dinosaur2,1);
        CreateCustomCharacter(cactus,2);
        CreateCustomCharacter(bird1,3);
        CreateCustomCharacter(bird2,4);
         
        // This code initializes the rand() function, without this code it doesn't seem to work.
        time_t t;
        srand((unsigned) time(&t));

        while(dino_game == true)
        {
            // This reads the y coordinate of the joystick.
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
            // The speed variable creates a delay in the movement of the obstacles by waiting for while loops to complete.
            // For example with a speed of 3 the obstacles will only move after 3 loops of the while loop. I did this because
            // the normal delays would also delay the dinosaur. The loop count just counts how long the while loop has gone on.
            // Using this variable I can make the obstacles speed up as the game goes on.
         
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
         
            // This is the code for the second cactus, which just trails behind the first.
            if(second_cactus == true)
            {
                cactus2_pos = cactus1_pos + 2;
            }
            // This code puts the cactus and bird at a random position after they leave the right side of the screen.
            // It also adds to the player's score.
         
            if(cactus1_pos < 63)
            {
                cactus1_pos = 79 + (rand() % 4);
                score += 1;
            } 

            if(bird_pos < 0)
            {
                bird_pos = 16 + (rand() % 4);
                score += 1;
            }
            // Dino jumping
            // This code detects if the joystick is pushed up, and if it is then it plays a noise
            // and sets the jumping condition to true.
            
            if(y < 100 && jumping == false)
            {
                jumping = true;
                tone(100);                                
            }
            
            // This code works by keeping the dinosaur in the air for 10 loops of the while loop.
            
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
            // These are the custom characters for this game. Although it may seem like
            // there are only 3 sprites when you play, there is actually 6. The reason for this
            // is because I had to make a sprite for the ship at a high position and the ship
            // at a low position.
            CreateCustomCharacter(spaceship_top,0);
            CreateCustomCharacter(spaceship_bottom,1);
            CreateCustomCharacter(asteroid_top,2);
            CreateCustomCharacter(asteroid_bottom,3);
            CreateCustomCharacter(laser_top,4);
            CreateCustomCharacter(laser_bottom,5);
            
            // This is for the rand() function.
            time_t t;
            srand((unsigned) time(&t));

            while(defender_game == true)
            {

                // Spaceship Movement
                // This reads both the x and y coordinates of the joystick.
                x = ADC_read_channel(ANH1);
                y = ADC_read_channel(ANH2);
                
                // The following if statements are just for moving the spaceship on the screen, and keeping it
                // from going off the screen.
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
                
                // This code makes it so a sound is played and laser is shot when SW2 is pressed.
                if(laser_count == 0 && SW2 == 0)
                {
                    laser_count = 1;
                    tone(300);
                }
                
                // This code moves the asteroids in the game.
                asteroid1_x -= 1;
                asteroid2_x -= 1;
                asteroid3_x -= 1;
                
                // The code below puts the asteroid at a random position after it has left the screen.
                if(asteroid1_x < 0)
                {
                    asteroid1_x = 15;
                    asteroid1_y = rand() % 5;
                }

                if(asteroid2_x < 0)
                {
                    asteroid2_x = 15;
                    asteroid2_y = rand() % 5;
                }

                if(asteroid3_x < 0)
                {
                    asteroid3_x = 15;
                    asteroid3_y = rand() % 5;
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

                // Update LCD and Hit detection
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
                display_asteroid(asteroid2_x, asteroid2_y);
                display_asteroid(asteroid3_x, asteroid3_y);
             
                // The code below is for the hit detection of the laser and the asteroids.
                if(laser_x <= asteroid1_x + 1 && laser_x >= asteroid1_x - 1 && asteroid1_y == laser_y)
                {
                    asteroid1_x = 16;
                    asteroid1_y = rand() % 5;
                    laser_count = 0;
                    laser_x = 18;
                    score += 1;
                }

                if(laser_x <= asteroid2_x + 1 && laser_x >= asteroid2_x - 1 && asteroid2_y == laser_y)
                {
                    asteroid2_x = 16;
                    asteroid2_y = rand() % 5;
                    laser_count = 0;
                    laser_x = 18;
                    score += 1;
                }

                if(laser_x <= asteroid3_x + 1 && laser_x >= asteroid3_x - 1 && asteroid3_y == laser_y)
                {
                    asteroid3_x = 16;
                    asteroid3_y = rand() % 5;
                    laser_count = 0;
                    laser_x = 18;
                    score += 1;
                }

                if(spaceship_x <= asteroid1_x + 1 && spaceship_x >= asteroid1_x - 1 && spaceship_y == asteroid1_y || spaceship_x <= asteroid2_x + 1 && spaceship_x >= asteroid2_x - 1 && spaceship_y == asteroid2_y || spaceship_x <= asteroid3_x + 1 && spaceship_x >= asteroid3_x - 1 && spaceship_y == asteroid3_y)
                {
                    lcd_cmd(0x01);
                    lcd_SetCursor(0);
                    lcd_WriteStr("Game Over");
                    lcd_SetCursor(63);
                    lcd_WriteStr("Score: ");
                    char str[6];
                    sprintf(str, "%d", score);
                    lcd_WriteStr(str);
                    defender_game = false;
                }
                
                
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



 
