#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include "console.h"
#include "Character.h"
#include "Player.h"
#include "Zombie.h"
#include "Manhole.h"
#include "Surviviour.h"

using namespace std;

void drawGrid(int size);

void game(int size, int difficulty);

void info();

/*note: I normally leave out std:: when using cin/cout 
but was getting error messages for this project*/
int main()
{
	Console::setWindowTitle("Zombie Island");
	Console::setWindowSize(750, 700);
	Console::setColour(Console::WHITE);
	srand(static_cast<int>(time(NULL)));
	rand();
	int playerSelect = 0;
	int mapSelect = 0;
	int difficulty = 0;
	while (playerSelect!=3)
	{
		//outputting for player to make a decision
		std::cout << "Enter in the corresponding number to select" << endl << endl;
		std::cout << "1. Start Game" << endl;
		std::cout << "2. Information" << endl;
		std::cout << "3. Close Down" << endl;
		//player enters their decision
		std::cin >> playerSelect;
		//checking for valid input
		while (playerSelect < 1 || playerSelect>3)
		{
			//outputting error and asking for new input
			Console::clear();
			Console::setCursorPosition(0, 0);
			std::cout << "Please enter a valid intput" << endl << endl;
			std::cout << "1. Start Game" << endl;
			std::cout << "2. Information" << endl;
			std::cout << "3. Close Down" << endl;
			std::cin >> playerSelect;
		}
		//player selects to play the game
		if (playerSelect == 1)
		{
			//asks player to choose the size of the map
			Console::clear();
			Console::setCursorPosition(0, 0);
			std::cout << "Select a map size" << endl << endl;
			//small is 20x20 grid
			std::cout << "1. Small" << endl;
			//medium is 30x30 grid
			std::cout << "2. Medium" << endl;
			//large is 40x40 grid
			std::cout << "3. Large" << endl;
			//player decides the size of the map
			std::cin >> mapSelect;
			//checking for valid input
			while (mapSelect < 1 || mapSelect>3)
			{
				//outputting error and asking for new input
				Console::clear();
				Console::setCursorPosition(0, 0);
				std::cout << "Please enter a valid map size" << endl << endl;
				std::cout << "1. Small" << endl;
				std::cout << "2. Medium" << endl;
				std::cout << "3. Large" << endl;
				std::cin >> mapSelect;
			}
			//asks player to choose the difficulty setting
			Console::clear();
			Console::setCursorPosition(0, 0);
			std::cout << "Select a difficulty" << endl << endl;
			//easy spawns length of grid/2 amount of zombies
			std::cout << "1. Easy" << endl;
			//hard spawns amount of zombies equal to length of grid
			std::cout << "2. Hard" << endl;
			std::cin >> difficulty;
			//checks for valid input
			while (difficulty < 1 || difficulty>2)
			{
				//outputting error and asking for new input
				Console::clear();
				Console::setCursorPosition(0, 0);
				std::cout << "Please enter a valid difficulty setting" << endl << endl;
				std::cout << "1. Easy" << endl;
				std::cout << "2. Hard" << endl;
				std::cin >> difficulty;
			}
			Console::clear();
			//run game taking in the map size and difficulty setting
			game(mapSelect, difficulty);
		}
		//bringing user to information screen
		else if (playerSelect == 2)
		{
			Console::clear();
			info();
		}
	}
	return 0;
}

