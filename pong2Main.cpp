#include "pong2.h"

using namespace std;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

void loadTexture();

//Frees media and shuts down SDL
void close();

void writeTest(Ball gameBall, Paddle rPaddle, Paddle lPaddle);

void checkCollision(Ball &gameBall,Paddle rPaddle, Paddle lPaddle, SDL_Rect ballRect);

void moveAfterCollision(Ball &gameBall, bool rightPaddleBlocked, bool leftPaddleBlocked, bool topWallBlocked, bool bottomWallBlocked,
                        Paddle rPaddle, Paddle lPaddle,SDL_Rect ballRect);

//Loads individual image
SDL_Surface* loadSurface(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//attempt to make overlapping windows
SDL_Window* ballWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

SDL_Surface* ballSurface = NULL;

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

SDL_Renderer* gRenderer = NULL;
SDL_Renderer* ballRenderer = NULL;

SDL_Texture* ballTexture = NULL;

int playerScore = 0;
int computerScore = 0;

Uint32 startTime = 0;

SDL_Rect* clip = NULL;
double angle = 0;
SDL_Point* center = NULL;
SDL_RendererFlip flip = SDL_FLIP_NONE;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}

		//create 2nd window
        ballWindow = gWindow;
        if(ballWindow == NULL)
        {
            printf("Second window could not be created. %s\n", SDL_GetError());
        }
        else
        {
            ballSurface = SDL_GetWindowSurface(ballWindow);
        }
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

//	SDL_Surface* loadedSurface = IMG_Load("pong/ball.bmp");
//	if( loadedSurface == NULL )
	//{
	//	printf( "Unable to load image %s! SDL_image Error: %s\n", "png/ball.bmp", IMG_GetError() );
	//}

	return success;
}

