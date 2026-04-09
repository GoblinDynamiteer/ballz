#ifndef BALLZ_BALLS_H
#define BALLZ_BALLS_H

#include "def.h"

bool addBall(ballsGame * game, int x, int y);
void moveBall(ballsGame * game, int i);
void rotateBall(ballsGame * game, int i);
void accelBall(ballsGame * game, int i);
void borderCheck(ballsGame * game, int i);
void huntCursor(ballsGame * game, int i);
void avoidCursor(ballsGame * game, int i);
void destroyBall(ballsGame * game, int i);
void killBalls(ballsGame * game, int i);
void flipBallSpeed(ballsGame * game, int i, bool direction);
void freezeBalls(ballsGame * game, int i);
int grabBall(ballsGame * game);

#endif //BALLZ_BALLS_H
