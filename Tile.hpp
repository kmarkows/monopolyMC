#pragma once

#include <string>

class Tile
{
  public:
	Tile() = default;
	Tile(const std::string givenType, const int givenCost) : type(givenType), cost(givenCost){};

	const std::string getType() const;
	const uint8_t getOwnerId() const;
	const int getCost() const;

	void setOwnerId(const uint8_t toBeOwnerId);

  private:
	std::string type{};
	uint8_t ownerId{0};
	int cost{0};
};