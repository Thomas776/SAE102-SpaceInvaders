/*!
 *
 * @file    pixelManager.h
 * @date    January 2022
 * @version 1.0
 * @brief    Manages screen display
 *
 */

#ifndef GUARD_PIXELMANAGER_H
#define GUARD_PIXELMANAGER_H

#include <string>
#include "mingl/mingl.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/gui/sprite.h"
#include "mingl/gui/text.h"
#include "utils.h"
#include "playMode.h"
#include "menu.h"
#include "scoresManager.h"
#include "mySprite.h"

using namespace std;

typedef nsGui::GlutFont::GlutFonts Font;

/*!
* @class PixelManager
* @brief main display function, clear the window and calls sub display functions
*/

/*
 * It's MinGL's fault. This is all I have to say
 */

#define ADD_SPRITE_TASK(X) tasks.push_back((X).asyncLoad("assets/"#X".si2"));

class PixelManager{
public:

	/*!
	* @brief display window
	*/
	MinGL& window;

	/*!
	* @brief loads sprites in parallel using multiple threads
 	* @param[in] tasks : vectot of task 
	* @fn void loadSprites();
	*/
	 virtual void loadSprites(vector<Task>& tasks);

	/*!
	* @brief sprite of the logo of the game
	*/
	MySprite logo;

	/*!
	* @brief sprite of the background during menu
	*/
	MySprite menuBackground;

	/*!
	* @brief sprite of the background during gameplay
	*/
	MySprite gameBackground;

	/*!
	* @brief sprite of the right hand of god
	*/
	MySprite rightHand;
	
	/*!
	* @brief sprite of the left hand of god
	*/
	MySprite leftHand;

	/*!
	* @brief constructor the pixel manager class
	* @param[in] window : window of the pixel manager
	* @fn PixelManager(MinGL&);
	*/
	explicit PixelManager(MinGL& window);

	/*!
 	* @brief display a type A invader on screen
 	* @param[in] baseVector : pixel coordinate of the invader
	* @param[in] size : size multiplicator of the invader
	* @param[in] color : color multiplicaror of the invader
	* @fn void drawInvaderA(const Position& baseVector, unsigned size, const RGBAcolor& color) const; 
	*/
	virtual void drawInvaderA(const Position& baseVector, unsigned size, const RGBAcolor& color) const;
	
	/*!
 	* @brief display a type B invader on screen
 	* @param[in] baseVector : pixel coordinate of the invader
	* @param[in] size : size multiplicator of the invader
	* @param[in] color : color multiplicaror of the invader
	* @fn void drawInvaderB(const Position& baseVector, unsigned size, const RGBAcolor& color) const;
	*/
	virtual void drawInvaderB(const Position& baseVector, unsigned size, const RGBAcolor& color) const;
	
	/*!
 	* @brief display a type C invader on screen
 	* @param[in] baseVector : pixel coordinate of the invader
	* @param[in] size : size multiplicator of the invader
	* @param[in] color : color multiplicaror of the invader
	* @fn void drawInvaderC(const Position& baseVector, unsigned size, const RGBAcolor& color) const; 
	*/
	virtual void drawInvaderC(const Position& baseVector, unsigned size, const RGBAcolor& color) const;
	
	/*!
	* @brief display a player on screen
	* @param[in] pID : the ID of the player to draw
	* @param[in] x : horizontal position of the player
	* @param[in] witdh : width of the player
	* @param[in] color : color of the plater
	* @fn void drawPlayer(unsigned x, unsigned width, const nsGraphics::RGBAcolor& color) const;
	*/
	virtual void drawPlayer(playerID pID, unsigned x, unsigned width, const nsGraphics::RGBAcolor& color) const;
	
	/*!
	* @brief display a missile on screen
	* @param[in] baseVector : pixel coordinates of the missile
	* @param[in] width : width of the missle
	* @param[in] color : color of the missile
	* @fn void drawMissile(const Position& baseVector, unsigned width, const nsGraphics::RGBAcolor& color) const;
	*/
	virtual void drawMissile(const Position& baseVector, unsigned width, const nsGraphics::RGBAcolor& color) const;
	
	/*!
	* @brief display a torpedo on screen
	* @param[in] baseVector : pixel coordinates of the torpedo
	* @param[in] width : width of the torpedo
	* @param[in] color : color of the torpedo
	* @fn void drawTorpedo(const Position& baseVector, unsigned width, const nsGraphics::RGBAcolor& color) const;
	*/
	virtual void drawTorpedo(const Position& baseVector, unsigned width, const nsGraphics::RGBAcolor& color) const;

#define HEART_LENGTH 64

