#include "trivia_questions.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "ece198.h"

void print_question(int category, int index, int answers) {
    char buff[500];
    sprintf(buff, "\n\n%i.%i - %s\n1. %s \t2. %s \n3. %s \t4. %s", (category + 1), (index + 1), get_question(category, index), get_answer(category, index, decipher_answer(answers, 1)), get_answer(category, index, decipher_answer(answers, 2)), get_answer(category, index, decipher_answer(answers, 3)), get_answer(category, index, decipher_answer(answers, 4)));
    SerialPuts(buff); 
}

void print_main_menu(){
    SerialPuts("\n\n\tWho Wants to be a Millionaire?\n\t\tPlay\n\t\tHelp");
}

void print_help_page() {
    SerialPuts("\n\nButton 1-4: Answer\nButton 5: Play in Main Menu, Exit in Question Page\nButton 6: Help in Main Menu, Hint in Question page\nAnswer 15 questions correctly to win. Answer any question incorrectly and you lost!\nGood Luck!");
}

void print_categories_page(){
    SerialPuts("\n\nChooose a Category: \n1. Random\t2. Computer\n3. Film\t4. Video Games");
}

void print_error_page(char * error) {
    char buff[200];
    sprintf(buff, "\n\n%s", error);
    SerialPuts(buff);
}

void print_status_page(char * status) {
    char buff[200];
    sprintf(buff, "\n\n%s", status);
    SerialPuts(buff);
}

// char * get_questions() {
//     return questions;
// }

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

    // char buffs[100];
    // sprintf(buffs, "\n%i", answers);
    // SerialPuts(buffs);

    return answers; 

}

// char * get_shuffled_answers(int category, int index) {
//     char * answers[4];
//     int i = get_random_number(4);
//     answers[0] = questions[category][index][i];
//     if(i == 0) {
//         answers[1] = questions[category][index][1];
//         answers[2] = questions[category][index][2];
//         answers[3] = questions[category][index][3];
//     } else if(i == 1) {
//         answers[1] = questions[category][index][0];
//         answers[2] = questions[category][index][2];
//         answers[3] = questions[category][index][3];
//     } else if(i == 2) {
//         answers[1] = questions[category][index][0];
//         answers[2] = questions[category][index][1];
//         answers[3] = questions[category][index][3];
//     } else if(i == 3) {
//         answers[1] = questions[category][index][0];
//         answers[2] = questions[category][index][1];
//         answers[3] = questions[category][index][2];
//     }
//     return &answers[0];
// }

int get_random_number(int to) {
    return rand() % to;
}

char * get_correct_answer(int category, int index) {
    return questions[category][index][1];
}
// char * get_wrong_answers(int category, int index) {
//     char * answers[3] = {questions[category][index][2], questions[category][index][3], questions[category][index][4]};
//     return answers;
// }
// char * get_answers(int category, int index) {
//     char * answers[4] = {questions[category][index][1], questions[category][index][2], questions[category][index][3], questions[category][index][4]};
//     return answers;
// }

// char * get_answer(int category, int index, int ans) {
//     return questions[category][index][ans];
// }

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
