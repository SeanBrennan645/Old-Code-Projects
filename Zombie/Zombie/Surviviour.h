#ifndef SURVIVOUR_H_
#define SURVIVOUR_H_
#include "Character.h"
class Surviviour : public Character
{
public:
	Surviviour();
	~Surviviour();
	void checkIfEaten(int zombieYPos, int zombieXPos);
	void checkIfSaved(int playerYPos, int playerXPos);
	void relocate();
	void checkSpawn(int playerY, int playerX, int gridSize);
	void checkManholes(int manholeY, int manholeX, int gridSize);
	void checkZombies(int zombieY, int zombieX, int gridSize);
};
#endif