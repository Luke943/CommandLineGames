#include <string>
#include <vector>

// Prints initial message
void greet();

// Prints result of the game
void end_game(std::string answer, std::string codeword);

// Prints current status of the game
void display_status(std::vector<char> incorrect, std::string answer);

// Asks if player wants another round
bool play_again();

// Prints ASCII art spaceship
void display_misses(int misses);

// Reads words from file
std::vector<std::string> read_words(const std::string filename);
