#include "mouseIsland.h"

using namespace std;


//constructor--location
Location::Location(int X, int Y)
{
    this -> X = X;
    this -> Y = Y;
}

//sets X variable
void Location::setX(int X)
{
    this -> X = X;
}

//sets Y variable
void Location::setY(int Y)
{
    this -> Y = Y;
}

//returns X
int Location::getX()
{
    return X;
}

//returns Y
int Location::getY()
{
    return Y;
}

//deconstructo--Location
Location::~Location()
{
    X = 0;
    Y = 0;
}

//constructor--character
Character::Character()
{
    name = " ";
    X = 0;
    Y = 0;
    dead = false;
    starvation = 0;
}

//set name variable
void Character::setName(string name)
{
    this -> name = name;
}

//set X variable
void Character::setX(int x)
{
    this -> X = x;
}

//set Y variable
void Character::setY(int y)
{
    this -> Y = y;
}

//set Dead Variable
void Character::setDead(bool dead)
{
    this -> dead = dead;
}

//set Starvation variable
void Character::setStarvation(int turn)
{
    if(turn < 100)
    {
        starvation++;
    }
    if(turn == 100)
    {
        dead = true;
    }
}

//return name variable
string Character::getName()
{
    return name;
}

//return X variable
int Character::getX()
{
    return X;
}

//return Y variable
int Character::getY()
{
    return Y;
}

//return dead variable
bool Character::getDead()
{
    return dead;
}

//return starvation variable
int Character::getStarvation()
{
    return starvation;
}

//deconstructor--character
Character::~Character()
{
    name = " ";
    X = 0;
    Y = 0;
    dead = false;
    starvation = 0;
}

//constructor--summary
Summary::Summary()
{
    gameNumber = 0;
    endOfGame = "";
}

//set gameNumber variable
void Summary::setGameNumber(int gameNumber)
{
    this -> gameNumber = gameNumber;
}

//set endOfGame variable
void Summary::setEndOfGame(string endOfGame)
{
    this -> endOfGame = endOfGame;
}

//returns gameNumber
int Summary::getGameNumber()
{
    return gameNumber;
}

//returns endOfGame variable
string Summary::getEndOfGame()
{
    return endOfGame;
}

//deconstructor--summary
Summary::~Summary()
{
    gameNumber = 0;
    endOfGame = "";
}

//write out to file
void writeOut(string outFileName,string mapName, int timesRan, int seed, vector <Summary> summaryTable,int board[20][20],int height, int width)
{
    //ofstream oFile(outFileName.c_str());

    ofstream oFile("outFile.txt");

    if (oFile.is_open())
    {
         oFile << mapName << endl
              << timesRan << endl
              << seed << endl << endl;

        oFile << "Game Endings" << endl;
        for(int a = 0; a < summaryTable.size();a++)
        {
            oFile << "Game " << summaryTable[a].getGameNumber()
                  << ": " << summaryTable[a].getEndOfGame() << endl;
        }

        oFile << endl << endl;

        oFile << "Frequency Map" << endl << " ";
        for(int b =0;b < width-1;b++)
        {
            oFile << "----";
        }
        oFile << endl;

       for(int y = 0; y < height; y++)
        {
            oFile << " | ";
            for(int x = 0; x < width-1; x++)
            {
               oFile << board[x][y] << " | ";
            }
            oFile << endl;
        }
        oFile << " ";
        for(int z = 0; z < width-1; z++)
        {
            oFile << "----";
        }
        oFile << endl;

        oFile.close();
    }
    else
    {
        cout << "Error opening file.";
    }
}

//returns length of board
int lengthOfBoard(string line)
{
    int length = 0;
    int charCounter = 0;
    int startingChar = 0;//first position of non-space character
    bool startFound = false;
    string multipleDigits = "";

    //skip all blanks in line
    for(int i = 0; i < line.length(); i++)
    {
        if(line[i] != ' ')
        {
            multipleDigits = multipleDigits + line[i];
            if(startFound == false)
            {
                startingChar = i;
                startFound = true;
            }
            charCounter++;
        }
    }

    if(charCounter == 1)
        length = changeCharToInt(line[startingChar]);
    else
        length = changeStringToInt(multipleDigits);

    return length;
}

