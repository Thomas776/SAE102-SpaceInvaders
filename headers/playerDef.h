/*!
 *
 * @file    playerDef.h
 * @date    January 2022
 * @version 1.0
 * @brief   player key configuration
 *
 */

#ifndef GUARD_PLAYER_DEF_H
#define GUARD_PLAYER_DEF_H

#include "mingl/graphics/rgbacolor.h"

/*!
 * @struct PlayerKeys
 * @brief player key configuration
 */
struct PlayerKeys {

	/*!
	* @brief key to move right
	*/
	char right;

	/*!
	* @brief key to move left
	*/
	char left;
	
	/*!
	* @brief key to shoot
	*/
	char shoot;
};

/*!
 * @struct PlayerDef
 * @brief player data, contains colors and key configuration
 */
struct PlayerDef {
	
	/*!
	* @brief player color
	*/
	nsGraphics::RGBAcolor color;
	
	/*!
	* @brief player key configuration
	*/
	PlayerKeys keys;
};

#endif
