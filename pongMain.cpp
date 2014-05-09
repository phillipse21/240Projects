/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* leftPaddle = NULL;
SDL_Surface* rightPaddle = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

SDL_Renderer* gRenderer = NULL;


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
	    //Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

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
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

		//Load splash image
	leftPaddle = SDL_LoadBMP( "C:/Users/Ashley/Documents/240/pong/paddle.bmp" );
	if( leftPaddle == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "C:/Users/Ashley/Documents/240/pong/paddle.bmp", SDL_GetError() );
		success = false;
	}

	//rightPaddle = SDL_LoadBMP( "C:/Users/Ashley/Documents/240/pong/paddle.bmp" );
	//if( rightPaddle == NULL )
	//{
		//printf( "Unable to load image %s! SDL Error: %s\n", "C:/Users/Ashley/Documents/240/pong/paddle.bmp", SDL_GetError() );
	//	success = false;
	//}

	//defult
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("C:/Users/Ashley/Documents/240/pong/paddle.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        printf("Failed to load image.\n");
        success = false;
    }

    //up
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("C:/Users/Ashley/Documents/240/pong/paddle.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        printf("Failed to load image.\n");
        success = false;
    }

    //down
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("C:/Users/Ashley/Documents/240/pong/paddle.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        printf("Failed to load image.\n");
        success = false;
    }

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface(leftPaddle);
	SDL_FreeSurface(rightPaddle);
	leftPaddle = NULL;
	rightPaddle = NULL;

	//destroy renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
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
                //Apply the image
                //SDL_BlitSurface(leftPaddle,NULL, gScreenSurface,NULL);
                //SDL_BlitSurface(rightPaddle,NULL,gScreenSurface,NULL);

                //Set default current surface
                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

                bool quit = false;

                SDL_Event e;


                //Clear screen
				SDL_SetRenderDrawColor( gRenderer,0,0,0,0);
				SDL_RenderClear(gRenderer);

				//Draw dividing line
				SDL_SetRenderDrawColor( gRenderer,255,255,255,255);
				for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
				{
					SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
				}

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

				//Update screen
				SDL_RenderPresent(gRenderer);

                while( !quit )
                {
                    //Handle events on queue
                    while( SDL_PollEvent( &e ) != 0 )
                    {
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
                                    SDL_SetRenderDrawColor( gRenderer,0,0,0,0);
                                    SDL_RenderClear(gRenderer);

                                    if(rightPaddleY > 0)
                                    {
                                        rightPaddleY = rightPaddleY-15;
                                    }

                                    break;
                                case SDLK_DOWN:
                                    //Clear screen
                                    SDL_SetRenderDrawColor( gRenderer,0,0,0,0);
                                    SDL_RenderClear(gRenderer);

                                    if(rightPaddleY+height < SCREEN_HEIGHT)
                                    {
                                        rightPaddleY = rightPaddleY+15;
                                    }

                                    break;
                                default:
                                    //Clear screen
                                    SDL_SetRenderDrawColor( gRenderer,0,0,0,0);
                                    SDL_RenderClear(gRenderer);

                                    rightPaddleY = rightPaddleY;
                                    break;
                            }
                            //Render right paddle
                            rightPaddle = {rightPaddleX,rightPaddleY,width,height};
                            SDL_SetRenderDrawColor(gRenderer,255,255,255,255 );
                            SDL_RenderFillRect(gRenderer,&rightPaddle);

                            //Render left paddle
                            SDL_Rect leftPaddle = {leftPaddleX,leftPaddleY,width,height};
                            SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
                            SDL_RenderFillRect(gRenderer,&leftPaddle);

                            //Draw vertical line of yellow dots
                            SDL_SetRenderDrawColor( gRenderer,255,255,255,255);
                            for( int a = 0; a < SCREEN_HEIGHT; a += 4 )
                            {
                                SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, a );
                            }

                            //Update screen
                            SDL_RenderPresent(gRenderer);
                        }
                    }//end of while e has pollevent
                }//end of while(!quite)
		}//end of if renderer is successful
	}//end of if media did not fail

	//Free resources and close SDL
	close();
	}//end of if else (!init())

	return 0;
}
