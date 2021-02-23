"""
Game to play BlackJack against an AI dealer on the command line.
"""

import os
import random

# Variables used to create, display and assess deck of cards
suits = ('Hearts', 'Diamonds', 'Spades', 'Clubs')
ranks = ('Two', 'Three', 'Four', 'Five', 'Six', 'Seven',
         'Eight', 'Nine', 'Ten', 'Jack', 'Queen', 'King', 'Ace')
values = {'Two': 2, 'Three': 3, 'Four': 4, 'Five': 5, 'Six': 6, 'Seven': 7,
          'Eight': 8, 'Nine': 9, 'Ten': 10, 'Jack': 10, 'Queen': 10, 'King': 10, 'Ace': 11}
short_ranks = {'Two': '2', 'Three': '3', 'Four': '4', 'Five': '5', 'Six': '6', 'Seven': '7',
               'Eight': '8', 'Nine': '9', 'Ten': 'T', 'Jack': 'J', 'Queen': 'Q', 'King': 'K', 'Ace': 'A'}


class Card():
    """ Card class to play game with """

    def __init__(self, suit, rank):
        # suit, rank
        self.suit = suit
        self.rank = rank
        self.value = values[rank]
        self.short_rank = short_ranks[rank]

    def __str__(self):
        return self.short_rank + self.suit[0]


class Deck():
    """ Deck class to deal cards from """

    def __init__(self):
        self.all_cards = []
        # generates deck object
        for suit in suits:
            for rank in ranks:
                # creates card objects
                created_card = Card(suit, rank)
                self.all_cards.append(created_card)

    def shuffle(self):
        random.shuffle(self.all_cards)

    def deal_one(self):
        return self.all_cards.pop(0)


class Player():
    """ Play class for user and dealer """

    def __init__(self, name, bankroll):
        self.name = name
        self.bankroll = bankroll
        self.stake = 0
        self.hand = []

    def play_card(self):
        return self.hand.pop(0)

    def take_cards(self, cards):
        try:
            # for multiple cards
            self.hand.extend(cards)
        except:
            # for single card
            self.hand.append(cards)

    def score(self):
        return blackjack_score(self.hand)

    def __str__(self):
        return f'Player {self.name} has ${self.bankroll} chips.'


"""
Main logic to play Blackjack
"""


def main():

    print('Welcome to BlackJack.')
    active_player = True

    while active_player:

        # set up game for new player
        player_name = input('Enter your name: ')
        player_bankroll = num_input('What is your balance (in dollars)? ')
        player = Player(player_name, player_bankroll)
        dealer = Player("Dealer", 0)
        play_blackjack = get_user_choice('Ready to play BlackJack?')

        # play a hand of blackjack
        while play_blackjack:

            # hand set up
            dealer.hand = []
            player.hand = []
            game_deck = Deck()
            game_deck.shuffle()
            show_board(player)
            print("Card's are shuffled.")

            # place bet
            stake = num_input("How much do you want to bet (in dollars)?",
                              player.bankroll)
            player.bankroll -= stake

            # deal cards
            for _ in range(2):
                player.take_cards(game_deck.deal_one())
                dealer.take_cards(game_deck.deal_one())
            dealer_seen = [dealer.hand[0], "??"]
            show_board(player, dealer_seen, f"Stake ${stake}", player.hand)
            print("Cards are dealt.")

            # check for blackjack
            if player.score() == dealer.score() == 21:
                show_board(player, dealer.hand,
                           f"Stake ${stake}", player.hand)
                print("You and the dealer have BLACKJACK!")
            elif dealer.score() == 21:
                show_board(player, dealer.hand,
                           f"Stake ${stake}", player.hand)
                print("Dealer has BLACKJACK!")
            elif player.score() == 21:
                show_board(player, dealer_seen,
                           f"Stake ${stake}", player.hand)
                print("You have BLACKJACK!")

            # when no blackjack
            else:
                # player actions
                print(f"Your score is {player.score()}")
                extra_card = get_user_choice("Hit or stick?", "H", "S")
                while extra_card:
                    player.take_cards(game_deck.deal_one())
                    show_board(player, dealer_seen,
                               f"Stake ${stake}", player.hand)
                    if player.score() > 21:
                        print("BUST")
                        break
                    print(f"Your score is {player.score()}")
                    extra_card = get_user_choice("Hit or stick?", "H", "S")

                # if player not bust
                if player.score() <= 21:
                    # dealer actions
                    show_board(player, dealer.hand,
                               f"Stake ${stake}", player.hand)
                    print(f"Dealer turns over {dealer.hand[1]}.")
                    print(f"Dealer's score is {dealer.score()}.")
                    while dealer.score() < 17:
                        print("Dealer will take another card")
                        input("Press enter to continue...")
                        dealer.take_cards(game_deck.deal_one())
                        show_board(player, dealer.hand,
                                   f'Stake ${stake}', player.hand)
                        print(f"Dealer's score is {dealer.score()}.")
                    if dealer.score() > 21:
                        print("BUST")

            # payout
            if (dealer.score() < player.score() <= 21 or
                    player.score() <= 21 < dealer.score()):
                if len(player.hand) == 2:
                    print(f"You win ${stake*3/2}!")
                    player.bankroll += stake*3/2
                else:
                    print(f"You win ${stake*2}!")
                player.bankroll += stake*2
            elif dealer.score() == player.score():
                print(f"It's a tie. Take back your stake of ${stake}.")
                player.bankroll += stake
            else:
                print("You lose.")

            print(f"Your bankroll is ${player.bankroll}.")

            # play again?
            if player.bankroll == 0:
                print("You have no money! Please leave the table.")
                play_blackjack = False
            else:
                play_blackjack = get_user_choice('Play another hand?')

        # another player?
        active_player = get_user_choice('Anyone else want to play?')

    print('Goodbye.')


"""
Getting user input
"""


def get_user_choice(question, option1='Y', option2='N'):
    answer = None
    while True:
        answer = input(f'{question} ({option1}/{option2}): ').lower()
        if answer == option1.lower():
            return True
        elif answer == option2.lower():
            return False
        else:
            print(f"Type '{option1}' or '{option2}'.")


def num_input(question, cap=None):
    while True:
        answer = input(f"{question} ")
        try:
            answer = float(answer)
        except:
            print("Enter a number in digits.")
            continue
        if cap == None or cap >= answer:
            return answer
        else:
            print(f"Number cannot exceed {cap}. Try again.")


"""
Display functions
"""


def show_hand(cards):
    hand = ''
    top = ''
    bottom = ''
    space = ''
    for card in cards:
        hand += f'| {str(card)} | '
        top += ' ____  '
        bottom += '|____| '
        space += '|    | '
    print(top)
    print(space)
    print(hand)
    print(bottom)


def show_board(player, dealer_hand=[], message='', player_hand=[]):
    os.system('cls' if os.name=='nt' else 'clear')
    print("-" * 50)
    print("Dealer's hand")
    show_hand(dealer_hand)
    print('\n' + message)
    show_hand(player_hand)
    print(f"{player.name}'s hand")
    print(f"Stack ${player.bankroll}")
    print("-" * 50)


"""
Assessing score
"""


def blackjack_score(hand):
    score = 0
    for card in hand:
        score += card.value
    num_aces = len([card for card in hand if card.rank == "Ace"])
    while score > 21 and num_aces:
        num_aces -= 1
        score -= 10
    return score


if __name__ == '__main__':
    main()