void game(int size, int difficulty)
{
	//intialising variables to be used later
	string playerName;
	string mapSize;
	string setting;
	string outcome;
	int pointsLost = 0;
	int zombieRadius = 0;
	int score = 0;
	int winBonus = 0;
	int manholeNo = 0;
	int trappedSurviviours = 0;
	//setting base zombie death bonus and loss penalties
	int killBonus = 100;
	int boundsManholeLoss = 10000;
	int eatenScoreLost = 5000;
	//asking for users name to be stored later
	std::cout << "Enter your name:" << endl;
	std::cin >> playerName;
	Console::clear();
	/*setting the size of the grid based of players selection
	also setting the base score based on the map size
	also setting the base win bonus
	setting score
	setting num of manholes
	setting the number of trapped survivors
	setting string of map size to be stored in file*/
	int gridSize = 0;
	//small map
	if (size == 1)
	{
		gridSize = 20;
		score = 100000;
		manholeNo = 10;
		winBonus = 10000;
		trappedSurviviours = 4;
		mapSize = "Small map";
	}
	//medium map
	else if (size == 2)
	{
		gridSize = 30;
		score = 200000;
		manholeNo = 16;
		winBonus = 20000;
		trappedSurviviours = 8;
		mapSize = "Medium map";
	}
	//large map
	else if (size == 3)
	{
		gridSize = 40;
		score = 300000;
		manholeNo = 26;
		winBonus = 30000;
		trappedSurviviours = 12;
		mapSize = "Large map";
	}
	/*setting number of zombies easy = gridsize/2 hard = gridsize
	setting distance zombies can detect player
	setting string of difficulty to be stored in file later*/
	int zombieSize = 0;
	//easy difficulty
	if (difficulty == 1)
	{
		zombieSize = gridSize / 2;
		//adjusting score to half its base score
		score = score / 2;
		zombieRadius = 5;
		setting = "Easy";
	}
	//hard difficulty
	else if (difficulty == 2)
	{
		zombieSize = gridSize;
		//increasing the win bonus
		winBonus = winBonus * 2;
		//increasing the bonus for each zombie that dies
		killBonus = killBonus * 2;
		zombieRadius = 7;
		//lowering the amount of trapped survivors 
		trappedSurviviours = trappedSurviviours / 2;
		//lowering the amount of manholes
		manholeNo == manholeNo / 2;
		setting = "Hard";
	}
	drawGrid(gridSize);
	//creating and outputting player
	Console::setColour(Console::WHITE);
	Player p;
	p.setPos(gridSize);
	p.outPos();
	//creating and outputting manholes
	vector<Manhole> m(manholeNo);
	for (int i = 0; i < manholeNo; i++)
	{
		//making sure manholes don't spawn on player
		m[i].spawnManhole(p.getYPos(), p.getXPos(), gridSize);
	}
	//creating and outputting zombies
	vector<Zombie> z(zombieSize);
	char ch = 0;
	for (int i = 0; i < zombieSize; i++)
	{
		z[i].setPos(gridSize);
		//checking that zombies don't spawn on player
		z[i].checkSpawnPlayer(p.getYPos(), p.getXPos(), gridSize);
		Console::setColour(Console::GREEN);
		z[i].outPos();
	}
	//setting variable to be updated which keeps track of how many zombies are alive
	int zombiesRemaining = zombieSize;
	//creating and outputting surviviours
	vector<Surviviour> s(trappedSurviviours);
	for (int i = 0; i < trappedSurviviours; i++)
	{
		s[i].setPos(gridSize);
		for (int j = 0; j < zombieSize; j++)
		{
			//checking that survivors don't spawn on other elements
			s[i].checkSpawn(p.getYPos(), p.getXPos(), gridSize);
			s[i].checkZombies(z[j].getYPos(), z[j].getXPos(), gridSize);
			for (int k = 0; k < manholeNo; k++)
			{
				s[i].checkManholes(m[k].getYPos(), m[k].getXPos(), gridSize);
			}
		}
		//rechecking that they haven't spawned on player so they don't have unfair advantage
		s[i].checkSpawn(p.getYPos(), p.getXPos(), gridSize);
		Console::setColour(Console::AQUA);
		s[i].outPos();
	}
	//outputting players current score
	Console::setColour(Console::WHITE);
	Console::setCursorPosition(10, gridSize + 5);
	std::cout << "Score:" << score;
	//outputting the number of zombies that are still alive
	Console::setCursorPosition(12, gridSize + 5);
	std::cout << "Zombies remaining:" << zombiesRemaining;
	//outputting players hp/group size
	Console::setCursorPosition(14, gridSize + 5);
	std::cout << "Current group size:" << p.getHp();
	//when win=1 when all zombies die, win=2 player died and lost
	int win = 0;
	//stores how the player died, 1=zombie, 2=manhole, 3=bounds
	int killedBy = 0;
	//message that will be outputted when game is over
	string endMessage;
	while (win == 0)
	{
		ch = _getch();
		p.setPrev();
		/*player movement using wasd
    	each time player moves score goes down by 100*/
		switch (ch)
		{
		case 'w':
			p.changeY((-1));
			p.outPos();
			p.clearPrev();
			score = score - 100;
			break;
		case 's':
			p.changeY(1);
			p.outPos();
			p.clearPrev();
			score = score - 100;
			break;
		case 'a':
			p.changeX((-1));
			p.outPos();
			p.clearPrev();
			score = score - 100;
			break;
		case 'd':
			p.changeX(1);
			p.outPos();
			p.clearPrev();
			score = score - 100;
			break;
		}
		//checking if surviviour is saved
		for (int i = 0; i < trappedSurviviours; i++)
		{
			p.savedSurvivor(s[i].getYPos(), s[i].getXPos());
			if (s[i].checkStatus() == 1)
			{
				s[i].checkIfSaved(p.getYPos(), p.getXPos());
				s[i].relocate();
				//reoutputting player is surviviour is saved
				if (s[i].checkStatus() == 0)
				{
					Console::setCursorPosition(s[i].getPrevY(), s[i].getPrevX());
					std::cout << "P";
					score = score + 250;
				}
			}
		}
		//updating hp
		Console::setCursorPosition(14, gridSize + 5);
		std::cout << "Current group size:" << p.getHp();
		//zombie movement
		for (int i = 0; i < zombieSize; i++)
		{
			//checking if zombie is alive so player can't be killed by already dead zombies
			if (z[i].checkStatus() == 1)
			{
				//random movement when there are more than half of original zombies
				if (zombiesRemaining > (zombieSize / 2))
				{
					int vertOrHorz = rand() / (RAND_MAX / 2);
					int upDownLeftRight = rand() / (RAND_MAX / 2);
					z[i].randomMovement(vertOrHorz, upDownLeftRight, gridSize);
				}
				/*once half of zombies are dead
				zombies are able to chase player at certain distances*/
				else if (zombiesRemaining <= (zombieSize / 2))
				{
					z[i].chasePlayer(gridSize, p.getYPos(), p.getXPos(), zombieRadius);	
				}
				/*checking if player is on a previous zombie position
				this prevents the player symbol from being deleted during zombie movement*/
				if ((p.getYPos() == z[i].getPrevY()) && (p.getXPos() == z[i].getPrevX()))
				{
					Console::setCursorPosition(p.getYPos(), p.getXPos());
					Console::setColour(Console::WHITE);
					std::cout << 'P';
				}
				//checking if zombie has fallen into a manhole
				for (int j = 0; j < manholeNo; j++)
				{
					z[i].checkFallInManhole(m[j].getYPos(), m[j].getXPos());
				}
				//lowering zombie count when killed by manhole
				if (z[i].checkStatus() == 0)
				{
					zombiesRemaining = zombiesRemaining - 1;
					Console::setCursorPosition(z[i].getYPos(), z[i].getXPos());
					//reoutputting sign for manhole incase its been erased by zombie walking onto it
					Console::setColour(Console::LIGHT_YELLOW);
					std::cout << 'O';
					Console::setColour(Console::WHITE);
				}
				//checking if player and zombie are on the same position
				if ((p.getYPos() == z[i].getYPos()) && (p.getXPos() == z[i].getXPos()))
				{
					//if player has collected other survivors
					if (p.getHp() > 1)
					{
						//killing zombie and lowering count
						z[i].kill();
						zombiesRemaining = zombiesRemaining - 1;
						//reoutputting player symbol
						Console::setColour(Console::WHITE);
						Console::setCursorPosition(z[i].getYPos(), z[i].getXPos());
						std::cout << 'P';
						//removing zombie from map
						z[i].changeX((-z[i].getXPos()));
						z[i].changeY((-z[i].getYPos()));
						//lowering value of players hp/groupsize
						p.hpTaken();
					}
				}
			}
		}
		//updating hp
		Console::setCursorPosition(14, gridSize + 5);
		std::cout << "Current group size:" << p.getHp();
		//checking if trapped survivors have been killed by zombies
		for (int i = 0; i < trappedSurviviours; i++)
		{
			//only checks if survivor is alive
			if (s[i].checkStatus() == 1)
			{
				for (int j = 0; j < zombieSize; j++)
				{
					s[i].checkIfEaten(z[j].getYPos(), z[j].getXPos());
					s[i].relocate();
				}
			}
		}
		/*checking if score has reached 0
		killing player, setting end message and win condition set to lost*/
		if (score == 0)
		{
			p.kill();
			endMessage = "Your score reached 0, you have starved to death.";
			win = 2;
		}
		//checking if player has hit the edge of grid
		p.checkBounds((gridSize + 1));
		//checking if player hit zombie 
		for (int i = 0; i < zombieSize; i++)
		{
			p.checkIfEaten(z[i].getYPos(), z[i].getXPos());
			//returning what killed player if player did die
			killedBy = p.whatKilledPlayer();
		}
		//checking if player fell in manhole
		for (int i = 0; i < manholeNo; i++)
		{
			//only checks if player is alive beforehand
			if (p.checkStatus() == 1)
			{
				p.checkFallInManhole(m[i].getYPos(), m[i].getXPos());
				/*if player is dead at this point the only thing they could've
				been killed by is a manhole*/
				if (p.checkStatus() == 0)
				{
					killedBy = 2;
				}
			}
		}
		//updating players score
		Console::setCursorPosition(10, gridSize + 5);
		//needed to clear zeros at end when score reaches lower values
		std::cout << "              ";
		Console::setCursorPosition(10, gridSize + 5);
		std::cout << "Score:" << score;
		//updating number of zombies still alive
		Console::setCursorPosition(12, gridSize + 5);
		std::cout << "                             ";
		Console::setCursorPosition(12, gridSize + 5);
		std::cout << "Zombies remaining:" << zombiesRemaining;
		/*checking if all zombies are dead
		setting win condition to won, applying bonus and setting end message*/
		if (zombiesRemaining == 0)
		{
			win = 1;
			score = score + winBonus;
			endMessage = "All the zombies are dead!";
		}
		//checking if player is dead and setting win condition to lost if they are
		if (killedBy > 0)
		{
			if (killedBy == 1)
			{
				endMessage = "You were eaten by a zombie.";
				score = score - eatenScoreLost;
				pointsLost = eatenScoreLost;
			}
			else if (killedBy == 2)
			{
				endMessage = "You fell into a manhole and died.";
				score = score - boundsManholeLoss;
				pointsLost = boundsManholeLoss;
			}
			else if (killedBy == 3)
			{
				endMessage = "You were killed by the nuclear radiation.";
				score = score - boundsManholeLoss;
				pointsLost = boundsManholeLoss;
			}
			win = 2;
		}
	};
	Console::clear();
	//player has won
	if (win == 1)
	{
		//outputting win message, win bonus and final score
		std::cout << endMessage << endl;
		std::cout << "You get a bonus of " << winBonus << " points" << endl;
		std::cout << "Your final score was " << score << endl;
		Console::setColour(Console::LIGHT_GREEN);
		Console::pause("Congratulations you have won!!!");
		outcome = "Won Game";
	}
	//player has lost
	if (win == 2)
	{
		//outputting lost meassage, penalty and final score
		std::cout << endMessage << endl;
		std::cout << "You lose an extra " << pointsLost << " points" << endl;
		std::cout << "Your final score was " << score << endl;
		Console::setColour(Console::RED);
		Console::pause("You Lose");
		outcome = "Lost Game";
	}
	//writing player name, score, map size and difficulty to file
	string line;
	ofstream scoreFile("ScoreLogFile.txt",ios::app);
	scoreFile << playerName << " " << score << " " << mapSize << " " << setting << " " << outcome << endl;
	scoreFile.close();
	Console::setColour(Console::WHITE);
	Console::clear();
	//returns user to menu screen
}

