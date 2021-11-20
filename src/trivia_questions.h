#ifndef TRIVIA_QUESTIONS_H
#define TRIVIA_QUESTIONS_H

int num_of_categories;
int questions_per_category;

char * questions[][10][5];

char * get_questions();
void print_question(int category, int index, int answers);
void print_main_menu();
void print_help_page();
void print_categories_page();
void print_error_page();
void print_status_page(char * status);
char * get_val(int category, int index, int val);
char * get_question(int category, int index);
char * get_answer(int category, int index, int ans);
int get_random_question();
void generate_random_questions(int * rand_questions, int num_questions);
void generaet_random_questions_with_category(int * rand_questions, int num_questions, int category);
int get_random_question_with_category(int category);
int get_random_number(int to);
int get_shuffled_answers();
char * get_correct_answer(int category, int index);
char * get_wrong_answers(int category, int index);
char * get_answers(int category, int index);
char * parse_question(int category, int index);
char * get_substring(char * str, int from, int to);
int get_size(char * arr);
int decipher_category(int question);
int decipher_question(int question);
int decipher_correct_answer(int answers);
int decipher_answer(int answers, int ans);


#endif