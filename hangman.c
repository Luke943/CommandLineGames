/* Command line hangman game.
 * Reads words from hangmanwords.txt.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LENGTH 32
#define MAX_COUNT 1000

int loadWords(const char *filename, char *words[MAX_COUNT]);
void printOutcome(int quit, int lives, char *word);
int playAgain(void);
void freeWords(char *array[MAX_COUNT]);

int main(void)
{
    srand(time(NULL));

    char *guessWords[MAX_COUNT];
    int wordCount = loadWords("hangmanwords.txt", guessWords);
    if (!wordCount)
    {
        printf("Failed to load words from hangmanwords.txt\n");
        return -1;
    }
    
    printf("Welcome to Hangman!\n");
    printf("Enter a letter to guess the word, or type 'quit' to quit.\n");
    int quit = 0;
    int play = 1;

    while (play && !quit)
    {
        int randomIndex = rand() % wordCount;
        int numLives = 5;
        int numCorrect = 0;
        int oldCorrect = 0;

        int lengthOfWord = strlen(guessWords[randomIndex]);
        int isLetterGuessed[MAX_LENGTH];
        for (int i = 0; i < MAX_LENGTH; i++)
        {
            isLetterGuessed[i] = 0;
        }

        char guess[MAX_LENGTH];
        char letterGuessed;

        // printf("guessWords: %s randomIndex: %d lengthofWord:%d\n", guessWords[randomIndex], randomIndex, lengthOfWord);

        while (numCorrect < lengthOfWord)
        {
            printf("\nNew turn...\nHangman word: ");
            for (int i = 0; i < lengthOfWord; i++)
            {
                if (isLetterGuessed[i] == 1)
                {
                    printf("%c", guessWords[randomIndex][i]);
                }
                else
                {
                    printf("-");
                }
            }
            printf("\n");
            if (numLives == 1)
            {
                printf("You have 1 life\n");
            }
            else
            {
                printf("You have %d lives\n", numLives);
            }

            printf("Guess a letter: ");
            fgets(guess, MAX_LENGTH, stdin);

            if (strncmp(guess, "quit", 4) == 0)
            {
                quit = 1;
                break;
            }

            letterGuessed = tolower(guess[0]);
            //printf("letterGuessed: %c\n", letterGuessed);

            for (int i = 0; i < lengthOfWord; i++)
            {
                if (isLetterGuessed[i] == 1)
                {
                    continue;
                }
                if (letterGuessed == guessWords[randomIndex][i])
                {
                    isLetterGuessed[i] = 1;
                    numCorrect++;
                }
            }

            if (oldCorrect == numCorrect)
            {
                numLives--;
                printf("Sorry, wrong guess!\n");
                if (numLives == 0)
                {
                    printf("\n");
                    break;
                }
            }
            else
            {
                printf("Correct guess!\n");
            }
            printf("\n");

            oldCorrect = numCorrect;
        }

        printOutcome(quit, numLives, guessWords[randomIndex]);
        
        if (!quit)
        {
            play = playAgain();
        }
    }
    
    printf("Goodbye.\n");
    freeWords(guessWords);
    return 0;
}

// Load words from file to memory
// Returns number of words loaded or 0 if words did not load
int loadWords(const char *filename, char *words[MAX_COUNT])
{
    int count = 0;
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        return 0;
    }
    char buffer[MAX_LENGTH];
    while (fscanf(file, "%s", buffer) != EOF && count < MAX_COUNT)
    {
        words[count] = malloc(sizeof(char) * (strlen(buffer) + 1));
        if (!words[count])
        {
            return 0;
        }
        strcpy(words[count], buffer);
        count++;
    }
    fclose(file);
    return count;
}

// Prints outcome of game
void printOutcome(int quit, int lives, char *word)
{
    if (quit == 1)
    {
        printf("The user quit early\n");
    }
    else if (lives == 0)
    {
        printf("You lose, the word was %s\n", word);
    }
    else
    {
        printf("Congratulations, you win!\nThe word was %s\n", word);
    }
}

// Start with new word?
int playAgain(void)
{
    int choice = 0;
    printf("Play again? (Y/N): ");
    while (1)
    {
        char buffer[MAX_LENGTH];
        fgets(buffer, MAX_LENGTH, stdin);
        char c = buffer[0];
        if (c == 'Y' || c == 'y')
        {
            choice = 1;
            break;
        }
        else if (c == 'N' || c == 'n')
        {
            choice = 0;
            break;
        }
        else
        {
            printf("Please type Y or N: ");
        }
    }
    return choice;
}

// Free memory allocated for words
void freeWords(char *array[MAX_COUNT])
{
    for (int i = 0; i < MAX_COUNT; i++)
    {
        free(array[i]);
    }
}
