#include "pong.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//timer()
Timer::Timer()
{
    runningOrPause = "paused";
    startTime = 0;
    stopTime = 0;
    midTime = 0;
}

//start timer
void Timer::start()
{
    runningOrPause = "running";

    startTime = SDL_GetTicks();
    stopTime = 0;
}

//stop timer
Uint32 Timer::getTicksWhileRunning()
{
    midTime = getTime();
    return midTime;
}
//pause timer
void Timer::pause()
{
    if(runningOrPause == "running")
    {
        runningOrPause = "paused";

        stopTime = getTime() - startTime;
    }
}

//unpaused timer
void Timer::unpause()
{
    runningOrPause = "running";

    startTime = getTime() - stopTime;
}

Uint32 Timer::getTime()
{
    if(runningOrPause == "paused")
    {
        time = stopTime;
    }
    else
    {
        return SDL_GetTicks() - startTime;
    }

    return time;
}

std::string Timer::runningOrPaused()
{
    return runningOrPause;
}


//Ball()
Ball::Ball()
{
    BALL_HEIGHT = 10;
    BALL_WIDTH = 10;
    mPosX = SCREEN_WIDTH/2 + 20;
    mPosY = SCREEN_HEIGHT/2;

    destinationX = SCREEN_WIDTH;
    destinationY = rand() % 2;

    if(destinationY == 1)
    {
        upOrDown = "up";
        destinationY = 160;
    }
    else
        upOrDown = "down";
        destinationY = 320;

    angle = 45;
    mVelX = 10 * cos(angle);
    mVelY = 10 * cos(angle);

    if(destinationX < mPosX)
        distanceX = mPosX - destinationX;
    else
        distanceX = destinationX - mPosX;

    if(destinationY < mPosY)
        distanceY = mPosY - destinationY;
    else
        distanceY = destinationY - mPosY;

    collision = false;

    findSlope();

    float distanceMag = sqrt(pow(mVelX,2) + pow(mVelY,2));
    float velocityMag = sqrt(pow(distanceX,2) + pow(distanceY,2));

    time = distanceMag/velocityMag;
}

//releases ball from center of screen after score
void Ball::releaseBall(std::string direction,int time, SDL_Rect &ballRect,SDL_Renderer* ballRenderer)
{
    leftOrRight = direction;
    int upDown = rand() % 2;
    if(upDown == 1)
        upOrDown = "up";
    else
        upOrDown = "down";

    mPosX = SCREEN_WIDTH/2 + 1;
    mPosY = SCREEN_HEIGHT/2;
    mVelX = 10;
    mVelY = 10;

    findSlope();

    ballRect.x = mPosX;
    ballRect.y = mPosY;
    SDL_SetRenderDrawColor(ballRenderer,255,255,255,255);
    SDL_RenderFillRect(ballRenderer,&ballRect);
    SDL_RenderPresent(ballRenderer);
}

void Ball::setCurrentX(int x)
{
    mPosX = x;
}

void Ball::setCurrentY(int y)
{
    mPosY = y;
}

//sets velocity of ball by first finding
void Ball::setVelocity(int startTime,int endingtime)
{
    mVelX = 10;
    mVelY = 10;
    /*int time = endingTime - startTime;
    int distance =  collisionX - mPosY;
    mVelX = distance/time;

    distance = collisionY - mPosY;
    mVelY = distance/time;*/


}

void Ball::setDestinationXandY()
{
    int tempX = mPosX;
    int tempY = mPosY;

    if(leftOrRight == "left")
        destinationX = -20;
    if(leftOrRight == "right")
        destinationX = SCREEN_WIDTH;
        destinationX = destinationX + 20;

    while(tempX != destinationX)
    {
        while(tempY <= SCREEN_HEIGHT)
        {
            if(upOrDown == "up")
                tempY = tempY - 1;
            else if(upOrDown == "down")
                tempY = tempY + 1;
        }

        if(tempX < destinationX)
            tempX = tempX - 1;
        else if(tempX > destinationX)
            tempX = tempX + 1;
    }
    if(tempX == destinationX)
        destinationY = tempY;

    findSlope();

    return;
}

int Ball::getCurrentX()
{
    return mPosX;
}

int Ball::getCurrentY()
{
    return mPosY;
}

int Ball::getVelocityX()
{
    return mVelX;
}

int Ball::getVelocityY()
{
    return mVelY;
}

int Ball::getDestinationX()
{
    return destinationX;
}

int Ball::getDestinationY()
{
    return destinationY;
}

int Ball::getBALLWIDTH()
{
    return BALL_WIDTH;
}

int Ball::getBALLHEIGHT()
{
    return BALL_WIDTH;
}

bool Ball::getCollision()
{
    return collision;
}

int Ball::getSlopeX()
{
    return slopeX;
}

int Ball::getSlopeY()
{
    return slopeY;
}

void Ball::findSlope()
{
    slopeX = destinationX - mPosX;
    signed slopeY = destinationY - mPosY;
    int bigger = 0;

    if(slopeX > slopeY)
        bigger = slopeX;
    else
        bigger = slopeY;

    if(slopeY % slopeX == 0)//even
    {
        slopeY == slopeY/slopeX;
        slopeX == slopeY/slopeX;
        return;
    }
    else//find common denominator
    {
        for(int i = 1; i < bigger; i++)
        {
            if(slopeY % i == 0 && slopeX % i == 0)
            {
                slopeY = slopeY/i;
                slopeX = slopeY/i;
                return;
            }
        }
    }
}

