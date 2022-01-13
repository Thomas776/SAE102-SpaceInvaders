/*!
 *
 * @file    goodPixelManager.h
 * @date    January 2022
 * @version 1.0
 * @brief   Second screen display method
 *
 */


#ifndef GUARD_GOODPIXELMANAGER_H
#define GUARD_GOODPIXELMANAGER_H

#include "pixelManager.h"


/*!
 * @class GoodPixelManager
 * @brief Extension of the PixelManager class, which override
 * the draw methods to use sprites instead of shapes
 */
class GoodPixelManager : public PixelManager{

	/*!
	* @brief loads sprites in parallel using multiple threads
 	* @param[out] tasks : vectot of task
	* @fn void loadSprites();
	*/
	void loadSprites(vector<Task>& tasks) override;

	/*!
	* @brief sprite of the first player
	*/
	MySprite player1;

	/*!
	* @brief sprite of the second player
	*/
	MySprite player2;

	/*!
	* @brief sprite of the type A invader
	*/
	MySprite invaderA;

	/*!
	* @brief sprite of the type B invader
	*/
	MySprite invaderB;

	/*!
	* @brief sprite of the type B invader
	*/
	MySprite invaderC;

	/*!
	* @brief sprite of the missile
	*/
	MySprite missile;

	/*!
	* @brief sprite of the torpedo
	*/
	MySprite torpedo;

	/*!
	* @brief sprite of the heart
	*/
	MySprite heart;

	void drawInvaderA(const Position& baseVector, unsigned size, const RGBAcolor& color) const override;
	void drawInvaderB(const Position& baseVector, unsigned size, const RGBAcolor& color) const override;
	void drawInvaderC(const Position& baseVector, unsigned size, const RGBAcolor& color) const override;
	void drawPlayer(playerID pID, unsigned x, unsigned width, const RGBAcolor& color) const override;
	void drawMissile(const Position& baseVector, unsigned width, const RGBAcolor& color) const override;
	void drawTorpedo(const Position& baseVector, unsigned width, const RGBAcolor& color) const override;
	void drawHeart(const Position& baseVector) const override;
public:

	/*!
	* @brief constructor the pixel manager class
	* @param[in] window : window of the pixel manager
	* @fn GoodPixelManager(MinGL&);
	*/
	explicit GoodPixelManager(MinGL& window);
};


#endif
