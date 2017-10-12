/*
 * balls.c
 *
 *  Created on: 8 jan. 2017
 *      Author: kampe_000
 */

#include "..\def.h"

bool addBall(ballsGame * game, int x, int y)
{
    int i = 0;

    /* Finds next free ball    */
    while(game->balls[i] != NULL && i < MAX_BALLS)
    {
        if(!game->balls[i]->active)
        {
            break;
        }

        i++;
    }

    /* Set ball x, y, width, height    */
    game->balls[i] = malloc(sizeof(ball));
    game->balls[i]->rect.x = x - (BALL_SIZE / 2);
    game->balls[i]->rect.y = y - (BALL_SIZE / 2);
    game->balls[i]->rect.w = BALL_SIZE;
    game->balls[i]->rect.h = BALL_SIZE;

    /* Set random ball speed    */
    game->balls[i]->speed.x = getRandomDirection();
    game->balls[i]->speed.y = getRandomDirection();

    /* Set balls starting angle, for rotation    */
    game->balls[i]->angle = 0.0;

    /* Set ball colour    */
    game->balls[i]->color = rand() % (MAX_BALL_ART);
    //game->balls[i]->colour = SMILEY;

    /* Set ball as active, used to destroy balls */
    game->balls[i]->active = 1;

    /* Ball count    */
    game->createdBalls++;

    return 1;
}

void destroyBall(ballsGame * game, int i)
{
    game->balls[i]->active = 0;
}

void accelBall(ballsGame * game, int i)
{
    /* Pointers to speed for ball */
    float *velx = &game->balls[i]->speed.x;
    float *vely = &game->balls[i]->speed.y;

    /* Accelerate balls until max speed.    */
    if( fabs(*velx) < MAXSPEED &&
        fabs(*vely) < MAXSPEED)
        {
            *velx *= ACC;
            *vely *= ACC;
        }
}

void rotateBall(ballsGame * game, int i)
{
    game->balls[i]->angle += 1.6f;

    if(game->balls[i]->angle >= 360)
    {
        game->balls[i]->angle = 0.0;
    }
}

void moveBall(ballsGame * game, int i)
{
    /* Pointers to x, y and speed    for ball */
    float *velx = &game->balls[i]->speed.x;
    float *vely = &game->balls[i]->speed.y;
    int *posx = &game->balls[i]->rect.x;
    int *posy = &game->balls[i]->rect.y;

    /* Move balls in x and y    */
    *posx += *velx;
    *posy += *vely;
}

void freezeBalls(ballsGame * game, int i)
{
    game->balls[i]->rect.x = game->cursor.x - 25;
    game->balls[i]->rect.y = game->cursor.y - 25;
}

int grabBall(ballsGame * game)
{
    /* Finds next free ball    */

    int i = 0;
    while(game->balls[i] != NULL && i < MAX_BALLS)
    {
        int *posx = &game->balls[i]->rect.x;
        int *posy = &game->balls[i]->rect.y;

        if( fabs(*posx + 25 - game->cursor.x) < 20 &&
            fabs(*posy + 25 - game->cursor.y) < 20)
            {
                return i;
            }

        i++;
    }

    return -1;
}

void borderCheck(ballsGame * game, int i)
{
    /* Pointers to x, y and speed    for ball */
    float *velx = &game->balls[i]->speed.x;
    float *vely = &game->balls[i]->speed.y;
    int *posx = &game->balls[i]->rect.x;
    int *posy = &game->balls[i]->rect.y;

    /* Check game window collision    */
    if(*posx + BALL_SIZE/2 >= WIN_WIDTH)
    {
        *velx *= -1;
        *posx = WIN_WIDTH - BALL_SIZE;
    }

    if(*posx - BALL_SIZE/2 < 0)
    {
        *velx *= -1;
        *posx = BALL_SIZE/2;
    }

    if(*posy + BALL_SIZE/2 >= WIN_HEIGHT)
    {
        *vely *= -1;
        *posy = WIN_HEIGHT - BALL_SIZE;
    }

    if(*posy - BALL_SIZE/2 < 0)
    {
        *vely *= -1;
        *posy = BALL_SIZE/2;
    }
}

void huntCursor(ballsGame * game, int i)
{
    /* Pointers to x, y and speed    for ball */
    int *posx = &game->balls[i]->rect.x;
    int *posy = &game->balls[i]->rect.y;

    /* Position balls nearer current cursor location    */
    /* Calculate distance    */
    double distance =
            calculateDistance(
                    *posx, game->cursor.x,
                    *posy, game->cursor.y
                );

    if(distance < MAG_RADIUS)
    {
        game->balls[i]->speed.x = getRandomDirection();
        game->balls[i]->speed.y = getRandomDirection();
        if(*posx != game->cursor.x)
        {
            *posx = (
                *posx > game->cursor.x ?
                    *posx - MAGSTR :
                    *posx + MAGSTR
            );
        }

        if(*posy != game->cursor.y)
        {
            *posy = (
                *posy > game->cursor.y ?
                    *posy - MAGSTR :
                    *posy + MAGSTR
            );
        }
    }

    else
    {
        moveBall(game, i);
    }
}

void avoidCursor(ballsGame * game, int i)
{
    /* Pointers to x, y and speed    for ball */
    int *posx = &game->balls[i]->rect.x;
    int *posy = &game->balls[i]->rect.y;
    float *velx = &game->balls[i]->speed.x;
    float *vely = &game->balls[i]->speed.y;

    /* Position balls away from current cursor location    */
    /* Calculate distance    */
    double distance =
            calculateDistance(
                    *posx, game->cursor.x,
                    *posy, game->cursor.y
                );

    if(distance < REPEL_RADIUS)
    {
        flipBallSpeed(game, i, HORIZONTAL);
        flipBallSpeed(game, i, VERTICAL);

        *posx = (
            *posx > game->cursor.x ?
                *posx + fabs(*velx) * 3 :
                *posx - fabs(*velx) * 3
        );

        *posy = (
            *posy > game->cursor.y ?
                *posy + fabs(*vely) * 3 :
                *posy - fabs(*vely) * 3
        );
    }

    else
    {
        moveBall(game, i);
    }
}


void killBalls(ballsGame * game, int i)
{
    /* Pointers to x, y and speed    for ball */
    int *posx = &game->balls[i]->rect.x;
    int *posy = &game->balls[i]->rect.y;

    /* Kill balls near cursor    */
    /* Calculate distance    */
    double distance =
            calculateDistance(
                    *posx, game->cursor.x,
                    *posy, game->cursor.y
                );

    if(distance < KILLSIZE)
    {
        destroyBall(game, i);
        game->killedBalls++;
    }

    else
    {
        moveBall(game, i);
    }
}

void flipBallSpeed(ballsGame * game, int i, bool direction)
{
    if(direction == VERTICAL)
    {
        game->balls[i]->speed.x *= -1;
    }

    else
    {
        game->balls[i]->speed.y *= -1;
    }
}
