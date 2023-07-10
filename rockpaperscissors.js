/*
 * Rock, Paper, Scissors
 * A game to play versus the computer
 * To install the prompt-sync module, run: 'npm install prompt-sync'
 */

// Load prompt-sync for user input
const prompt = require('prompt-sync')({ sigint: true });

// Get user choice
const getUserChoice = () => {
    let userInput = prompt('What do you choose? ');
    userInput = userInput.toLowerCase();
    if (userInput === 'rock' || userInput === 'paper' || userInput === 'scissors' || userInput === 'bomb') {
        return userInput;
    } else {
        console.log('Error: Invalid input. Write rock, paper or scissors.')
    }
};

// Get computer choice
const getComputerChoice = () => {
    let randomNumber = Math.floor(Math.random() * 3)
    if (randomNumber === 0) {
        return 'rock';
    } else if (randomNumber === 1) {
        return 'paper';
    } else {
        return 'scissors';
    }
};

// Determine who wins
const determineWinner = (userChoice, computerChoice) => {
    if (userChoice === 'bomb') {
        return 'The player wins! Kaboom!'
    }
    if (userChoice === computerChoice) {
        return "It's a tie!";
    }
    if (userChoice === 'rock') {
        if (computerChoice === 'paper') {
            return 'The computer wins!';
        } else {
            return 'The player wins!';
        }
    }
    if (userChoice === 'paper') {
        if (computerChoice === 'scissors') {
            return 'The computer wins!';
        } else {
            return 'The player wins!';
        }
    }
    if (userChoice === 'scissors') {
        if (computerChoice === 'rock') {
            return 'The computer wins!';
        } else {
            return 'The player wins!';
        }
    }
};

// Start game and log results
const playGame = () => {
    let userChoice = getUserChoice();
    if (!userChoice) return 1;
    console.log(`The player chooses ${userChoice}.`);
    let computerChoice = getComputerChoice();
    console.log(`The computer chooses ${computerChoice}.`);
    console.log(determineWinner(userChoice, computerChoice));
};

// Start the game
console.log("Hi! Let's play rock, paper scissors.");
playGame();
