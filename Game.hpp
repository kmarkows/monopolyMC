#pragma once

#include "Board.hpp"
#include "DiceThrower.hpp"
#include "Player.hpp"
#include <map>
#include <vector>

class Game
{
  public:
	Game() = default;
	Game(const uint32_t givenIterations, const uint8_t givenNumOfPlayers, const DiceThrower *givenDiceThrower);
	void play();

	void printPlayersData();
	void printTilesVisitedCounters();
	void printPropertiesData();

	std::vector<Player> &getPlayersDataForManipulation();
	const std::vector<Player> &getPlayersData() const;

	const Board &getBoardData() const;

	void enableBuying();

  private:
	void createPlayersData();
	void handleMovement(Player &player);
	void handleTile(Player &player);
	void handleBuyProperty(Player &player, const std::string &currTileType);
	void setPrison(Player &player);

	void collectTilesData(const uint8_t currTile);

	uint32_t iterations;
	uint8_t numOfPlayers;
	std::vector<Player> players{};
	const DiceThrower *diceThrower;
	Board board{};
	bool isBuyingEnabled{false};

	std::map<uint8_t, uint32_t> tilesVisitedCounters{};
};