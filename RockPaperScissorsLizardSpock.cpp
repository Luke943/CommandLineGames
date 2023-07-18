// Rock, Paper, Scissors, Lizard, Spock
// Sheldon's variation of rock, paper, scissors in the Big Bang Theory
// https://youtu.be/iSHPVCBsnLw

#include <iostream>
#include <unordered_map>
#include <ctime>
#include <cstdlib>

int main()
{
    std::string names[6] = {"", "rock", "paper", "scissors", "lizard", "Spock"};

    std::unordered_map<int, std::string> outcomes = {
        {32, "Scissors cut paper"},
        {21, "Paper covers rock"},
        {14, "Rock crushes lizard"},
        {45, "Lizard poisons Spock"},
        {53, "Spock smashes scissors"},
        {34, "Scissors decapitate lizard"},
        {42, "Lizard eats paper"},
        {25, "Paper disproves Spock"},
        {51, "Spock vaporizes rock"},
        {13, "Rock crushes scissors"}};

    srand(std::time(NULL));
    int computer = rand() % 5 + 1;
    int user = 0;

    std::cout << "=====================================\n";
    std::cout << "Rock, Paper, Scissors, Lizard, Spock!\n";
    std::cout << "=====================================\n\n";

    std::cout << "Let's play rock, paper, scissors, lizard, Spock!\n";
    std::cout << "You can find Sheldon Cooper's explanation here: https://youtu.be/iSHPVCBsnLw\n\n";

    std::cout << "1) Rock\n2) Paper \n3) Scissors\n4) Lizard\n5) Spock\nShoot! ";
    std::cin >> user;
    std::cout << "Computer choses " << names[computer] << ".\n";

    bool isWin = outcomes.count(user * 10 + computer);
    bool isLoss = outcomes.count(computer * 10 + user);

    if (computer == user)
        std::cout << "It's a tie!\n";
    else if (isWin)
    {
        std::cout << outcomes[user * 10 + computer] << ".\n";
        std::cout << "You win!\n";
    }
    else if (isLoss)
    {
        std::cout << outcomes[computer * 10 + user] << ".\n";
        std::cout << "You lose!\n";
    }
    else
        std::cout << "Invalid input.\n";
}
