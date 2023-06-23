/* 
 * Command line Tetris game.
 * 
 * Controls:
 *  Left arrow - move piece left
 *  Right arrow - move piece right
 *  Down arrow - move piece down faster
 *  Space - rotate piece
 * 
 * Requires resizing console window to width 80 and height at least 18.
 * 
 * Based on OneLoneCoder guide.
 * Youtube: https://www.youtube.com/watch?v=8OK8_tHeCIA&ab_channel=javidx9
 * Github source: https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_Tetris.cpp
 */

#include <iostream>
#include <thread>
#include <vector>

using namespace std;

#ifndef UNICODE
#define UNICODE
#endif // UNICODE
#ifndef _UNICODE
#define _UNICODE
#endif // _UNICODE

#include <Windows.h>

wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char *pField = nullptr;
int nScreenWidth = 80;
int nScreenHeight = 30;

int Rotate(int px, int py, int r);
bool DoesPieceFit(int nTetromino, int nRotation, int posX, int posY);

int main(void)
{
    srand(time(NULL));
    
    // Create assets
    tetromino[0] = L"..X...X...X...X."; // Hero
    tetromino[1] = L"..X..XX..X......"; // Cleveland Z
    tetromino[2] = L".X...XX...X....."; // Rhode Island Z
    tetromino[3] = L"..XX..XX........"; // Smashboy
    tetromino[4] = L"..X..XX...X....."; // Teewee
    tetromino[5] = L".....XX...X...X."; // Orange Ricky
    tetromino[6] = L".....XX..X...X.."; // Blue Ricky

    pField = new unsigned char[nFieldWidth * nFieldHeight];
    for (int x = 0; x < nFieldWidth; x++)
    {
        for (int y = 0; y < nFieldHeight; y++)
        {
            if (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1)
                pField[y * nFieldWidth + x] = 9;
            else
                pField[y * nFieldWidth + x] = 0;
        }
    }

    // Create screen buffer
    wchar_t *screen = new wchar_t[nScreenWidth * nScreenHeight];
    for (int i = 0; i < nScreenWidth * nScreenHeight; i++)
        screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    // Game variables
    bool bGameOver = false;
    int nCurrentPiece = rand() % 7;
    int nCurrentRotation = 0;
    int nCurrentX = nFieldWidth / 2;
    int nCurrentY = 0;
    bool bKey[4];
    bool bRotateHeld = false;
    int nSpeed = 20;
    int nSpeedCounter = 0;
    bool bForceDown = false;
    int nPiece = 0;
    int nScore = 0;
    vector<int> vLines;

    // Game loop
    while (!bGameOver)
    {
        // Game timing
        this_thread::sleep_for(50ms);
        nSpeedCounter++;
        bForceDown = (nSpeedCounter == nSpeed);

        // Input
        for (int k = 0; k < 4; k++)
            // https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
            bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28\x20"[k]))) != 0; // right, left, down, space

        // Game logic
        if (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY))
            nCurrentX++;      
        if (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY))
            nCurrentX--;
        if (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
            nCurrentY++;
        if (bKey[3] && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY) && !bRotateHeld)
        {
            nCurrentRotation++;
            bRotateHeld = true;
        }
        else
            bRotateHeld = false;

        if (bForceDown)
        {
            if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
                // Can move down
                nCurrentY++;
            else    
            {
                // Lock piece in
                for (int px = 0; px < 4; px++)
                    for (int py = 0; py < 4; py++)
                        if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
                            pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;
                
                nPiece++;
                if (nPiece % 10 == 0 && nSpeed >= 10)
                    nSpeed--;

                // Check for lines
                for (int py = 0; py < 4; py++)
                    if (nCurrentY + py < nFieldHeight - 1)
                    {
                        bool bLine = true;
                        for (int x = 1; x < nFieldWidth - 1; x++)
                        {
                            if (pField[(nCurrentY + py) * nFieldWidth + x] == 0)
                            {
                                bLine = false;
                                break;
                            }
                        }
                        if (bLine)
                        {
                            for (int x = 1; x < nFieldWidth - 1; x++)
                                pField[(nCurrentY + py) * nFieldWidth + x] = 8;
                            vLines.push_back(nCurrentY + py);
                        }
                    }

                // Update score
                nScore += 25;
                if (!vLines.empty())
                    nScore += (1 << vLines.size()) * 100;

                // Next piece
                nCurrentX = nFieldWidth / 2;
                nCurrentY = 0;
                nCurrentRotation = 0;
                nCurrentPiece = rand() % 7;

                // If new piece does not fit, game over
                bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
            }

            nSpeedCounter = 0;
        }

        // Draw Field
        for (int x = 0; x < nFieldWidth; x++)
            for (int y = 0; y < nFieldHeight; y++)
                screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];

        // Draw current piece
        for (int px = 0; px < 4; px++)
            for (int py = 0; py < 4; py++)
                if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
                    screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65; // 65 is ASCII 'A'

        // Draw score
        swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"SCORE: %8d", nScore);

        // Update for completed lines
        if (!vLines.empty())
        {
            WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dwBytesWritten);
            this_thread::sleep_for(400ms);  // Delay to show completed lines for a bit

            for (auto &v: vLines)
                for (int x = 1; x < nFieldWidth - 1; x++)
                {
                    for (int y = v; y > 0; y--)
                        pField[y * nFieldWidth + x] = pField[(y - 1) * nFieldWidth + x];    // Move down rows above
                    pField[x] = 0;  // Top row clear
                }
            vLines.clear();
        }

        // Display frame
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dwBytesWritten);
    }

    CloseHandle(hConsole);
    cout << "Game Over! Your score is: " << nScore << endl;
    system("pause");
    return 0;
}

// Rotate the falling piece
int Rotate(int px, int py, int r)
{
    switch (r % 4)
    {
    case 0:
        return py * 4 + px; // 0 degrees
    case 1:
        return 12 + py - (px * 4); // 90 degrees
    case 2:
        return 15 - (py * 4) - px; // 180 degrees
    case 3:
        return 3 - py + (px * 4); // 270 degrees
    }
    return -1;
}

// Check there are no collisions
bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
    for (int px = 0; px < 4; px++)
    {
        for (int py = 0; py < 4; py++)
        {
            int nPieceIndex = Rotate(px, py, nRotation);
            int nFieldIndex = (nPosY + py) * nFieldWidth + (nPosX + px);
            
            if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
                if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
                    if (tetromino[nTetromino][nPieceIndex] == L'X' && pField[nFieldIndex] != 0)
                        return false; // collision!
        }
    }
    return true;
}
