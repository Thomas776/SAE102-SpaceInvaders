/*!
 *
 * @file    drawEntity.cpp
 * @date    January 2022
 * @version 1.0
 * @brief   entity drawing functions
 *
 */

#include "mingl/gui/text.h"
#include "pixelManager.h"
#include "utils.h"
#include "god.h"

using namespace nsShape;
using namespace nsGui;


PixelManager::PixelManager(MinGL& win) : window(win) {
	window.initGlut();
	window.initGraphic();
}

void PixelManager::drawHeart(const Position& baseVector) const {
	window << Circle(Position(10, 10)+baseVector,10, nsGraphics::KRed);
	window << Circle(Position(30, 10)+baseVector,10, nsGraphics::KRed);
	window << Triangle(Position(0,10)+baseVector,Position(40,10)+baseVector,Position(20,40)+baseVector,nsGraphics::KRed);
}

void PixelManager::drawInvaderA(const Position& baseVector, unsigned size, const RGBAcolor& color) const {
	float scale = size/(float)100;
	window << Circle(Position(50*scale, 50*scale)+baseVector, 50*scale, nsGraphics::KGray);
	window << Triangle(Position(35*scale, 50*scale)+baseVector, Position(15*scale, 25*scale)+baseVector, Position(15*scale, 75*scale)+baseVector, nsGraphics::KBlack);
	window << Triangle(Position(25*scale, 50*scale)+baseVector, Position(10*scale, 25*scale)+baseVector, Position(10*scale, 75*scale)+baseVector, nsGraphics::KGray);
	window << Triangle(Position(65*scale, 50*scale)+baseVector, Position(85*scale, 25*scale)+baseVector, Position(85*scale, 75*scale)+baseVector, nsGraphics::KBlack);
	window << Triangle(Position(75*scale, 50*scale)+baseVector, Position(90*scale, 25*scale)+baseVector, Position(90*scale, 75*scale)+baseVector, nsGraphics::KGray);
	window << Rectangle(Position(35*scale, 65*scale)+baseVector, Position(65*scale, 72*scale)+baseVector, nsGraphics::KBlack);
}

void PixelManager::drawInvaderB(const Position& baseVector, unsigned size, const RGBAcolor& color) const {
	float scale = size/(float)100;
	window << Circle(Position(50*scale, 50*scale)+baseVector, 50*scale, nsGraphics::KRed);
	window << Rectangle(Position(25*scale, 30*scale)+baseVector, Position(45*scale, 40*scale)+baseVector, nsGraphics::KBlack);
	window << Rectangle(Position(55*scale, 30*scale)+baseVector, Position(75*scale, 40*scale)+baseVector, nsGraphics::KBlack);
	window << Rectangle(Position(35*scale, 65*scale)+baseVector, Position(65*scale, 72*scale)+baseVector, nsGraphics::KBlack);
}

void PixelManager::drawInvaderC(const Position& baseVector, unsigned size, const RGBAcolor& color) const {
	float scale = size/(float)100;
	window << Circle(Position(50*scale, 50*scale)+baseVector, 50*scale, nsGraphics::KGreen);
	window << Circle(Position(35*scale, 35*scale)+baseVector, 10*scale, nsGraphics::KBlack);
	window << Circle(Position(65*scale, 35*scale)+baseVector, 10*scale, nsGraphics::KBlack);
	window << Rectangle(Position(35*scale, 65*scale)+baseVector, Position(65*scale, 72*scale)+baseVector, nsGraphics::KBlack);
}

// playerID argument is unused here, so we don't even give it a name
void PixelManager::drawPlayer(playerID, unsigned x, unsigned width, const nsGraphics::RGBAcolor& color) const {
	width = width-10-10;
	width = width/2;
	window << Triangle(Position(0+x, 720), Position(5+x, 720), Position(5+x, 720-PLAYER_HEIGHT/2), color);
	window << Rectangle(Position(5+x, 720), Position(5+width+x, 720-PLAYER_HEIGHT/2), color);
	window << Rectangle(Position(5+width+x, 720), Position(15+width+x, 720-PLAYER_HEIGHT), color);
	window << Rectangle(Position(15+width+x, 720), Position(15+width*2+x, 720-PLAYER_HEIGHT/2), color);
	window << Triangle(Position(15+width*2+x, 720), Position(15+width*2+x, 720-PLAYER_HEIGHT/2), Position(20+width*2+x, 720), color);
	window << Triangle(Position(5+x,720-PLAYER_HEIGHT/2), Position(5+width+x,720-PLAYER_HEIGHT/2), Position(5+width+x,720-PLAYER_HEIGHT*0.9), color);
	window << Triangle(Position(15+width+x,720-PLAYER_HEIGHT/2), Position(15+width*2+x,720-PLAYER_HEIGHT/2), Position(15+width+x,720-PLAYER_HEIGHT*0.9), color);
}

void PixelManager::drawMissile(const Position& baseVector, unsigned width, const nsGraphics::RGBAcolor& color) const {
	window << Rectangle(baseVector, baseVector + Position(width, width * PROJ_LENGTH_FACTOR), color);

}

void PixelManager::drawTorpedo(const Position& baseVector, unsigned width, const nsGraphics::RGBAcolor& color) const {
	window << Rectangle(baseVector, baseVector + Position(width, width * PROJ_LENGTH_FACTOR), color);
}

void PixelManager::drawSprite(const MySprite& msp, const Position& pos) const {
	// The sprite is associated with a Vec2D for whatever reason, so yeah, we modify it each time we draw it
	msp.sp->setPosition(pos);
	msp.sp->draw(window);
}

void PixelManager::drawGodBench(int y) const {
	window << Rectangle(Position(0, y), Position(getScreenWidth(), y+GOD_BENCH_SIZE), nsGraphics::KGray);
}

void PixelManager::drawGodFace(int y, bool angry) const {
	Text t(
		Position(getScreenWidth()/2, y),
		angry ? ">w<" : ".w.",
		nsGraphics::KBlue,
		GlutFont::GlutFonts::BITMAP_TIMES_ROMAN_24,
		Text::HorizontalAlignment::ALIGNH_CENTER
	);

	// computeHeight() returns a height bigger than the actual text size, that's why there's padding above it(
	t.setPosition(t.getPosition()+Position(0, t.computeHeight()));
	window << t;

}

void PixelManager::drawText(const Position& pos, const string& text, const nsGraphics::RGBAcolor& color, Font font) const {
	window << Text(pos, text, color, font);
}
