#ifndef MANHOLE_H_
#define MANHOLE_H_
#include <iostream>
#include "console.h"
class Manhole
{
private:
	int position[2];
	char symbol;
public:
	Manhole();
	~Manhole();
	void spawnManhole(int playerY, int playerX, int gridSize);
	int getYPos();
	int getXPos();
};
#endif