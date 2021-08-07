#ifndef CHARACTER_H_
#define CHARACTER_H_
#include <iostream>
#include "console.h"
class Character
{
private:
	int status;
	int position[2];
	char name;
	int prevPosition[2];
public:
	int checkStatus();
	int getXPos();
	int getYPos();
	int getPrevY();
	int getPrevX();
	void kill();
	void clearPrev();
	void setPrev();
	void changeX(int x);
	void changeY(int y);
	void outPos();
	void setName(char n);
	void setPos(int bounds);
	char getName();
	void checkFallInManhole(int manholeYPos, int manholeXPos);
	Character();
	~Character();
};
#endif