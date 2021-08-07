#include "Hare.h"

//constructor
Hare::Hare()
{
	harePosition = 0;
	hareTotalMoveCounter = 0;
	moveOpening = "Hare used ";
	//reading data from hare txt file and storing in arrays
	int fileInt;
	std::string fileString;
	std::ifstream distFile("hare.txt");
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
		std::cout << "ERROR UNABLE TO OPEN hare.txt";
	}
	distFile.close();
}

//Destructor
Hare::~Hare()
{
}

//hare class functions
int Hare::getHarePosition()
{
	return harePosition;
}

int Hare::getTotalCount()
{
	return hareTotalMoveCounter;
}

void Hare::hareMove()
{
	//randomly selecting which move the hare will use
	moveSelect = rand() % 9 + 0;
	//changing hares position on course after move is used
	harePosition = harePosition + moveDist[moveSelect];
	//checking if hare is at negative position and correcting back to 0
	if (harePosition < 0)
	{
		harePosition = 0;
	}
	//checking if hare position is above win condition
	//and setting it to win condition so that its symbol
	//doesn't affect other text outputs
	if (harePosition > 20)
	{
		harePosition = 20;
	}
	//incrementing to total amount of moves used by the hare
	hareTotalMoveCounter++;
	//setting move description depending on what move is used
	moveDescription = moveList[moveSelect];
}

std::string Hare::getOpening()
{
	return moveOpening;
}

std::string Hare::getDescription()
{
	return moveDescription;
}