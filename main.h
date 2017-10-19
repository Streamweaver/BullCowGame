#pragma once
#include <iostream>
#include "FBullCowGame.h"

using FText = std::string;

void HandleGuesses(FBullCowGame&);
void HandleOutcome(FBullCowGame&);
void IntroGame(FBullCowGame&);
FText GetValidGuess(FBullCowGame&);
bool AskToPlayAgain();