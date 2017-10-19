#include <iostream>
#include <string>
#include "main.h"
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

int main() {
	bool PlayGame = true;
	FBullCowGame Game;
	while (PlayGame) {
		Game.Reset();
		IntroGame(Game);
		HandleGuesses(Game);
		HandleOutcome(Game);
		PlayGame = AskToPlayAgain();
	}

	return 0;
}

FText RandomWord() {
	return "word";
}

void IntroGame(FBullCowGame& game) {
	std::cout << "Welcome to Bulls and Cows, a fun word game" << std::endl;
	std::cout << "Can you guess the " << game.GetWordLength() << " letter isogram I'm thinking of?" << std::endl;
}

void HandleGuesses(FBullCowGame& game) {
	while (game.TriesLeft() > 0 && !game.IsGameWon()) { // repeat until 'exit' is typed.
		FText PlayerGuess = GetValidGuess(game);
		FResultCount TurnResult = game.CheckGuess(PlayerGuess); // Check the guess and act appropriatly
		std::cout << "Bulls = " << TurnResult.Bulls << ". Cows = " << TurnResult.Cows << "." << std::endl;
	}
}

FText GetValidGuess(FBullCowGame& game) {
	EGuessStatus Status = EGuessStatus::Unchecked;
	do {
		FText PlayerGuess = "";
		std::cout << "\nGuess #" << game.GetCurrentTry() << ". Type your guess: ";
		std::getline(std::cin, PlayerGuess); //

		EGuessStatus Status = game.ValidateGuess(PlayerGuess);
		switch (Status) {
		case EGuessStatus::Blank:
		case EGuessStatus::WrongLength:
			std::cout << "Please enter a " << game.GetWord().length() << " letter word." << std::endl;
			break;
		case EGuessStatus::NotLowercase:
			std::cout << "Please enter a only lower case letters." << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters." << std::endl;
			break;
		default:
			return PlayerGuess;
		}
	} while (Status != EGuessStatus::OK);
}


void HandleOutcome(FBullCowGame& game) {
	if (game.IsGameWon()) {
		std::cout << "You WON!!! The word was '" << game.GetWord() << "' Great Job!" << std::endl;
	}
	else {
		std::cout << "Sorry! You didn't guess correctly, the word was: '" << game.GetWord() << "'." << std::endl;
	}
}

bool AskToPlayAgain() {
	std::cout << "\nDo you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}
