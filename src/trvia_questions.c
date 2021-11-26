#include "trivia_questions.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "ece198.h"
#include "LiquidCrystal.h"



/**
 * @brief Get the number of words in the inputted string
 * 
 * @param text the pointer to the char array (aka string)
 * @return int 
 */
int get_num_words(char * text) {
    int num_words = 0;
    bool isWord = true;
    for (int i = 0; i < strlen(text); i++) {
        if(text[i] == ' ') {
            isWord = true;
        } else if(isWord) {
            isWord = false;
            ++num_words;
        }
    }
    return num_words;
}

/**
 * @brief Calculate the length of each word in text and store the lengths in word_lengths
 * 
 * @param text the text of which the length of each words is to be calculated from
 * @param word_lengths the array in which the length of each word is to be stored respectively
 */
void get_word_lengths(char * text, int * word_lengths) {
    int curr_word_length = 0;
    int word_lengths_index = 0;
    for(int i = 0; i < strlen(text); i++) {
        if(text[i] == ' ' || i == strlen(text) - 1) {
            word_lengths[word_lengths_index] = curr_word_length;
            curr_word_length = 0;
            ++word_lengths_index;
        } else {
            ++curr_word_length;
        }
    }
}

/**
 * @brief Word Wrap function. Given a string, it 1. Calculates where words exceed the lcd screen's character limit and 
 * places a '|' to indicate moving to a new row and 2. Calculates when the total rows exceed the lcd screen's row limit 
 * and places a '>' to indicate moving to a new page
 * 
 * @param text the text to be encrypted 
 */
void encrypt_text(char * text) {
    int num_words = get_num_words(text);
    int word_lengths[num_words];
    get_word_lengths(text, word_lengths);
    int curr_sentence_length = 0;
    int index = 0;
    int curr_row = 0;

    for(int i = 0; i < num_words; ++i) {
        if (text[index] == '|') {
            ++curr_row;
            curr_sentence_length = 0;
        } else if (text[index] == '>') {
            curr_row = 0;
            curr_sentence_length = 0;
        } else if (curr_sentence_length + word_lengths[i] > max_col) {
            text[index - 1] = '|';
            ++curr_row;
            curr_sentence_length = 0;
        }
        if(curr_row == 4) {
            if(text[index] == '|') {
                text[index] = '>';
            } else {
                text[index - 1] = '>';
            }
            curr_row = 0;
        }
        curr_sentence_length += word_lengths[i] + 1;
        index += word_lengths[i] + 1;
    }
}

/**
 * @brief Gets the total number of rows that an inputted string text will require
 * 
 * @param text 
 * @return int 
 */
int get_num_rows(char * text) {
    int row_num = 1;
    for(int i = 0; i < strlen(text); ++i) {
        if (text[i] == '|' || text[i] == '>') {
            ++row_num;
        }
    }
    return row_num;
}

/**
 * @brief Gets the total number of pages that an inputted string text will require
 * 
 * @param text 
 * @return int 
 */
int get_num_pages(char * text) {
    int pages_num = 1;
    for(int i = 0; i < strlen(text); ++i) {
        if(text[i] == '>') {
            ++pages_num;
        }
    }
    return pages_num;
}

/**
 * @brief Get the value in the 3rd dimension of the questions 3D array
 * 
 * @param category the category index
 * @param index the question index within that category
 * @param val the value within the question --> 0 for the question itself, 1 for the correct answer, 2-4 for wrong answer
 * @return char* 
 */
char * get_val(int category, int index, int val) {
    char * empty = "";
    if(val == 5) {
        return empty;
    }
    return questions[category][index][val];
}

/**
 * @brief Get a question from the questions array
 * 
 * @param category the category index
 * @param index the question index within that category
 * @return char* 
 */
char * get_question(int category, int index) {
    return get_val(category, index, 0);
}

/**
 * @brief Get an answer to a question from the questions array
 * 
 * @param category the category index
 * @param index  the question index within that category
 * @param ans the index of the desired answer of that question
 * @return char* 
 */
char * get_answer(int category, int index, int ans) {
    if (ans >= 1 && ans <= 4) {
        return get_val(category, index, ans);
    }
    return "";
}

