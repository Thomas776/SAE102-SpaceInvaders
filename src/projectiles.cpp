/*!
 *
 * @file    projectiles.cpp
 * @date    January 2022
 * @version 1.0
 * @brief   projectiles data storage
 *
 */
#include "projectiles.h"

Torpedo::Torpedo(int x, int y, playerID owner) : Position(x, y) {
	this->owner = owner;
}
