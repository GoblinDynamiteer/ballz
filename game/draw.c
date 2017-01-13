#include "..\def.h"

/*
 * draw.c
 *
 *  Created on: 8 jan. 2017
 *      Author: kampe_000
 */

bool renderGame(ballsGame * game){
	/*	 Sets background color	*/
	SDL_SetRenderDrawColor(game->renderer, 102, 204, 204, 255);
	SDL_RenderClear(game->renderer);

	/*	 Render balls and mouse cursor, order matters	*/
	renderBalls(game);
	renderCursor(game);

	/*	 Display text	*/
	char displayText[80];
	sprintf(displayText, "Added balls: %d", game->createdBalls);
	drawText(game, displayText, 0);
	sprintf(displayText, "Killed balls: %d", game->killedBalls);
	drawText(game, displayText, 1);

	/*	 Presents render	*/
	SDL_RenderPresent(game->renderer);
	return 1;
}

/*	 Draw text	*/
void drawText(ballsGame * game, char * text, int pos){
	SDL_Surface *textSurface;
	SDL_Color color = {0,0,0};
	textSurface = TTF_RenderText_Solid(
		game->font, text, color
	);
	SDL_Texture * textTexture = SDL_CreateTextureFromSurface(
		game->renderer, textSurface
	);
	SDL_Rect textRect = {10, FONT_SIZE * pos + 2, 0, 0};
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(game->renderer, textTexture, NULL, &textRect);

	SDL_FreeSurface(textSurface);
}

void renderBalls(ballsGame * game){
	/*	 Draws balls	*/
	for(int i = 0; i< MAX_BALLS; i++){
		if(!game->balls[i]){
			break;
		}
		if(!game->balls[i]->active){
			continue;
		}
		short color = game->balls[i]->color;
		SDL_RenderCopyEx(
			game->renderer,
			game->ballArt[color],
			NULL,
			&game->balls[i]->rect,
			game->balls[i]->angle,
			NULL,
			SDL_FLIP_NONE
		);
	}
}

void renderCursor(ballsGame * game){
	/*	 Draw mouse cursor	*/
	SDL_Rect cursorRect;

	/*	 Gets width and height from texture	*/
	SDL_QueryTexture(
		game->cursorArt[game->mode],
		NULL,
		NULL,
		&cursorRect.w,
		&cursorRect.h
	);

	cursorRect.x = game->cursor.x - cursorRect.w / 2;
	cursorRect.y = game->cursor.y - cursorRect.h / 2;

	if(game->mode == BLADE){
		game->cursorAngle += BLADE_SPEED;
	}

	else{
		game->cursorAngle = 0.0;
	}

	if(game->mode == REPEL){
		drawShield(game);
	}

	SDL_RenderCopyEx(
		game->renderer,
		game->cursorArt[game->mode],
		NULL,
		&cursorRect,
		game->cursorAngle,
		NULL,
		SDL_FLIP_NONE
	);
}

void drawShield(ballsGame * game){
	SDL_Rect shieldRect;

	/*	 Gets width and height from texture	*/
	SDL_QueryTexture(
		game->shield,
		NULL,
		NULL,
		&shieldRect.w,
		&shieldRect.h
	);

	shieldRect.x = game->cursor.x - shieldRect.w / 2;
	shieldRect.y = game->cursor.y - shieldRect.h / 2;

	SDL_RenderCopy(
		game->renderer,
		game->shield,
		NULL,
		&shieldRect
	);

}