//returns width of board
int widthOfBoard(string line)
{
    int width = 0;
    int charCounter = 0;
    int startingChar = 0;//first position of non-space character
    bool startFound = false;
    string multipleDigits = "";

    //skip all blanks in line
    for(int i = 0; i < line.length(); i++)
    {
        if(line[i] != ' ')
        {
            multipleDigits = multipleDigits + line[i];
            if(startFound == false)
            {
                startingChar = i;
                startFound = true;
            }
            charCounter++;
        }
    }

    if(charCounter == 1)
        width = changeCharToInt(line[startingChar]);
    else
        width = changeStringToInt(multipleDigits);

    return width;
}

//changes string to number
int changeStringToInt(string line)
{
    istringstream buffer(line);
    int value;
    buffer >> value;

    return value;
}

//change char to number
int changeCharToInt(char line)
{
    switch(line)
    {
        case '0':
            return 0;
            break;
        case '1':
            return 1;
            break;
        case '2':
            return 2;
            break;
        case '3':
            return 3;
            break;
        case '4':
            return 4;
            break;
        case '5':
            return 5;
            break;
        case '6':
            return 6;
            break;
        case '7':
            return 7;
            break;
        case '8':
            return 8;
            break;
        case '9':
            return 9;
            break;
    }
}

//find first non blank space in line and return position in line
int findFirstChar(string line)
{
    for(int i = 0; i < line.length(); i++)
    {
        if(line[i] != ' ')
        {
            return i;
            break;
        }
    }
}

//initialize waterVector with positions
void initializeWaterVector(string line,vector <Location> &waterVector, int width)
{
    int start = findFirstChar(line);
    int numToPush = 0;
    vector <int> convertedNumbers;
    string multiChar = "";
    int counter = 0;

    for(int i = start; i < line.length(); i++)
    {
        if(line[i] != ' ' && line[i+1] == ' ')
        {
            numToPush = changeCharToInt(line[i]);
            convertedNumbers.push_back(numToPush);
        }
        else if(line[i] != ' ' && line[i+1] != ' ')
        {
            counter = i;
            while(line[counter] != ' ')
            {
                multiChar = multiChar + line[counter];
                counter++;
            }
            numToPush = changeStringToInt(multiChar);
            convertedNumbers.push_back(numToPush);
        }
    }

    for(int a = 0; a < convertedNumbers.size();a++)
    {
        for(int x = 0; x < width; x++)
        {
            Location newLocation(x,convertedNumbers[a]);
            waterVector.push_back(newLocation);
        }
    }

    return;
}

//initialize bridgeVector with positions
void initializeBridgeVector(string line,vector <Location> &bridgeVector,int height,int width)
{
    int start = findFirstChar(line);
    int numToPush = 0;
    vector <int> convertedNumbers;
    int counter = 0;
    string multiChar = "";

    for(int i = start; i < line.length(); i++)
    {
        if(line[i] != ' ' && line[i+1] == ' ')
        {
            numToPush = changeCharToInt(line[i]);
            convertedNumbers.push_back(numToPush);
        }
        else if(line[i] != ' ' && line[i+1] != ' ')
        {
            multiChar = line[i] + line[i+1];
            numToPush = changeStringToInt(multiChar);
            convertedNumbers.push_back(numToPush);
        }
    }

    for(int a = 0; a < convertedNumbers.size();)
    {
        Location newLocation(convertedNumbers[a],convertedNumbers[a+1]);
        bridgeVector.push_back(newLocation);
        a++;
        a++;
    }

    return;
}

//initialize foodVector with positions
void initializeFoodVector(string line,vector <Location> &foodVector)
{
    int start = findFirstChar(line);
    int numToPush = 0;
    vector <int> convertedNumbers;
    int counter = 0;
    string multiChar = "";

    for(int i = start; i < line.length(); i++)
    {
        if(line[i] != ' ' && line[i+1] == ' ')
        {
            numToPush = changeCharToInt(line[i]);
            convertedNumbers.push_back(numToPush);
        }
        else if(line[i] != ' ' && line[i+1] != ' ')
        {
            multiChar = line[i] + line[i+1];
            numToPush = changeStringToInt(multiChar);
            convertedNumbers.push_back(numToPush);
        }
    }

    for(int a = 0; a < convertedNumbers.size();)
    {
        Location newLocation(convertedNumbers[a],convertedNumbers[a+1]);
        foodVector.push_back(newLocation);
        a++;
        a++;
    }

    return;
}

