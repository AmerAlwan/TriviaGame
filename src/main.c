// Sample code for ECE 198

// Written by Bernie Roehl, August 2021

// This file contains code for a number of different examples.
// Each one is surrounded by an #ifdef ... #endif block inside of main().

// To run a particular example, you should remove the comment (//) in
// front of exactly ONE of the following lines:

//#define BUTTON_BLINK
// #define LIGHT_SCHEDULER
// #define TIME_RAND
// #define KEYPAD
// #define KEYPAD_CONTROL
// #define SEVEN_SEGMENT
// #define KEYPAD_SEVEN_SEGMENT
// #define COLOR_LED
// #define ROTARY_ENCODER
// #define ANALOG
// #define PWM

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions
#include <time.h>

#include "ece198.h"
#include "trivia_questions.h"
#include "LiquidCrystal.h"

int main(void)
{
    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    // initialize the pins to be input, output, alternate function, etc...

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED
        
 

    // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // is required, since there's one on the board)

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);

    GPIO_TypeDef * button_1_gpio = GPIOC;
    GPIO_TypeDef * button_2_gpio = GPIOC;
    GPIO_TypeDef * button_3_gpio = GPIOB;
    GPIO_TypeDef * button_4_gpio = GPIOA;
    GPIO_TypeDef * button_5_gpio = GPIOA;
    GPIO_TypeDef * button_6_gpio = GPIOA;
    GPIO_TypeDef * led_gpio = GPIOA;
    uint16_t button_1_gpio_pin = GPIO_PIN_0;
    uint16_t button_2_gpio_pin = GPIO_PIN_1;
    uint16_t button_3_gpio_pin = GPIO_PIN_0;
    uint16_t button_4_gpio_pin = GPIO_PIN_4;
    uint16_t button_5_gpio_pin = GPIO_PIN_1;
    uint16_t button_6_gpio_pin = GPIO_PIN_0;
    uint16_t led_r_gpio_pin = GPIO_PIN_5;
    uint16_t led_g_gpio_pin = GPIO_PIN_6;
    uint16_t led_b_gpio_pin = GPIO_PIN_7;

    // LCD Port and Pins
    GPIO_TypeDef * lcd_gpio_port = GPIOA;
    uint16_t lcd_rs_gpio_pin = GPIO_PIN_2;
    uint16_t lcd_rw_gpio_pin = GPIO_PIN_3;
    uint16_t lcd_e_gpio_pin = GPIO_PIN_5;
    uint16_t lcd_d0_gpio_pin = GPIO_PIN_6;
    uint16_t lcd_d1_gpio_pin = GPIO_PIN_7;
    uint16_t lcd_d2_gpio_pin = GPIO_PIN_8;
    uint16_t lcd_d3_gpio_pin = GPIO_PIN_9;

    InitializePin(button_6_gpio, button_6_gpio_pin, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // Button 6 - Start/Exit
    InitializePin(button_5_gpio, button_5_gpio_pin, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // Button 5 - Help/Hint
    InitializePin(button_4_gpio, button_4_gpio_pin, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // Button 4 - Answer 4
    InitializePin(button_3_gpio, button_3_gpio_pin, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // Button 3 - Answer 3
    InitializePin(button_2_gpio, button_2_gpio_pin, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // Button 2 - Answer 2
    InitializePin(button_1_gpio, button_1_gpio_pin, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // Button 1 - Answer 1
    InitializePin(led_gpio, led_r_gpio_pin | led_g_gpio_pin | led_b_gpio_pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // initialize color LED output pins
    
    int num_questions = 10;
    int timer_limit = 9000;
    int rand_questions[num_questions];
    int chosen_category;
    int category;
    int question;
    int answers;
    int points;
    bool restart;
    bool debug_mode;



    // initialize the library by associating any needed LCD interface pin
//	LiquidCrystal(lcd_gpio_port, lcd_rs_gpio_pin, lcd_rw_gpio_pin, lcd_e_gpio_pin, lcd_d0_gpio_pin, lcd_d1_gpio_pin, lcd_d2_gpio_pin, lcd_d3_gpio_pin);
    LiquidCrystal(GPIOB, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6);
    Initialize7Segment();

    while (true) {

        restart = false;
        points = 0;
        debug_mode = false;

        display_main_menu();
        //print_main_menu();
        Display7Segment(-1);

        while(!restart) {
                // Debug Mode
                if (HAL_GPIO_ReadPin(button_1_gpio, button_1_gpio_pin)) {
                    while(HAL_GPIO_ReadPin(button_1_gpio, button_1_gpio_pin)) {
                        if(HAL_GPIO_ReadPin(button_2_gpio, button_2_gpio_pin)) {
                            debug_mode = true;
                            HAL_GPIO_WritePin(led_gpio, led_b_gpio_pin, 0x01);  // blue  (hex 1 == 0001 binary)
                            HAL_Delay(500);
                            HAL_GPIO_WritePin(led_gpio, led_b_gpio_pin, 0x00);  // turn blue LED Off
                            while(HAL_GPIO_ReadPin(button_2_gpio, button_2_gpio_pin));
                        }
                    }
                }
                // Start Game
                if (HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin))  {   // Check for button 6 press 
                        // Generate random seed
                        srand(HAL_GetTick());
                        //print_categories_page();
                        display_categories_page();
                        chosen_category = -1;
                        while (HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin));  // wait for button 6 release
                        // Wait for user to choose category
                        while(true) {
                            // Go back if they press button 6
                            if (HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin) || HAL_GPIO_ReadPin(button_5_gpio, button_5_gpio_pin))  {   // Check for button 5 or 6 press 
                                while (HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin) || HAL_GPIO_ReadPin(button_5_gpio, button_5_gpio_pin));  // wait for button 5 or 6 release
                                SerialPuts("\nRestart");
                                restart = true;
                                break;
                            }
                            if (HAL_GPIO_ReadPin(button_4_gpio, button_4_gpio_pin))  {   // check for button 4 press 
                                while (HAL_GPIO_ReadPin(button_4_gpio, button_4_gpio_pin));  // wait for button 4 release
                                chosen_category = 2;
                            }
                            if (HAL_GPIO_ReadPin(button_3_gpio, button_3_gpio_pin))  {   // check for button 3 press 
                                while (HAL_GPIO_ReadPin(button_3_gpio, button_3_gpio_pin));  // wait for button 3 release
                                chosen_category = 1;
                            }
                            if (HAL_GPIO_ReadPin(button_2_gpio, button_2_gpio_pin))  {   // check for button 2 press 
                                while (HAL_GPIO_ReadPin(button_2_gpio, button_2_gpio_pin));  // wait for button 2 release
                                chosen_category = 0;
                            }
                            if (HAL_GPIO_ReadPin(button_1_gpio, button_1_gpio_pin))  {   // check for button 1 press 
                                while (HAL_GPIO_ReadPin(button_1_gpio, button_1_gpio_pin));  // wait for button 1 release
                                chosen_category = 3;
                            }
                            if (chosen_category != -1) {
                                break;
                            }
                        }

                        if (restart) {
                            break;
                        }

                        // Generates random questions (based on category chouse) and stores them in the rand_questions array
                        if (chosen_category == 3) {
                            generate_random_questions(rand_questions, num_questions);
                        } else {
                            generate_random_questions_with_category(rand_questions, num_questions, chosen_category);
                        }

                        if(rand_questions) {
                            for (int i = 0; i < num_questions; ++i) {
                                Display7Segment(9);
                                int chosen_answer = -1;
                                int timer = timer_limit;
                                int next_timer_limit = timer - 1000;
                                char timer_buff[100];
                                bool hint_used = false;
                                int page = 1;
                                int max_pages;

                                category = decipher_category(rand_questions[i]);
                                question = decipher_question(rand_questions[i]);
                                answers = get_shuffled_answers();

                                char text_question[500];
                                sprintf(text_question, "%i - %s > 1. %s | 2. %s | 3. %s | 4. %s", (i+1), get_question(category, question),  get_answer(category, question, decipher_answer(answers, 1)), get_answer(category, question, decipher_answer(answers, 2)),get_answer(category, question, decipher_answer(answers, 3)),get_answer(category, question, decipher_answer(answers, 4)));
                                encrypt_text(text_question);

                                // char text_answers[500];
                                // sprintf(text_answers, "",);
                                // encrypt_text(text_answers);

                                max_pages = get_num_pages(text_question);

                                // char gotten_question[500];
                                // sprintf(gotten_question, "%i - %s", (i+1), get_question(category, question));
                                //max_pages = get_num_pages(gotten_question) + 1;

                             //   encrypt_text(gotten_question);
                                

                                // char buff[100];
                                // sprintf(buff, "\nMax Pages = %i, Max Rows = %i", max_pages, get_max_rows(get_question(category, question)));
                                // SerialPuts(buff);

                              //  print_question(category, question, answers);
                                display_question(text_question, 1);


                                // char points_buff[100];
                                // sprintf(points_buff, "\nCurrent Points: %i/%i\n", points, num_questions);
                                // SerialPuts(points_buff);

                                while(timer > 0) {
                                    // Go back to main menu
                                    if (HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin))  {   // check for button 6 press 
                                        int counter = 0;
                                        while (counter <= 1000 && HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin)) {  // wait for button 6 release
                                            counter++;
                                            HAL_Delay(1);
                                        }
                                        timer -= counter;
                                        if (counter >= 1000) {
                                            restart = true;
                                            break;
                                        } else {
                                            page++;
                                            if (page > max_pages) {
                                                page = 1;
                                            }
                                            display_question(text_question, page);
                                            // if (page == max_pages) {
                                            //     display_answers(text_answers, page);
                                            // } else {
                                            //     display_question(text_question, page);
                                            // }
                                        }
                                    }

                                    // Remove two answers for hint
                                    if (HAL_GPIO_ReadPin(button_5_gpio, button_5_gpio_pin))  {   // check for button 6 press 
                                        int counter = 0;
                                        while (counter <= 1000 && HAL_GPIO_ReadPin(button_5_gpio, button_5_gpio_pin)) {  // wait for button 6 release
                                            counter++;
                                            HAL_Delay(1);
                                        }
                                        timer -= counter;
                                        if(counter >= 1000 && !hint_used) {
                                            int first_number = get_random_number(3) + 1;
                                            if(debug_mode) {
                                                answers = 1555;
                                            } else if (first_number == 1) {
                                                // Generates number in format of 1#55 where # is a random number from 2-4
                                                answers = ((10 + (get_random_number(2) + 2)) * 100) + 55;
                                            } else {
                                                // Generates number in format of #155 where # is a random number from 2-4
                                                answers = (((first_number * 10) + 1) * 100) + 55;
                                            }
                                            sprintf(text_question, "%i - %s > 1. %s | 2. %s | 3. %s | 4. %s", (i+1), get_question(category, question),  get_answer(category, question, decipher_answer(answers, 1)), get_answer(category, question, decipher_answer(answers, 2)),get_answer(category, question, decipher_answer(answers, 3)),get_answer(category, question, decipher_answer(answers, 4)));
                                            encrypt_text(text_question);
                                            hint_used = true;
                                            // SerialPuts("\nBefore Print");
                                            // print_question(category, question, answers);
                                            display_question(text_question, 1);
                                            page = 1;
                                        } else {
                                            page--;
                                            if(page <= 0) {
                                                page = max_pages;
                                            }
                                            display_question(text_question, page);
                                            //  if(page == max_pages) {
                                            //     display_answers(text_answers, page);
                                            // } else {
                                            //     display_question(text_question, page);
                                            // }
                                        }
                                    }

                                    // Wait for buttons 1-4 press for selecting answer

                                    if (HAL_GPIO_ReadPin(button_4_gpio, button_4_gpio_pin))  {   // check for button 4 press 
                                        while (HAL_GPIO_ReadPin(button_4_gpio, button_4_gpio_pin));  // wait for button 4 release
                                        chosen_answer = 3;
                                    }
                                    if (HAL_GPIO_ReadPin(button_3_gpio, button_3_gpio_pin))  {   // check for button 3 press 
                                        while (HAL_GPIO_ReadPin(button_3_gpio, button_3_gpio_pin));  // wait for button 3 release
                                        chosen_answer = 2;
                                    }
                                    if (HAL_GPIO_ReadPin(button_2_gpio, button_2_gpio_pin))  {   // check for button 2 press 
                                        while (HAL_GPIO_ReadPin(button_2_gpio, button_2_gpio_pin));  // wait for button 2 release
                                        chosen_answer = 1;
                                    }
                                    if (HAL_GPIO_ReadPin(button_1_gpio, button_1_gpio_pin))  {   // check for button 6 press 
                                        while (HAL_GPIO_ReadPin(button_1_gpio, button_1_gpio_pin));  // wait for button 6 release
                                        chosen_answer = 0;
                                    }

                                    if (chosen_answer != -1) {
                                        break;
                                    }

                                    if(timer <= next_timer_limit) {
                                        next_timer_limit -= 1000;
                                       // sprintf(timer_buff, "\rTime Left: %is", timer / 1000);
                                      //  SerialPuts(timer_buff);
                                        Display7Segment(timer / 1000);
                                    }
                                    timer--;
                                    HAL_Delay(1);
                                }

                                if(restart) {break;}
                                // char buffs[100];
                                // sprintf(buffs, "\n\nChosen Answer: %i, Correct Answer: %i, Answers: %i", chosen_answer, decipher_correct_answer(answers), answers);
                                // SerialPuts(buffs);
                                char status[200];
                                Display7Segment(-1);
                                if (chosen_answer == decipher_correct_answer(answers)) {
                                    points++;
                                    sprintf(status, "Correct!|Your score is %i/%i", points, num_questions);
                                    display_status_page(status);
                                    //print_status_page("Correct");
                                    int counter = 0;
                                    HAL_GPIO_WritePin(led_gpio, led_g_gpio_pin, 0x04);  // LED set to green color
                                    while (counter < 3) {
                                        counter++;
                                        HAL_Delay(1000);
                                    }
                                    HAL_GPIO_WritePin(led_gpio, led_g_gpio_pin, 0 & 0x02); // LED set to no color
                                } else {
                                    if (timer == 0) {
                                        sprintf(status, "Time Out!|Your score is %i/%i", points, num_questions);
                                        display_status_page(status);
                                      //  print_status_page("Time Out!");
                                    } else {
                                        sprintf(status, "Wrong!|Your score is %i/%i", points, num_questions);
                                        display_status_page(status);
                                    }
                                    int counter = 0;
                                    HAL_GPIO_WritePin(led_gpio, led_r_gpio_pin, 0x04); // LED set to red color
                                    while (counter < 3) {
                                        counter++;
                                        HAL_Delay(1000);
                                    }
                                    HAL_GPIO_WritePin(led_gpio, led_r_gpio_pin, 0 & 0x04); // LED set to no color
                                }
                            }



                            if(!restart) {
                                char points_buff[100];
                               // SerialPuts(points_buff);
                                restart = true;
                                if(points == num_questions) {
                                    sprintf(points_buff, "Game Over!|Your score is %i/%i|Congrats, You Won!|Thanks for playing!", points, num_questions);
                                    display_status_page(points_buff);
                                    int counter = 0;
                                    while(counter < 30) {
                                        HAL_GPIO_WritePin(led_gpio, led_b_gpio_pin, counter & 0x01);  // blue  (hex 1 == 0001 binary)
                                        HAL_GPIO_WritePin(led_gpio, led_g_gpio_pin, counter & 0x02);  // green (hex 2 == 0010 binary)
                                        HAL_GPIO_WritePin(led_gpio, led_r_gpio_pin, counter & 0x04);  // red   (hex 4 == 0100 binary)
                                        counter++;
                                        HAL_Delay(100);
                                    }

                                    HAL_GPIO_WritePin(led_gpio, led_r_gpio_pin, 0 & 0x00); // LED set to no color
                                    HAL_GPIO_WritePin(led_gpio, led_g_gpio_pin, 0 & 0x00); // LED set to no color
                                    HAL_GPIO_WritePin(led_gpio, led_b_gpio_pin, 0 & 0x00); // LED set to no color
                                } else {
                                    sprintf(points_buff, "Game Over!|Your score is %i/%i|You Lost :(|Play Again! :D", points, num_questions);
                                    display_status_page(points_buff);
                                    int counter = 0;
                                    while(counter < 3) {
                                        counter++;
                                        HAL_Delay(1000);
                                    }
                                }
                            } 
                        }
                } 
                // Help Page
                else if (HAL_GPIO_ReadPin(button_5_gpio, button_5_gpio_pin))  {   // check for button 5 press 
                    //print_help_page();
                    display_help_page();
                    while (HAL_GPIO_ReadPin(button_5_gpio, button_5_gpio_pin));  // wait for button 5 release
                    while(1) {
                    // Back to main menu
                        if (HAL_GPIO_ReadPin(button_5_gpio, button_5_gpio_pin) || HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin))  {   // check for button 5 or 6 press 
                            while (HAL_GPIO_ReadPin(button_5_gpio, button_5_gpio_pin) || HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin));  // wait for button 5 or 6 release
                            restart = true;
                            break;
                        }
                    }
                }
            } 
    }

    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)