	/*!
	* @brief display a singular heart on screen
	* @param[in] baseVector : pixel coordinates of the heart
	* @fn void drawHeart(const Position& baseVector) const;
	*/
	virtual void drawHeart(const Position& baseVector) const;
	
	/*!
	* @brief display a sprite on screen
	* @param[in] msp : sprite to draw
	* @param[in] pos : pixel coordinates to draw the sprite 
	* @fn void drawSprite(const MySprite& msp, const Position& pos = Position(0, 0)) const;
	*/
	void drawSprite(const MySprite& msp, const Position& pos) const;
	
	/*!
	* @brief display a menu button on screen
	* @param[in] baseVector : pixel coordinates of the button
	* @param[in] text : text inside the button
	* @param[in] color : color of the text inside the button
	* @fn void displayButton(const Position& baseVector,const string& text,nsGraphics::RGBAcolor& color);
	*/
	void displayButton(const Position& baseVector,const string& text,nsGraphics::RGBAcolor& color);

	/*!
	* @brief display text on screen
	* @param[in] pos : pixel coordinates of the text
	* @param[in] text : text to show on screen
	* @param[in] color : color of the text to show
	* @param[in] font : the glut font to use for the text
	* @fn void drawText(const Position& pos, const string& text, const RGBAcolor& color = nsGraphics::KWhite, Font font = Font::BITMAP_TIMES_ROMAN_24) const;
	*/
	void drawText(const Position& pos, const string& text, const RGBAcolor& color = nsGraphics::KWhite, Font font = Font::BITMAP_TIMES_ROMAN_24) const;

	/*!
	* @brief show the title screen of the game
	* @return the playmode chosen inside the menu 
	* @fn PlayMode showInitialMenu();
	*/
	PlayMode showInitialMenu();

	/*!
	* @brief show the menu after a player lose, or all invader has been defeated
	* @return true if the player plays again, else false
	* @param[in] rankings : the current top 5 score
	* @param[in] winner : the winner of the game 
	* @fn bool showDeathMenu();
	*/
	bool showDeathMenu(const vector<ScoreLink>& rankings,const WinValue& winner);

	/*!
	* @brief give the height of the screen
	* @return the height of the screen in pixel
	* @fn unsigned getScreenHeight() const;
	*/
	unsigned getScreenHeight() const;
	
	/*!
	* @brief give the width of the screen
	* @return the width of the screen in pixel
	* @fn unsigned getScreenWidth() const;
	*/
	unsigned getScreenWidth() const;
	
	/*!
	* @brief clear the screen for a new frame
	* @fn void startFrame() const;
	*/
	void startFrame() const;
	
	/*!
	* @brief finish a frame render
	* @fn void endFrame() const;
	*/
	void endFrame() const;

	/*!
	* @brief display the player name selection menu
	* @param[in] pID : player id
	* @param[in] score : score of this player
	* @param[out] name : name selected by the player
	* @fn void askPlayerNameMenu(playerID pID, unsigned score, string& name);
	*/
	void askPlayerNameMenu(playerID pID, unsigned score, string& name);

	// y will be negative sometimes, so not unsigned
	
	/*!
	* @brief display god's bar
	* @param[in] y : god y pixel position
	* @fn void drawGodBench(int y) const
	*/
	void drawGodBench(int y) const;
	
	/*!
	* @brief display god's face
	* @param[in] y : god's face y pixel position
	* @param[in] angry : flag if god is angry or not
	* @fn void drawGodFace(int y, bool angry=false) const;
	*/
	void drawGodFace(int y, bool angry=false) const;

private:

	/*!
	* @brief display a menu on screen
	* @param[in] pos : pixel coordinates of the menu
	* @param[in,out] currentMenu : menu struct conteining the menu option
	* @fn void drawMenu(const Position& pos, Menu& currentMenu);
	*/
	void drawMenu(const Position& pos, Menu& currentMenu);

	/*!
	* @brief display a menu on screen
	* @param[in] pos : pixel coordinates of the menu
	* @param[in,out] currentMenu : menu struct conteining the menu option
	* @param[in] rankings : the current top 10 players
	* @param[in] winner : the winner of the game
	* @fn void drawMenu(const Position& pos, Menu& currentMenu);
	*/
	void drawMenu(const Position& pos, Menu& currentMenu, const vector<ScoreLink>& rankings, const WinValue& winner);
};


#endif