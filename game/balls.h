#ifndef BALLZ_BALLS_H
#define BALLZ_BALLS_H

#include "def.h"

bool ball_add(Game *game, int x, int y);
void ball_move(Game *game, int i);
void ball_rotate(Game *game, int i);
void accelBall(Game *game, int i);
void ball_border_check(Game *game, int i);
void ball_hunt_cursor(Game *game, int i);
void ball_avoid_cursor(Game *game, int i);
void ball_destroy(Game *game, int i);
void ball_kill_all(Game *game, int i);
void ball_flip_direction(Game *game, int i, bool direction);
void ball_freeze(Game *game, int i);
int ball_grab(Game *game);

#endif // BALLZ_BALLS_H
