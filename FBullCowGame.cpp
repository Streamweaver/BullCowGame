#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include "FBullCowGame.h"
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return iMaxTries; }

int32 FBullCowGame::GetCurrentTry() const { return iCurrentTry; }

int32 FBullCowGame::GetWordLength() const { return sWord.length(); }

FString FBullCowGame::GetWord() const { return sWord; }

bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

void FBullCowGame::Reset()
{
	iCurrentTry = 1;
	bIsGameWon = false;
	sWord = "abcdefg";
	iMaxTries = 10;
	return;
}

int32 FBullCowGame::TriesLeft() const
{
	return iMaxTries - iCurrentTry;
}

void FBullCowGame::NextTry() {
	iCurrentTry++;
}

FResultCount FBullCowGame::CheckGuess(FString GWord)
{
	FResultCount ResultCount;
	FString SWord = GetWord();
	for (int32 GIdx = 0; GIdx < GWord.length(); GIdx++) {
		for (int32 SIdx = 0; SIdx < SWord.length(); SIdx++) {
			if (GWord[GIdx] == SWord[SIdx] && GIdx == SIdx) {
				ResultCount.Bulls++;
			}
			else if (GWord[GIdx] == SWord[SIdx]) {
				ResultCount.Cows++;
			}
		}
	}
	if (GWord == SWord) {
		bIsGameWon = true;
	}
	NextTry();
	return ResultCount;
}

EGuessStatus FBullCowGame::ValidateGuess(FString GWord)
{
	if (!IsIsogram(GWord)) { return EGuessStatus::Not_Isogram; }
	if (GWord == "") { return EGuessStatus::Blank; }
	if (GWord.length() != GetWord().length()) { return EGuessStatus::WrongLength; }
	for (auto Letter : GWord) {
		if (isupper(Letter)) { return EGuessStatus::NotLowercase; }
	}
	return EGuessStatus::OK;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }
	bool result = true;
	TMap<char, bool> CharSeen;
	for (char Letter : Word) {
		Letter = tolower(Letter);
		result = CharSeen.count(Letter) ? false : result;
		CharSeen[Letter] = true;
	}
	return result;
}