void ScoreBoard(SDL_Renderer* gRenderer,int playerScore,int computerScore)
{
    int playerX = 350;
    int playerY = 10;
    int computerX = 250;
    int computerY = 10;

    SDL_Rect zeroSide = {-10,-10,10,30};
    SDL_Rect zeroTop = {-10,-10,20,10};
    SDL_Rect zeroRSide = {-10,-10,10,30};
    SDL_Rect zeroBottom = {10,-10,20,10};
    SDL_Rect one = {-10,-10,10,40};
    SDL_Rect twoHang {-10,-10,10,20};
    SDL_Rect twoTop = {-10,10,30,10};
    SDL_Rect twoSide = {-10,10,10,30};
    SDL_Rect twoMid = {-10,-10,20,10};
    SDL_Rect threeSide = {-10,-10,10,50};
    SDL_Rect threeLayer = {-10,-10,30,10};
    SDL_Rect fourSide = {-10,-10,10,50};
    SDL_Rect shortSide = {-10,-10,10,20};
    SDL_Rect fourLayer = {-10,-10,30,10};
    SDL_Rect fiveVertical = {-10,-10,10,30};
    SDL_Rect fiveHorizontal = {-10,-10,30,10};
    SDL_Rect sixVertical = {-10,-10,10,30};
    SDL_Rect sixHorizontal = {-10,-10,30,10};
    SDL_Rect sevenHorizontal = {-10,-10,20,10};
    SDL_Rect sevenVertical = {-10,-10,10,50};
    SDL_Rect eightSide = {-10,-10,10,50};
    SDL_Rect eightLayer = {-10,-10,30,10};
    SDL_Rect nineHorizontal = {-10,-10,20,10};
    SDL_Rect nineVertical = {-10,-10,10,50};

    SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
    switch(playerScore)
    {
        case 0:
            zeroSide.x = playerX;
            zeroSide.y = playerY;
            zeroRSide.x = playerX + 30;
            zeroRSide.y = playerY;
            zeroTop.x = playerX+10;
            zeroTop.y = 0;
            zeroBottom.x = playerX+10;
            zeroBottom.y = playerY+30;
            SDL_RenderFillRect(gRenderer,&zeroSide);
            SDL_RenderFillRect(gRenderer,&zeroRSide);
            SDL_RenderFillRect(gRenderer,&zeroTop);
            SDL_RenderFillRect(gRenderer,&zeroBottom);
            break;
        case 1:
            one.x = playerX;
            one.y = playerY;
            SDL_RenderFillRect(gRenderer,&one);
            SDL_RenderPresent(gRenderer);
            break;
        case 2:
            twoHang.x = playerX;
            twoHang.y = playerY;
            twoTop.x = playerX;
            twoTop.y = playerY;
            twoSide.x = playerX+30;
            twoSide.y = playerY;
            twoMid.x = playerX + 10;
            twoMid.y = playerY + 30;
            SDL_RenderFillRect(gRenderer,&twoHang);
            SDL_RenderFillRect(gRenderer,&twoTop);
            SDL_RenderFillRect(gRenderer,&twoSide);
            SDL_RenderFillRect(gRenderer,&twoMid);
            SDL_RenderPresent(gRenderer);
            twoSide.x = playerX;
            twoSide.y = playerY + 30;
            twoTop.x = playerX + 10;
            twoTop.y = playerY + 50;
            SDL_RenderFillRect(gRenderer,&twoSide);
            SDL_RenderFillRect(gRenderer,&twoTop);
            SDL_RenderPresent(gRenderer);
            break;
        case 3:
            threeSide.x = playerX+30;
            threeSide.y = playerY;
            SDL_RenderFillRect(gRenderer,&threeSide);
            threeLayer.x = playerX;
            threeLayer.y = playerY;
            SDL_RenderFillRect(gRenderer,&threeLayer);
            SDL_RenderPresent(gRenderer);
            threeLayer.y = playerY + 20;
            SDL_RenderFillRect(gRenderer,&threeLayer);
            SDL_RenderPresent(gRenderer);
            threeLayer.y = playerY + 40;
            SDL_RenderFillRect(gRenderer,&threeLayer);
            SDL_RenderPresent(gRenderer);
            break;
        case 4:
            fourSide.x = playerX + 30;
            fourSide.y = playerY;
            shortSide.x = playerX;
            shortSide.y = playerY;
            fourLayer.x = playerX;
            fourLayer.y = playerY+20;
            SDL_RenderFillRect(gRenderer,&fourSide);
            SDL_RenderFillRect(gRenderer,&shortSide);
            SDL_RenderFillRect(gRenderer,&fourLayer);
            SDL_RenderPresent(gRenderer);
            break;
        case5:
            fiveVertical.x = playerX;
            fiveVertical.y = playerY;
            fiveHorizontal.x = playerX;
            fiveHorizontal.y = playerY;
            SDL_RenderFillRect(gRenderer,&fiveVertical);
            SDL_RenderFillRect(gRenderer,&fiveHorizontal);
            SDL_RenderPresent(gRenderer);
            fiveHorizontal.x = playerX+10;
            fiveHorizontal.y = playerY+20;
            fiveHorizontal.w = 10;
            fiveVertical.x = playerX+20;
            fiveVertical.y = playerY+20;
            fiveVertical.h = 30;
            SDL_RenderFillRect(gRenderer,&fiveVertical);
            SDL_RenderFillRect(gRenderer,&fiveHorizontal);
            SDL_RenderPresent(gRenderer);
            fiveHorizontal.x = playerX;
            fiveHorizontal.y = playerY + 40;
            fiveHorizontal.w = 30;
            SDL_RenderFillRect(gRenderer,&fiveHorizontal);
            SDL_RenderPresent(gRenderer);
            break;
        case 6:
            sixVertical.x = playerX;
            sixVertical.y = playerY;
            sixVertical.h = 40;
            sixHorizontal.x = playerX;
            sixHorizontal.y = playerY;
            SDL_RenderFillRect(gRenderer,&sixVertical);
            SDL_RenderFillRect(gRenderer,&sixHorizontal);
            SDL_RenderPresent(gRenderer);
            sixHorizontal.x = playerX+10;
            sixHorizontal.y = playerY+20;
            sixHorizontal.w = 10;
            sixVertical.x = playerX+20;
            sixVertical.y = playerY+20;
            sixVertical.h = 30;
            SDL_RenderFillRect(gRenderer,&sixVertical);
            SDL_RenderFillRect(gRenderer,&sixHorizontal);
            SDL_RenderPresent(gRenderer);
            sixHorizontal.x = playerX;
            sixHorizontal.y = playerY + 40;
            sixHorizontal.w = 30;
            SDL_RenderFillRect(gRenderer,&sixHorizontal);
            SDL_RenderPresent(gRenderer);
            break;
        case 7:
            sevenHorizontal.x = playerX;
            sevenHorizontal.y = playerY;
            sevenVertical.x = playerX+20;
            sevenVertical.y = playerY;
            SDL_RenderFillRect(gRenderer,&sevenHorizontal);
            SDL_RenderFillRect(gRenderer,&sevenVertical);
            SDL_RenderPresent(gRenderer);
            break;
        case8:
            eightSide.x = playerX+30;
            eightSide.y = playerY;
            SDL_RenderFillRect(gRenderer,&eightSide);
            eightLayer.x = playerX;
            eightLayer.y = playerY;
            SDL_RenderFillRect(gRenderer,&eightLayer);
            SDL_RenderPresent(gRenderer);
            eightLayer.y = playerY + 20;
            SDL_RenderFillRect(gRenderer,&eightLayer);
            SDL_RenderPresent(gRenderer);
            eightLayer.y = playerY + 40;
            SDL_RenderFillRect(gRenderer,&eightLayer);
            SDL_RenderPresent(gRenderer);
            eightSide.x = playerX;
            eightSide.y = playerY;
            SDL_RenderFillRect(gRenderer,&eightSide);
            SDL_RenderPresent(gRenderer);
            break;
        case 9:
            nineHorizontal.x = playerX;
            nineHorizontal.y = playerY;
            nineVertical.x = playerX+20;
            nineVertical.y = playerY;
            SDL_RenderFillRect(gRenderer,&nineHorizontal);
            SDL_RenderFillRect(gRenderer,&nineVertical);
            SDL_RenderPresent(gRenderer);
            nineVertical.x = playerX;
            nineVertical.y = playerY;
            nineVertical.h = 30;
            nineHorizontal.x = playerX;
            nineHorizontal.y = playerY + 20;
            SDL_RenderFillRect(gRenderer,&nineHorizontal);
            SDL_RenderFillRect(gRenderer,&nineVertical);
            SDL_RenderPresent(gRenderer);
            break;
        case 10:
            one.x = playerX;
            one.y = playerY;
            SDL_RenderFillRect(gRenderer,&one);
            SDL_RenderPresent(gRenderer);
            zeroSide.x = playerX + 30;
            zeroSide.y = playerY;
            zeroRSide.x = playerX + 60;
            zeroRSide.y = playerY;
            zeroTop.x = playerX+40;
            zeroTop.y = 0;
            zeroBottom.x = playerX+40;
            zeroBottom.y = playerY+30;
            SDL_RenderFillRect(gRenderer,&zeroSide);
            SDL_RenderFillRect(gRenderer,&zeroRSide);
            SDL_RenderFillRect(gRenderer,&zeroTop);
            SDL_RenderFillRect(gRenderer,&zeroBottom);
            SDL_RenderPresent(gRenderer);
            break;
    }

     switch(computerScore)
    {
        case 0:
            zeroSide.x = computerX;
            zeroSide.y = computerY;
            zeroRSide.x = computerX + 30;
            zeroRSide.y = computerY;
            zeroTop.x = computerX+10;
            zeroTop.y = 0;
            zeroBottom.x = computerX+10;
            zeroBottom.y = computerY+30;
            SDL_RenderFillRect(gRenderer,&zeroSide);
            SDL_RenderFillRect(gRenderer,&zeroRSide);
            SDL_RenderFillRect(gRenderer,&zeroTop);
            SDL_RenderFillRect(gRenderer,&zeroBottom);
            break;
        case 1:
            one.x = computerX;
            one.y = computerY;
            SDL_RenderFillRect(gRenderer,&one);
            SDL_RenderPresent(gRenderer);
            break;
        case 2:
            twoHang.x = computerX;
            twoHang.y = computerY;
            twoTop.x = computerX;
            twoTop.y = computerY;
            twoSide.x = computerX+30;
            twoSide.y = computerY;
            twoMid.x = computerX + 10;
            twoMid.y = computerY + 30;
            SDL_RenderFillRect(gRenderer,&twoHang);
            SDL_RenderFillRect(gRenderer,&twoTop);
            SDL_RenderFillRect(gRenderer,&twoSide);
            SDL_RenderFillRect(gRenderer,&twoMid);
            SDL_RenderPresent(gRenderer);
            twoSide.x = computerX;
            twoSide.y = computerY + 30;
            twoTop.x = computerX + 10;
            twoTop.y = computerY + 50;
            SDL_RenderFillRect(gRenderer,&twoSide);
            SDL_RenderFillRect(gRenderer,&twoTop);
            SDL_RenderPresent(gRenderer);
            break;
        case 3:
            threeSide.x = computerX+30;
            threeSide.y = computerY;
            SDL_RenderFillRect(gRenderer,&threeSide);
            threeLayer.x = computerX;
            threeLayer.y = computerY;
            SDL_RenderFillRect(gRenderer,&threeLayer);
            SDL_RenderPresent(gRenderer);
            threeLayer.y = computerY + 20;
            SDL_RenderFillRect(gRenderer,&threeLayer);
            SDL_RenderPresent(gRenderer);
            threeLayer.y = computerY + 40;
            SDL_RenderFillRect(gRenderer,&threeLayer);
            SDL_RenderPresent(gRenderer);
            break;
        case 4:
            fourSide.x = computerX + 30;
            fourSide.y = computerY;
            shortSide.x = computerX;
            shortSide.y = computerY;
            fourLayer.x = computerX;
            fourLayer.y = computerY+20;
            SDL_RenderFillRect(gRenderer,&fourSide);
            SDL_RenderFillRect(gRenderer,&shortSide);
            SDL_RenderFillRect(gRenderer,&fourLayer);
            SDL_RenderPresent(gRenderer);
            break;
        case 5:
            fiveVertical.x = computerX;
            fiveVertical.y = computerY;
            fiveHorizontal.x = computerX;
            fiveHorizontal.y = computerY;
            SDL_RenderFillRect(gRenderer,&fiveVertical);
            SDL_RenderFillRect(gRenderer,&fiveHorizontal);
            SDL_RenderPresent(gRenderer);
            fiveHorizontal.x = computerX+10;
            fiveHorizontal.y = computerY+20;
            fiveHorizontal.w = 10;
            fiveVertical.x = computerX+20;
            fiveVertical.y = computerY+20;
            fiveVertical.h = 30;
            SDL_RenderFillRect(gRenderer,&fiveVertical);
            SDL_RenderFillRect(gRenderer,&fiveHorizontal);
            SDL_RenderPresent(gRenderer);
            fiveHorizontal.x = computerX;
            fiveHorizontal.y = computerY + 40;
            fiveHorizontal.w = 30;
            SDL_RenderFillRect(gRenderer,&fiveHorizontal);
            SDL_RenderPresent(gRenderer);
            break;
        case 6:
            sixVertical.x = computerX;
            sixVertical.y = computerY;
            sixVertical.h = 40;
            sixHorizontal.x = computerX;
            sixHorizontal.y = computerY;
            SDL_RenderFillRect(gRenderer,&sixVertical);
            SDL_RenderFillRect(gRenderer,&sixHorizontal);
            SDL_RenderPresent(gRenderer);
            sixHorizontal.x = computerX+10;
            sixHorizontal.y = computerY+20;
            sixHorizontal.w = 10;
            sixVertical.x = computerX+20;
            sixVertical.y = computerY+20;
            sixVertical.h = 30;
            SDL_RenderFillRect(gRenderer,&sixVertical);
            SDL_RenderFillRect(gRenderer,&sixHorizontal);
            SDL_RenderPresent(gRenderer);
            sixHorizontal.x = computerX;
            sixHorizontal.y = computerY + 40;
            sixHorizontal.w = 30;
            SDL_RenderFillRect(gRenderer,&sixHorizontal);
            SDL_RenderPresent(gRenderer);
            break;
        case 7:
            sevenHorizontal.x = computerX;
            sevenHorizontal.y = computerY;
            sevenVertical.x = computerX+20;
            sevenVertical.y = computerY;
            SDL_RenderFillRect(gRenderer,&sevenHorizontal);
            SDL_RenderFillRect(gRenderer,&sevenVertical);
            SDL_RenderPresent(gRenderer);
            break;
        case 8:
            eightSide.x = computerX+30;
            eightSide.y = computerY;
            SDL_RenderFillRect(gRenderer,&eightSide);
            eightLayer.x = computerX;
            eightLayer.y = computerY;
            SDL_RenderFillRect(gRenderer,&eightLayer);
            SDL_RenderPresent(gRenderer);
            eightLayer.y = computerY + 20;
            SDL_RenderFillRect(gRenderer,&eightLayer);
            SDL_RenderPresent(gRenderer);
            eightLayer.y = computerY + 40;
            SDL_RenderFillRect(gRenderer,&eightLayer);
            SDL_RenderPresent(gRenderer);
            eightSide.x = computerX;
            eightSide.y = computerY;
            SDL_RenderFillRect(gRenderer,&eightSide);
            SDL_RenderPresent(gRenderer);
            break;
        case 9:
            nineHorizontal.x = computerX;
            nineHorizontal.y = computerY;
            nineVertical.x = computerX+20;
            nineVertical.y = computerY;
            SDL_RenderFillRect(gRenderer,&nineHorizontal);
            SDL_RenderFillRect(gRenderer,&nineVertical);
            SDL_RenderPresent(gRenderer);
            nineVertical.x = computerX;
            nineVertical.y = computerY;
            nineVertical.h = 30;
            nineHorizontal.x = computerX;
            nineHorizontal.y = computerY + 20;
            SDL_RenderFillRect(gRenderer,&nineHorizontal);
            SDL_RenderFillRect(gRenderer,&nineVertical);
            SDL_RenderPresent(gRenderer);
            break;
        case 10:
            one.x = computerX;
            one.y = computerY;
            SDL_RenderFillRect(gRenderer,&one);
            SDL_RenderPresent(gRenderer);
            zeroSide.x = computerX + 30;
            zeroSide.y = computerY;
            zeroRSide.x = computerX + 60;
            zeroRSide.y = computerY;
            zeroTop.x = computerX+40;
            zeroTop.y = 0;
            zeroBottom.x = computerX+40;
            zeroBottom.y = computerY+30;
            SDL_RenderFillRect(gRenderer,&zeroSide);
            SDL_RenderFillRect(gRenderer,&zeroRSide);
            SDL_RenderFillRect(gRenderer,&zeroTop);
            SDL_RenderFillRect(gRenderer,&zeroBottom);
            SDL_RenderPresent(gRenderer);
            break;
    }


}

