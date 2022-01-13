/*!
 *
 * @file    god.h
 * @date    January 2022
 * @version 1.0
 * @brief   Special entity known as "God"  
 *
 *  Well, I (Djalim) discovered that Thomas put God in the game
 *  I didnt think it was a good idea but no man can stop Thomas
 *
 */

#ifndef GUARD_GOD_H
#define GUARD_GOD_H

#include "utils.h"
#include "invadersGrid.h"

/*!
 * @brief list of all known god states
 */
enum class GodState{
	NONE,
	AWAKE,
	WAIT,
	RETRIEVE1,
	RETRIEVE2,
	THROW,
};


// I don't want to put that in config, I feel like it would be useless and overkill at this point
#define GOD_BENCH_SIZE 64
#define GOD_HAND_SIZE 64
#define GOD_HAND_DISTANCE 100


/*!
 * Hand position is determined
 */

/*!
 * @class God
 * @brief stores all God's data
 */
class God{
public:
	
	/*!
 	* @brief god's current state
 	*/
	GodState state;
	
	/*!
 	* @brief timer used differently in all states
 	*/
	unsigned counter;


	// we do not use a Position because it is not used for pixel coordinate, but vector indexes
	/*!
 	* @brief x index (column in the grid) of the invader thrown by the hand of god
 	*/
	unsigned thrownInvPosX;
	
	/*!
 	* @brief y index (invader in the column) of the invader thrown by the hand of god
 	*/
	unsigned thrownInvPosY;
	
	/*!
 	* @brief type of the invader thrown by the hand of god
 	*/
	InvaderType thrownInvType;
	
	/*!
 	* @brief direction of the thrown invader movement
 	*/
	Position thrownVector;
	
	/*!
 	* @brief position of a point for bezier's curve (used in RETRIEVE1 and RETRIEVE2 states, for the hand animation)
 	*/
	Position thrownTransition;

	/*!
 	* @brief give initial the pixel coordinates of god's right hand
	* @param[in] screenWidth : width of the screen in pixel
	* @return pixel coordinates of the hand
	* @fn Position getRightHandPos(unsigned screenWidth) const; 
 	*/
	Position getRightHandPos(unsigned screenWidth) const;

};

#endif