#ifdef BUTTON_BLINK
    // Wait for the user to push the blue button, then blink the LED.

    // wait for button press (active low)
    while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
    {
    }

    while (1) // loop forever, blinking the LED
    {
       // char buff[100];
        //sprintf(buff, "something to print");
       // SerialPuts("something to print"); 
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(500);  // 250 milliseconds == 1/4 second
    }
#endif

#ifdef LIGHT_SCHEDULER
    // Turn on the LED five seconds after reset, and turn it off again five seconds later.

    while (true) {
        uint32_t now = HAL_GetTick();
        if (now > 5000 && now < 10000)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true);   // turn on LED
        else
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);  // turn off LED
    }
#endif

#ifdef TIME_RAND
    // This illustrates the use of HAL_GetTick() to get the current time,
    // plus the use of random() for random number generation.
    
    // Note that you must have "#include <stdlib.h>"" at the top of your main.c
    // in order to use the srand() and random() functions.

    // while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button press
    // srand(HAL_GetTick());  // set the random seed to be the time in ms that it took to press the button
    // if the line above is commented out, your program will get the same sequence of random numbers
    // every time you run it (which may be useful in some cases)

    while (true) // loop forever
    {
        while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button press

        // Display the time in milliseconds along with a random number.
        // We use the sprintf() function to put the formatted output into a buffer;
        // see https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm for more
        // information about this function
        char buff[100];
        sprintf(buff, "Time: %lu ms   Random = %ld\r\n", HAL_GetTick(), random());
        // lu == "long unsigned", ld = "long decimal", where "long" is 32 bit and "decimal" implies signed
        SerialPuts(buff); // transmit the buffer to the host computer's serial monitor in VSCode/PlatformIO

        while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button to be released
    }