//check for collision
void Ball::checkCollision(int rPaddleY, int lPaddleY, int paddleWidth, int paddleHeight,int playerScore,int computerScore,std::string paddleDirection)
{
    bool rPaddleBlockBall = false;
    bool lPaddleBlockBall = false;
    int bottomRightPaddle = rPaddleY + paddleHeight;
    int bottomLeftPaddle = lPaddleY + paddleHeight;
    int rPaddleRightSide = rPaddleY + paddleWidth;
    int lPaddleRightSide = lPaddleY - paddleWidth;

    if(leftOrRight == "right")
    {
        for(int a = rPaddleY; a < bottomRightPaddle; a++)
        {
            for(int b = mPosX; b < mPosX+BALL_WIDTH; b++)
            {
                if(b == a)
                    rPaddleBlockBall = true;
                    collision = true;
            }
        }
    }
    if(leftOrRight == "left")
    {
        for(int c = rPaddleY; c < bottomRightPaddle; c++)
        {
            for(int d = mPosX; d < mPosX+BALL_WIDTH; d++)
            {
                if(d == c)
                    lPaddleBlockBall = true;
                    collision = true;
            }
        }
    }

}

//called when ball hits paddle and adjusts the dot's velocity
void Ball::moveAfterCollision(bool rPaddleBlockBall, bool lPaddleBlockBall,int rPaddleY, int lPaddleY,
                              int bottomRightPaddle, int bottomLeftPaddle,std::string paddleDirection)
{
    int middlePaddle = 0; //ball path is straighter the closer to the middle the ball hits
    int differenceOfCollisionAndMid = 0;

    if(rPaddleBlockBall == true && lPaddleBlockBall == false)//right paddle blocked
    {
        destinationX = 0;
        middlePaddle = 26;
        differenceOfCollisionAndMid = signed(middlePaddle - mPosY);

        if(upOrDown == paddleDirection)//upDown doesn't change
        {
            leftOrRight = "left";
        }

    }
    else if(rPaddleBlockBall == false && lPaddleBlockBall == true)//left paddle blocked
    {

    }
    else if(rPaddleBlockBall == false && lPaddleBlockBall == false)//hit wall
    {
        if(upOrDown == "up")
            upOrDown = "down";
            return;
        if(upOrDown == "down")
            upOrDown = "up";
            return;
    }
    return;
}

//Moves the dot
void Ball::move(SDL_Renderer* ballRenderer,SDL_Rect ballRect)
{
    SDL_SetRenderDrawColor(ballRenderer,0,0,0,0);
    SDL_RenderFillRect(ballRenderer,&ballRect);
    SDL_RenderPresent(ballRenderer);

    if(leftOrRight == "left")//mPosx > destinationX
    {
        //mPosX = mPosX - slopeX;
        for(int a = 1; a < slopeX;a++)
        {
            mPosX--;
            SDL_SetRenderDrawColor(ballRenderer,255,255,255,255);
            SDL_RenderFillRect(ballRenderer,&ballRect);
            SDL_RenderPresent(ballRenderer);
            if(upOrDown == "up" && mPosY < destinationY && a == slopeY)//mPosY < destinationY
            {
                for(int b = 1; b < slopeY; b++)
                {
                    mPosY++;
                    ballRect.x = mPosX;
                    ballRect.y = mPosY;
                    SDL_SetRenderDrawColor(ballRenderer,255,255,255,255);
                    SDL_RenderFillRect(ballRenderer,&ballRect);
                    SDL_RenderPresent(ballRenderer);
                    return;
                }
            }
            if(upOrDown == "down" && mPosY < destinationY && a == slopeY)//mPosY > destinationY
            {
                for(int c = 1; c < slopeY; c++)
                {
                    mPosY--;
                    ballRect.x = mPosX;
                    ballRect.y = mPosY;
                    SDL_SetRenderDrawColor(ballRenderer,255,255,255,255);
                    SDL_RenderFillRect(ballRenderer,&ballRect);
                    SDL_RenderPresent(ballRenderer);
                    return;
                }
            }
        }
    }
    if(leftOrRight == "right")//mPosx < destinationX
    {
        //mPosX = mPosX + slopeX;
        for(int d = 1; d < slopeX; d++)
        {
            mPosX = mPosX + 2;
            ballRect.x = mPosX;
            if(upOrDown == "up" && mPosY < destinationY && d == slopeY)//mPosY < destinationY
            {
                // mPosY = mPosY + slopeY;
                for(int c = 1; c < slopeY; c++)
                {
                    mPosY++;
                    ballRect.x = mPosX;
                    ballRect.y = mPosY;
                    SDL_SetRenderDrawColor(ballRenderer,255,255,255,255);
                    SDL_RenderFillRect(ballRenderer,&ballRect);
                    SDL_RenderPresent(ballRenderer);
                    return;
                }
            }
            if(upOrDown == "down" && mPosY > destinationY && d == slopeY)//mPosY > destinationY
            {
                //mPosY = mPosY - slopeY;
                for(int d = 1; d < slopeY; d++)
                {
                    mPosY--;
                    ballRect.x = mPosX;
                    ballRect.y = mPosY;
                    SDL_SetRenderDrawColor(ballRenderer,255,255,255,255);
                    SDL_RenderFillRect(ballRenderer,&ballRect);
                    SDL_RenderPresent(ballRenderer);
                    return;
                }
            }
        }
    }

    ballRect.x = mPosX;
    ballRect.y = mPosY;
    SDL_SetRenderDrawColor(ballRenderer,255,255,255,255);
    SDL_RenderFillRect(ballRenderer,&ballRect);
    SDL_RenderPresent(ballRenderer);

    return;
}

//Shows the dot on the screen
void Ball::render( SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip,SDL_Renderer* gRenderer,SDL_Texture* ballTexture)
{
    //Set rendering space and render to screen
	SDL_Rect renderQuad = {mPosX,mPosY,BALL_WIDTH,BALL_HEIGHT};

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer,ballTexture, clip, &renderQuad, angle, center, flip );
}
