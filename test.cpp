#include "mouseIsland.h"

using namespace std;

void testLocationClass(Location testLocation,ofstream &oFile)
{
    //ofstream oFile("test.txt");

    oFile << "Test getX: " << testLocation.getX() << endl;
    oFile << "Test getY: " << testLocation.getY() << endl;

    testLocation.setX(5);
    testLocation.setY(7);

    oFile << "Test getX after setX: " << testLocation.getX() << endl;
    oFile << "Test getY after setY: " << testLocation.getY() << endl;

    oFile << endl << endl;

}


void testCharacterClass(Character testCharacter,ofstream &oFile)
{
//    ofstream oFile("test.txt");

    oFile << "Test Character name: ";
    testCharacter.setName("Cat");
    oFile << testCharacter.getName() << endl;

    oFile << "Test Character X: ";
    testCharacter.setX(2);
    oFile << testCharacter.getX() << endl;

    oFile << "Test Character Y: ";
    testCharacter.setY(1);
    oFile << testCharacter.getY() << endl;

    oFile << "Test Character dead: ";
    testCharacter.setDead(true);
    oFile << testCharacter.getDead() << endl;

    oFile << "Test Character dead: ";
    testCharacter.setDead(false);
    oFile << testCharacter.getDead() << endl;

    oFile << "Test Character starvation: ";
    testCharacter.setStarvation(20);
    oFile << testCharacter.getStarvation() << endl;

    oFile << endl << endl;

    return;
}

void testSummaryClass(Summary testSummary,ofstream &oFile)
{
    oFile << "Test getGameNumber: " << testSummary.getGameNumber() << endl;
    oFile << "Test getEndOfGame: " << testSummary.getEndOfGame() << endl << endl;

    testSummary.setGameNumber(3);
    testSummary.setEndOfGame("Mouse drowned");

    oFile << "Test getGameNumber: " << testSummary.getGameNumber() << endl;
    oFile << "Test getEndOfGame: " << testSummary.getEndOfGame() << endl << endl;
}



void testVectors(vector <Location> waterVector, vector <Location> bridgeVector, vector <Location> foodVector,
                 vector <Location> mouseHoleVector,vector <Summary> gameEndingsVector,ofstream &oFile)
{
//    ofstream oFile("test.txt");

    oFile << "Test waterVector: " << endl;
    for(int a = 0; a < waterVector.size(); a++)
    {
        oFile << a << ". X: " << waterVector[a].getX() << endl
              << "    Y: " << waterVector[a].getY() << endl;
    }

    oFile << endl << endl;

    oFile << "Test bridgeVector: " << endl;
    for(int b = 0; b < bridgeVector.size();b++)
    {
        oFile << b << ". X: " << bridgeVector[b].getX() << endl
              << "   Y: " << bridgeVector[b].getY() << endl;
    }

    oFile << endl << endl;

    oFile << "Test foodVector: " << endl;
    for(int c = 0; c < foodVector.size(); c++)
    {
        oFile << c << ". X: " << foodVector[c].getX() << endl
              << "   Y: " << foodVector[c].getY() << endl;
    }

    oFile << endl << endl;

    oFile << "Test mouseHoleVector: " << endl;
    for(int d = 0; d < mouseHoleVector.size(); d++)
    {
        oFile << d << ". X: " << mouseHoleVector[d].getX() << endl
              << "   Y: " << mouseHoleVector[d].getY() << endl;
    }

    oFile << endl << endl;

    oFile << "Test gameEndingsVector: " << endl;
    for(int e = 0; e < gameEndingsVector.size();e++)
    {
        oFile << "Game " << gameEndingsVector[e].getGameNumber() << "      "
              << gameEndingsVector[e].getEndOfGame() << endl;
    }

    return;
}
