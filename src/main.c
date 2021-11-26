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

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    // initialize the pins to be input, output, alternate function, etc...

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED

    SerialSetup(9600);

    // Button Port and Pins
    GPIO_TypeDef * button_1_gpio = GPIOC;
    GPIO_TypeDef * button_2_gpio = GPIOC;
    GPIO_TypeDef * button_3_gpio = GPIOB;
    GPIO_TypeDef * button_4_gpio = GPIOA;
    GPIO_TypeDef * button_5_gpio = GPIOA;
    GPIO_TypeDef * button_6_gpio = GPIOA;
    uint16_t button_1_gpio_pin = GPIO_PIN_0;
    uint16_t button_2_gpio_pin = GPIO_PIN_1;
    uint16_t button_3_gpio_pin = GPIO_PIN_0;
    uint16_t button_4_gpio_pin = GPIO_PIN_4;
    uint16_t button_5_gpio_pin = GPIO_PIN_1;
    uint16_t button_6_gpio_pin = GPIO_PIN_0;

    // LED Diode Port and Pins
    GPIO_TypeDef * led_gpio = GPIOA;
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

    // Button and LED Diode Initialization
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



    // initialize the LCD and 7 Segment Display
    LiquidCrystal(GPIOB, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6);
    Initialize7Segment();

    // Main Game Loop
    while (true) {

        restart = false;
        points = 0;
        debug_mode = false;

        display_main_menu();
        Display7Segment(-1);

        while(!restart) {
                // Debug Mode
                if (HAL_GPIO_ReadPin(button_1_gpio, button_1_gpio_pin)) { // Check for button 1 press
                    while(HAL_GPIO_ReadPin(button_1_gpio, button_1_gpio_pin)) { // While button 1 is being pressed
                        if(HAL_GPIO_ReadPin(button_2_gpio, button_2_gpio_pin)) { // Check for button 2 press

                            // Set Debug Mode to True and Set LED to blue for half a second

                            debug_mode = true;
                            HAL_GPIO_WritePin(led_gpio, led_b_gpio_pin, 0x01);  // blue  (hex 1 == 0001 binary)
                            HAL_Delay(500);
                            HAL_GPIO_WritePin(led_gpio, led_b_gpio_pin, 0x00);  // turn blue LED Off
                            while(HAL_GPIO_ReadPin(button_2_gpio, button_2_gpio_pin)); // Wait for button 2 release
                        }
                    }
                }
                // Start Game
                if (HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin))  {   // Check for button 6 press 
                        // Generate random seed based on how long button 6 was pressed
                        srand(HAL_GetTick());
                        chosen_category = -1;

                        display_categories_page();

                        while (HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin));  // wait for button 6 release

                        // Wait for user to choose category
                        while(true) {
                            // Go back if they presses button 5 or 6
                            if (HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin) || HAL_GPIO_ReadPin(button_5_gpio, button_5_gpio_pin))  {   // Check for button 5 or 6 press 
                                while (HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin) || HAL_GPIO_ReadPin(button_5_gpio, button_5_gpio_pin));  // wait for button 5 or 6 release
                                restart = true;
                                break;
                            }

                            // Video Games Category
                            if (HAL_GPIO_ReadPin(button_4_gpio, button_4_gpio_pin))  {   // check for button 4 press 
                                while (HAL_GPIO_ReadPin(button_4_gpio, button_4_gpio_pin));  // wait for button 4 release
                                chosen_category = 2;
                            }

                            // Film Category
                            if (HAL_GPIO_ReadPin(button_3_gpio, button_3_gpio_pin))  {   // check for button 3 press 
                                while (HAL_GPIO_ReadPin(button_3_gpio, button_3_gpio_pin));  // wait for button 3 release
                                chosen_category = 1;
                            }

                            // Computer Category
                            if (HAL_GPIO_ReadPin(button_2_gpio, button_2_gpio_pin))  {   // check for button 2 press 
                                while (HAL_GPIO_ReadPin(button_2_gpio, button_2_gpio_pin));  // wait for button 2 release
                                chosen_category = 0;
                            }

                            // Random Category
                            if (HAL_GPIO_ReadPin(button_1_gpio, button_1_gpio_pin))  {   // check for button 1 press 
                                while (HAL_GPIO_ReadPin(button_1_gpio, button_1_gpio_pin));  // wait for button 1 release
                                chosen_category = 3;
                            }

                            // Break put of loop if category is chosen
                            if (chosen_category != -1) {
                                break;
                            }
                        }

                        // Return to main menu
                        if (restart) {
                            break;
                        }

                        // Generates random questions (based on category choice) and stores them in the rand_questions array
                        if (chosen_category == 3) {
                            generate_random_questions(rand_questions, num_questions);
                        } else {
                            generate_random_questions_with_category(rand_questions, num_questions, chosen_category);
                        }

                        // If rand_questions is not null
                        if(rand_questions) {
                            // Loop through all the questions
                            for (int i = 0; i < num_questions; ++i) {

                                // Start off 10 second timer with displaying 9
                                Display7Segment(9);

                                // Decipher and display the question

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

                                max_pages = get_num_pages(text_question);
                                display_question(text_question, 1);

                                // While time has not run out
                                while(timer > 0) {
                                    // Go back to main menu
                                    if (HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin))  {   // check for button 6 press 
                                        int counter = 0;
                                        // While button 6 is being held or if it is held for a second
                                        while (counter <= 1000 && HAL_GPIO_ReadPin(button_6_gpio, button_6_gpio_pin)) {  // wait for button 6 release
                                            counter++;
                                            HAL_Delay(1);
                                        }
                                        
                                        // Since the timer is not running inside the previous loop, subtract from timer the
                                        // nmumber of milliseconds that the user held button 6 for
                                        timer -= counter;

                                        // If the user held button 6 for a second, then return to main menu
                                        // Else, go to the next page (or first page if already on last page)
                                        if (counter >= 1000) {
                                            restart = true;
                                            break;
                                        } else {
                                            page++;
                                            if (page > max_pages) {
                                                page = 1;
                                            }
                                            display_question(text_question, page);
                                        }
                                    }

                                    // Remove two answers for hint
                                    if (HAL_GPIO_ReadPin(button_5_gpio, button_5_gpio_pin))  {   // check for button 5 press 
                                        int counter = 0;
                                        // While button 5 is being held or if it is held for a second
                                        while (counter <= 1000 && HAL_GPIO_ReadPin(button_5_gpio, button_5_gpio_pin)) {  // wait for button  5release
                                            counter++;
                                            HAL_Delay(1);
                                        }

                                        timer -= counter;
                                        
                                        // If button 5 was held for a second and the user has not already used a 
                                        // hint for this question then remove two answers
                                        // Else go back a page (If the user is on the first page, then go to the last page)
                                        if(counter >= 1000 && !hint_used) {
                                            int first_number = get_random_number(3) + 1;
                                            // If Debug Mode is activated, then display only the correct answer
                                            if(debug_mode) {
                                                answers = 1555;
                                            } else if (first_number == 1) {
                                                // Generates number in format of 1#55 where # is a random number from 2-4
                                                answers = ((10 + (get_random_number(2) + 2)) * 100) + 55;
                                            } else {
                                                // Generates number in format of #155 where # is a random number from 2-4
                                                answers = (((first_number * 10) + 1) * 100) + 55;
                                            }

                                            // Update the question and display the first page
                                            sprintf(text_question, "%i - %s > 1. %s | 2. %s | 3. %s | 4. %s", (i+1), get_question(category, question),  get_answer(category, question, decipher_answer(answers, 1)), get_answer(category, question, decipher_answer(answers, 2)),get_answer(category, question, decipher_answer(answers, 3)),get_answer(category, question, decipher_answer(answers, 4)));
                                            encrypt_text(text_question);

                                            hint_used = true;

                                            display_question(text_question, 1);
                                            page = 1;
                                        } else {
                                            page--;
                                            if(page <= 0) {
                                                page = max_pages;
                                            }
                                            display_question(text_question, page);
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

                                    // If the timer has gone down a second (1000 milliseconds), then update the 7 segment
                                    // display
                                    if(timer <= next_timer_limit) {
                                        next_timer_limit -= 1000;
                                        Display7Segment(timer / 1000);
                                    }
                                    timer--;
                                    HAL_Delay(1);
                                }

                                // Go back to main menu
                                if(restart) {
                                    break;
                                }

                                char status[200];

                                Display7Segment(-1);

                                // If the user selected the correct answer. Then increase points by 1 and display a 
                                // correct answer message with their score and a green LED light for 3 seconds
                                // Else if the user selected a wrong answer or time ran out. Then display a wrong 
                                // answer/time out message with their score and a red LED light for 3 seconds
                                if (chosen_answer == decipher_correct_answer(answers)) {
                                    points++;

                                    sprintf(status, "Correct!|Your score is %i/%i", points, num_questions);
                                    display_status_page(status);

                                    int counter = 0;

                                    HAL_GPIO_WritePin(led_gpio, led_g_gpio_pin, 0x04);  // LED set to green color

                                    // Wait 3 seconds
                                    while (counter < 3) {
                                        counter++;
                                        HAL_Delay(1000);
                                    }

                                    HAL_GPIO_WritePin(led_gpio, led_g_gpio_pin, 0 & 0x02); // LED set to no color
                                } else {
                                    // If time ran out
                                    // Else if answer was wrong
                                    if (timer <= 0) {
                                        sprintf(status, "Time Out!|Your score is %i/%i", points, num_questions);
                                        display_status_page(status);
                                    } else {
                                        sprintf(status, "Wrong!|Your score is %i/%i", points, num_questions);
                                        display_status_page(status);
                                    }

                                    // Activate RED light LED and wait 3 seconds
                                    int counter = 0;
                                    HAL_GPIO_WritePin(led_gpio, led_r_gpio_pin, 0x04); // LED set to red color
                                    while (counter < 3) {
                                        counter++;
                                        HAL_Delay(1000);
                                    }
                                    HAL_GPIO_WritePin(led_gpio, led_r_gpio_pin, 0 & 0x04); // LED set to no color
                                }
                            }


                            // At this point, we have exited the for loop. If restart is false, it means that the for
                            // loop exited not because the user opted to restart the game, but because the user reached
                            // the end of the game
                            if(!restart) {

                                char points_buff[100];
                                restart = true;

                                // If the user answered all the questions correctly. Then display a game won message
                                // and flash random colors from the LED light
                                // Else if even one question was answered incorrectly, then display a game lost
                                // message and flash a blinking red light from the LED light
                                if(points == num_questions) {

                                    sprintf(points_buff, "Game Over!|Your score is %i/%i|Congrats, You Won!|Thanks for playing!", points, num_questions);
                                    display_status_page(points_buff);

                                    int counter = 0;

                                    // Don't even know what colors this specifically flashes. I just wanted random shiny
                                    // colors haha!
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
                                    while(counter < 30) {
                                        HAL_GPIO_WritePin(led_gpio, led_r_gpio_pin, counter & 0x04);  // red   (hex 4 == 0100 binary)
                                        counter++;
                                        HAL_Delay(100);
                                    }
                                    HAL_GPIO_WritePin(led_gpio, led_r_gpio_pin, 0 & 0x00); // LED set to no color
                                }
                            } 
                        }
                } 
                // Help Page
                else if (HAL_GPIO_ReadPin(button_5_gpio, button_5_gpio_pin))  {   // check for button 5 press 
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
    return 0;
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}