#endif

#ifdef KEYPAD
    // Read buttons on the keypad and display them on the console.

    // this string contains the symbols on the external keypad
    // (they may be different for different keypads)
    char *keypad_symbols = "123A456B789C*0#D";
    // note that they're numbered from left to right and top to bottom, like reading words on a page

    InitializeKeypad();
    while (true)
    {
        while (ReadKeypad() < 0);   // wait for a valid key
        SerialPutc(keypad_symbols[ReadKeypad()]);  // look up its ASCII symbol and send it to the hsot
        while (ReadKeypad() >= 0);  // wait until key is released
    }
#endif

#ifdef KEYPAD_CONTROL
    // Use top-right button on 4x4 keypad (typically 'A') to toggle LED.

    InitializeKeypad();
    while (true)
    {
        while (ReadKeypad() < 0);   // wait for a valid key
        int key = ReadKeypad();
        if (key == 3)  // top-right key in a 4x4 keypad, usually 'A'
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);   // toggle LED on or off
         while (ReadKeypad() >= 0);  // wait until key is released
    }
#endif

#ifdef SEVEN_SEGMENT
    // Display the numbers 0 to 9 inclusive on the 7-segment display, pausing for a second between each one.
    // (remember that the GND connection on the display must go through a 220 ohm current-limiting resistor!)
    
    Initialize7Segment();
    while (true)
        for (int i = 0; i < 10; ++i)
        {
            Display7Segment(i);
            HAL_Delay(1000);  // 1000 milliseconds == 1 second
        }
