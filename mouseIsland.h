#ifndef itemh_H
#define itemh_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

class Location
{
public:
    Location(int X, int Y);
    void setX(int X);
    void setY(int Y);
    int getX();
    int getY();
    ~Location();
private:
    int X;
    int Y;
};


class Character
{
public:
    Character();
    void setName(string name);
    void setX(int x);
    void setY(int y);
    void setDead(bool dead);
    void setStarvation(int turn);
    string getName();
    int getX();
    int getY();
    bool getDead();
    int getStarvation();
    ~Character();
private:
    string name;
    int X;
    int Y;
    bool dead;
    int starvation;
};

class Summary
{
public:
    Summary();
    void setGameNumber(int gameNumber);
    void setEndOfGame(string endOfGame);
    int getGameNumber();
    string getEndOfGame();
    ~Summary();
private:
    int gameNumber;
    string endOfGame;
};

//write out to file
void writeOut(string outFileName,string mapName, int timesRan, int seed, vector <Summary> summaryTable,
              int board[20][20], int height, int width);

//write tests to test file for classes
void testLocationClass(Location testLocation,ofstream &oFile);
void testCharacterClass(Character testCharacter,ofstream &oFile);
void testSummaryClass(Summary testSummary,ofstream& oFile);
void testVectors(vector <Location> waterVector, vector <Location> bridgeVector,
                 vector <Location> foodVector, vector <Location> mouseHoleVector,
                 vector <Summary> gameEndingsVector,ofstream & oFile);

//returns length of board
int lengthOfBoard(string line);
//returns width of board
int widthOfBoard(string line);
//changes string to number
int changeStringToInt(string line);
//change char to number
int changeCharToInt(char line);
//find first non blank space in line and return position in line
int findFirstChar(string line);

//initialize all vectors with positions
void initializeWaterVector(string line,vector <Location> &waterVector,int width);
void initializeBridgeVector(string line,vector <Location> &bridgeVector,int height,int width);
void initializeFoodVector(string line,vector <Location> &foodVector);
void initializeMouseHoleVector(string line,vector <Location> &mouseHoleVector);

//set board with values from inFile
void setBoardWithFileValues(int board[20][20],vector <Location> waterVector, vector <Location> bridgeVector,
                            vector <Location> foodVector,vector <Location> mouseHoleVector,int height,int width,
                            Character cat, Character mouse);

//clears screen
void clearScreen();

//print board
void printBoard(int board[20][20], int height, int width);

//adds to each space if the mouse is on it
//does not reset every game
void testForFrequency(int board[20][20], int frequencyBoard[20][20],int height, int width);

//move character
void moveMouse(int board[20][20],int height,int width, Character &mouse,Character cat,string &gameOver);
void moveCat(int board[20][20],int height,int width, Character &cat, Character mouse);

//change board values
void changeBoardValues(int board[20][20],Character cat, Character mouse);

//check if either cat or mouse is dead
bool checkForDeath(int board[20][20],Character cat, Character mouse, string &reasonForDeath);

#endif // itemh_H
