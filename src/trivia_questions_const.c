#include "trivia_questions.h"

int num_of_categories = 3;
int questions_per_category = 10;

char * questions[][10][5] = {
    // Computer Category
    {
        {
            "What does GHz stand for?",
            "Gigahertz",
            "Gigahotz",
            "Gagahetz",
            "Gigahatz"
        },
        {
            "The computer OEM manufacturer Clevo, known for its Sager notebook line, is based in which country?",
            "Taiwan",
            "United States",
            "Germany",
            "China"
        },
        {     
            "How many cores does the Intel i7-6950X have?",
            "10",
            "12",
            "8",
            "4"
        },
        {
            "Which of these names was an actual codename for a cancelled Microsoft project?",
            "Neptune",
            "Enceladus",
            "Pollux",
            "Saturn"
        },
        {
            "In the programming language 'Python', which of these statements would display the string 'Hello World' correctly?",
            "print(\"Hello World\")",
            "console.log(\"Hello World\")",
            "echo \"Hello World\"",
            "printf(\"Hello World\")"
        },
        {
            "What does 'LCD' stand for?",
            "Liquid Crystal Display",
            "Language Control Desgin",
            "Last Common Difference",
            "Long Continuous Design"
        },
        {
            "What does the International System of Quantities refer 1024 bytes as?",
            "Kibibyrte",
            "Kylobyte",
            "Kilobyte",
            "Kelobyte"
        },
        {
            "What is the name given to layer 4 of the Open Systems Interconnection (ISO) model?",
            "Transport",
            "Session",
            "Data Link",
            "Network"
        },
        {
            "The acronym 'RIP' stands for which of these?",
            "Routing Information Protocol",
            "Runtime Instance Processes",
            "Regular Interval Processes",
            "Routine Inspection Protocol"
        },
        {
            "How many bits make up the significand portion of a single precision floating point number?",
            "23",
            "8",
            "53",
            "15"
        }
    },
    // Film Category
    {
        {
            "Daniel Radcliffe became a global star in the film industry due to his performance in which film franchise?",
            "Harry Potter",
            "Ted",
            "Spy Kids",
            "Pirates of the Caribbean"
        },
        {
            "What is the name of the dog that played Toto in the 1939 film \"The Wizard of Oz\"?",
            "Terry",
            "Tommy",
            "Teddy",
            "Toto"
        },
        {
            "What is the name of the Artificial Intelligence system in the 1983 film, \"WarGames\"",
            "War Operation Plan Response",
            "Self Evolving Thought Helix",
            "Master Control Program",
            "West Campus Analog Computer"
        },
        {
            "In the 1971 film \"Willy Wonka & the Chocolate Factory\", who played Willy Wonka?",
            "Gene Wilder",
            "Shia LeBouf",
            "Peter Ostrum",
            "Johmmy Depp"
        },
        {
            "The 2002 film \"28 Days Later\" is mainly set in which European country?",
            "United Kingdom",
            "France",
            "Italy",
            "Germany"
        },
        {
            "In the movie \"Spaceballs\", what are the Spaceballs attempting to steal from Planet Druidia?",
            "Air",
            "The Schwartz",
            "Princess Lonester",
            "Meatballs"
        },
        {
            "Which animated film did Steven Lisberger direct in 1980 before going on to direct Tron",
            "Animalympics",
            "The Fox and the Hound",
            "The Black Cauldron",
            "The Great Mouse Detecive"
        },
        {
            "In the 1995 film \"Balto\", who are Steele's accomplices?",
            "Kaltag, Nikki, and Star",
            "Dusty, Kirby, and Ralph",
            "Nuk, Yak, and Sumac",
            "Jenna, Sylvie, and Dixie"
        },
        {
            "What is Lilo's last name from Lilo and Stitch?",
            "Pelekai",
            "Anoa'i",
            "Kealoha",
            "Ku'ulei"
        },
        {
            "In the movie \"V for Vendetta\", what is the date that masked vigilante \"V\" urges people to remember?",
            "November 5th",
            "November 6th",
            "November 4th",
            "September 5th"
        }
    },
    {
        // Video Games Category
        {
            "Who is the protagonist in the game \"The Walking Dead: Season One\"?",
            "Lee Everett",
            "Clementine",
            "Kenny",
            "Rick Grimes"
        },
        {
            "What is the name of the final boss in Turok: Dinosaur Hunter?",
            "The Campaigner",
            "The Primagen",
            "Oblivian",
            "Lord Tyrannus"
        },
        {
            "\"Tomb Raider\" icon Lara Croft was originally called...",
            "Laura Cruz",
            "Laura Craft",
            "Laura Croft",
            "Lara Craft"
        },
        {
            "Which souls game was not directed by Hidetaka Miyazaki?",
            "Dark Souls 2",
            "Demon Souls",
            "Dark Souls",
            "Dark Souls 3"
        },
        {
            "TF2: What code does Soldier put into the door keypad in \"Meet the Spy\"?",
            "1111",
            "1432",
            "1337",
            "No code"
        },
        {
            "What type of genre is the controversial 2015 game \"Hatred\"?",
            "Shoot 'Em Up",
            "Point & Click",
            "MMORPG",
            "Simulation"
        },
        {
            "Who is the leader of Team Instinct in Pokemon Go?",
            "Spark",
            "Candela",
            "Blanche",
            "Willow"
        },
        {
            "In Halo 2, how many rounds does the M6C hold in a single magazine?",
            "12",
            "6",
            "36",
            "12"
        },
        {
            "What are the names of the Ice Climbers in the video game Ice Climber?",
            "Popo and Nana",
            "Popo and Nina",
            "Papi and Nana",
            "Papi and Nina"
        },
        {
            "Who is Sora's Nobody in Kingdom Hearts?",
            "Roxas",
            "Riku",
            "Kairi",
            "Mickey"
        }
    }
};