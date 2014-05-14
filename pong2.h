#ifndef pong_H
#define pong_H

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <SDL_image.h>
#include <sstream>
#include <cmath>
#include <iostream>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


class Ball
{
public:
    Ball();
    int getCurrentX();
    int getCurrentY();
    int getDestinationX();
    int getDestinationY();
    int getSlopeX();
    int getSlopeY();
    int getDistanceX();
    int getDistanceY();
    int getWidth();
    int getHeight();
    void resetBall(int desitinationX);
    void setDestinationXandY();
    void findSlope();
    void moveBall(SDL_Renderer* gRenderer, SDL_Rect &ballRect);
    void renderBall(SDL_Renderer* gRenderer, SDL_Rect &ballRect);
private:
    int currentX;
    int currentY;
    int destinationX;
    int destinationY;
    int slopeX;
    int slopeY;
    int distanceX;
    int distanceY;
    int speed;
    int HEIGHT;
    int WIDTH;
};

class Paddle
{
public:
    Paddle();
    void setWidth(int width);
    void setHeight(int height);
    void setX(int x);
    void setTopandBottomY(int Y);
    void setSpeed(int speed);
    int getWidth();
    int getHeight();
    int getX();
    int getTopY();
    int getBottomY();
    int getSpeed();
    int getDestinationY();
    bool getCollision();
    void setCollision(bool collision);
    void renderPaddle(SDL_Renderer* gRenderer, SDL_Rect &paddleRect);
    void moveLeftPaddle(Ball gameBall,SDL_Rect &leftPaddleRect);
    void moveRightPaddle(SDL_Event& e,SDL_Rect &rightPaddleRect, SDL_Renderer* gRenderer,Paddle leftPaddle,Ball gameBall,
                         SDL_Rect &leftPaddleRect, SDL_Rect ballRect);
private:
    int WIDTH;
    int HEIGHT;
    int X;
    int topY;
    int bottomY;
    int speed;
    int destinationY;
    int randomDirection;
    bool collision;
};


#endif // pong_H

