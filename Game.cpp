#include "Game.hpp"

Game::Game(const uint32_t givenIterations, const uint8_t givenNumOfPlayers, const DiceThrower *givenDiceThrower)
{
	iterations = givenIterations;
	numOfPlayers = givenNumOfPlayers;
	diceThrower = givenDiceThrower;
	createPlayersData();
}

void Game::play()
{
	for (uint32_t it = 0; it < iterations; it++)
	{
		for (auto &player : players)
		{
			if (player.isPlaying())
			{
				if (not player.isInPrison())
				{
					handleMovement(player);
					if (player.getCurrTile() == goToPrisonTile)
					{
						setPrison(player);
					}
                    // Cards here so when player is moved on tile he lands can be handled
				}
				else
				{
					handleGetOutOfPrison(player);
				}
				handleTile(player);

				collectTilesData(player.getCurrTile());
			}
			else
			{
				// TO DO remove player from players vector
				std::cout << "player lost" << std::endl;
			}
		}
		// printPlayersData();
		// std::cout << std::endl;
	}
	// printPropertiesData();
}

void Game::handleTile(Player &player)
{
	// std::cout << "Game::handleTile" << std::endl;
	const auto currTileType = board.getTiles().at(player.getCurrTile()).getType();

	// TO DO community chest and chance handling

	if (currTileType == "IncomeTax" or currTileType == "LuxuryTax")
	{
		const int subtraction = currTileType == "IncomeTax" ? 200 : 100;
		player.subtractBalance(subtraction);
		return;
	}

	if (currTileType == "Railroad" and isBuyingEnabled)
	{
		handleBuyProperty(player, currTileType);
		return;
	}

	if (currTileType == "Utilities" and isBuyingEnabled)
	{
		handleBuyProperty(player, currTileType);
		return;
	}

	if (currTileType == "Property" and isBuyingEnabled)
	{
		handleBuyProperty(player, currTileType);
		return;
	}
}

void Game::handleBuyProperty(Player &player, const std::string &currTileType)
{
	// always buy strategy
	const int tileCost = board.getTiles().at(player.getCurrTile()).getCost();
	const uint8_t ownerId = board.getTiles().at(player.getCurrTile()).getOwnerId();
	if (ownerId == invalidPlayerId and player.getCurrentBalance() > tileCost)
	{
		board.getTilesForModification().at(player.getCurrTile()).setOwnerId(player.getId());
		player.subtractBalance(tileCost);
	}
}

void Game::handleMovement(Player &player)
{
	uint8_t throwCounter = 0;
	bool isDouble = true;
	auto nextTile = player.getCurrTile();

	while (throwCounter < 3 and isDouble)
	{
		auto diceResult = diceThrower->throwDice();
		// std::cout << (int)diceResult.getFirst() << " " << (int)diceResult.getSecond() << std::endl;
		isDouble = diceResult.getFirst() == diceResult.getSecond();
		throwCounter++;

		nextTile += (diceResult.getFirst() + diceResult.getSecond());
	}

	if (throwCounter == 3 and isDouble)
	{
		setPrison(player);
		return;
	}

	if (nextTile / numOfMonopolyBoradTiles == 1)
	{
		player.addBalance(200);
	}

	nextTile = nextTile % numOfMonopolyBoradTiles;
	player.setCurrTile(nextTile);
}

void Game::handleGetOutOfPrison(Player &player)
{
	const auto diceResult = diceThrower->throwDice();
	if (player.getTurnsSpentInPrison() == 2)
	{
		player.getOutOfPrison();
		auto nextTile = player.getCurrTile();
		nextTile += (diceResult.getFirst() + diceResult.getSecond());
		nextTile = nextTile % numOfMonopolyBoradTiles;
		player.setCurrTile(nextTile);
		return;
	}
	// TO DO choose to pay 50$ to get out of prison instantly
	// std::cout << (int)diceResult.getFirst() << " " << (int)diceResult.getSecond() << std::endl;
	// std::cout << "trying to get out of prison" << std::endl;
	if (diceResult.getFirst() == diceResult.getSecond())
	{
		// std::cout << "got out of prison" << std::endl;
		player.getOutOfPrison();
	}
	else
	{
		// std::cout << "increment get out of prison counter" << std::endl;
		player.incrementTurnsSpentInPrison();
	}
}

void Game::setPrison(Player &player)
{
	// std::cout << "goToPrisonTile" << std::endl;
	player.goToPrison();
	player.setCurrTile(prisonTile);
}

void Game::createPlayersData()
{
	for (uint8_t id = 1; id < numOfPlayers + 1; id++)
	{
		Player player(id);
		players.push_back(player);
	}
}

void Game::collectTilesData(const uint8_t currTile)
{
	tilesVisitedCounters[currTile]++;
}

void Game::printTilesVisitedCounters()
{
	for (const auto &[tile, counter] : tilesVisitedCounters)
	{
		std::cout << "tile:" << (int)tile << " number of visits:" << (int)counter << std::endl;
	}
}

void Game::printPlayersData()
{
	for (uint8_t id = 0; id < numOfPlayers; id++)
	{
		players.at(id).print();
	}
}

void Game::printPropertiesData()
{
	for (const auto &tile : getBoardData().getTiles())
	{
		if (tile.getType() == "Property")
		{
			std::cout << "tile:" << (int)tile.getId() << " owner:" << (int)tile.getOwnerId() << std::endl;
		}
	}
}

std::vector<Player> &Game::getPlayersDataForManipulation()
{
	return players;
}

const std::vector<Player> &Game::getPlayersData() const
{
	return players;
}

const Board &Game::getBoardData() const
{
	return board;
}

void Game::enableBuying()
{
	isBuyingEnabled = true;
}
