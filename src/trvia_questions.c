#include "trivia_questions.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "ece198.h"
#include "LiquidCrystal.h"



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

int get_num_rows(char * text) {
    int row_num = 1;
    for(int i = 0; i < strlen(text); ++i) {
        if (text[i] == '|' || text[i] == '>') {
            ++row_num;
        }
    }
    return row_num;
}

int get_num_pages(char * text) {
    int pages_num = 1;
    for(int i = 0; i < strlen(text); ++i) {
        if(text[i] == '>') {
            ++pages_num;
        }
    }
    return pages_num;
}

char * get_questions() {
    return questions;
}

char * get_val(int category, int index, int val) {
    char * empty = "";
    if(val == 5) {
        return empty;
    }
    return questions[category][index][val];
}

char * get_question(int category, int index) {
    return get_val(category, index, 0);
}

char * get_answer(int category, int index, int ans) {
    if (ans >= 1 && ans <= 4) {
        return get_val(category, index, ans);
    }
    return "";
}

int get_random_question() {
    int rand_category = get_random_number(num_of_categories);
    int rand_question = get_random_number(questions_per_category);
    return (rand_question * 10) + rand_category;
}

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

int get_random_question_with_category(int category) {
    return (get_random_number(10) * 10) + category;
}

int decipher_category(int question) {
    return question % 10;
}

int decipher_question(int question) {
    return question / 10;
}

int decipher_correct_answer(int answers) {
    for (int i = 3; i >= 0; i--) {
        if (answers % 10 == 1) {
            return i;
        }
        answers /= 10;
    }
    return 0;
}

int decipher_answer(int answers, int ans) {
    for (int i = 4; i > 0; i--) {
        if (ans == i) {
            return answers % 10;
        }
        answers /= 10;
    }
    return 1;
}

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

char * get_correct_answer(int category, int index) {
    return questions[category][index][1];
}

int get_size_1(char * arr[]) {
    int size = 0;
    while(1) {
        if (arr[size]) {
            size++;
        } else {
            return size;
        }
    }
    return 0;
}
