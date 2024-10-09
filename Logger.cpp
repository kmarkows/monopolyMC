#include "Logger.hpp"

Logger::Logger(const std::string &fileName)
{
    logFile.open(fileName, std::ios::app);
    if (!logFile.is_open())
    {
        std::cout << "Log file not opened" << std::endl;
    }
}

Logger::~Logger()
{
    logFile.close();
}

void Logger::logHouseBuying(const Player &player, const Tile &tile)
{
    logFile << "Player:" << (int)player.getId() << " boughtHouseNumber:" << (int)tile.getNumOfHouses()
            << " onTile:" << (int)tile.getId() << " for:" << tile.getHouseCost()
            << " balanceLeft:" << player.getCurrentBalance() << std::endl;
}

void Logger::logTileBuying(const Player &player, const Tile &tile)
{
    logFile << "Player: " << (int)player.getId() << " boughtTileNumer::" << (int)tile.getId()
            << " for: " << tile.getCost() << " balanceLeft: " << player.getCurrentBalance() << std::endl;
}
