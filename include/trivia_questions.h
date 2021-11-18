#ifndef TRIVIA_QUESTIONS_H
#define TRIVIA_QUESTIONS_H

extern const char * questions[][10][4] = {
    {
        {"What does GHz stand for?"},
        {"Gigahertz"},
        {"Gigahotz"},
        {"Gagahetz"},
        {"Gigahatz"}
    },
    {
        {"The computer OEM manufacturer Clevo, known for its Sager notebook line, is based in which country?"},
        {"Taiwan"},
        {"United States"},
        {"Germany"},
        {"China"}
    },
    {        
        {"How many cores does the Intel i7-6950X have?"},
        {"10"},
        {"12"},
        {"8"},
        {"4"}
    },
    {
        {"Which of these names was an actual codename for a cancelled Microsoft project?"},
        {"Neptune"},
        {"Enceladus"},
        {"Pollux"},
        {"Saturn"}
    },
    {
        {"In the programming language 'Python', which of these statements would display the string 'Hello World' correctly?"},
        {"print(\"Hello World\")"},
        {"console.log(\"Hello World\")"},
        {"echo \"Hello World\""},
        {"printf(\"Hello World\")"}
    },
    {
        {"What does 'LCD' stand for?"},
        {"Liquid Crystal Display"},
        {"Language Control Desgin"},
        {"Last Common Difference"},
        {"Long Continuous Design"}
    },
    {
        {"What does the International System of Quantities refer 1024 bytes as?"},
        {"Kibibyrte"},
        {"Kylobyte"},
        {"Kilobyte"},
        {"Kelobyte"}
    },
    {
        {"What is the name given to layer 4 of the Open Systems Interconnection (ISO) model?"},
        {"Transport"},
        {"Session"},
        {"Data Link"},
        {"Network"}
    },
    {
        {"The acronym 'RIP' stands for which of these?"},
        {"Routing Information Protocol"},
        {"Runtime Instance Processes"},
        {"Regular Interval Processes"},
        {"Routine Inspection Protocol"}
    },
    {
        {"How many bits make up the significand portion of a single precision floating point number?"},
        {"23"},
        {"8"},
        {"53"},
        {"15"}
    }
};

char * get_question(int category, int index);
char * get_random_question();
char * get_random_question_with_category(int category);
int get_random_number(int to);
char * get_correct_answer(int category, int index);
char * get_wrong_answers(int category, int index);
char * get_answers(int category, int index);
char * parse_question(int category, int index);
char * get_substring(char * str, int from, int to);
int get_size(char * arr);


#endif