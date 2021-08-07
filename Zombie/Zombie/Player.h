#ifndef PLAYER_H_
#define PLAYER_H_
#include "Character.h"
class Player : public Character
{
private:
	int killedBy;
	int hp;
public:
	Player();
	~Player();
	void savedSurvivor(int surviveYPos, int surviveXPos);
	int getHp();
	void checkBounds(int bounds);
	void checkIfEaten(int zombieYPos, int zombieXPos);
	void hpTaken();
	int whatKilledPlayer();
};
#endif