//initialize mouseHoleVector with positions
void initializeMouseHoleVector(string line,vector <Location> &mouseHoleVector)
{
    int start = findFirstChar(line);
    int numToPush = 0;
    vector <int> convertedNumbers;
    int counter = 0;
    string multiChar = "";

    for(int i = start; i < line.length(); i++)
    {
        if(line[i] != ' ' && line[i+1] == ' ')
        {
            numToPush = changeCharToInt(line[i]);
            convertedNumbers.push_back(numToPush);
        }
        else if(line[i] != ' ' && line[i+1] != ' ')
        {
            multiChar = line[i] + line[i+1];
            numToPush = changeStringToInt(multiChar);
            convertedNumbers.push_back(numToPush);
        }
    }

    for(int a = 0; a < convertedNumbers.size();)
    {
        Location newLocation(convertedNumbers[a],convertedNumbers[a+1]);
        mouseHoleVector.push_back(newLocation);
        a++;
        a++;
    }

    return;
}


//set board with values from inFile
void setBoardWithFileValues(int board[20][20],vector <Location> waterVector, vector <Location> bridgeVector,
                            vector <Location> foodVector,vector <Location> mouseHoleVector,int height,int width,
                            Character cat, Character mouse)
{
    int X = 0;
    int Y = 0;

    for(int a = 0; a < waterVector.size();a++)
    {
        X = waterVector[a].getX();
        Y = waterVector[a].getY();

        if(X <= width && Y <= height)
        {
            board[X][Y] = -1;
        }
    }

    for(int b = 0; b < bridgeVector.size();b++)
    {
        X = bridgeVector[b].getX();
        Y = bridgeVector[b].getY();

        if(X >= 0 && X <= width && Y >= 0 && Y <= height)
        {
            board[X][Y] = 0;
        }
    }

    for(int c = 0; c < foodVector.size(); c++)
    {
        X = foodVector[c].getX();
        Y = foodVector[c].getY();

        if(X >= 0 && X <= width && Y >= 0 && Y <= height)
        {
            board[X][Y] = 3;
        }
    }

    for(int d = 0; d < mouseHoleVector.size(); d++)
    {
        X = mouseHoleVector[d].getX();
        Y = mouseHoleVector[d].getY();

        if(X >= 0 && X <= width && Y >= 0 && Y <= height)
        {
            board[X][Y] = 4;
        }
    }

    if(mouse.getX() >= 0 && mouse.getX() <= width &&
       mouse.getY() >= 0 && mouse.getY() <= height)
    {
        board[mouse.getX()][mouse.getY()] = 1;
    }

    if(cat.getX() >= 0 && cat.getX() <= width &&
       cat.getY() >= 0 && cat.getY() <= height)
    {
        board[cat.getX()][cat.getY()] = 2;
    }


    return;
}


void clearScreen()
{
    for(int y = 0; y < 20; y++)
    {
        for(int x = 0; x < 20; x++)
        {
            cout << " ";
        }
        cout << endl;
    }

    return;
}

void printBoard(int board[20][20], int height, int width)
{
    cout << " ";
    for(int a = 0; a < width-1; a++)
    {
        cout << "----";
    }
    cout << endl;

    for(int y = 0; y < height; y++)
    {
        cout << " | ";
        for(int x = 0; x < width-1; x++)
        {
            if(board[x][y] == -1)
            {
                cout << "W";
            }
            else if(board[x][y] == 1)
            {
                cout << "M";
            }
            else if(board[x][y] == 2)
            {
                cout << "C";
            }
            else if(board[x][y] == 3)
            {
                cout << "F";
            }
            else if(board[x][y] == 4)
            {
                cout << "H";
                if(x == width)
                    cout << " |";
            }
            else
            {
                cout << " ";
            }
           // cout << board[x][y];
            cout << " | ";
        }
        cout << endl << " ";
        for(int z = 0; z < width-1; z++)
        {
            cout << "----";
        }
        cout << endl;
    }

    cout << endl << endl << endl << endl;
}


//adds to each space if the mouse is on it
//does not reset every game
void testForFrequency(int board[20][20], int frequencyBoard[20][20],int height,int width)
{
    for(int y = 0; y < height;y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(board[x][y] == 1)
            {
                frequencyBoard[x][y]++;
                return;
            }
        }
    }
}

