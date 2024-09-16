#include "Game.hpp"
#include "GetOutOfPrisonHandler.hpp"

Game::Game(const uint32_t givenIterations, const uint8_t givenNumOfPlayers, const DiceThrower *givenDiceThrower,
		   const DiceThrowerSingle *givenDiceThrowerSingle)
{
	iterations = givenIterations;
	numOfPlayers = givenNumOfPlayers;
	diceThrower = givenDiceThrower;
	diceThrowerSingle = givenDiceThrowerSingle;
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
				}
				else
				{
					GetOutOfPrisonHandler getOutOfPrisonHandler(player, diceThrower);
					getOutOfPrisonHandler.handle();
				}
				// TO DOCards here so when player is moved on tile he lands can be
				// handled

				handleTile(player);
                
                // TO DO 
                // if (tile owned)
                // pay
                // else
                // try to buy

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

	if (currTileType == "IncomeTax" or currTileType == "LuxuryTax")
	{
		const int subtraction = currTileType == "IncomeTax" ? 200 : 100;
		player.subtractBalance(subtraction);
		return;
	}

	if (currTileType == "Railroad" and buyingEnabled)
	{
		handleBuyProperty(player, currTileType);
		return;
	}

	if (currTileType == "Utilities" and buyingEnabled)
	{
		handleBuyProperty(player, currTileType);
		return;
	}

	if (currTileType == "Property" and buyingEnabled)
	{
		handleBuyProperty(player, currTileType);
		return;
	}
}

void Game::handleBuyProperty(Player &player, const std::string &currTileType)
{
	// always buy strategy
	// TO DO extract to new class BuyPropertyHandler
	const auto &tile = board.getTiles().at(player.getCurrTile());
	const int tileCost = tile.getCost();
	const uint8_t ownerId = tile.getOwnerId();
	if (ownerId == invalidPlayerId and player.getCurrentBalance() > tileCost)
	{
		board.getTilesForModification().at(player.getCurrTile()).setOwnerId(player.getId());
		player.addOwnedTileId(tile.getId());
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
		// std::cout << (int)diceResult.getFirst() << " " <<
		// (int)diceResult.getSecond() << std::endl;
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

Board &Game::getBoardDataForModification()
{
	return board;
}

const bool Game::isBuyingEnabled() const
{
	return buyingEnabled;
}

void Game::enableBuying()
{
	buyingEnabled = true;
}
