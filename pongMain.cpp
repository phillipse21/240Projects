#include "pong.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

void loadTexture();

//Frees media and shuts down SDL
void close();

void writeTest(Ball gameBall, Timer gameTimer);

void moveLeftPaddle(int &paddleY,int paddleHeight,Ball gameBall);

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

void writeTest(Ball gameBall, Timer gameTimer)
{
    Uint32 timeT = gameTimer.getTicksWhileRunning();
    cout << "Time: " << timeT << endl;
    cout << "Destination X: " << gameBall.getDestinationX() << endl;
    cout << "Destination Y: " << gameBall.getDestinationY() << endl;
    cout << "Current X: " << gameBall.getCurrentX() << endl;
    cout << "Current Y: " << gameBall.getCurrentY() << endl;
    cout << "Slope X: " << gameBall.getSlopeX() << endl;
    cout << "Slope Y: " << gameBall.getSlopeY() << endl;
    cout << "Collision: " << gameBall.getCollision() << endl << endl;
    return;
}

void moveLeftPaddle(int &paddleY,int paddleHeight,Ball gameBall)
{
    int paddleVel = 10;
    int paddleDirction = rand() % 2 + 1;
    int paddleDestinationY = 0;
    int bottomOfPaddle = paddleY = paddleHeight;

    while(gameBall.getDestinationX() != 40)
    {
        if(paddleDirction == 1 && (paddleY -= paddleVel >= 0))
        {
            paddleY -= paddleVel;
            bottomOfPaddle = paddleY + paddleHeight;
        }
        else if(paddleDirction == 2 && (bottomOfPaddle -= paddleVel <= SCREEN_HEIGHT))
        {
            paddleY += paddleVel;
            bottomOfPaddle = paddleY + paddleHeight;
        }
        else
            moveLeftPaddle(paddleY,paddleHeight,gameBall);
    }
    if(gameBall.getDestinationX() == 40)
    {
        paddleDestinationY = gameBall.getDestinationY();
        if(paddleDestinationY + paddleHeight < paddleY)
        {
            paddleY -= paddleVel;
            bottomOfPaddle = paddleY + paddleHeight;
        }
        else
        {
            paddleY += paddleVel;
            bottomOfPaddle = paddleY + paddleHeight;
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
			ballRenderer = gRenderer;
//			ballRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else if(ballRenderer == NULL)
            {
                printf("ballRenderer could not be created. Error %s\n", SDL_GetError());
                success = false;
            }
			else
            {
                bool quit = false;

                SDL_Event e;

                Ball gameBall;

                int startTime = 0;
                Timer gameTimer;

                string paddleDirection;

                SDL_SetRenderDrawColor(ballRenderer,255,255,255,0);
				SDL_RenderClear(ballRenderer);

                //Clear screen
				SDL_SetRenderDrawColor( gRenderer,0,0,0,0);
                SDL_RenderClear(gRenderer);

				//Apply the ball to window
                SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL );
                SDL_UpdateWindowSurface(gWindow);

				//Draw dividing line
				SDL_SetRenderDrawColor( gRenderer,255,255,255,255);
				for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
				{
					SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
				}

//                SDL_RenderDrawPoint(gRenderer,gameBall.getCurrentX(),gameBall.getCurrentY());

				int rightPaddleX = 600;
				int rightPaddleY = 200;
				int leftPaddleX = 20;
				int leftPaddleY = 200;
				int height = 80;
				int width = 20;

				//Render right paddle
				SDL_Rect rightPaddle = {rightPaddleX,rightPaddleY,width,height};
				SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );
				SDL_RenderFillRect(gRenderer,&rightPaddle);

                //Render left paddle
                SDL_Rect leftPaddle = {leftPaddleX,leftPaddleY,width,height};
                SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
                SDL_RenderFillRect(gRenderer,&leftPaddle);

                SDL_Rect ballRect = {gameBall.getCurrentX(),gameBall.getCurrentY(),gameBall.getBALLWIDTH(),gameBall.getBALLHEIGHT()};

				//Update screen
				SDL_RenderPresent(gRenderer);

                gameTimer.start();
                gameBall.releaseBall("right",gameTimer.getTicksWhileRunning(),ballRect,ballRenderer);

                while(!quit)
                {
                    if( SDL_PollEvent( &e ) != 0)
                    {
//                        gameBall.checkCollision(rightPaddleY,leftPaddleY,width,height,playerScore,computerScore,paddleDirection);
                        writeTest(gameBall,gameTimer);
                            //User requests quit
                            if(e.type == SDL_QUIT)
                            {
                                quit = true;
                            }
                            //keyboard input
                            else if(e.type == SDL_KEYDOWN)
                            {
                                switch(e.key.keysym.sym)
                                {
                                    case SDLK_UP:
                                        //Clear screen
                                        SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
                                        SDL_RenderClear(gRenderer);

                                        if(rightPaddleY > 0)
                                        {
                                            rightPaddleY = rightPaddleY-15;
                                        }
                                        paddleDirection = "up";
                                        //gameBall.checkCollision(rightPaddleY,leftPaddleY,width,height,playerScore,computerScore,paddleDirection);
                                        break;
                                    case SDLK_DOWN:
                                        //Clear screen
                                        SDL_SetRenderDrawColor( gRenderer,0,0,0,0);
                                        SDL_RenderClear(gRenderer);

                                        if(rightPaddleY+height < SCREEN_HEIGHT)
                                        {
                                            rightPaddleY = rightPaddleY+15;
                                        }
                                        paddleDirection = "down";
                                       // gameBall.checkCollision(rightPaddleY,leftPaddleY,width,height,playerScore,computerScore,paddleDirection);
                                        break;
                                    default:
                                        //Clear screen
                                        SDL_SetRenderDrawColor( gRenderer,0,0,0,0);
                                        SDL_RenderClear(gRenderer);

                                        rightPaddleY = rightPaddleY;
                                        paddleDirection = "still";
                                       // gameBall.checkCollision(rightPaddleY,leftPaddleY,width,height,playerScore,computerScore,paddleDirection);
                                        break;
                                }
                                SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
                                SDL_RenderClear(gRenderer);
                                //gameBall.move(gRenderer,ballRect);

                                //Render right paddle
                                rightPaddle = {rightPaddleX,rightPaddleY,width,height};
                                SDL_SetRenderDrawColor(gRenderer,255,255,255,255 );
                                SDL_RenderFillRect(gRenderer,&rightPaddle);

                                //Render left paddle
                                SDL_Rect leftPaddle = {leftPaddleX,leftPaddleY,width,height};
                                SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
                                SDL_RenderFillRect(gRenderer,&leftPaddle);


                                //Draw dividing line
                                SDL_SetRenderDrawColor( gRenderer,255,255,255,255);
                                for( int a = 0; a < SCREEN_HEIGHT; a += 4 )
                                {
                                    SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, a );
                                }

                                //Update screen
                                SDL_RenderPresent(gRenderer);

                            }
                            gameBall.move(gRenderer,ballRect);


                            //Render right paddle
                            rightPaddle = {rightPaddleX,rightPaddleY,width,height};
                            SDL_SetRenderDrawColor(gRenderer,255,255,255,255 );
                            SDL_RenderFillRect(gRenderer,&rightPaddle);

                            //Render left paddle
                            SDL_Rect leftPaddle = {leftPaddleX,leftPaddleY,width,height};
                            SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
                            SDL_RenderFillRect(gRenderer,&leftPaddle);

                            //Draw dividing line
                            SDL_SetRenderDrawColor( gRenderer,255,255,255,255);
                            for( int a = 0; a < SCREEN_HEIGHT; a += 4 )
                            {
                                SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, a );
                            }

                            //Update screen
                            SDL_RenderPresent(gRenderer);
                            //SDL_RenderPresent(ballRenderer);

                        }//end of while e has pollevent
                }//end of while(!quite)
		}//end of if renderer is successful
	}//end of if media did not fail

	//Free resources and close SDL
	close();
	}//end of if else (!init())

	return 0;
}
