#include "trivia_questions.h"
#include <stdlib.h>

char * get_question(int category, int index) {
    return (char *)questions[category][index][0];
}
char * get_random_question() {
    int rand_category = (char *)questions[get_random_number(get_size((char *)questions))];
    return (char *)questions[rand_category][get_random_number(get_size((char *)questions[rand_category]) )][0];
}
char * get_random_question_with_category(int category) {
    return (char *)questions[category][get_random_number(get_size((char *)questions[category]))][0];
}

char * get_shuffled_answers(int category, int index) {
    char * answers[4];
    int i = get_random_number(4);
    answers[0] = (char *)questions[category][index][i];
    if(i == 0) {
        answers[1] = (char *)questions[category][index][1];
        answers[2] = (char *)questions[category][index][2];
        answers[3] = (char *)questions[category][index][3];
    } else if(i == 1) {
        answers[1] = (char *)questions[category][index][0];
        answers[2] = (char *)questions[category][index][2];
        answers[3] = (char *)questions[category][index][3];
    } else if(i == 2) {
        answers[1] = (char *)questions[category][index][0];
        answers[2] = (char *)questions[category][index][1];
        answers[3] = (char *)questions[category][index][3];
    } else if(i == 3) {
        answers[1] = (char *)questions[category][index][0];
        answers[2] = (char *)questions[category][index][1];
        answers[3] = (char *)questions[category][index][2];
    }
    return answers;
}

int get_random_number(int to) {
    return rand() % to;
}

char * get_correct_answer(int category, int index) {
    return (char *)questions[category][index][1];
}
char * get_wrong_answers(int category, int index) {
    char * answers[3] = {(char *)questions[category][index][2], (char *)questions[category][index][3], (char *)questions[category][index][4]};
    return answers;
}
char * get_answers(int category, int index) {
    char * answers[4] = {(char *)questions[category][index][1], (char *)questions[category][index][2], (char *)questions[category][index][3], (char *)questions[category][index][4]};
    return answers;
}

int get_size(char * arr) {
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