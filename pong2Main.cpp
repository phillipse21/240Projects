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

void checkCollision(Ball &gameBall,Paddle rPaddle, Paddle lPaddle);

void moveAfterCollision(Ball &gameBall, bool rightPaddleBlocked, bool leftPaddleBlocked, bool topWallBlocked, bool bottomWallBlocked,
                        Paddle rPaddle, Paddle lPaddle);

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

void checkCollision(Ball &gameBall,Paddle rPaddle, Paddle lPaddle)
{
    bool rightPaddleBlocked = false;
    bool leftPaddleBlocked = false;
    bool topWallBlock = false;
    bool bottomWallBlock = false;
    int rightOfBall = gameBall.getCurrentX() + gameBall.getWidth();
    int bottomOfBall = gameBall.getCurrentX() + gameBall.getHeight();
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
    else if(bottomOfBall >= SCREEN_HEIGHT)
    {
        bottomWallBlock = true;
        moveAfterCollision(gameBall,rightPaddleBlocked,leftPaddleBlocked,topWallBlock,bottomWallBlock,rPaddle,lPaddle);

    }
    else if(gameBall.getCurrentX() <= 0)
    {
        topWallBlock = true;
        moveAfterCollision(gameBall,rightPaddleBlocked,leftPaddleBlocked,topWallBlock,bottomWallBlock,rPaddle,lPaddle);

    }
    else
    {
        if(gameBall.getCurrentX() >= rPaddle.getX() && gameBall.getCurrentX() <= rightOfRightPaddle)
        {
            if(gameBall.getCurrentY() >= rPaddle.getTopY() && gameBall.getCurrentY() <= rPaddle.getBottomY())
            {
                rightPaddleBlocked = true;
                moveAfterCollision(gameBall,rightPaddleBlocked,leftPaddleBlocked,topWallBlock,bottomWallBlock,rPaddle,lPaddle);
            }
        }










        for(int c = gameBall.getCurrentX(); c < rightOfBall; c++)
        {
            for(int d = lPaddle.getX(); d < rightOfLeftPaddle; d++)
            {
                if(c == d)
                {
                    leftPaddleBlocked = true;
                    moveAfterCollision(gameBall,rightPaddleBlocked,leftPaddleBlocked,topWallBlock,bottomWallBlock,rPaddle,lPaddle);
                }
            }
        }
    }

    moveAfterCollision(gameBall,rightPaddleBlocked,leftPaddleBlocked,topWallBlock,bottomWallBlock,rPaddle,lPaddle);
}

void moveAfterCollision(Ball &gameBall, bool rightPaddleBlocked, bool leftPaddleBlocked, bool topWallBlocked, bool bottomWallBlocked,
                        Paddle rPaddle, Paddle lPaddle)
{
    int midBall = gameBall.getCurrentX() + (gameBall.getHeight()/2);
    int distanceFromMidRight = rPaddle.getMidPaddle() - midBall;
    int distanceFromMidLeft = lPaddle.getMidPaddle() - midBall;
    int possibleY = 0;

    if(topWallBlocked == true)
    {
        gameBall.setDestinationX(gameBall.getDestinationX());
        if(gameBall.getCurrentY() + gameBall.getSlopeY() <= SCREEN_HEIGHT)
            gameBall.setDestinationY(gameBall.getCurrentY() + gameBall.getSlopeY());
        else
        {
            possibleY = gameBall.getCurrentY() + gameBall.getSlopeY();
            while(gameBall.getCurrentY() + gameBall.getSlopeY() > SCREEN_HEIGHT)
            {
                possibleY = possibleY - 20;
            }
            gameBall.setDestinationY(possibleY);
        }
    }
    else if(bottomWallBlocked == true)
    {
        gameBall.setDestinationX(gameBall.getDestinationX());
        if(gameBall.getCurrentY() - gameBall.getSlopeY() >= 0)
            gameBall.setDestinationY(gameBall.getCurrentY() - gameBall.getSlopeY());
        else
        {
            possibleY = gameBall.getCurrentY() - gameBall.getSlopeY();
            while(gameBall.getCurrentY() - gameBall.getSlopeY() < 0)
            {
                possibleY = possibleY + 20;
            }
            gameBall.setDestinationY(possibleY);
        }
    }
    else if(rightPaddleBlocked == true)
    {
        gameBall.setDestinationX(0);
        if(distanceFromMidRight > 10 || distanceFromMidRight < 10)
        {
            if(gameBall.getCurrentY() < rPaddle.getMidPaddle())
                gameBall.setDestinationY(gameBall.getCurrentY() + distanceFromMidRight);
            else
                gameBall.setDestinationY(gameBall.getCurrentY() - distanceFromMidRight);
        }
        else if(gameBall.getCurrentY() > rPaddle.getMidPaddle())
        {
            gameBall.setDestinationY(gameBall.getCurrentY() - distanceFromMidRight);
        }
        else if(gameBall.getCurrentY() < rPaddle.getMidPaddle())
        {
            gameBall.setDestinationY(gameBall.getCurrentY() + distanceFromMidRight);
        }
    }
    else if(leftPaddleBlocked == true)
    {
        gameBall.setDestinationX(SCREEN_WIDTH);
        if(distanceFromMidLeft > 10 || distanceFromMidLeft < 10)
        {
            if(gameBall.getCurrentY() < lPaddle.getMidPaddle())
                gameBall.setDestinationY(gameBall.getCurrentY() + distanceFromMidLeft);
            else
                gameBall.setDestinationY(gameBall.getCurrentY() - distanceFromMidLeft);
        }
        else if(gameBall.getCurrentY() > rPaddle.getMidPaddle())
        {
            gameBall.setDestinationY(gameBall.getCurrentY() - distanceFromMidLeft);
        }
        else if(gameBall.getCurrentY() < lPaddle.getMidPaddle())
        {
            gameBall.setDestinationY(gameBall.getCurrentY() + distanceFromMidLeft);
        }
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

                        rightPaddle.moveRightPaddle(e,rightPaddleRect,gRenderer,leftPaddle,gameBall,leftPaddleRect,ballRect);
                        gameBall.moveBall(gRenderer,ballRect);

                        gameBall.renderBall(gRenderer,ballRect);
                        leftPaddle.renderPaddle(gRenderer,leftPaddleRect);
                        rightPaddle.renderPaddle(gRenderer,rightPaddleRect);

                        checkCollision(gameBall,rightPaddle,leftPaddle);

                    }//end of while e has pollevent

                }//end of while(!quite)

		}//end of if renderer is successful
	}//end of if media did not fail
	}
	//Free resources and close SDL
	close();
}//end of if else (!init())