//change mouse x and y
void moveMouse(int board[20][20], int height,int width, Character &mouse,Character cat, string &gameOver)
{
    int direction = rand() % 4 + 1;
    int oldX = mouse.getX();
    int oldY = mouse.getY();

    switch(direction)
    {
        case 1://up
            if(mouse.getY() - 1 >= 0)
            {
                board[mouse.getX()][mouse.getY()] = 0;
                mouse.setY(mouse.getY() - 1);
                break;
            }
        case 2://down
            if(mouse.getY() + 1 <= height)
            {
                board[mouse.getX()][mouse.getY()] = 0;
                mouse.setY(mouse.getY() + 1);
                break;
            }
        case 3://left
            if(mouse.getX() - 1 >= 0)
            {
                board[mouse.getX()][mouse.getY()] = 0;
                mouse.setX(mouse.getX() - 1);
                break;
            }
        case 4://right
            if(mouse.getX() + 1 <= width-1)
            {
                cout << "right" << endl;
                board[mouse.getX()][mouse.getY()] = 0;
                mouse.setX(mouse.getX() + 1);
                break;
            }
    }

    if(board[mouse.getX()][mouse.getY()] == 3)//food
    {
        mouse.setStarvation(0);
        board[mouse.getX()][mouse.getY()] = 1;
    }
    else
    {
        mouse.setStarvation(mouse.getStarvation() + 1);
        return;
    }

    if(board[mouse.getX()][mouse.getY()] == -1)//drown
    {
        board[mouse.getX()][mouse.getY()] = -1;
        mouse.setDead(true);
        gameOver = "Mouse drowned";
        return;
    }

    if(mouse.getX() == cat.getX() && mouse.getY() == cat.getY() && board[mouse.getX()][mouse.getY()] != 4)//eaten
    {
        mouse.setDead(true);
        gameOver = "Cat ate mouse";
        return;
    }

    if(board[mouse.getX()][mouse.getY()] == 0 &&
       board[mouse.getX()][mouse.getY()-1] == -1 && board[mouse.getX()][mouse.getY()+1] == -1)
    {
        mouse.setDead(true);
        gameOver = "Mouse escaped island";
        return;
    }

    if(board[mouse.getX()][mouse.getY()] == 0 &&
       board[mouse.getX()+1][mouse.getY()] == -1 && board[mouse.getX()-1][mouse.getY()] == -1)
    {
        mouse.setDead(true);
        gameOver = "Mouse escaped island";
        return;
    }

}

//change character x and y
void moveCat(int board[20][20],int height,int width, Character &cat, Character mouse)
{
    int direction = rand() % 4 + 1;
    int catX = cat.getX();
    int catY = cat.getY();
    bool mouseInHole = false;

    if(board[mouse.getX()][mouse.getY()] == 4)
    {
        mouseInHole == true;
    }

    switch(direction)
    {
        case 1://up
            catY = catY - 1;
            break;
        case 2://down
            catY = catY + 1;
            break;
        case 3://left
            catX = catX - 1;
            break;
        case 4://right
            catX = catX + 1;
            break;
    }


    switch(direction)
    {
        case 1://up
            if(cat.getY() - 1 >= 0 && board[cat.getX()][cat.getY()-1] != -1)
            {
                if(board[cat.getX()][cat.getY()-1] == -1)
                    break;
                else
                {
                    if(board[cat.getX()][cat.getY()-1] == 0)
                    {
                        board[cat.getX()][cat.getY()] = 0;
                        cat.setY(cat.getY() - 1);
                        break;
                    }
                    else
                    {
                        cat.setY(cat.getY() - 1);
                        break;
                    }
                }
            }
        case 2://down
            if(cat.getY() + 1 <= height && board[cat.getX()][cat.getY()+1] != -1)
            {
                if(board[cat.getX()][cat.getY() + 1] == -1)
                    break;
                else
                {
                    if(board[cat.getX()][cat.getY() + 1] == 0)
                    {
                        board[cat.getX()][cat.getY()] = 0;
                        cat.setY(cat.getY() + 1);
                        break;
                    }
                    else
                    {
                        cat.setY(cat.getY() + 1);
                        break;
                    }
                }
            }
        case 3://left
            if(cat.getX() - 1 >= 0)
            {
                if(board[cat.getX()-1][cat.getY()] == -1)
                    break;
                else
                {
                    if(board[cat.getX()-1][cat.getY()] == 0)
                    {
                        board[cat.getX()][cat.getY()] = 0;
                        cat.setX(cat.getX() - 1);
                        break;
                    }
                    else
                    {
                        cat.setX(cat.getX() - 1);
                        break;
                    }
                }
            }
        case 4://right
            if(cat.getX() + 1 <= width)
            {
                if(board[cat.getX()+1][cat.getY()] == -1)
                    break;
                else
                {
                    if(board[cat.getX()+1][cat.getY()] == 0)
                    {
                        board[cat.getX()][cat.getY()] = 0;
                        cat.setX(cat.getX() + 1);
                        break;
                    }
                    else
                    {
                        cat.setX(cat.getX() + 1);
                        break;
                    }
                }
            }
    }
    return;
}

