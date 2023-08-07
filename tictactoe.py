"""
One or two player game of Tic-Tac-Toe.
There are three levels of difficulty available for single player.
Squares on the grid are numbered in the same way as the numberpad on keyboard.
"""

import os
import random
import time

import tictactoe_ai


marks = ("X", "O")
ai_names = ("Easy AI", "Standard AI", "Impossible AI")


def main():
    print("_____________")
    print("             ")
    print(" TIC TAC TOE ")
    print("_____________")
    print("Welcome to Tic Tac Toe!")
    print(
        "Take turns placing markers on the grid using using 1-9 in a numberpad layout."
    )
    print("Get three in a row to win.")

    # Start a game
    play = True
    while play:
        # Pick one or two player and who plays first
        player_names = setup_players()
        if play_order(player_names):
            player_names.reverse()

        board = ["#"] + [" "] * 9
        display_board(board)
        active_idx = 0

        # Gameplay loop
        for _ in range(9):
            if player_names[active_idx].startswith("Player"):
                # human player
                move = select_move(board, player_names[active_idx])
            else:
                # computer player
                move = tictactoe_ai.ai_select_move(
                    board, active_idx, player_names[active_idx]
                )
                print(f"{player_names[active_idx]} chooses square {move}.")
                time.sleep(2)
            board = update_board(board, move, marks[active_idx])
            display_board(board)
            if win_check(board, marks[active_idx]):
                print(f"{player_names[active_idx]} wins!")
                break
            active_idx = 1 - active_idx
        else:
            print("It's a draw!")

        # Check to play again
        play = play_again()

    # Ending
    print("Goodbye!")


def setup_players() -> list[str]:
    player_count = ""
    print("Choose number of players:\n(1) Single player\n(2) Two player")
    while True:
        player_count = input()
        if player_count in ["1", "2"]:
            break
        print("Enter either 1 or 2. ")
    if player_count == "2":
        return ["Player 1", "Player 2"]

    ai_level = ""
    print("Select difficulty level:\n(1) Easy\n(2) Standard\n(3) Impossible")
    while True:
        ai_level = input()
        if ai_level in ["1", "2", "3"]:
            break
        print("Enter either 1, 2 or 3. ")
    return ["Player", ai_names[int(ai_level) - 1]]


def play_order(player_names: list[str]) -> int:
    first_player = ""
    print(
        f"Choose who will play first:\n(1) {player_names[0]}\n(2) {player_names[1]}\n(3) Random choice"
    )
    while True:
        first_player = input()
        if first_player in ["1", "2", "3"]:
            break
        print("Enter either 1, 2 or 3. ")
    if first_player == "3":
        idx = random.randint(0, 1)
    else:
        idx = int(first_player) - 1
    print(f"{player_names[idx]} will move first!")
    return idx


def display_board(board: list[int]):
    os.system("cls" if os.name == "nt" else "clear")
    print("     |     |     ")
    print("  " + board[7] + "  |  " + board[8] + "  |  " + board[9] + "  ")
    print("     |     |     ")
    print("-----+-----+-----")
    print("     |     |     ")
    print("  " + board[4] + "  |  " + board[5] + "  |  " + board[6] + "  ")
    print("     |     |     ")
    print("-----+-----+-----")
    print("     |     |     ")
    print("  " + board[1] + "  |  " + board[2] + "  |  " + board[3] + "  ")
    print("     |     |     ")


def select_move(board: list[int], player_name: str) -> int:
    square = 0
    square_is_valid = False
    print(f"{player_name}, place your marker (1-9): ")
    while not square_is_valid:
        square = input()
        if not square.isdigit():
            print("Input must be a digit. ")
        elif int(square) not in range(1, 10):
            print("Input must be a number 1 to 9. ")
        elif board[int(square)] != " ":
            print("That square is taken! ")
        else:
            square_is_valid = True
    return int(square)


def update_board(board: list[int], square: int, mark: str) -> list[int]:
    board[square] = mark
    return board


def win_check(board: list[int], mark: str) -> bool:
    winning_lines = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9],
        [1, 4, 7],
        [2, 5, 8],
        [3, 6, 9],
        [1, 5, 9],
        [3, 5, 7],
    ]
    for a, b, c in winning_lines:
        if board[a] == board[b] == board[c] == mark:
            return True
    return False


def play_again() -> bool:
    answer = ""
    while True:
        answer = input("Play again? (Y/N): ").upper()
        if answer in ["Y", "N"]:
            break
        print("Type 'Y' or 'N'.")
    return answer == "Y"


if __name__ == "__main__":
    main()
