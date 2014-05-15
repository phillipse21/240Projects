#include "pong2.h"

using namespace std;

Ball::Ball()
{
    WIDTH = 10;
    HEIGHT = 10;
    destinationX = SCREEN_WIDTH;
    destinationY = SCREEN_HEIGHT/3;
    currentX = SCREEN_WIDTH/2;
    currentY = SCREEN_HEIGHT/2;
    slopeX = 0;
    slopeY = 0;
    speed = 20;
    findSlope();
}

int Ball::getCurrentX()
{
    return currentX;
}

int Ball::getCurrentY()
{
    return currentY;
}

int Ball::getDestinationX()
{
    return destinationX;
}

int Ball::getDestinationY()
{
    return destinationY;
}

int Ball::getSlopeX()
{
    return slopeX;
}

int Ball::getSlopeY()
{
    return slopeY;
}

int Ball::getDistanceX()
{
    return distanceX;
}

int Ball::getDistanceY()
{
    return distanceY;
}

int Ball::getWidth()
{
    return WIDTH;
}

int Ball::getHeight()
{
    return HEIGHT;
}

void Ball::resetBall(int destinationX)
{
    currentX = SCREEN_WIDTH/2;
    currentY = SCREEN_HEIGHT/2;
    this -> destinationX = destinationX;
    destinationY = currentY + distanceY;
}

void Ball::setDestinationXandY()
{

}

void Ball::setDestinationX(int x)
{
    this -> destinationX = x;
}

void Ball::setDestinationY()
{
    if(destinationY < currentY)
        destinationY = abs(currentY - slopeY);
    else
        destinationY = abs(slopeY - currentY);

    destinationY = abs(destinationY - SCREEN_HEIGHT);
}

void Ball::setDestinationYIndividually(int y,int midPoint)
{
    if(currentY < midPoint)//above middle - move up
    {
        destinationY = destinationY - y;
    }
    else
        destinationY = destinationY + y;
}

void Ball::findSlope()
{
    int bigger = 0;

    if(destinationX < currentX)
        slopeX = abs(currentX - destinationX);
    else
        slopeX = abs(destinationX - currentX);

    if(destinationY < currentY)
        slopeY = abs(currentY - destinationY);
    else
        slopeY = abs(destinationY - currentY);

    if(slopeX < slopeY)
        bigger = slopeY;
    else
        bigger = slopeX;

    for(int i = 2; i < bigger; i++)
    {
        if(slopeY % i == 0 && slopeX % i == 0)
        {
            slopeX = slopeX/i;
            slopeY = slopeY/i;
        }
    }
}

void Ball::moveBall(SDL_Renderer* gRenderer, SDL_Rect &ballRect)
{
    if(destinationX < currentX)//moving left
    {
        currentX = currentX - speed;
        ballRect.x = currentX;
        if(destinationY < currentY)//moving up
        {
            for(int a = 0; a < slopeX;a++)
            {
                if(currentY != destinationY && a == slopeY)
                {
                    currentY = currentY - slopeY;
                    ballRect.x = currentX;
                    ballRect.y = currentY;
                    renderBall(gRenderer,ballRect);
                }
            }
        }
        else if(destinationY > currentY)//moving down
        {
            for(int b = 0; b < slopeX; b++)
            {
                if(currentY != destinationY && b == slopeY)
                {
                    currentY = currentY + slopeY;
                    ballRect.x = currentX;
                    ballRect.y = currentY;
                    renderBall(gRenderer,ballRect);
                }
            }
        }
    }
    else if(destinationX > currentX)//moving right
    {
        currentX = currentX + speed;
        ballRect.x = currentX;
        if(destinationY < currentY)//moving up
        {
            for(int c = 0; c < slopeX; c++)
            {
                if(currentY < destinationY && c == slopeY)
                {
                    currentY = currentY - slopeY;
                    ballRect.y = currentY;
                    renderBall(gRenderer,ballRect);
                    return;
                }
            }
        }
        else if(destinationY > currentY)//moving down
        {
            for(int d = 0; d < slopeX; d++)
            {
                if(currentY != destinationY && d == slopeY)
                {
                    currentY = currentY + slopeY;
                    ballRect.y = currentY;
                    renderBall(gRenderer,ballRect);
                    return;
                }
            }
        }
    }
}

