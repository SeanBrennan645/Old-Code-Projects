#include "Tortoise.h"

//constructor
Tortoise::Tortoise()
{
	tortiosePosition = 0;
	tortoiseTotalMoveCounter = 0;
	moveOpening = "Tortoise used ";
	//reading data from tortoise txt file and storing in arrays
	int fileInt;
	std::string fileString;
	std::ifstream distFile("tortoise.txt");
	if (distFile.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			distFile >> fileString >> fileInt;
			moveList[i] = fileString;
			moveDist[i] = fileInt;
		}
	}
	else
	{
		std::cout << "ERROR UNABLE TO OPEN tortoise.txt";
	}
	distFile.close();
}

//destructor
Tortoise::~Tortoise()
{
}

//tortoise class functions
int Tortoise::getTortoisePosition()
{
	return tortiosePosition;
}

int Tortoise::getTotalCount()
{
	return tortoiseTotalMoveCounter;
}

void Tortoise::tortoiseMove()
{
	//randomly selecting which move the tortoise will use
	moveSelect = rand() % 9 + 0;
	//changing tortoises position on course after move is used
	tortiosePosition = tortiosePosition + moveDist[moveSelect];
	//checking if tortoise is at negative position and correcting back to 0
	if (tortiosePosition < 0)
	{
		tortiosePosition = 0;
	}
	//checking if tortoise position is above win condition
	//and setting it to win condition so that its symbol
	//doesn't affect other text outputs
	if (tortiosePosition > 20)
	{
		tortiosePosition = 20;
	}
	//incrementing to total amount of moves used by the tortoise
	tortoiseTotalMoveCounter++;
	//setting move description depending on what move is used
	moveDescription = moveList[moveSelect];
}

std::string Tortoise::getOpening()
{
	return moveOpening;
}

std::string Tortoise::getDescription()
{
	return moveDescription;
}