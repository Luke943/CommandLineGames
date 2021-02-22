"""
Two player game of TicTacToe.
Squares on the grid are numbered in the same way as the numberpad on keyboard.
"""

import random
from IPython.display import clear_output


def main():
    # run the game
    replay = True

    # start
    while replay == True:
        game_on = True
        board = ['#'] + [' '] * 9
        display_board(board)
        print('Welcome to Tic Tac Toe!')
        print('Take turns placing markers on the grid using using 1-9 in a numberpad layout.')

        # picks who plays first and markers
        p1 = play_order()
        p2 = 3 - p1
        mark1 = choose_symbol(p1)
        if mark1 == 'X':
            mark2 = 'O'
        else:
            mark2 = 'X'

        # gameplay
        while game_on == True:

            # first player turn
            p1move = select_move(board, p1)
            board = update_board(board, p1move, mark1)
            display_board(board)
            if win_check(board, mark1):
                print("Player {} wins!".format(p1))
                game_on = False
                break
            if not space_check(board):
                print("It's a draw!")
                game_on = False
                break

            # second player turn
            p2move = select_move(board, p2)
            board = update_board(board, p2move, mark2)
            display_board(board)
            if win_check(board, mark2):
                print("Player {} wins!".format(p2))
                game_on = False
                break

        # check to play again
        replay = play_again()

    # ending
    print('Goodbye!')


def display_board(board):
    clear_output()
    print('   |   |   ')
    print(' ' + board[7] + ' | ' + board[8] + ' | ' + board[9] + ' ')
    print('---|---|---')
    print(' ' + board[4] + ' | '+board[5] + ' | ' + board[6] + ' ')
    print('---|---|---')
    print(' ' + board[1] + ' | '+board[2]+' | '+board[3] + ' ')
    print('   |   |   ')


def choose_symbol(player):
    choice = ''
    while choice not in ['X', 'O']:
        choice = input('Player {}: Play as X or O? '.format(player)).upper()
        if choice not in ['X', 'O']:
            print("Enter either 'X' or 'O'.")
    return choice


def select_move(board, player):
    square = 0
    square_is_valid = False
    while not square_is_valid:
        square = input('Player {}, place your marker (1-9): '.format(player))
        if not square.isdigit():
            print('Input must be a digit.')
        elif int(square) not in range(1, 10):
            print('Input must be a number 1 to 9.')
        elif board[int(square)] != ' ':
            print('That square is taken!')
        else:
            square_is_valid = True
    return int(square)


def update_board(board, square, mark):
    board[square] = mark
    return board


def win_check(board, mark):
    winning_lines = [[1, 2, 3], [4, 5, 6], [7, 8, 9], [1, 4, 7],
                     [2, 5, 8], [3, 6, 9], [1, 5, 9], [3, 5, 7]]
    for a, b, c in winning_lines:
        if board[a] == board[b] == board[c] == mark:
            return True
    else:
        return False


def space_check(board):
    return ' ' in board


def play_again():
    answer = ''
    while answer not in ['Y', 'N']:
        answer = input('Play again? (Y/N): ').upper()
        if answer not in ['Y', 'N']:
            print("Type 'Y' or 'N'.")
    if answer == 'Y':
        return True
    else:
        return False


def play_order():
    choice = ''
    while choice not in ['1', '2', '3']:
        choice = input(
            'Choose who will play first:\n(1) Player 1\n(2) Player 2\n(3) Random choice\n')
        if choice not in ['1', '2', '3']:
            print("Enter either 1, 2 or 3.")
    if choice == '3':
        player = random.randint(1, 2)
    else:
        player = int(choice)
    print('Player {} will move first!'.format(player))
    return player


if __name__ == '__main__':
    main()
