#include "trivia_questions.h"

int num_of_categories = 3;
int questions_per_category = 20;
int max_col = 20;
int max_row = 4;

char * questions[][20][5] = {
    // Computer Category
    {
        {
            "According to the International System of Units, how many bytes are in a kilobyte of RAM?",
            "1000",
            "512",
            "1024",
            "500"
        },
        {
            "The programming language 'Swift' was created to replace what other programming language?",
            "Objective-C",
            "C#",
            "Ruby",
            "C++"
        },
        {
            "Nvidia's headquarters are based in which Silicon Valley city?",
            "Santa Clara",
            "Palo Alto",
            "Cupertino",
            "Mountain View"
        },
        {
            "What did the name of the Tor Anonymity Network orignially stand for?",
            "The Onion Router",
            "The Only Router",
            "The Orange Router",
            "The Ominous Router"
        },
        {
            "On Twitter, what was the original character limit for a Tweet?",
            "140",
            "120",
            "160",
            "100"
        },
        {
            "When did the online streaming service \"Mixer\" launch?",
            "2016",
            "2013",
            "2009",
            "2011"
        },
        {
            "What vulnerability ranked #1 on the OWASP Top 10 in 2013?",
            "Injection",
            "Broken Authentication",
            "Cross-Site Scripting",
            "Insecure Direct Object References"
        },
        {
            "Unix Time is defined as the number of seconds that have elapsed since when?",
            "Midnight, January 1, 1970",
            "Midnight, July 4, 1976",
            "Midnight on the creator of Unix's birthday",
            "Midnight, July 4, 1980"
        },
        {
            "Which of these Cherry MX mechanical keyboard switches is both tactile and clicky?",
            "Cherry MX Blue",
            "Cherry MX Black",
            "Cherry MX Red",
            "Cherry MX Brown"
        },
        {
            "The series of the Intel HD graphics generation succeeding that of the 5000 and 6000 series (Broadwell) is called:",
            "HD Graphics 500",
            "HD Graphics 700",
            "HD Graphics 600",
            "HD Graphics 7000"
        },
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
            "Language Control Design",
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
            "How many bits make up the significant portion of a single precision floating point number?",
            "23",
            "8",
            "53",
            "15"
        }
    },
    // Film Category
    {
        {
            "This movie contains the quote, \"Nobody puts Baby in a corner.\"",
            "Dirty Dancing",
            "Three Men and a Baby",
            "Ferris Bueller's Day Off",
            "PRetty in Pink"
        },
        {
            "This movie contains the quote, \"What we've got here is a failure to communicate\"",
            "Cool Hand Luke",
            "Bonnie and Clyde",
            "The Graduate",
            "In the Heat of the Night"
        },
        {
            "What was the name of the planet in \"Aliens\"?",
            "LV-426",
            "Weyland Yitani Corporation Base",
            "FR-838",
            "DI-621"
        },
        {
            "Who plays the Nemesis in the Resident Evil movies?",
            "Matthew Taylor",
            "Jason Dip",
            "Eric Mabius",
            "Jimmy Matts"
        },
        {
            "This trope refers to minor characters that are killed off to show how a monster works.",
            "Red Shirt",
            "Minions",
            "Expendables",
            "Cannon Fodder"
        },
        {
            "What year did the James Cameron film \"Titanic\" come out in theaters?",
            "1997",
            "1996",
            "1998",
            "1999"
        },
        {
            "What was Bruce Campbell's iconic one-liner after getting a chainsaw hand in Evil Dead 2?",
            "Groovy",
            "Gnarly",
            "Perfect",
            "Nice"
        },
        {
            "Ed Koch, the Mayor of New York in 1984, played himself in which Muppets movie?",
            "The Muppets Take Manhattan",
            "The Great Muppet Caper",
            "The Muppet Christmas Carol",
            "The Mupper Movie"
        },
        {
            "In the 2014 film \"Birdman\", what is the primary instrument in the score?",
            "Drums",
            "Saxophone",
            "Violin",
            "Actual Live Birds Singing"
        },
        {
            "What is the birth name of Michael Caine?",
            "Maurice Micklewhite",
            "Morris Coleman",
            "Carl Myers",
            "Martin Michaels"
        },
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
            "When was the original Star Wars: Battlefront II released?",
            "October 31, 2005",
            "December 18, 2004",
            "November 21, 2006",
            "September 9, 2007"
        },
        {
            "Who is the villain company in \"Stardew Valley\"?",
            "Joja Co",
            "Ronin",
            "Empire",
            "Robotnik Industry's"
        },
        {
            "Which student in Yandere Simulator is known for asking irritating and stupid questions?",
            "Midori Gurin",
            "Kokona Hruka",
            "Oka Ruto",
            "Pipi Osu"
        },
        {
            "In Forza Motorsport 6, which of these track-exclusive cars was NOT featured in the game, either originally with the game or added as DLC?",
            "Aston Martin Vulcan",
            "Ferrari FXX-K",
            "McLaren P1 GTR",
            "Lotus E23"
        },
        {
            "Which one of the following actors did not voice a character in \"Saints Row: The Third\"?",
            "Ron Jeremy",
            "Sasha Grey",
            "Burt Reynolds",
            "Hulk Hogan"
        },
        {
            "Which of these Starbound races has a Wild West culture?",
            "Novakid",
            "Avian",
            "Human",
            "Hylotl"
        },
        {
            "What is the item required to summon the boss Duke Fishron in the game Terraria?",
            "Truffle Worm",
            "Suspicious Looking Fish",
            "King Grasshopper",
            "Slug"
        },
        {
            "Which town was Seamus \"Sledge\" Cowden from \"Tom Clancy's Rainbow Six Siege\" born in?",
            "John 'Groats",
            "Brawl",
            "Kearvaig",
            "Talmine"
        },
        {
            "In \"Resident Evil 2\", what is Leon Kennedy's middle name",
            "Scott",
            "Shaun",
            "Simon",
            "Sam"
        },
        {
            "In which game did the character \"Mario\" make his first appearance?",
            "Donkey Kong",
            "Super Mario Bros.",
            "Super Mario Land",
            "Mario Bros."
        },
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
            "15"
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