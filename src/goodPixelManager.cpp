/*!
 *
 * @file    goodPixelManager.cpp
 * @date    January 2022
 * @version 1.0
 * @brief implementation of the second screen display method
 *
 */

#include "goodPixelManager.h"

void GoodPixelManager::loadSprites(vector<Task>& tasks) {
	PixelManager::loadSprites(tasks);
	ADD_SPRITE_TASK(player1)
	ADD_SPRITE_TASK(player2)
	ADD_SPRITE_TASK(invaderA)
	ADD_SPRITE_TASK(invaderB)
	ADD_SPRITE_TASK(invaderC)
	ADD_SPRITE_TASK(missile)
	ADD_SPRITE_TASK(torpedo)
	ADD_SPRITE_TASK(heart)
}

GoodPixelManager::GoodPixelManager(MinGL& win) : PixelManager(win) {

}

void GoodPixelManager::drawInvaderA(const Position& baseVector, unsigned size, const RGBAcolor &color) const {
	drawSprite(invaderA, baseVector);
}

void GoodPixelManager::drawInvaderB(const Position& baseVector, unsigned size, const RGBAcolor &color) const {
	drawSprite(invaderB, baseVector);
}

void GoodPixelManager::drawInvaderC(const Position& baseVector, unsigned size, const RGBAcolor &color) const {
	drawSprite(invaderC, baseVector);
}

void GoodPixelManager::drawPlayer(playerID pID, unsigned x, unsigned width, const RGBAcolor& color) const {
	Position pos(x, getScreenHeight() - PLAYER_HEIGHT);

	if (pID == PLAYER1) {
		drawSprite(player1, pos);
	} else if (pID == PLAYER2) {
		drawSprite(player2, pos);
	} else throw runtime_error("Invalid player ID to draw : " + to_string(pID));
}

void GoodPixelManager::drawMissile(const Position& baseVector, unsigned width, const RGBAcolor& color) const {
	drawSprite(missile, baseVector);
}

void GoodPixelManager::drawTorpedo(const Position& baseVector, unsigned width, const RGBAcolor& color) const {
	drawSprite(torpedo, baseVector);
}

void GoodPixelManager::drawHeart(const Position& baseVector) const {
	drawSprite(heart, baseVector);
}
