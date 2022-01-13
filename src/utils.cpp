/*!
 *
 * @file    utils.cpp
 * @date    January 2022
 * @version 1.0
 * @brief    utility for the game
 *
 */

#include "utils.h"

bool areLinesColliding(unsigned start1, unsigned end1, unsigned start2, unsigned end2){
	return start1 < end2 == start2 < end1;
	// if it returns true, lines are colliding. I like truth tables
}

void applyTransformation(Position& pos, unsigned sizeFrom, unsigned sizeTo){
	pos += Position(sizeFrom/2, sizeFrom/2);
	pos -= Position(sizeTo/2, sizeTo/2);
}