void Ball::renderBall(SDL_Renderer* gRenderer, SDL_Rect &ballRect)
{
    SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
    SDL_RenderFillRect(gRenderer,&ballRect);
    SDL_RenderPresent(gRenderer);
}

Paddle::Paddle()
{
    WIDTH = 20;
    HEIGHT = 80;
    X = 0;
    topY = 0;
    bottomY = 0;
    midPaddle = 0;
    speed = 15;
    destinationY = 0;
    randomDirection = rand() % 2 + 1;
    collision = false;
}

void Paddle::setWidth(int width)
{
    this -> WIDTH = width;
}

void Paddle::setHeight(int height)
{
    this -> HEIGHT = height;
}

void Paddle::setX(int x)
{
    this -> X = x;
}

void Paddle::setTopandBottomY(int y)
{
    this -> topY = y;
    bottomY = topY + HEIGHT;
}

void Paddle::setSpeed(int speed)
{
    this -> speed = speed;
}

int Paddle::getWidth()
{
    return WIDTH;
}

int Paddle::getHeight()
{
    return HEIGHT;
}

int Paddle::getX()
{
    return X;
}

int Paddle::getTopY()
{
    return topY;
}

int Paddle::getBottomY()
{
    return bottomY;
}

int Paddle::getSpeed()
{
    return speed;
}

bool Paddle::getCollision()
{
    return collision;
}

void Paddle::setCollision(bool collision)
{
    this -> collision = collision;
}

int Paddle::getMidPaddle()
{
    return midPaddle;
}

void Paddle::renderPaddle(SDL_Renderer* gRenderer,SDL_Rect &paddleRect)
{
    SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
    SDL_RenderFillRect(gRenderer,&paddleRect);
    SDL_RenderPresent(gRenderer);
}

void Paddle::moveLeftPaddle(Ball gameBall,SDL_Rect &leftPaddleRect)
{
    if(gameBall.getCurrentY() < topY & topY >= 0)
    {
        topY = topY - (speed/2);
        bottomY = topY + HEIGHT;
        midPaddle = topY + (HEIGHT/2);
        leftPaddleRect.y = topY;
        if(gameBall.getCurrentY() >= topY && gameBall.getCurrentY() <= bottomY)
            return;
    }
    else if(gameBall.getCurrentY() > topY && bottomY <= SCREEN_HEIGHT)
    {
        topY = topY + (speed/2);
        bottomY = topY + HEIGHT;
        midPaddle = topY + (HEIGHT/2);
        if(gameBall.getCurrentY() >= topY && gameBall.getCurrentY() <= bottomY)
            return;
    }
}

int Paddle::getDestinationY()
{
    return destinationY;
}

void Paddle::moveRightPaddle(SDL_Event& e,SDL_Rect &rightPaddleRect,SDL_Renderer* gRenderer,Paddle leftPaddle,Ball gameBall,
                             SDL_Rect &leftPaddleRect, SDL_Rect ballRect)
{
    if(e.type == SDL_KEYDOWN)
    {
       // leftPaddle.moveLeftPaddle(gameBall,leftPaddleRect);
     //   gameBall.moveBall(gRenderer,ballRect);
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
                if(getTopY() - getSpeed() >= 0)
                {
                    topY = topY - speed;
                    bottomY = topY + HEIGHT;
                    midPaddle = topY + (HEIGHT/2);
                    rightPaddleRect.x = X;
                    rightPaddleRect.y = topY;
                }
                renderPaddle(gRenderer,rightPaddleRect);
                break;
            case SDLK_DOWN:
                if(getBottomY() + getSpeed() <= SCREEN_HEIGHT)
                {
                    topY = topY + speed;
                    bottomY = topY + HEIGHT;
                    midPaddle = topY + (HEIGHT/2);
                    rightPaddleRect.x = X;
                    rightPaddleRect.y = topY;
                }
                renderPaddle(gRenderer,rightPaddleRect);
                break;
        }
    }
}