//load texture
void loadTexture()
{
    SDL_Surface* imageSurface = SDL_LoadBMP("pong/ball.bmp");
    if(imageSurface == NULL)
    {
        printf( "Error loading image%s. Error: %s\n", "pong/ball.bmp", SDL_GetError() );
    }
    else
    {
        gCurrentSurface = imageSurface;
        ballTexture = SDL_CreateTextureFromSurface(gRenderer,imageSurface);
        if(ballTexture == NULL)
        {
            printf("Error setting texture. Error: %s\n", SDL_GetError());
        }
    }
}

void close()
{
	//destroy renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyRenderer(ballRenderer);
	ballRenderer = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	SDL_DestroyWindow(ballWindow);
	ballWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void writeTest(Ball gameBall,Paddle rPaddle,Paddle lPaddle)
{
    cout << "Ball:" << endl;
    cout << "   Current X: " << gameBall.getCurrentX() << endl;
    cout << "   X of right side: " << gameBall.getCurrentX()+ gameBall.getWidth() << endl;
    cout << "   Current Y: " << gameBall.getCurrentY() << endl;
    cout << "   Destination X: " << gameBall.getDestinationX() << endl;
    cout << "   Destination Y: " << gameBall.getDestinationY() << endl;
    cout << "   Slope X: " << gameBall.getSlopeX() << endl;
    cout << "   Slope Y: " << gameBall.getSlopeY() << endl;

    cout << "Right Paddle:" << endl;
    cout << "   Current X: " << rPaddle.getX() << endl;
    cout << "   Current TopY: " << rPaddle.getTopY() << endl;
    cout << "   Current bottomY: " << rPaddle.getBottomY() << endl;

    cout << "Left Paddle:" << endl;
    cout << "   Current X: " << lPaddle.getX() << endl;
    cout << "   Current TopY: " << lPaddle.getTopY() << endl;
    cout << "   Current bottomY: " << lPaddle.getBottomY() << endl;
    cout << "   Destination Y: " << lPaddle.getDestinationY() << endl << endl;
    return;
}

void checkCollision(Ball &gameBall,Paddle rPaddle, Paddle lPaddle,SDL_Rect ballRect)
{
    bool rightPaddleBlocked = false;
    bool leftPaddleBlocked = false;
    bool topWallBlock = false;
    bool bottomWallBlock = false;
    int rightOfBall = gameBall.getCurrentX() + gameBall.getWidth();
    int bottomOfBall = gameBall.getCurrentY() + gameBall.getHeight();
    int rightOfLeftPaddle = lPaddle.getX() + lPaddle.getWidth();
    int rightOfRightPaddle = rPaddle.getX() + rPaddle.getWidth();

    if(gameBall.getCurrentX() == 0 && gameBall.getDestinationX() == 0)
    {
        playerScore++;
        gameBall.resetBall(SCREEN_WIDTH);
        return;
    }
    else if(gameBall.getCurrentX() == SCREEN_WIDTH && gameBall.getDestinationX() == SCREEN_WIDTH)
    {
        computerScore++;
        gameBall.resetBall(0);
        return;
    }
    if(bottomOfBall >= SCREEN_HEIGHT || gameBall.getCurrentY() >= SCREEN_HEIGHT)
    {
        bottomWallBlock = true;
        moveAfterCollision(gameBall,rightPaddleBlocked,leftPaddleBlocked,topWallBlock,bottomWallBlock,rPaddle,lPaddle,ballRect);

    }
    else if(gameBall.getCurrentY() <= 0)
    {
        topWallBlock = true;
        moveAfterCollision(gameBall,rightPaddleBlocked,leftPaddleBlocked,topWallBlock,bottomWallBlock,rPaddle,lPaddle,ballRect);

    }
    else
    {
        //right paddle
        if(rightOfBall >= rPaddle.getX() && gameBall.getCurrentX() <= rPaddle.getX()+rPaddle.getWidth())
        {
            if((gameBall.getCurrentY() >= rPaddle.getTopY() && gameBall.getCurrentY() <= rPaddle.getBottomY()) ||
                (bottomOfBall >= rPaddle.getTopY() && bottomOfBall <= rPaddle.getBottomY()))
            {
                rightPaddleBlocked = true;
                moveAfterCollision(gameBall,rightPaddleBlocked,leftPaddleBlocked,topWallBlock,bottomWallBlock,rPaddle,lPaddle,ballRect);
            }
        }

        //left paddle
        if(gameBall.getCurrentX() >= lPaddle.getX() && gameBall.getCurrentX() <= lPaddle.getX()+lPaddle.getWidth())
        {
            if((gameBall.getCurrentY() >= lPaddle.getTopY() && gameBall.getCurrentY() <= lPaddle.getBottomY()) ||
               (bottomOfBall >= lPaddle.getTopY() && bottomOfBall <= lPaddle.getBottomY()))
            {
                leftPaddleBlocked = true;
                moveAfterCollision(gameBall,rightPaddleBlocked,leftPaddleBlocked,topWallBlock,bottomWallBlock,rPaddle,lPaddle,ballRect);
                return;
            }
        }
    }


}

void moveAfterCollision(Ball &gameBall, bool rightPaddleBlocked, bool leftPaddleBlocked, bool topWallBlocked, bool bottomWallBlocked,
                        Paddle rPaddle, Paddle lPaddle,SDL_Rect  ballRect)
{
    int midBall = gameBall.getCurrentX() + (gameBall.getHeight()/2);
    int distanceFromMidRight = rPaddle.getMidPaddle() - midBall;
    int distanceFromMidLeft = lPaddle.getMidPaddle() - midBall;

    if(topWallBlocked == true)
    {
        gameBall.setDestinationX(gameBall.getDestinationX());
        gameBall.setDestinationY();
        gameBall.moveBall(gRenderer,ballRect);
    }
    else if(bottomWallBlocked == true)
    {
        gameBall.setDestinationX(gameBall.getDestinationX());
        gameBall.setDestinationY();
        gameBall.moveBall(gRenderer,ballRect);
    }
    else if(rightPaddleBlocked == true)
    {
        gameBall.setDestinationX(0);
        gameBall.setDestinationYIndividually(distanceFromMidRight,rPaddle.getMidPaddle());
        gameBall.moveBall(gRenderer,ballRect);
    }
    else if(leftPaddleBlocked == true)
    {
        gameBall.setDestinationX(SCREEN_WIDTH);
        gameBall.setDestinationYIndividually(distanceFromMidLeft,lPaddle.getMidPaddle());
        gameBall.moveBall(gRenderer,ballRect);
    }
}


int main( int argc, char* args[] )
{
    bool success = true;
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
		success = false;
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
		    //Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
            {
                bool quit = false;

                SDL_Event e;

                Ball gameBall;

                Paddle rightPaddle;
                rightPaddle.setX(600);
                rightPaddle.setTopandBottomY(200);

                Paddle leftPaddle;
                leftPaddle.setX(20);
                leftPaddle.setTopandBottomY(200);

                //Clear screen
				SDL_SetRenderDrawColor( gRenderer,0,0,0,0);
                SDL_RenderClear(gRenderer);

                //Draw dividing line
				SDL_SetRenderDrawColor( gRenderer,255,255,255,255);
				for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
				{
					SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
				}

				//Render right paddle
				SDL_Rect rightPaddleRect = {rightPaddle.getX(),rightPaddle.getTopY(),rightPaddle.getWidth(),rightPaddle.getHeight()};

                //Render left paddle
                SDL_Rect leftPaddleRect = {leftPaddle.getX(),leftPaddle.getTopY(),rightPaddle.getWidth(),rightPaddle.getHeight()};
                leftPaddle.renderPaddle(gRenderer,leftPaddleRect);

                SDL_Rect ballRect = {gameBall.getCurrentX(),gameBall.getCurrentY(),gameBall.getWidth(),gameBall.getHeight()};
                gameBall.renderBall(gRenderer,ballRect);

                //Update screen
				SDL_RenderPresent(gRenderer);

				bool ballMoving = true;

				while(!quit)
                {
                    if( SDL_PollEvent( &e ) != 0)
                    {
                        writeTest(gameBall,rightPaddle,leftPaddle);
                        if(e.type == SDL_QUIT)
                        {
                            quit = true;
                        }
                        SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
                        SDL_RenderClear(gRenderer);

                        SDL_SetRenderDrawColor( gRenderer,255,255,255,255);
                        for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
                        {
                            SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
                        }

                        leftPaddle.moveLeftPaddle(gameBall,leftPaddleRect);
                        rightPaddle.moveRightPaddle(e,rightPaddleRect,gRenderer,leftPaddle,gameBall,leftPaddleRect,ballRect);
                        gameBall.moveBall(gRenderer,ballRect);
                        leftPaddle.moveLeftPaddle(gameBall,leftPaddleRect);

                        gameBall.renderBall(gRenderer,ballRect);
                        leftPaddle.renderPaddle(gRenderer,leftPaddleRect);
                        rightPaddle.renderPaddle(gRenderer,rightPaddleRect);

                        checkCollision(gameBall,rightPaddle,leftPaddle,ballRect);
                        leftPaddle.moveLeftPaddle(gameBall,leftPaddleRect);
                        leftPaddle.renderPaddle(gRenderer,leftPaddleRect);

                        ScoreBoard(gRenderer,playerScore,computerScore);


                    }//end of while e has pollevent

                }//end of while(!quite)

		}//end of if renderer is successful
	}//end of if media did not fail
	}
	//Free resources and close SDL
	close();
}//end of if else (!init())
