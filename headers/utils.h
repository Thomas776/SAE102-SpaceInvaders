/*!
 *
 * @file    utils.h
 * @date    January 2022
 * @version 1.0
 * @brief   utilies for the game
 *
 */

#ifndef GUARD_UTILS_H
#define GUARD_UTILS_H

#include<vector>
#include<future>
#include "mingl/mingl.h"

// hardcoded values
#define PLAYER_HEIGHT 100
#define PROJ_LENGTH_FACTOR 2

#define INV_GET_SINGLE_POS(i) confData.invadersSize*(i)+confData.invadersDistance*(i)

// Syntax : DEBUG(cout << "hey" << endl)
// The debug flag defintion has been set here, but normally we would add it to the MakeFile
//#define DEBUG_FLAG

#ifdef DEBUG_FLAG
#define DEBUG_MSG(X) cerr << "DEBUG: " << X << endl;
#define DEBUG_INSTR(X) X;
#else
#define DEBUG_MSG(X)
#define DEBUG_INSTR(X)
#endif


using namespace std;
using nsGraphics::RGBAcolor;

/*!
 * @brief list of win values
 */
enum class WinValue{
	NOBODY, // should never be used
	PLAYERS,
	INVADERS,
	GOD,
};


typedef nsGraphics::Vec2D Position;
typedef unsigned playerID;
typedef future<void> Task;
#define PLAYER1 0
#define PLAYER2 1


/*!
 * @brief tells if 2 lines are colliding in a 1 dimensional space. Didn't want to use Position because of the semantic with x and y
 * @param[in] start1 : position of the first point of the first line
 * @param[in] end1: position of the last point of the first line
 * @param[in] start2 : position of the first point of the seconde line
 * @param[in] end2: position of the last point of the second line
 * @return true if they are colliding, false otherwise
 */
bool areLinesColliding(unsigned start1, unsigned end1, unsigned start2, unsigned end2);

// change draw position for a specified size (keeps the same center)

/*!
 * @brief change the position object to reflect the top-right position of a "sizeTo"-sized entity, from a "sizeFrom"-sized entity, keeping the same center
 * @param[in,out] pos : Position object
 * @param[in] sizeFrom: current size of the objet
 * @param[in] sizeTo : new size of the object
 */
void applyTransformation(Position& pos, unsigned sizeFrom, unsigned sizeTo);

#endif