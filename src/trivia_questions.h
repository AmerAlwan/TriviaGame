#ifndef TRIVIA_QUESTIONS_H
#define TRIVIA_QUESTIONS_H

int num_of_categories;
int questions_per_category;

char * questions[][10][5];

char * get_questions();
//void print_question(char * question[]);
char * get_val(int category, int index, int val);
int get_random_question();
int get_random_question_with_category(int category);
int get_random_number(int to);
char * get_correct_answer(int category, int index);
char * get_wrong_answers(int category, int index);
char * get_answers(int category, int index);
char * parse_question(int category, int index);
char * get_substring(char * str, int from, int to);
int get_size(char * arr);
int decipher_category(int question);
int decipher_question(int question);


#endif