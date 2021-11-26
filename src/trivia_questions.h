#ifndef TRIVIA_QUESTIONS_H
#define TRIVIA_QUESTIONS_H

int num_of_categories;
int questions_per_category;
int max_col;
int max_row;

char * questions[][20][5];

void display_main_menu();
void display_help_page();
void display_categories_page();
void display_status_page(char * status);
void display_text(char * text, int page);
void display_question(char * question, int page);
void display_answers(char * answer, int page);

void encrypt_text(char * text);
int get_num_words(char * text);
void get_word_lengths(char * text, int * word_lengths);
int get_num_rows(char * text);
int get_num_pages(char * text);
void display_text(char * text, int page);

char * get_val(int category, int index, int val);
char * get_question(int category, int index);
char * get_answer(int category, int index, int ans);
void generate_random_questions(int * rand_questions, int num_questions);
void generaet_random_questions_with_category(int * rand_questions, int num_questions, int category);
int get_random_number(int to);
int get_shuffled_answers();
int decipher_category(int question);
int decipher_question(int question);
int decipher_correct_answer(int answers);
int decipher_answer(int answers, int ans);


#endif