void drawGrid(int size)
{
	Console::setCursorPosition(0, 0);
	Console::setColour(Console::RED);
	//drawing grid on top horizontal
	for (int i = 0; i < size + 3; i++)
	{
		std::cout << "X";
	}
	//drawing bottom horizontal
	Console::setCursorPosition(size+1, 0);
	for (int i = 0; i < size + 3; i++)
	{
		std::cout << "X";
	}
	//drawing left vertical
	for (int i = 0; i < size+1; i++)
	{
		Console::setCursorPosition(i + 1, 0);
		std::cout << "X";
	}
	//drawing right vertical
	for (int i = 0; i < size+1; i++)
	{
		Console::setCursorPosition(i + 1, size + 2);
		std::cout << "X";
	}
}

void info()
{
	Console::setColour(Console::WHITE);
	//outputting what each symbol represents
	std::cout << "Key:" << endl;
	std::cout << "P = Player" << endl;
	Console::setColour(Console::GREEN);
	std::cout << "Z ";
	Console::setColour(Console::WHITE);
	std::cout << "= Zombie" << endl;
	Console::setColour(Console::LIGHT_YELLOW);
	std::cout << "O ";
	Console::setColour(Console::WHITE);
	std::cout << "= Manhole" << endl;
	Console::setColour(Console::AQUA);
	std::cout << "S ";
	Console::setColour(Console::WHITE);
	std::cout << "= Trapped Survivor" << endl;
	Console::setColour(Console::RED);
	std::cout << "X ";
	Console::setColour(Console::WHITE);
	std::cout << "= Nuclear radiation" << endl << endl;
	//reading information about game from file and outputting to user
	string line;
	ifstream infoFile("Info.txt");
	if (infoFile.is_open())
	{
		while (getline(infoFile, line))
		{
			std::cout << line << endl;
		}
		infoFile.close();
	}
	else
	{
		std::cout << "Error unable to open Info.txt" << endl;
	}
	std::cout << endl;
	Console::pause("Press any key to return to menu");
	Console::clear();
}