#endif

#ifdef KEYPAD_SEVEN_SEGMENT
    // Combines the previous two examples, displaying numbers from the keypad on the 7-segment display.

    // this string contains the symbols on the external keypad
    // (they may be different for different keypads)
    char *keypad_symbols = "123A456B789C*0#D";
    // note that they're numbered from left to right and top to bottom, like reading words on a page

    InitializeKeypad();
    Initialize7Segment();
    while (true)
    {
        int key = ReadKeypad();
        if (key >= 0)
            Display7Segment(keypad_symbols[key]-'0');  // tricky code to convert ASCII digit to a number
    }
#endif

#ifdef COLOR_LED
    // Cycle through all 8 possible colors (including off and white) as the on-board button is pressed.
    // This example assumes that the color LED is connected to pins D11, D12 and D13.

    // Remember that each of those three pins must go through a 220 ohm current-limiting resistor!
    // Also remember that the longest pin on the LED should be hooked up to GND.

    InitializePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // initialize color LED output pins
    while (true) {
        for (int color = 0; color < 8; ++color) {
            // bottom three bits indicate which of the three LEDs should be on (eight possible combinations)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, color & 0x01);  // blue  (hex 1 == 0001 binary)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, color & 0x02);  // green (hex 2 == 0010 binary)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, color & 0x04);  // red   (hex 4 == 0100 binary)

            while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));   // wait for button press 
            while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button release
        }
    }
