#include "mouseIsland.h"

using namespace std;

int main()
{
    string inFileName;
    string outFileName;
    string line;
    string mapName;
    string reasonForDeath;

    char firstCharInLine;

    int lineCounter = 1;
    int timesToRun = 0;
    int timesRan = 0;
    int turnsPerGame = 0;
    int seedNumber = (time(NULL));
    srand(seedNumber);

    int height = 0;
    int width = 0;
    int startingX = 0;
    int startingY = 0;

    vector <Location> waterVector;
    vector <Location> bridgeVector;
    vector <Location> foodVector;
    vector <Location> mouseHoleVector;
    vector <Summary> gameEndingsVector;

    Character mouse;
    mouse.setName("M");
    Character cat;
    cat.setName("C");

    bool gameOver = false;

    //file to read
   // cout << "File name: ";
    //cin >> inFileName;

    //ifstream iFile(inFileName.c_str());
    ifstream iFile;
    iFile.open("inFile.txt");

    if (iFile.fail())
    {
        cout << "Error opening file";
    }
    else
    {
        while(!iFile.eof())
        {
            getline(iFile,line);
            switch(lineCounter)
            {
                case 1://name
                    mapName = line;
                    lineCounter++;
                    break;
                case 2://how many times to run
                    timesToRun = changeStringToInt(line);
                    lineCounter++;
                    break;
                case 3://length of array
                    height = lengthOfBoard(line);
                    height++;
                    lineCounter++;
                    break;
                case 4://width of array
                    width = widthOfBoard(line);
                    width++;
                    lineCounter++;
                    break;
                case 5://rows with water
                    initializeWaterVector(line,waterVector,width);
                    lineCounter++;
                    break;
                case 6://positions of bridges
                    initializeBridgeVector(line,bridgeVector,height,width);
                    lineCounter++;
                    break;
                case 7://mouse starting
                    firstCharInLine = findFirstChar(line);
                    startingX = changeCharToInt(line[firstCharInLine]);
                    startingY = changeCharToInt(line[firstCharInLine + 2]);//+ 2 allows for 1 space inbetween
                    mouse.setX(startingX);
                    mouse.setY(startingY);
                    lineCounter++;
                    break;
                case 8://cat starting
                    firstCharInLine = findFirstChar(line);
                    startingX = changeCharToInt(line[firstCharInLine]);
                    startingY = changeCharToInt(line[firstCharInLine + 2]);//+ 2 allows for 1 space inbetween
                    cat.setX(startingX);
                    cat.setY(startingY);
                    lineCounter++;
                    break;
                case 9://positions food
                    initializeFoodVector(line,foodVector);
                    lineCounter++;
                    break;
                case 10://mouse holes
                    initializeMouseHoleVector(line,mouseHoleVector);
                    lineCounter++;
                    break;
            }
        }
        iFile.close();
    }

    //file to write to
    //cout << "File name: ";
    //cin >> outFileName;


    int board[20][20];
    int frequencyBoard[20][20];

    for(int y = 0; y < 20; y++)
    {
        for(int x = 0; x < 20; x++)
        {
            board[x][y] = 0;
            frequencyBoard[x][y] = 0;
        }
    }


    if(height <= 20 && width <= 20)
    {
        for(int i = timesRan; i < timesToRun; i++)
        {
            setBoardWithFileValues(board,waterVector,bridgeVector,foodVector,mouseHoleVector,height,width,cat,mouse);
            printBoard(board,height,width);
            testForFrequency(board,frequencyBoard,height,width);

            while(turnsPerGame < 100)
            {
                cout << "Game " << i+1 << ": turn " << turnsPerGame << endl;
                cout << "Starvation: " << mouse.getStarvation() << endl;

                moveCat(board,height,width,cat,mouse);
                moveMouse(board,height,width,mouse,cat,reasonForDeath);
                changeBoardValues(board,cat,mouse);
                printBoard(board,height,width);
                system("PAUSE");
                //clearScreen();
                testForFrequency(board,frequencyBoard,height,width);
                gameOver = checkForDeath(board,cat,mouse,reasonForDeath);
                turnsPerGame++;

                if(gameOver == true)
                    break;
                if(turnsPerGame == 101)
                    break;
                if(mouse.getDead() == true)
                    break;
                if(cat.getDead() == true)
                    break;
            }

            cout << reasonForDeath << endl << endl;
            system("PAUSE");

            Summary newSummary;
            newSummary.setEndOfGame(reasonForDeath);
            newSummary.setGameNumber(i+1);

            gameEndingsVector.push_back(newSummary);

            gameOver = false;
            turnsPerGame = 0;
            mouse.setDead(false);
            cat.setDead(false);
            reasonForDeath = "";
            timesRan++;
            mouse.setStarvation(0);
        }

        writeOut(outFileName,mapName,timesRan,seedNumber,gameEndingsVector,frequencyBoard,height,width);
    }
    else
    {
        if(height > 20)
        {
            cout << "Height cannot be greater than 20" << endl;
        }
        if(width < 20)
        {
            cout << "Width cannot be greater than 20" << endl;
        }
//        writeOut(outFileName,0,0,0,gameEndingsVector,frequencyBoard,height,width);
    }


    //write tests
    ofstream testFile("test.txt");

    Location testLocation(0,0);
    testLocationClass(testLocation,testFile);

    Character testChar;
    testCharacterClass(testChar,testFile);

    Summary testSum;
    testSummaryClass(testSum,testFile);

    testVectors(waterVector,bridgeVector,foodVector,mouseHoleVector,gameEndingsVector,testFile);


    return 0;
}
