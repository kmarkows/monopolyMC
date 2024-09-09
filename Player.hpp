#pragma once

#include "DiceResult.hpp"
#include "Tile.hpp"
#include <cinttypes>

constexpr uint8_t invalidPlayerId = 0;
constexpr int startingBalance = 1500;

class Player
{
  public:
	Player(uint8_t givenId) : id{givenId} {};

	const bool isInPrison() const;
    const bool hasGetOutOfPrisonCard() const;
	const uint8_t getCurrTile() const;
	const uint8_t getId() const;
	const uint8_t getTurnsSpentInPrison() const;
	const int getCurrentBalance() const;
	const bool isPlaying() const;

	void goToPrison();
    void acquireGetOutOfPrisonCard();
    void useGetOutOfPrisonCard();
	void getOutOfPrison();
	void setCurrTile(const uint8_t nextTile);
	void incrementTurnsSpentInPrison();
	void resetTurnsSpentInPrison();
	void setBalance(const int balance);
	void addBalance(const int addition);
	void subtractBalance(const int subtraction);
	void setNotPlaying();

	void print();

  private:
	uint8_t id{invalidPlayerId};
	uint8_t currTile{0};
	bool prison{false};
    bool getOutOfPrisonCard{false};
	bool playing{true};
	uint8_t turnsSpentInPrison{0};
	int balance{startingBalance};
};