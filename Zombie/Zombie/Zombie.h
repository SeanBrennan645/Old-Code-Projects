#ifndef ZOMBIE_H_
#define ZOMBIE_H_
#include "Character.h"
#include <iostream>
class Zombie : public Character
{	
public:
	Zombie();
	~Zombie();
	void moveUp();
	void moveDown(int gridSize);
	void moveLeft();
	void moveRight(int gridSize);
	void randomMovement(int vertOrHorz, int upDownLeftRight, int gridSize);
	void checkSpawnPlayer(int playerY, int playerX, int gridSize);
	void chasePlayer(int gridsize, int playerY, int playerX, int radius);
};
#endif