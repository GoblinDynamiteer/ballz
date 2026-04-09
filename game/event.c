#include <math.h>

#include "def.h"
#include "balls.h"
#include "event.h"


/* Process game events */
bool event_process_events(ballsGame * game)
{
    /* Event union */
    SDL_Event event;
    bool quit = 0;

    while(SDL_PollEvent(&event))
    {
        Uint32 type = event.type;
        switch(type)
        {
            /* Close button is pressed */
            case SDL_QUIT:
                quit = 1;
                break;

            /* A key has been pressed */
            case SDL_KEYDOWN:
                if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    quit = 1;
                }
                break;

            /* A mouse button has been pressed */
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    if(game->mode == NORMAL)
                    {
                        ball_add(game, game->cursor.x, game->cursor.y);
                    }

                    if(game->mode == NEO)
                    {
                        game->grabbedBallIndex = ball_grab(game);
                    }
                }
                break;

            case SDL_MOUSEWHEEL:
                event_cycle_game_mode(game, (event.wheel.y < 0));
                break;
        }
    }

    /*	 Gets mouse cursor position	*/
    Uint32 mouseState = SDL_GetMouseState(&game->cursor.x, &game->cursor.y);

    if(mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
    {
        for(int i = 0; i< BALLS_PER_SPRAY; i++)
        {
            ball_add(game, game->cursor.x, game->cursor.y);
        }
    }

    if((mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
        game->mode == NEO &&
        game->grabbedBallIndex >= 0)
        {
            ball_freeze(game, game->grabbedBallIndex);
        }

    /*	 Moves and rotate balls	*/
    for(int i = 0; i< MAX_BALLS; i++)
    {
        /*	 Break if NULL pointer	*/
        if(!game->balls[i])
        {
            break;
        }
        /*	 Skip if ball is inactive	*/
        if(!game->balls[i]->active)
        {
            continue;
        }

        switch(game->mode)
        {
            case NORMAL:
                ball_move(game, i);
                break;
            case MAGNET:
                ball_hunt_cursor(game, i);
                break;
            case REPEL:
                ball_avoid_cursor(game, i);
                break;
            case BLADE:
                ball_kill_all(game, i);
                break;
            case NEO:
                ;
                break;
        }

        ball_rotate(game, i);
        accelBall(game, i);
        ball_border_check(game, i);
    }

    game->ticker++;

    return (quit == 0);
}

/*	 Uses distance formula	*/
double event_calculate_distance(int x1, int x2, int y1, int y2)
{
    double calc =
    sqrt(
        pow((float)x1 - (float)x2, 2) +
        pow((float)y1 - (float)y2, 2)
    );

    return calc;
}

/* Generates a random direction (and speed) for new balls */
float event_get_random_direction(void)
{
    float direction = (float)(rand() % 5)
        + (float)(rand() % 10) / 10.0f;

    return (rand() % 10 > 5) ? 0.4 + direction : 0.4 - direction;
}


void event_cycle_game_mode(ballsGame * game, bool cycle_direction)
{
    game->mode = (game->mode == MAX_GAME_TYPES -1 ) ?
    NORMAL : (cycle_direction ? game->mode + 1 : game->mode +1);
}