/**
 * @brief Get num_questions of random questions from the inputted category index and store them in rand_questions
 * 
 * @param rand_questions the pointer to the int array in which the random question indexes will be stored into
 * @param num_questions the number of questions to get
 * @param category the category of the questions to get
 */
void generate_random_questions_with_category(int * rand_questions, int num_questions, int category) {
    int cat_questions[questions_per_category];
    for (int i = 0; i < questions_per_category; i++) {
        cat_questions[i] = i;
    } 

    // Shuffle each category 10 times
    for (int n = 0; n < 10; n++) {
        // Fisher Yates algorithm to shuffle questions in category
        for (int q = questions_per_category - 1; q >= 0; q--) {
            int j = get_random_number(q + 1);
            int copy = cat_questions[q];
            cat_questions[q] = cat_questions[j];
            cat_questions[j] = copy;
        }
    }

    // Initialize questions
    for (int i = 0; i < num_questions; i++) {
        int rand_question = cat_questions[i];
        rand_questions[i] = (rand_question * 10) + category;
    }
}

/**
 * @brief Gets num_questions of random questions each from a random category
 * 
 * @param rand_questions the pointer to the int array in which the indexes of the questions will be stored into
 * @param num_questions the number of questions to get
 */
void generate_random_questions(int * rand_questions, int num_questions) {
    int category_index[num_of_categories];
    for (int i = 0; i < num_of_categories; i++) {
        category_index[i] = 0;
    }
    int cat_questions[questions_per_category];
    for (int i = 0; i < questions_per_category; i++) {
        cat_questions[i] = i;
    } 

    // Shuffle each category 10 times
    for (int n = 0; n < 10; n++) {
        // Fisher Yates algorithm to shuffle questions in category
        for (int q = questions_per_category - 1; q >= 0; q--) {
            int j = get_random_number(q + 1);
            int copy = cat_questions[q];
            cat_questions[q] = cat_questions[j];
            cat_questions[j] = copy;
        }
    }

    // Initialize questions
    for (int i = 0; i < num_questions; i++) {
        int cat = get_random_number(num_of_categories);
        while(category_index[cat] >= questions_per_category) {
            cat = get_random_number(num_of_categories);
        }
        int rand_question = cat_questions[category_index[cat]];
        category_index[cat]++;
        rand_questions[i] = (rand_question * 10) + cat;
    }
}

/**
 * @brief Get the category index from the inputted question indexes number
 * 
 * @param question ex: if question = 41, then the question index is 4, and the category index is 1, so 1 is returned
 * @return int 
 */
int decipher_category(int question) {
    return question % 10;
}

/**
 * @brief Get the question index from the inputted question indexes number
 * 
 * @param question ex: if question = 41, then the question index is 4, and the category index is 1, so 4 is returned
 * @return int 
 */
int decipher_question(int question) {
    return question / 10;
}

/**
 * @brief Get the index of the correct answer in an answers number
 * 
 * @param answers ex: if the answers number is 2314, the correct answer is 1, so the returned index is 2
 * @return int 
 */
int decipher_correct_answer(int answers) {
    for (int i = 3; i >= 0; i--) {
        if (answers % 10 == 1) {
            return i;
        }
        answers /= 10;
    }
    return 0;
}

/**
 * @brief Get the index of the inputted ans number from the inputted answers number
 * 
 * @param answers ex: if answers = 1234 and ans = 3, the index of 3 is 2, so the returned number is 2
 * @param ans 
 * @return int 
 */
int decipher_answer(int answers, int ans) {
    for (int i = 4; i > 0; i--) {
        if (ans == i) {
            return answers % 10;
        }
        answers /= 10;
    }
    return 1;
}

/**
 * @brief Returns a shuffled number containing the digits: 1, 2, 3, 4. Ex: 1234, 2341, 1324
 * 
 * @return int 
 */
int get_shuffled_answers() {
    int answers = 0;
    int ans[4] = {1,2,3,4};

    // Fisher Yates shuffling algorithm repeated 3 times
    for (int z = 0; z < 3; z++) {
        for (int i = 3; i >= 0; i--) {
            int j = get_random_number(i + 1);
            int copy = ans[i];
            ans[i] = ans[j];
            ans[j] = copy;
        }
    }

    for (int i = 0; i < 4; i++) {
        answers *= 10;
        answers += ans[i];
    }

    return answers; 

}

int get_random_number(int to) {
    return rand() % to;
}


