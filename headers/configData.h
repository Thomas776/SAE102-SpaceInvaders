/*!
 *
 * @file    configData.h
 * @date    January 2022
 * @version 1.0
 * @brief   Configuration file data storage
 *
 */

#ifndef GUARD_CONFIGDATA_H
#define GUARD_CONFIGDATA_H

#include<string>
#include "utils.h"
#include "playerDef.h"
#include "invaderDef.h"
#include "invadersGrid.h"

typedef string configKey;


/*!
 * @struct ConfigData
 * @brief this struct stores all relevant data from the configuration file
 */
struct ConfigData {

	/*!
	 * @brief theme to use. Valid values : good,bad
	 */
	string theme;

	/*!
	 * @brief maximum framerate at which the game will run
	 */
	unsigned maxFPS;
	
	/*!
	 * @brief Invader type matrix
	 */
	InvadersGrid grid;

	/*!
	 * @brief players horizontal start position
	 */
	unsigned startXPosition;
	
	/*!
	 * @brief player movement speed
	 */
	unsigned playersSpeed;
	
	/*!
	 * @brief player horizontal size in pixel
	 */
	unsigned playersWidth;

	/*!
	 * @brief player shooting wait time
	 */
	unsigned playersFireCooldown;

	/*!
	 * @brief player life points
	 */
	unsigned playersLives;

	/*!
	 * @brief players configuration
	 */
	vector<PlayerDef> playerDefs;

	/*!
	 * @brief invader movement speed
	 */
	unsigned invadersSpeed;

	/*!
	 * @brief invader radius size in pixel
	 */
	unsigned invadersSize;
	
	/*!
	 * @brief distance in pixel between two invader
	 */
	unsigned invadersDistance;

	/*!
	 * @brief wait time between two invader missile
	 */
	unsigned invadersFireCooldown;

	/*!
	 * @brief link between an invader type, and its data
	 */
	map<InvaderType, InvaderTypeDef> invadersDef;

	/*!
	 * @brief invaders missiles width in pixel
	 */
	unsigned missilesWidth;
	
	/*!
	 * @brief virtual value : invaders missiles length in pixel - auto defined from width
	 */
	unsigned missilesLength;
	
	/*!
	 * @brief invaders missiles movement speed
	 */
	unsigned missilesSpeed;

	/*!
	 * @brief invaders missiles color 
	 */
	nsGraphics::RGBAcolor missilesColor;

	/*!
	 * @brief players torpedos width in pixel
	 */
	unsigned torpedosWidth;

	/*!
	 * @brief virtual value : players torpedos length in pixel - auto defined from width
	 */
	unsigned torpedosLength; 

	/*!
	 * @brief players topedos movement speed 
	 */
	unsigned torpedosSpeed;
	
	/*!
	 * @brief players torpedos color 
	 */
	nsGraphics::RGBAcolor torpedosColor;
};

#endif