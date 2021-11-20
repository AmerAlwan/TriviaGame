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

int main(void)
{
    HAL_Init(); // initialize the Hardware Abstraction Layer
    srand(time(0));

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

    InitializePin(GPIOA, GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // Button 6 - Start/Exit
    InitializePin(GPIOA, GPIO_PIN_1, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // Button 5 - Help/Hint
    InitializePin(GPIOA, GPIO_PIN_4, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // Button 4 - Answer 4
    InitializePin(GPIOB, GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // Button 3 - Answer 3
    InitializePin(GPIOC, GPIO_PIN_1, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // Button 2 - Answer 2
    InitializePin(GPIOC, GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // Button 1 - Answer 1
    InitializePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // initialize color LED output pins
    
    int num_questions = 1;
    int timer_limit = 5000;
    int rand_questions[num_questions];
    int chosen_category;
    int category;
    int question;
    int answers;
    int points;
    bool restart;
    while (true) {

        restart = false;
        points = 0;

        print_main_menu();

        while(!restart) {
                // Start Game
                if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))  {   // Check for start button 6 press 
                    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));  // wait for button 6 release
                        print_categories_page();
                        chosen_category = -1;
                        // Wait for user to choose category
                        while(true) {
                            // Go back if they press button 6
                            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))  {   // check for button 6 press 
                                while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));  // wait for button 6 release
                                SerialPuts("\nRestart");
                                restart = true;
                                break;
                            }
                            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))  {   // check for button 4 press 
                                while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4));  // wait for button 4 release
                                chosen_category = 2;
                            }
                            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))  {   // check for button 3 press 
                                while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0));  // wait for button 3 release
                                chosen_category = 1;
                            }
                            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))  {   // check for button 2 press 
                                while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1));  // wait for button 2 release
                                chosen_category = 0;
                            }
                            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0))  {   // check for button 1 press 
                                while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0));  // wait for button 1 release
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
                                int chosen_answer = -1;
                                int timer = timer_limit;
                                char timer_buff[100];

                                category = decipher_category(rand_questions[i]);
                                question = decipher_question(rand_questions[i]);
                                answers = get_shuffled_answers();
                                print_question(category, question, answers);

                                char points_buff[100];
                                sprintf(points_buff, "\nCurrent Points: %i/%i\n", points, num_questions);
                                SerialPuts(points_buff);

                                while(timer > 0) {
                                    // Go back to main menu
                                    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))  {   // check for button 6 press 
                                        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));  // wait for button 6 release
                                        restart = true;
                                        break;
                                    }
                                    // Wait for buttons 1-4 press for selecting answer

                                    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))  {   // check for button 4 press 
                                        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4));  // wait for button 4 release
                                        chosen_answer = 3;
                                    }
                                    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))  {   // check for button 3 press 
                                        while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0));  // wait for button 3 release
                                        chosen_answer = 2;
                                    }
                                    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))  {   // check for button 2 press 
                                        while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1));  // wait for button 2 release
                                        chosen_answer = 1;
                                    }
                                    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0))  {   // check for button 1 press 
                                        while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0));  // wait for button 1 release
                                        chosen_answer = 0;
                                    }

                                    if (chosen_answer != -1) {
                                        break;
                                    }

                                    if(timer % 1000 == 0) {
                                        sprintf(timer_buff, "\rTime Left: %is", timer / 1000);
                                        SerialPuts(timer_buff);
                                    }
                                    timer--;
                                    HAL_Delay(1);
                                }

                                if(restart) {break;}
                                char buffs[100];
                                sprintf(buffs, "\n\nChosen Answer: %i, Correct Answer: %i, Answers: %i", chosen_answer, decipher_correct_answer(answers), answers);
                                SerialPuts(buffs);
                                if (chosen_answer == decipher_correct_answer(answers)) {
                                    print_status_page("Correct");
                                    int counter = 0;
                                    points++;
                                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0x04);  // LED set to green color
                                    while (counter < 3) {
                                        counter++;
                                        HAL_Delay(1000);
                                    }
                                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0x00); // LED set to no color
                                } else {
                                    if (timer == 0) {
                                        print_status_page("Time Out!");
                                    } else {
                                        print_status_page("Wrong!");
                                    }
                                    int counter = 0;
                                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0x02); // LED set to red color
                                    while (counter < 3) {
                                        counter++;
                                        HAL_Delay(1000);
                                    }
                                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0x00); // LED set to no color
                                }
                            }



                            if(!restart) {
                                char points_buff[100];
                                sprintf(points_buff, "\n\nGame Over!\nYour score is %i/%i", points, num_questions);
                                SerialPuts(points_buff);
                                restart = true;
                                if(points == num_questions) {
                                    print_status_page("You Won!");
                                    int counter = 0;
                                    while(counter < 30) {
                                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, counter & 0x01);  // blue  (hex 1 == 0001 binary)
                                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, counter & 0x04);  // green (hex 2 == 0010 binary)
                                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, counter & 0x02);  // red   (hex 4 == 0100 binary)
                                        counter++;
                                        HAL_Delay(100);
                                    }

                                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0x00); // LED set to no color
                                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0x00); // LED set to no color
                                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0x00); // LED set to no color
                                } else {
                                    print_status_page("You Lost!");
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
                else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1))  {   // check for button 5 press 
                    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1));  // wait for button 5 release
                    print_help_page();
                    while(1) {
                    // Back to main menu
                        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) || HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1))  {   // check for button 5 or 6 press 
                            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) || HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1));  // wait for button 5 or 6 release
                            restart = true;
                            break;
                        }
                    }
                }
            }
        
        //  get_random_questions_with_category(rand_questions, num_questions, 1);
          
        //     for(int i = 0; i < num_questions; i++) {
        //         category = decipher_category(rand_questions[i]);
        //         question = decipher_question(rand_questions[i]);
        //         answers = get_shuffled_answers();    
        //         print_question(category, question, answers);    
        //     }   
       

         if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))  {   // check for button 6 press 
            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));  // wait for button 6 release
           
         }

         if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1))  {   // check for button 5 press 
            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1));  // wait for button 5 release
            SerialPuts("\nButton 5 - Help/Hint");
         }
         if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))  {   // check for button 4 press 
            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4));  // wait for button 4 release
            SerialPuts("\nButton 4 - Answer 4");
         }
         if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))  {   // check for button 3 press 
            while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0));  // wait for button 3 release
            SerialPuts("\nButton 3 - Answer 3");
         }
         if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))  {   // check for button 2 press 
            while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1));  // wait for button 2 release
            SerialPuts("\nButton 2 - Answer 2");
         }
         if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0))  {   // check for button 1 press 
            while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0));  // wait for button 1 release
            SerialPuts("\nButton 1 - Answer 1");
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
