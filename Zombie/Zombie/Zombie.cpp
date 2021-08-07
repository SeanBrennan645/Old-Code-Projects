#include "Zombie.h"

Zombie::Zombie()
{
	//sets symbol
	setName('Z');
}

Zombie::~Zombie()
{
}

void Zombie::moveUp()
{
	//record previous position
	setPrev();
	changeY((-1));
	//checking if zombie is about to exit bounds from top
	if (getYPos() == 0)
	{
		//moving the zombie 1 down instead of 1 up
		changeY(2);
	}
	//outputting new position
	Console::setColour(Console::GREEN);
	outPos();
	Console::setColour(Console::WHITE);
	//delete the output on previous position
	clearPrev();
}

void Zombie::moveDown(int gridSize)
{
	//record previous position
	setPrev();
	changeY(1);
	//checking if zombie is about to exit bounds from bottom
	if (getYPos() == (gridSize + 1))
	{
		//moving the zombie 1 up instead of 1 down
		changeY((-2));
	}
	//outputting new position
	Console::setColour(Console::GREEN);
	outPos();
	Console::setColour(Console::WHITE);
	//delete the output on previous position
	clearPrev();
}

void Zombie::moveLeft()
{
	//record previous position
	setPrev();
	changeX((-1));
	//checking if zombie is about to exit bounds from left
	if (getXPos() == 0)
	{
		//moving zombie 1 right instead of 1 left
		changeX(2);
	}
	//outputting new position
	Console::setColour(Console::GREEN);
	outPos();
	Console::setColour(Console::WHITE);
	//delete the output on previous position
	clearPrev();
}

void Zombie::moveRight(int gridSize)
{
	//record previous position
	setPrev();
	changeX(1);
	//checking if zombie is about to exit bounds from right
	if (getXPos() == (gridSize + 1))
	{
		//moving zombie 1 left instead of 1 right
		changeX((-2));
	}
	//outputting new position
	Console::setColour(Console::GREEN);
	outPos();
	Console::setColour(Console::WHITE);
	//delete the output on previous position
	clearPrev();
}

void Zombie::randomMovement(int vertOrHorz, int upDownLeftRight, int gridSize)
{
		//if vertOrHorz equals 1 moves on y axis if 2 x axis

		//y axis movement
		if (vertOrHorz == 0)
		{
			//if upDownLeftRight equals 0 moves up if 1 moves down

		    //up movement
			if (upDownLeftRight == 0)
			{
				moveUp();
			}
			//down movement
			if (upDownLeftRight == 1)
			{
				moveDown(gridSize);	
			}
		}
		//x axis movement
		else if (vertOrHorz == 1)
		{
			//if upDownLeftRight equals 0 moves left if 1 moves right

			//left movement
			if (upDownLeftRight == 0)
			{
				moveLeft();
			}
			//right movement
			if (upDownLeftRight == 1)
			{
				moveRight(gridSize);
			}
		}
}

void Zombie::chasePlayer(int gridSize, int playerY, int playerX, int zombieRadius)
{
	//positive=player is to the right and negative means left
	int playerDistX = (playerX - getXPos());
	//positive=player is below and negative above
	int playerDistY = (playerY - getYPos());
	//checking if player is outside of zombie radius
	if (abs(playerDistX) > zombieRadius)
	{
		//doing normal random movement
		int vertOrHorz = rand() / (RAND_MAX / 2);
		int upDownLeftRight = rand() / (RAND_MAX / 2);
		randomMovement(vertOrHorz, upDownLeftRight, gridSize);
	}
	else if (abs(playerDistY > zombieRadius))
	{
		//doing normal random movement
		int vertOrHorz = rand() / (RAND_MAX / 2);
		int upDownLeftRight = rand() / (RAND_MAX / 2);
		randomMovement(vertOrHorz, upDownLeftRight, gridSize);
	}
	//checking if both are less than radius
	else if ((abs(playerDistX) && abs(playerDistY)) <= zombieRadius)
	{
		//checking if x distance is greater than the y
		if (abs(playerDistX) > abs(playerDistY))
		{
			//checking if difference is positive
			if (playerDistX > 0)
			{
				moveRight(gridSize);
			}
			//if difference is negative
			else if (playerDistX < 0)
			{
				moveLeft();
			}
		}
		//checking if y distance is greater than the x
		else if (abs(playerDistY) > abs(playerDistX))
		{
			//checking if difference is positive
			if (playerDistY > 0)
			{
				moveDown(gridSize);
			}
			//if difference is negative
			else if (playerDistY < 0)
			{
				moveUp();
			}
		}
		//checking if the player distance on x and y are equal
		else if (playerDistX == playerDistY)
		{
			//if distances are equal horizontal or vertical movement is decided randomly
			int vertOrHorz = rand() / (RAND_MAX / 2);
			if (vertOrHorz == 0)
			{
				//checking if difference is positive
				if (playerDistX > 0)
				{
					moveRight(gridSize);
				}
				//if difference is negative
				else if (playerDistX < 0)
				{
					moveLeft();
				}
			}
			if (vertOrHorz == 1)
			{
				//checking if difference is positive
				if (playerDistY > 0)
				{
					moveDown(gridSize);
				}
				//if difference is negative
				else if (playerDistY < 0)
				{
					moveUp();
				}
			}
		}
	}
	//if the distance betwwen player and zombie on x axis is within the radius
	else if (abs(playerDistX) <= zombieRadius)
	{
		//checking if difference is positive
		if (playerDistX > 0)
		{
			moveRight(gridSize);
		}
		//if difference is negative
		else if (playerDistX < 0)
		{
			moveLeft();
		}
	}
	else if (abs(playerDistY) <= zombieRadius)
	{
		//checking if difference is positive
		if (playerDistY > 0)
		{
			moveDown(gridSize);
		}
		//if difference is negative
		else if (playerDistY < 0)
		{
			moveUp();
		}
	}
}

//checks that the zombie doesn't spawn on top of the player
void Zombie::checkSpawnPlayer(int playerY, int playerX, int gridSize)
{
	while (playerY == getYPos() && playerX == getXPos())
	{
		setPos(gridSize);
	}
}