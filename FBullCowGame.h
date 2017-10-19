#pragma once
#include <string>

using FString = std::string;
using int32 = int;

enum class EGuessStatus
{
	Unchecked,
	OK,
	Not_Isogram,
	Blank,
	NotLowercase,
	WrongLength
};

struct FResultCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
public:
	// Const Methods
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetWordLength() const;
	int32 TriesLeft() const;
	FString GetWord() const;
	bool IsGameWon() const;

	// Methods with logic
	FBullCowGame(); // constructor
	void Reset(); // TODO make more rich
	void NextTry();
	FResultCount CheckGuess(FString GWord);
	EGuessStatus ValidateGuess(FString GWord);

private: // Init is constructor
	int32 iMaxTries;
	int32 iCurrentTry;
	FString sWord;
	bool bIsGameWon;

	bool IsIsogram(FString Word) const;
};