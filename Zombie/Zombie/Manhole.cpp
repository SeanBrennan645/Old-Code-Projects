#include "Manhole.h"

Manhole::Manhole()
{
	//setting symbol
	symbol = 'O';
}

Manhole::~Manhole()
{
}

//randomly selecting x and y positions
void Manhole::spawnManhole(int playerY, int playerX, int gridSize)
{
	position[0] = rand() % gridSize + 1;
	position[1] = rand() % gridSize + 1;
	//changing positions if they are same as players
	while (position[0] == playerY&&position[1] == playerX)
	{
		position[0] = rand() % gridSize + 1;
		position[1] = rand() % gridSize + 1;
	}
	//outputting manholes
	Console::setCursorPosition(position[0], position[1]);
	Console::setColour(Console::LIGHT_YELLOW);
	std::cout << symbol;
}

//getters
int Manhole::getYPos()
{
	return position[0];
}

int Manhole::getXPos()
{
	return position[1];
}