#endif

#ifdef ROTARY_ENCODER
    // Read values from the rotary encoder and update a count, which is displayed in the console.

    InitializePin(GPIOB, GPIO_PIN_5, GPIO_MODE_INPUT, GPIO_PULLUP, 0);   // initialize CLK pin
    InitializePin(GPIOB, GPIO_PIN_4, GPIO_MODE_INPUT, GPIO_PULLUP, 0);   // initialize DT pin
    InitializePin(GPIOB, GPIO_PIN_10, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // initialize SW pin
    
    bool previousClk = false;  // needed by ReadEncoder() to store the previous state of the CLK pin
    int count = 0;             // this gets incremented or decremented as we rotate the encoder

    while (true)
    {
        int delta = ReadEncoder(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, &previousClk);  // update the count by -1, 0 or +1
        if (delta != 0) {
            count += delta;
            char buff[100];
            sprintf(buff, "%d  \r", count);
            SerialPuts(buff);
        }
        bool sw = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);  // read the push-switch on the encoder (active low, so we invert it using !)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, sw);  // turn on LED when encoder switch is pushed in
    }
#endif

#ifdef ANALOG
    // Use the ADC (Analog to Digital Converter) to read voltage values from two pins.

    __HAL_RCC_ADC1_CLK_ENABLE();        // enable ADC 1
    ADC_HandleTypeDef adcInstance;      // this variable stores an instance of the ADC
    InitializeADC(&adcInstance, ADC1);  // initialize the ADC instance
    // Enables the input pins
    // (on this board, pin A0 is connected to channel 0 of ADC1, and A1 is connected to channel 1 of ADC1)
    InitializePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1, GPIO_MODE_ANALOG, GPIO_NOPULL, 0);   
    while (true)
    {
        // read the ADC values (0 -> 0V, 2^12 -> 3.3V)
        uint16_t raw0 = ReadADC(&adcInstance, ADC_CHANNEL_0);
        uint16_t raw1 = ReadADC(&adcInstance, ADC_CHANNEL_1);

        // print the ADC values
        char buff[100];
        sprintf(buff, "Channel0: %hu, Channel1: %hu\r\n", raw0, raw1);  // hu == "unsigned short" (16 bit)
        SerialPuts(buff);
    }
#endif

#ifdef PWM
    // Use Pulse Width Modulation to fade the LED in and out.
    uint16_t period = 100, prescale = 16;

    __TIM2_CLK_ENABLE();  // enable timer 2
    TIM_HandleTypeDef pwmTimerInstance;  // this variable stores an instance of the timer
    InitializePWMTimer(&pwmTimerInstance, TIM2, period, prescale);   // initialize the timer instance
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_1);          // initialize one channel (can use others for motors, etc)

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2); // connect the LED to the timer output

    while (true)
    {
        // fade the LED in by slowly increasing the duty cycle
        for (uint32_t i = 0; i < period; ++i)
        {
            SetPWMDutyCycle(&pwmTimerInstance, TIM_CHANNEL_1, i);
            HAL_Delay(5);
        }
        // fade the LED out by slowly decreasing the duty cycle
        for (uint32_t i = period; i > 0; --i)
        {
            SetPWMDutyCycle(&pwmTimerInstance, TIM_CHANNEL_1, i);
            HAL_Delay(5);
        }
    }
#endif
    return 0;
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}
