#include "Character.h"

//constructor
Character::Character()
{
	//setting status to alive
	status = 1;
}

Character::~Character()
{
}

void Character::setPos(int bounds)
{
	//giving the character random x & y positions
	position[0] = rand() % bounds + 1;
	position[1] = rand() % bounds + 1;
}

void Character::clearPrev()
{
	//removing the output from the previous position of character
	Console::setCursorPosition(prevPosition[0], prevPosition[1]);
	std::cout << " ";
}

void Character::setPrev()
{
	//making a note of the previous position of the character
	prevPosition[0] = position[0];
	prevPosition[1] = position[1];
}

void Character::changeX(int x)
{
	//changing the x position
	position[1] = position[1] + x;
}

void Character::changeY(int y)
{
	//changing the y position
	position[0] = position[0] + y;
}

char Character::getName()
{
	return name;
}

void Character::outPos()
{
	//Used to output where character is on grid
	Console::setCursorPosition(position[0], position[1]);
	std::cout << name;
}

int Character::checkStatus()
{
	//checks if the character is alive
	return status;
}

void Character::kill()
{
	//sets the characters status to dead
	status = 0;
}

void Character::setName(char n)
{
	//used to set the letter that will represent the character
	name = n;
}

//getters
int Character::getXPos()
{
	return position[1];
}

int Character::getYPos()
{
	return position[0];
}

int Character::getPrevX()
{
	return prevPosition[1];
}

int Character::getPrevY()
{
	return prevPosition[0];
}

//check for death on manhole
void Character::checkFallInManhole(int manholeYPos, int manholeXPos)
{
	if (manholeYPos == getYPos() && manholeXPos == getXPos())
	{
		kill();
	}
}