//change board values
void changeBoardValues(int board[20][20],Character cat, Character mouse)
{
    int X = 0;
    int Y = 0;

    if (mouse.getDead() == false)
    {
        X = mouse.getX();
        Y = mouse.getY();

        board[X][Y] = 1;
    }

    if(cat.getDead() == false)
    {
        X = cat.getX();
        Y = cat.getY();

        board[X][Y] = 2;
    }

    return;
}


//check if either cat or mouse is dead
bool checkForDeath(int board[20][20],Character cat, Character mouse, string &reasonForDeath)
{
    int catX = cat.getX();
    int catY = cat.getY();
    int mouseX = mouse.getX();
    int mouseY = mouse.getY();

    //mouse crosses bridge
    bool mouseOnMap = false;
    for(int a = 0; a < 20; a++)
    {
        for(int b = 0; b < 20; b++)
        {
            if(board[a][b] == 1)
            {
                mouseOnMap = true;
                break;
            }
        }
    }

    //cat crossed bridge
    bool catOnMap = false;
    for(int y = 0; y < 20; y++)
    {
        for(int x = 0; x < 20; x++)
        {
            if(board[x][y] == 2)
            {
                catOnMap == true;
                break;
            }
        }
    }

    //cat and mouse on same space without mouse hole
    if(catX == mouseX && catY == mouseY && board[catX][catY] != 4)
    {
        reasonForDeath = "Cat ate mouse";
        mouse.setDead(true);
        return true;
    }
    //mouse entered water
    else if(board[mouseX][mouseY] == -1)
    {
        reasonForDeath = "Mouse drowned";
        mouse.setDead(true);
        return true;
    }
    else if(mouseOnMap == false)
    {
        reasonForDeath == "Mouse got off the island";
        return true;
    }
    //mouse starves
    else if(mouse.getStarvation() == 100)
    {
        reasonForDeath = "Mouse starved";
        mouse.setDead(true);
        return true;
    }
    /*else if(mouse.getStarvation() < 100 && catOnMap == false)
    {
        reasonForDeath = "Cat Left Island! Mouse Survived!";
        return true;
    }*/
    else
    {
        return false;
    }
    /*  if(board[mouse.getX()][mouse.getY()] == 3 || board[mouse.getX()][mouse.getY()] == 0)//food
    {
        board[mouse.getX()][mouse.getY()] = 1;
    }
    else
    {
        mouse.setStarvation(mouse.getStarvation() + 1);
        return;
    }

    if(board[mouse.getX()][mouse.getY()] == -1)//drown
    {
        mouse.setDead(true);
        gameOver = "Mouse drowned";
        return;
    }


    if(mouse.getX() == cat.getX() && mouse.getY() == cat.getY() && board[mouse.getX()][mouse.getY()] != 4)//eaten
    {
        mouse.setDead(true);
        gameOver = "Cat ate mouse";
        return;
    }

    if(board[mouse.getX()][mouse.getY()] == 0 &&
       board[mouse.getX()][mouse.getY()-1] == -1 && board[mouse.getX()][mouse.getY()+1] == -1)
    {
        mouse.setDead(true);
        gameOver = "Mouse escaped island";
        return;
    }

    if(board[mouse.getX()][mouse.getY()] == 0 &&
       board[mouse.getX()+1][mouse.getY()] == -1 && board[mouse.getX()-1][mouse.getY()] == -1)
    {
        mouse.setDead(true);
        gameOver = "Mouse escaped island";
        return;
    }*/
}
