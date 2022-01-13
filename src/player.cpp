/**
 *
 * @file    player.h
 * @date    January 2022
 * @version 1.0
 * @brief   player data storage
 *
 **/
 
#include "player.h"

bool Player::isPlaying() const {
	return !isEliminated() && !hasDeathAnimation();
}

bool Player::hasDeathAnimation() const {
	return deathAnimCounter!=0;
}

bool Player::isEliminated() const {
	return lives == 0;
}

void Player::damage() {
	--lives;
	deathAnimCounter = 1;
}