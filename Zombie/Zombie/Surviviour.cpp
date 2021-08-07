#include "Surviviour.h"

Surviviour::Surviviour()
{
	//sets symbol
	setName('S');
}

Surviviour::~Surviviour()
{
}

//checks if zombie has killed survivor
void Surviviour::checkIfEaten(int zombieYPos, int zombieXPos)
{
	if ((zombieYPos == getYPos()) && (zombieXPos == getXPos()))
	{
		kill();
	}
}

//checks if player has saved  survivor
void Surviviour::checkIfSaved(int playerYPos, int playerXPos)
{
	if ((playerYPos == getYPos()) && (playerXPos == getXPos()))
	{
		kill();
	}
}

void Surviviour::relocate()
{
	/*when status is set to 0 surviors coordinates are set to 0,0
	this removes them from the map so the player can't pick
	up several survivors from one position*/
	if (checkStatus() == 0)
	{
		setPrev();
		clearPrev();
		changeX((-getXPos()));
		changeY((-getYPos()));
	}
}

//checks that survivor hasn't spawned on a manhole
void Surviviour::checkManholes(int manholeY, int manholeX, int gridSize)
{
	while ((manholeY == getYPos()) && (manholeX == getXPos()))
	{
		setPos(gridSize);
	}
}

//checks that survivor hasn't spawned on a zombie
void Surviviour::checkZombies(int zombieY, int zombieX, int gridSize)
{
	while ((zombieY == getYPos()) && (zombieX == getXPos()))
	{
		setPos(gridSize);
	}
}

//checks that survivor hasn't spawned on player
void Surviviour::checkSpawn(int playerYPos, int playerXPos, int gridSize)
{
	while ((playerYPos == getYPos()) && (playerXPos == getXPos()))
	{
		setPos(gridSize);
	}
}