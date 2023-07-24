// Main file for UFO abduction game
// (Hangman clone with alien abduction)
// Reads words from hangmanwords.txt

#include <iostream>
#include <time.h>
#include "ufo_functions.hpp"

int main()
{
    srand(time(NULL));
    greet();
    std::vector<std::string> words = read_words("hangmanwords.txt");
    if (words.empty())
    {
        return 1;
    }
    bool play_game = true;

    while (play_game)
    {
        std::string codeword = words[rand() % words.size()];
        std::string answer(codeword.size(), '_');
        int misses = 0;
        std::vector<char> incorrect;
        bool guess = false;
        char letter;

        while (answer != codeword && misses < 7)
        {
            display_misses(misses);
            display_status(incorrect, answer);
            std::cout << "Please enter your guess: ";
            std::cin >> letter;
            letter = tolower(letter);

            for (int i = 0; i < codeword.size(); i++)
            {
                if (codeword[i] == letter)
                {
                    answer[i] = letter;
                    guess = true;
                }
            }

            if (guess)
            {
                std::cout << "Correct!\n";
            }
            else
            {
                std::cout << "Incorrect! The tractor beam pulls the person in further.\n";
                incorrect.push_back(letter);
                misses++;
            }
            guess = false;
        }

        end_game(answer, codeword);
        play_game = play_again();
    }

    std::cout << "Goodbye.\n";
}
