/*!
 *
 * @file    mySprite.h
 * @date    January 2022
 * @version 1.0
 * @brief  Custom sprite implementation (needed for async load)
 *
 */

#ifndef GUARD_MYSPRITE_H
#define GUARD_MYSPRITE_H

#include <future>
#include <optional>
#include "mingl/gui/sprite.h"
#include "utils.h"

using namespace std;

class MySprite{
public:
	/*!
	 * @brief optional actual Sprite
	 * We need to use an optional to init the object through a function, that can be used with std::async
	 * mutable because for some reason MinGL stores a Vec2D with the pixel data,
	 * so we modify it each time we need to draw it
	 * Else, we could copy the Sprite each time, but copying a bunch of images each frame doesn't seems like a good idea
	 */
	mutable optional<nsGui::Sprite> sp;

	/*!
	 * @brief load a sprite asynchronously
	 * @fn Task asyncLoad(const string& fname);
	 * @returns An async task of the loading action
	 */
	Task asyncLoad(const string& fname);

	/*!
	 * @brief Mirror a sprite pixel data into this one
	 * @fn void mirror(MySprite& msp);
	 */
	void mirror(MySprite& msp);
};

#endif
