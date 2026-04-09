#ifndef BALLZ_BALLS_H
#define BALLZ_BALLS_H

#include "def.h"

bool ball_add(ballsGame *game, int x, int y);
void ball_move(ballsGame *game, int i);
void ball_rotate(ballsGame *game, int i);
void accelBall(ballsGame *game, int i);
void ball_border_check(ballsGame *game, int i);
void ball_hunt_cursor(ballsGame *game, int i);
void ball_avoid_cursor(ballsGame *game, int i);
void ball_destroy(ballsGame *game, int i);
void ball_kill_all(ballsGame *game, int i);
void ball_flip_direction(ballsGame *game, int i, bool direction);
void ball_freeze(ballsGame *game, int i);
int ball_grab(ballsGame *game);

#endif // BALLZ_BALLS_H
