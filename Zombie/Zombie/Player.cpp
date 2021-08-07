#include "Player.h"

//constructor
Player::Player()
{
	//setting symbol and groupsize/hp to 1
	setName('P');
	killedBy = 0;
	hp = 1;
}

Player::~Player()
{
}

//checking if either position is outside bounds
void Player::checkBounds(int bounds)
{
	if (getXPos() == 0 || getXPos() == bounds)
	{
		//kills player and sets value to represent what killed them
		kill();
		killedBy = 3;
	}
	if (getYPos() == 0 || getYPos() == bounds)
	{
		kill();
		killedBy = 3;
	}
}

//checking if player was killed by a zombie
void Player::checkIfEaten(int zombieYPos, int zombieXPos)
{
	if ((zombieYPos == getYPos()) && (zombieXPos == getXPos()))
	{
		//player will only die if hp/groupsize is 1
		if (hp == 1)
		{
			kill();
			killedBy = 1;
		}
	}
}

//checking if player has saved a survivor
void Player::savedSurvivor(int surviveYPos, int surviveXPos)
{
	if ((surviveYPos == getYPos()) && (surviveXPos == getXPos()))
	{
		//increasing hp/groupsize by 1
		hp = hp + 1;
	}
}

//lowers hp/groupsize by 1
void Player::hpTaken()
{
	hp = hp - 1;
}

//getters
int Player::getHp()
{
	return hp;
}

int Player::whatKilledPlayer()
{
	return killedBy;
}