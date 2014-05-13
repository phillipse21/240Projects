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

//timer class
class Timer
{
public:
    Timer();
    void start();
    Uint32 getTicksWhileRunning();
    void pause();
    void unpause();
    Uint32 getTime();
    void runningOrPaused(bool status);
    std::string runningOrPaused();
private:
    Uint32 startTime;
    Uint32 stopTime;
    Uint32 midTime;
    Uint32 time;
    std::string runningOrPause;
};


//ball class
class Ball
{
    public:
        Ball();
        void releaseBall(std::string direction,int time,SDL_Rect &ballRect,SDL_Renderer* ballRenderer);
        void setCurrentX(int x);
        void setCurrentY(int y);
        void setVelocity(int startingTime,int endingTime);
        void checkCollision(int rPaddleY, int lPaddleY, int paddleWidth, int paddleHeight, int playerScore, int computerScore);
        void setDestinationXandY();
        int getCurrentX();
        int getCurrentY();
        int getVelocityX();
        int getVelocityY();
        int getcollisionX();
        int getCollisionY();
        int getDestinationX();
        int getDestinationY();
        int getBALLWIDTH();
        int getBALLHEIGHT();
        bool getCollision();
        int getSlopeX();
        int getSlopeY();
        void findSlope();
        void checkCollision(int rPaddleY, int lPaddleY, int paddleWidth, int paddleHeight,int playerScore,
                            int computerScore,std::string paddleDirection);
        void moveAfterCollision(bool rPaddleBlockBall, bool lPaddleBlockBall,int rPaddleY, int lPaddleY,
                                int bottomRightPaddle, int bottomLeftPaddle,std::string paddleDirection);
        void move(SDL_Renderer* ballRenderer,SDL_Rect ballRect);
        void render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip,SDL_Renderer* gRenderer,SDL_Texture* ballTexture);
    private:
        Timer moveTimer;
        int mPosX;
        int mPosY;
        int destinationX;
        int destinationY;
        int angle;
        int distanceX;
        int distanceY;
        int mVelX;
        int mVelY;
        int slopeX;
        int slopeY;
        float time;
        int BALL_WIDTH;
        int BALL_HEIGHT;
        int BALL_VEL;
        std::string leftOrRight;
        std::string upOrDown;
        bool collision;
};

void writeTest(Ball gameBall, Timer gameTimer);

#endif // pong_H

