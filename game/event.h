#ifndef BALLZ_EVENT_H
#define BALLZ_EVENT_H

#include "def.h"

bool processEvent(ballsGame * game);
float getRandomDirection(void);
void cycleGameMode(ballsGame * game, bool cycle_direction);
double calculateDistance(int x1, int x2, int y1, int y2);

#define BALLZ_EVENT_H

#endif //BALLZ_EVENT_H
