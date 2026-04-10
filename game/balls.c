#include "balls.h"
#include "event.h"

bool ball_add(Game *game, int x, int y) {
    int i = 0;

    /* Finds next free ball    */
    while (game->balls[i] != NULL && i < MAX_BALLS) {
        if (!game->balls[i]->active) {
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
    game->balls[i]->speed.x = event_get_random_direction();
    game->balls[i]->speed.y = event_get_random_direction();

    /* Set balls starting angle, for rotation    */
    game->balls[i]->angle = 0.0;

    /* Set ball colour    */
    game->balls[i]->color = (short)(rand() % MAX_BALL_ART);
    // game->balls[i]->colour = SMILEY;

    /* Set ball as active, used to destroy balls */
    game->balls[i]->active = 1;

    /* Ball count    */
    game->createdBalls++;

    return 1;
}

void ball_destroy(Game *game, int i) { game->balls[i]->active = 0; }

void accelBall(Game *game, int i) {
    /* Pointers to speed for ball */
    float *velx = &game->balls[i]->speed.x;
    float *vely = &game->balls[i]->speed.y;

    /* Accelerate balls until max speed.    */
    if (fabs(*velx) < MAXSPEED && fabs(*vely) < MAXSPEED) {
        *velx *= ACC;
        *vely *= ACC;
    }
}

void ball_rotate(Game *game, int i) {
    game->balls[i]->angle += 1.6f;

    if (game->balls[i]->angle >= 360) {
        game->balls[i]->angle = 0.0;
    }
}

void ball_move(Game *game, int i) {
    /* Pointers to x, y and speed    for ball */
    float *velx = &game->balls[i]->speed.x;
    float *vely = &game->balls[i]->speed.y;
    int *posx = &game->balls[i]->rect.x;
    int *posy = &game->balls[i]->rect.y;

    /* Move balls in x and y    */
    *posx += (int)*velx;
    *posy += (int)*vely;
}

void ball_freeze(Game *game, int i) {
    game->balls[i]->rect.x = game->cursor.x - 25;
    game->balls[i]->rect.y = game->cursor.y - 25;
}

int ball_grab(Game *game) {
    /* Finds next free ball    */

    int i = 0;
    while (game->balls[i] != NULL && i < MAX_BALLS) {
        int *posx = &game->balls[i]->rect.x;
        int *posy = &game->balls[i]->rect.y;

        if (abs(*posx + 25 - game->cursor.x) < 20 && abs(*posy + 25 - game->cursor.y) < 20) {
            return i;
        }

        i++;
    }

    return -1;
}

void ball_border_check(Game *game, int i) {
    /* Pointers to x, y and speed    for ball */
    float *velx = &game->balls[i]->speed.x;
    float *vely = &game->balls[i]->speed.y;
    int *posx = &game->balls[i]->rect.x;
    int *posy = &game->balls[i]->rect.y;

    /* Check game window collision    */
    if (*posx + BALL_SIZE / 2 >= WINDOW_WIDTH) {
        *velx *= -1;
        *posx = WINDOW_WIDTH - BALL_SIZE;
    }

    if (*posx - BALL_SIZE / 2 < 0) {
        *velx *= -1;
        *posx = BALL_SIZE / 2;
    }

    if (*posy + BALL_SIZE / 2 >= WINDOW_HEIGHT) {
        *vely *= -1;
        *posy = WINDOW_HEIGHT - BALL_SIZE;
    }

    if (*posy - BALL_SIZE / 2 < 0) {
        *vely *= -1;
        *posy = BALL_SIZE / 2;
    }
}

void ball_hunt_cursor(Game *game, int i) {
    /* Pointers to x, y and speed    for ball */
    int *posx = &game->balls[i]->rect.x;
    int *posy = &game->balls[i]->rect.y;

    /* Position balls nearer current cursor location    */
    /* Calculate distance    */
    double distance = event_calculate_distance(*posx, game->cursor.x, *posy, game->cursor.y);

    if (distance < MAG_RADIUS) {
        game->balls[i]->speed.x = event_get_random_direction();
        game->balls[i]->speed.y = event_get_random_direction();
        if (*posx != game->cursor.x) {
            *posx = (*posx > game->cursor.x ? *posx - (int)lroundf(MAGSTR)
                                            : *posx + (int)lroundf(MAGSTR));
        }

        if (*posy != game->cursor.y) {
            *posy = (*posy > game->cursor.y ? *posy - (int)lroundf(MAGSTR)
                                            : *posy + (int)lroundf(MAGSTR));
        }
    }

    else {
        ball_move(game, i);
    }
}

void ball_avoid_cursor(Game *game, int i) {
    /* Pointers to x, y and speed    for ball */
    int *posx = &game->balls[i]->rect.x;
    int *posy = &game->balls[i]->rect.y;
    float *velx = &game->balls[i]->speed.x;
    float *vely = &game->balls[i]->speed.y;

    /* Position balls away from current cursor location    */
    /* Calculate distance    */
    double distance = event_calculate_distance(*posx, game->cursor.x, *posy, game->cursor.y);

    if (distance < REPEL_RADIUS) {
        ball_flip_direction(game, i, HORIZONTAL);
        ball_flip_direction(game, i, VERTICAL);

        *posx = (*posx > game->cursor.x ? *posx + (int)lroundf(fabsf(*velx) * 3.0f)
                                        : *posx - (int)lroundf(fabsf(*velx) * 3.0f));

        *posy = (*posy > game->cursor.y ? *posy + (int)lroundf(fabsf(*vely) * 3.0f)
                                        : *posy - (int)lroundf(fabsf(*vely) * 3.0f));
    }

    else {
        ball_move(game, i);
    }
}

void ball_kill_all(Game *game, int i) {
    /* Pointers to x, y and speed    for ball */
    int *posx = &game->balls[i]->rect.x;
    int *posy = &game->balls[i]->rect.y;

    /* Kill balls near cursor    */
    /* Calculate distance    */
    double distance = event_calculate_distance(*posx, game->cursor.x, *posy, game->cursor.y);

    if (distance < KILLSIZE) {
        ball_destroy(game, i);
        game->killedBalls++;
    }

    else {
        ball_move(game, i);
    }
}

void ball_flip_direction(Game *game, int i, bool direction) {
    if (direction == VERTICAL) {
        game->balls[i]->speed.x *= -1;
    }

    else {
        game->balls[i]->speed.y *= -1;
    }
}
