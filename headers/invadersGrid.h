/*!
 *
 * @file    invaderGrid.h
 * @date    January 2022
 * @version 1.0
 * @brief   invader matrix structure
 *
 */


#ifndef GUARD_INVADERSGRID_H
#define GUARD_INVADERSGRID_H

#include<vector>

using namespace std;

/*!
 * @brief List of all invader type
 */
enum class InvaderType {
	TYPEA,
	TYPEB,
	TYPEC,
	NONE,
};

/*!
 * @class InvadersColumn
 * @brief Column of invader 
 */
class InvadersColumn : public vector<InvaderType>{
public:
	/*!
	 * @brief tells if the column contains no non type NONE invader
	 * @return True if there's only type NONE invader, False otherwise
	 * @fn bool hasNoValid() const; 
	 */
	bool hasNoValid() const;
	
	/*!
	 * @brief gives the index of the last valid (type different than NONE) invader
	 * @return index of the last valid invader if found, else size of the column 
	 * @fn unsigned getOutterInvader() const; 
	 */
	unsigned getOutterInvader() const;
	
	/*!
	 * @brief  Returns a random valid invader in the column (reminder, the column can contains NONE invaders)
	 * @return an index pointing to an invader in this column
	 * @fn unsigned randomValidInv() const;
	 */
	unsigned randomValidInv() const;
};


/*!
 * @class InvadersColumn
 * @brief Column of invader 
 */
class InvadersGrid : public vector<InvadersColumn>{
public:

	/*!
	 * @brief Helper function for randomValidCol() that returns the number of valid column
	 * (at least one invader in them) in the grid
	 * This is a separate function because we need to use it elsewhere
	 * @return The number of valid columns in the grid
	 * @fn unsigned validColsNumber() const;
	 */

	unsigned validColsNumber() const;

	/*!
	 * @brief  Returns a random valid column in the grid
	 * @return an index pointing to a column in the grid
	 * @fn unsigned randomValidCol() const;
	 */
	unsigned randomValidCol() const;
};

#endif