#ifndef TORTOISE_H_
#define TORTOISE_H_
#include <iostream>
#include <fstream>
#include <string>
class Tortoise
{
private:
	//randomly selected number used to decide which move is used
	int moveSelect;
	//tortoise position on course
	int tortiosePosition;
	//total amount of moves used by tortoise
	int tortoiseTotalMoveCounter;
	//array of moves and how they affect position
	int moveDist[10]{};
	//used at start of output of which move was used
	std::string moveOpening;
	//list of move descriptions
	std::string moveList[10]{};
    //used to output which move is used
	std::string moveDescription;
public:
	//constructor and destructor
	Tortoise();
	~Tortoise();
	//function deciding which move is used and
	//sets move description to appropriate text
	void tortoiseMove();
	//getters
	int getTortoisePosition();
	int getTotalCount();
	std::string getOpening();
	std::string getDescription();
};
#endif