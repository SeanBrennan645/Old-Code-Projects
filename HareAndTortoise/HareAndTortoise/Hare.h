#ifndef HARE_H_
#define HARE_H_
#include <iostream>
#include <fstream>
#include <string>
class Hare
{
private:
	//randomly selected number used to decide which move is used
	int moveSelect;
	//hare position on course
	int harePosition;
	//total amount of moves used by hare
	int hareTotalMoveCounter;
	//array of moves and how they affect position
	int moveDist[10]{};
	//used at start of output of which move was used
	std::string moveOpening;
	//list of move descriptions
	std::string moveList[10]{};
	//used to output which move is used
	std::string moveDescription;
public:
	Hare();
	~Hare();
	//function deciding which move is used and
	//sets move description to appropriate text
	void hareMove();
	//getters
	int getHarePosition();
	int getTotalCount();
	std::string getOpening();
	std::string getDescription();
};
#endif