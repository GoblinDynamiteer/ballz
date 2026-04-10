#ifndef BALLZ_EVENT_H
#define BALLZ_EVENT_H

#include "def.h"

bool event_process_events(Game *game);
float event_get_random_direction(void);
void event_cycle_game_mode(Game *game, bool cycle_direction);
double event_calculate_distance(int x1, int x2, int y1, int y2);

#define BALLZ_EVENT_H

#endif // BALLZ_EVENT_H
