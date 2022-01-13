/*!
 *
 * @file    invaderDef.h
 * @date    January 2022
 * @version 1.0
 * @brief   invader type deffinition and related data  
 *
 */

#ifndef GUARD_INVADERDEF_H
#define GUARD_INVADERDEF_H

#include "mingl/graphics/rgbacolor.h"
#include "utils.h"
	
/*!
 * @struct InvaderTypeDef
 * @brief defines an invader type
 */
struct InvaderTypeDef {
	/*!
 	* @brief color of the invader type
 	*/
	nsGraphics::RGBAcolor color;

	/*!
 	* @brief points given to the player by defeating this invader type
 	*/
	unsigned points;
};

#endif
