#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "console.h"
#include "Hare.h"
#include "Tortoise.h"

using namespace std;

//function headers for drawing course and outputting a victory screen
void drawCourse(int y, int x, int length, char course, int &harePos,
	int &tortoisePos);

void victoryScreen(int y, int length, int &win, int &hareCount,
	int &tortoiseCount);

int main()
{
	//setting basic random num generator things
	srand(static_cast<int>(time(NULL)));
	rand();
	//creating hare and tortoise classes
	Hare h;
	Tortoise t;
	//creating win condition to end while loop, if win=1 then hare wins
	//win=2 then tortoise wins
	int win = 0;
	//drawing course at start of game
	int harePos = h.getHarePosition();
	int tortoisePos = t.getTortoisePosition();
	drawCourse(5, 4, 20, '-', harePos, tortoisePos);
	//outputting what the game will do when the game is started
	Console::setCursorPosition(0, 0);
	Console::setColour(Console::WHITE);
	cout << "When the game is started the hare and the tortoise will race" << endl;
	cout << "The character that goes first will be randomly decided" << endl;
	//asking player to guess who will win the race
	int guess = 0;
	cout << "Guess who will win the race, 1=Hare and 2=Tortoise" << endl;
	cin >> guess;
	//checking for valid input
	while (guess < 1 || guess > 2)
	{
		//output and asking for new value
		Console::setCursorPosition(3, 0);
		cout << "Error invalid input, try again ";
		//in place of a console clear to delete previous incorrect output
		//in case user enters multiple incorrect answers
		Console::setCursorPosition(3, 32);
		cout << "          ";
		Console::setCursorPosition(3, 32);
		cin >> guess;
	}
	//randomly deciding which character goes first
	int whichTurn = rand() % 2;
	//when whichTurn=0 it is the hares move and when =1 it is the tortoises move
	//countdown for race to start after user enters their guess
	for (int i = 0; i < 3; i++)
	{
		Console::clear();
		Console::setCursorPosition(2, 2);
		Console::setColour(Console::WHITE);
		cout << "Race will begin in " << 3 - i;
		drawCourse(5, 4, 20, '-', harePos, tortoisePos);
		//sleep occurs every second (is measured in milliseconds)
		Sleep(1000);
	}
	//loop for race
	while (win == 0)
	{
		//clears start game prompt and removes text
		//from move description from previous turn
		Console::clear();
		Console::setColour(Console::WHITE);
		//hares move and swapping condition for tortoise move next loop
		if (whichTurn == 0)
		{
			h.hareMove();
			//checking if hare has completed the race
			if (h.getHarePosition() == 20)
			{
				win = 1;
			}
			//output move hare used
			Console::setCursorPosition(7, 4);
			cout << h.getOpening() << h.getDescription();
			//changing condition so it's tortoises move next loop
			whichTurn = 1;
		}
		//tortoise move and swapping condition for hare move next loop
		else if (whichTurn == 1)
		{
			t.tortoiseMove();
			//checking if tortoise has completed the race
			if (t.getTortoisePosition() == 20)
			{
				win = 2;
			}
			//output move tortoise used
			Console::setCursorPosition(7, 4);
			cout << t.getOpening() << t.getDescription();
			//changing condition so it's tortoises move next loop
			whichTurn = 0;
		}
		//re-drawing course with new position of characters
		harePos = h.getHarePosition();
		tortoisePos = t.getTortoisePosition();
		drawCourse(5, 4, 20, '-', harePos, tortoisePos);
		Sleep(1750);
	}
	//outputting victory/end screen
	int hareCount = h.getTotalCount();
	int tortoiseCount = t.getTotalCount();
	victoryScreen(5, 20, win, hareCount, tortoiseCount);
	//outputting whether player correctly guessed the winner
	Console::setCursorPosition(9, 4);
	if (guess == win)
	{
		cout << "Congratulations you correctly guessed the winner!" << endl;
	}
	else
	{
		cout << "Sorry you did not correctly guess the winner" << endl;
	}
	Console::setCursorPosition(11, 4);
	//end of program
	Console::pause("The race has finished");
	return 0;
}

//function to draw course with positions of characters
void drawCourse(int y, int x, int length, char course, int &harePos, int &tortoisePos)
{
	//drawing the race track base
	Console::setCursorPosition(y, x);
	for (int i = 0; i < length; i++)
	{
		cout << course;
	}
	//if hare and tortoise are in the same position
	if (harePos == tortoisePos)
	{
		Console::setCursorPosition(y, x + harePos);
		Console::setColour(Console::LIGHT_PURPLE);
		cout << "B";
	}
	//hare and tortoise are in different positions
	else
	{
		//outputting location of hare on race track
		Console::setCursorPosition(y, x + harePos);
		Console::setColour(Console::LIGHT_AQUA);
		cout << "H";
		//outputting location of tortoise on race track
		Console::setCursorPosition(y, x + tortoisePos);
		Console::setColour(Console::GREEN);
		cout << "T";
		//resetting text colour to back to white
		Console::setColour(Console::WHITE);
	}
	//writing what each symbol represents to bottom of screen
	Console::setCursorPosition(13, 4);
	Console::setColour(Console::LIGHT_PURPLE);
	cout << "B ";
	Console::setColour(Console::WHITE);
	cout << "means that both characters are on the same position";
	Console::setCursorPosition(14, 4);
	Console::setColour(Console::LIGHT_AQUA);
	cout << "H ";
	Console::setColour(Console::WHITE);
	cout << "shows the position of the Hare";
	Console::setCursorPosition(15, 4);
	Console::setColour(Console::GREEN);
	cout << "T ";
	Console::setColour(Console::WHITE);
	cout << "shows the position of the Tortoise";
}

//function to output victory screen
void victoryScreen(int y, int length, int &win, int &hareCount, int &tortoiseCount)
{
	//if hare won the race
	if (win == 1)
	{
		//outputting that the hare is the winner of the race
		Console::setCursorPosition(y, 8 + length);
		Console::setColour(Console::YELLOW);
		cout << "HARE IS THE WINNER!";
		//resetting the text colour back to white
		Console::setColour(Console::WHITE);
		//creating file to output details about winner when hare wins 
		ofstream winnerFile;
		winnerFile.open("winner.txt");
		//writing that hare won to file and the total amount
		//of moves used by hare
		winnerFile << "The hare won the race" << endl;
		winnerFile << "Hare used a total of " << hareCount << " moves";
		winnerFile.close();
	}
	//if tortoise won the race
	else if (win == 2)
	{
		//outputting that the tortoise is the winner of the race
		Console::setCursorPosition(y, 8 + length);
		Console::setColour(Console::YELLOW);
		cout << "TORTOISE IS THE WINNER!";
		//resetting the text colour back to white
		Console::setColour(Console::WHITE);
		//creating file to output details about winner when tortoise wins
		ofstream winnerFile;
		winnerFile.open("winner.txt");
		//writing that tortoise won to file and the total amount
		//of moves used by tortoise
		winnerFile << "The tortoise won the race" << endl;
		winnerFile << "Tortoise used a total of " << tortoiseCount << " moves";
		winnerFile.close();
	}
}