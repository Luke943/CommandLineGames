// Simple snake game
// Created by: Luke
// Created on: 2025

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#ifndef UNICODE
#define UNICODE
#endif // UNICODE
#ifndef _UNICODE
#define _UNICODE
#endif // _UNICODE

#include <Windows.h>

#define ARENA_WIDTH 20
#define ARENA_HEIGHT 20

const COORD LEFT = {-1, 0};
const COORD UP = {0, -1};
const COORD RIGHT = {1, 0};
const COORD DOWN = {0, 1};

typedef struct _SnakePart
{
    COORD position;
    struct _SnakePart *prev;
    struct _SnakePart *next;
} SnakePart;

typedef struct _Snake
{
    SnakePart *head;
    SnakePart *tail;
    COORD direction;
} Snake;

Snake *InitSnake();
void DelSnake(Snake *snake);

wchar_t *InitArena();
void UpdateArena(wchar_t *arena, Snake *snake, COORD food);
void DelArena(wchar_t *arena);

COORD RandomFood(Snake *snake);

int main()
{
    /////////////
    // Setup
    /////////////

    // Create game
    int arenaSize = ARENA_HEIGHT * ARENA_WIDTH;
    bool gameOver = false;
    int score = 0;
    srand(time(NULL));

    wchar_t *arena = InitArena();
    Snake *snake = InitSnake();

    COORD food = RandomFood(snake);
    UpdateArena(arena, snake, food);

    // Setup display
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);

    SMALL_RECT consoleRect = {0, 0, ARENA_WIDTH - 1, ARENA_HEIGHT};
    SetConsoleWindowInfo(hConsole, TRUE, &consoleRect);
    SetConsoleScreenBufferSize(hConsole, (COORD){ARENA_WIDTH, ARENA_HEIGHT + 1});

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    DWORD dwBytesWritten = 0;
    WriteConsoleOutputCharacter(hConsole, arena, arenaSize, (COORD){0, 0}, &dwBytesWritten);

    /////////////
    // Game Loop
    /////////////

    while (!gameOver)
    {
        // Get input
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            gameOver = true;
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000 && snake->direction.Y)
            snake->direction = LEFT;
        else if (GetAsyncKeyState(VK_UP) & 0x8000 && snake->direction.X)
            snake->direction = UP;
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && snake->direction.Y)
            snake->direction = RIGHT;
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && snake->direction.X)
            snake->direction = DOWN;

        // Update game state

        SnakePart *newHead = malloc(sizeof(SnakePart));
        newHead->position = (COORD){snake->head->position.X + snake->direction.X, snake->head->position.Y + snake->direction.Y};
        newHead->prev = NULL;
        newHead->next = snake->head;
        snake->head->prev = newHead;
        snake->head = newHead;

        if (snake->head->position.X <= 0 || snake->head->position.X >= ARENA_WIDTH - 1 || snake->head->position.Y <= 0 || snake->head->position.Y >= ARENA_HEIGHT - 1)
            gameOver = true;
        SnakePart *part = snake->head->next;
        while (part != NULL)
        {
            if (part->position.X == snake->head->position.X && part->position.Y == snake->head->position.Y)
            {
                gameOver = true;
                break;
            }
            part = part->next;
        }

        if (snake->head->position.X == food.X && snake->head->position.Y == food.Y)
        {
            food = RandomFood(snake);
            score += 10;
        }
        else
        {
            SnakePart *oldTail = snake->tail;
            snake->tail = snake->tail->prev;
            snake->tail->next = NULL;
            free(oldTail);
        }

        // Update display
        UpdateArena(arena, snake, food);
        WriteConsoleOutputCharacter(hConsole, arena, arenaSize, (COORD){0, 0}, &dwBytesWritten);
        wchar_t scoreText[ARENA_WIDTH];
        swprintf(scoreText, ARENA_WIDTH, L"Score: %d", score);
        WriteConsoleOutputCharacter(hConsole, scoreText, wcslen(scoreText), (COORD){0, ARENA_HEIGHT}, &dwBytesWritten);

        Sleep(200);
    }

    /////////////
    // Exit
    /////////////

    DelSnake(snake);
    DelArena(arena);
    CloseHandle(hConsole);
    puts("Game Over!");
    printf("Score: %d\n", score);
    system("pause");

    // Show the cursor
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    return 0;
}

Snake *InitSnake()
{
    Snake *snake = malloc(sizeof(Snake));
    snake->head = malloc(sizeof(SnakePart));
    snake->head->position = (COORD){ARENA_WIDTH / 2 + 1, ARENA_HEIGHT / 2};
    snake->head->prev = NULL;
    snake->head->next = NULL;
    SnakePart *partPrev = snake->head;
    for (int i = 0; i < 3; i++)
    {
        SnakePart *part = malloc(sizeof(SnakePart));
        part->position = (COORD){ARENA_WIDTH / 2 - i, ARENA_HEIGHT / 2};
        part->prev = partPrev;
        part->next = NULL;
        partPrev->next = part;
        partPrev = part;
    }
    snake->tail = partPrev;
    snake->direction = RIGHT;

    SnakePart *part = snake->head;
    while (part != NULL)
    {
        part = part->next;
    }

    return snake;
}

void DelSnake(Snake *snake)
{
    SnakePart *part = snake->head;
    while (part != NULL)
    {
        SnakePart *next = part->next;
        free(part);
        part = next;
    }
    free(snake);
}

wchar_t *InitArena()
{

    wchar_t *arena = malloc(sizeof(wchar_t) * ARENA_WIDTH * ARENA_HEIGHT);
    for (int i = 0; i < ARENA_WIDTH * ARENA_HEIGHT; i++)
        arena[i] = L' ';
    for (int i = 0; i < ARENA_WIDTH; i++)
    {
        arena[i] = L'#';
        arena[ARENA_WIDTH * ARENA_HEIGHT - ARENA_WIDTH + i] = L'#';
    }
    for (int i = 0; i < ARENA_HEIGHT; i++)
    {
        arena[i * ARENA_WIDTH] = L'#';
        arena[i * ARENA_WIDTH + ARENA_WIDTH - 1] = L'#';
    }

    return arena;
}

void UpdateArena(wchar_t *arena, Snake *snake, COORD food)
{
    for (int i = 1; i < ARENA_WIDTH - 1; i++)
    {
        for (int j = 1; j < ARENA_HEIGHT - 1; j++)
        {
            arena[j * ARENA_WIDTH + i] = L' ';
        }
    }
    SnakePart *part = snake->head;
    while (part != NULL)
    {
        arena[part->position.Y * ARENA_WIDTH + part->position.X] = L'O';
        part = part->next;
    }
    arena[food.Y * ARENA_WIDTH + food.X] = L'@';
}

void DelArena(wchar_t *arena)
{
    free(arena);
}

COORD RandomFood(Snake *snake)
{
    COORD food;
    bool foodOnSnake = true;
    while (foodOnSnake)
    {
        foodOnSnake = false;
        food.X = (short)rand() % (ARENA_WIDTH - 2) + 1;
        food.Y = (short)rand() % (ARENA_HEIGHT - 2) + 1;

        SnakePart *part = snake->head;
        while (part != NULL)
        {
            if (part->position.X == food.X && part->position.Y == food.Y)
            {
                foodOnSnake = true;
                break;
            }
            part = part->next;
        }
    }
    return food;
}