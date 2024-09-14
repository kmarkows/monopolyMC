#include "Player.hpp"
#include <iostream>

void Player::print()
{
	std::cout << "player id:" << (int)id << " currentTile:" << (int)currTile << std::endl;
}

const bool Player::isInPrison() const
{
	return prison;
}

const bool Player::hasGetOutOfPrisonCard() const
{
	return getOutOfPrisonCard;
}

const uint8_t Player::getStayingInPrisonStrategy() const
{
	return stayingInPrisonStrategy;
}

const uint8_t Player::getCurrTile() const
{
	return currTile;
}

const uint8_t Player::getId() const
{
	return id;
}

const uint8_t Player::getTurnsSpentInPrison() const
{
	return turnsSpentInPrison;
}

const int Player::getCurrentBalance() const
{
	return balance;
}

const bool Player::isPlaying() const
{
	return playing;
}

const bool Player::hasInterActedWithTile() const
{
	return interactedWithTile;
}

const std::vector<uint8_t> &Player::getOwnedTilesIds() const
{
	return ownedTilesIds;
}

void Player::goToPrison()
{
	prison = true;
}

void Player::acquireGetOutOfPrisonCard()
{
	getOutOfPrisonCard = true;
}

void Player::useGetOutOfPrisonCard()
{
	getOutOfPrisonCard = false;
}

void Player::getOutOfPrison()
{
	prison = false;
}

void Player::setStayingInPrisonStrategy(const uint8_t givenStayingInPrisonStrategy)
{
	stayingInPrisonStrategy = givenStayingInPrisonStrategy;
}

void Player::setCurrTile(const uint8_t nextTile)
{
	currTile = nextTile;
}

void Player::incrementTurnsSpentInPrison()
{
	turnsSpentInPrison++;
}

void Player::resetTurnsSpentInPrison()
{
	turnsSpentInPrison = 0;
}

void Player::setBalance(const int balance)
{
	this->balance = balance;
}

void Player::addBalance(const int addition)
{
	balance += addition;
}

void Player::subtractBalance(const int subtraction)
{
	balance -= subtraction;
	if (balance <= 0)
	{
		setNotPlaying();
	}
}

void Player::setNotPlaying()
{
	playing = false;
}

void Player::setInteractedWithTile()
{
	interactedWithTile = true;
}

void Player::resetInteractedWithTile()
{
	interactedWithTile = false;
}

void Player::addOwnedTileId(const uint8_t newTileId)
{
	ownedTilesIds.push_back(newTileId);
}
