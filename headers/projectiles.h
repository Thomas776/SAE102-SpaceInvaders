/*!
 *
 * @file    projectiles.h
 * @date    January 2022
 * @version 1.0
 * @brief   projectiles data storage
 *
 */

#ifndef GUARD_PROJECTILES_H
#define GUARD_PROJECTILES_H

#include "utils.h"

typedef Position missile;

/*!
 * @class Torpedo
 * @brief player's projectiles 
 */
class Torpedo : public Position {
public:
	
	/*!
	 * @brief id of the player that shot the torpedo
	 */
	playerID owner;
	
	/*!
	 * @brief constuctor for the torpedo class
	 * @param[in] x : horizontal pixel coordinate
	 * @param[in] y : vertical pixel coordinate 
	 * @fn Torpedo(int x, int y, playerID owner);
	 */
	Torpedo(int x, int y, playerID owner);
};

#endif
