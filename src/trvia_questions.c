#include "trivia_questions.h"
#include <stdlib.h>
#include <stdio.h>
//#include "ece198.h"



// char * get_questions() {
//     return questions;
// }

char * get_val(int category, int index, int val) {
    return questions[category][index][val];
}
int get_random_question() {
    int rand_category = get_random_number(num_of_categories);
    int rand_question = get_random_number(questions_per_category);
    return (rand_question * 10) + rand_category;
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

char * get_answer(int category, int index, int ans) {
    return questions[category][index][ans];
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
