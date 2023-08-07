"""
Three levels of AI to play tic-tac-toe.
Designed to work with tictactoe.py.
"""

import random

import tictactoe


def ai_select_move(board: list[int], idx: int, ai_name: str) -> int:
    """Selects which AI to call."""
    if ai_name == tictactoe.ai_names[0]:
        return ai_easy(board, idx)
    elif ai_name == tictactoe.ai_names[1]:
        return ai_standard(board, idx)
    elif ai_name == tictactoe.ai_names[2]:
        return ai_impossible(board, idx)
    else:
        raise ValueError("Invalid AI")


def ai_easy(board: list[int], idx: int) -> int:
    """Selects an empty square at random."""
    empty_squares = get_empty_squares(board)
    idx = random.randint(0, len(empty_squares) - 1)
    return empty_squares[idx]


def ai_standard(board: list[int], idx: int) -> int:
    """
    If the AI has an immediate win, it plays it.
    If other player has win next move, the AI blocks it.
    Otherwise, selects a random empty square.
    """
    empty_squares = get_empty_squares(board)

    mark = tictactoe.marks[idx]
    for sq in empty_squares:
        if tictactoe.win_check(tictactoe.update_board(board, sq, mark), mark):
            return sq
        else:
            tictactoe.update_board(board, sq, " ")

    alt_mark = tictactoe.marks[1 - idx]
    for sq in empty_squares:
        if tictactoe.win_check(tictactoe.update_board(board, sq, alt_mark), alt_mark):
            return sq
        else:
            tictactoe.update_board(board, sq, " ")

    return empty_squares[random.randint(0, len(empty_squares) - 1)]


def ai_impossible(board: list[int], idx: int) -> int:
    """
    Chooses randomly between moves that give optimal assessment of position given by min/max algorithm.
    Can't be beaten.
    """
    empty_squares = get_empty_squares(board)

    if len(empty_squares) == 9:
        # starting position is a draw
        return random.randint(1, 9)

    assessments = []
    for sq in empty_squares:
        tictactoe.update_board(board, sq, tictactoe.marks[idx])
        assessments.append(-assess(board, 1 - idx))
        tictactoe.update_board(board, sq, " ")

    max_assessment = max(assessments)
    optimal_squares = [
        i for i, a in zip(empty_squares, assessments) if a == max_assessment
    ]
    return optimal_squares[random.randint(0, len(optimal_squares) - 1)]


def assess(board: list[int], side: int) -> int:
    """
    Recursive min/max algorithm used in ai_impossible.
    Returns 1 if player wins, 0 if draws, -1 if losses.
    """
    if tictactoe.win_check(board, tictactoe.marks[side]):
        return 1
    elif tictactoe.win_check(board, tictactoe.marks[1 - side]):
        return -1
    elif board.count(" ") == 0:
        return 0

    assessments = []
    for sq in get_empty_squares(board):
        tictactoe.update_board(board, sq, tictactoe.marks[side])
        assessments.append(-assess(board, 1 - side))
        tictactoe.update_board(board, sq, " ")
    return max(assessments)


def get_empty_squares(board: list[int]) -> list[int]:
    return [i for i, x in enumerate(board) if x == " "]
