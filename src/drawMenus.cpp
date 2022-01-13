/*!
 *
 * @file    drawMenu.cpp
 * @date    January 2022
 * @version 1.0
 * @brief   menu drawing functions
 *
 */

#include <chrono>
#include <thread>
#include "mingl/shape/rectangle.h"
#include "playMode.h"
#include "pixelManager.h"
#include "utils.h"

using namespace nsShape;
using namespace nsGraphics;

void PixelManager::displayButton(const Position& baseVector, const string& text, nsGraphics::RGBAcolor& color){
    window << Rectangle(baseVector, Position(180, 40)+baseVector,  KGray);
	window << Rectangle(baseVector+Position(2,2), Position(178, 38)+baseVector,  KBlack);
    window << nsGui::Text(baseVector+Position(10,22), text, color);
}

void PixelManager::drawMenu(const Position& pos, Menu& currentMenu){
	startFrame();
	drawSprite(menuBackground, Position(0, 0));
	drawSprite(logo,Position(100,50));
	drawText(Position(10, 692), "tips:",nsGraphics::KWhite,Font::BITMAP_8_BY_13);
	drawText(Position(10, 702), "use 'z','s','q','d' and 'enter' to navigate the menus",nsGraphics::KWhite,Font::BITMAP_8_BY_13);
	drawText(Position(10, 712), "see the configuration file for player specific key bindings",nsGraphics::KWhite,Font::BITMAP_8_BY_13);
	drawText(Position(1150, 712), "version 1.0.0");
	unsigned margin = 0;
	unsigned cpt = 0;
	for(string& value : currentMenu.entries ){
		displayButton(Position(0,0+margin)+ pos, value, (currentMenu.selectedEntry == cpt) ? currentMenu.selectedColor : currentMenu.unSelectedColor );
		++cpt;
		margin += 50;
	}
	endFrame();
}


void PixelManager::drawMenu(const Position& pos, Menu& currentMenu, const vector<ScoreLink>& rankings, const WinValue& winner){
	startFrame();
	drawSprite(menuBackground, Position(0, 0));
	drawSprite(logo,Position(100,50));
	drawText(Position(1150, 700), "version 1.0.0");
	unsigned margin = 0;
	unsigned cpt = 0;
	if (winner == WinValue::PLAYERS) drawText(Position(0-55,0-20)+ pos,"The players won, earth is now safe",nsGraphics::KWhite);
	else if (winner == WinValue::INVADERS) drawText(Position(0-55,0-20)+ pos,"The invaders have reached earth",nsGraphics::KWhite);
	else drawText(Position(0-55,0-20)+ pos,"God won, as His power are infinite",nsGraphics::KWhite);
	for(string& value : currentMenu.entries ){
		displayButton(Position(0,0+margin)+ pos, value, (currentMenu.selectedEntry == cpt) ? currentMenu.selectedColor : currentMenu.unSelectedColor );
		++cpt;
		margin += 50;
	}
	margin = 0;
	drawText(Position(0,350), "Top 10 of the best players",nsGraphics::KWhite);
	for (auto& value: rankings){
		drawText(Position(0,400+margin),value.name,nsGraphics::KWhite,Font::BITMAP_HELVETICA_12);
		drawText(Position(140,400+margin),to_string(value.score),nsGraphics::KWhite,Font::BITMAP_HELVETICA_12);
		margin += 15;
	}
	endFrame();
}

PlayMode PixelManager::showInitialMenu(){
	vector<string> entries {"single player","multi player (local)","exit"};
	Menu initialMenu {entries, 0, nsGraphics::KRed, nsGraphics::KWhite};
	unsigned xOffset = getScreenHeight() / 2 ;
	unsigned yOffset = getScreenWidth() / 2 - 90;
	chrono::milliseconds waitTime = chrono::milliseconds(100);
	while(window.isOpen()){
		drawMenu(Position(yOffset, xOffset), initialMenu);
		// go down	
		if (window.isPressed({'s', false})){
			++initialMenu.selectedEntry;
			if (initialMenu.selectedEntry > initialMenu.entries.size() - 1) initialMenu.selectedEntry = 0;
			this_thread::sleep_for(waitTime);
		} 
		// go up
		if (window.isPressed({'z', false})){
			if (initialMenu.selectedEntry == 0) initialMenu.selectedEntry = initialMenu.entries.size() - 1;
			else --initialMenu.selectedEntry;
			this_thread::sleep_for(waitTime);
		}// select option
		else if (window.isPressed({13, false})){
			switch(initialMenu.selectedEntry){
				case 0:
					return PlayMode::SINGLE;
				case 1:
					return PlayMode::TWO_LOCAL;
				case 2:
					return PlayMode::EXIT;
				default:
					return PlayMode::SINGLE;
			}
		}
	}
	exit(0);
}

void PixelManager::askPlayerNameMenu(playerID pID, unsigned score, string& name) {
	name = string(6, 'A');
	unsigned currentSelected = 0 ;
	chrono::milliseconds waitTime = chrono::milliseconds(100);
	while (window.isOpen()){
		startFrame();
		drawSprite(menuBackground, Position(0, 0));
		drawText(Position(600, 100), "Nom du joueur " + to_string(pID + 1));
		drawText(Position(600, 150), "Score : " + to_string(score));
		for (unsigned i = 0; i < name.size(); ++i){
			drawText(Position(600 + 30 * i, 200), string(1, name[i]),
					 (i == currentSelected) ? nsGraphics::KRed : nsGraphics::KWhite);
		}
		endFrame();
		// go down	
		if (window.isPressed({'s', false})){
			++name[currentSelected];
			if (name[currentSelected] > 90) name[currentSelected] = 65;
			this_thread::sleep_for(waitTime);
		} 
		// go up
		if (window.isPressed({'z', false})){
			--name[currentSelected];
			if (name[currentSelected] < 65) name[currentSelected] = 90;
			this_thread::sleep_for(waitTime);
		}
		// go right	
		if (window.isPressed({'d', false})){
			++currentSelected;
			if (currentSelected > name.size()-1) currentSelected = 0;
			this_thread::sleep_for(waitTime);
		}
		// go left	
		if (window.isPressed({'q', false})){
			if (currentSelected == 0) currentSelected = name.size()-1;
			else --currentSelected;
			this_thread::sleep_for(waitTime);
		}
		// select option
		else if (window.isPressed({13, false}))
		{
			window.resetKey({13, false});
			return;
		}
	}
	exit(0);
}

bool PixelManager::showDeathMenu(const vector<ScoreLink>& rankings,const WinValue& winner) {
	vector<string> entries {"retry","main menu"};
	Menu death {entries,0,nsGraphics::KRed,nsGraphics::KWhite};
	unsigned xOffset = getScreenHeight() / 2 ;
	unsigned yOffset = getScreenWidth() / 2 - 90;
	chrono::milliseconds waitTime = chrono::milliseconds(100);
	while(window.isOpen()){
		drawMenu(Position(yOffset, xOffset), death, rankings, winner);
		// go down	
		if (window.isPressed({'s', false})){
			++death.selectedEntry;
			if (death.selectedEntry > death.entries.size() - 1) death.selectedEntry = 0;
			this_thread::sleep_for(waitTime);
		} 
		// go up
		if (window.isPressed({'z', false})){
			if (death.selectedEntry == 0) death.selectedEntry = death.entries.size() - 1;
			else --death.selectedEntry;
			this_thread::sleep_for(waitTime);
		}// select option
		else if (window.isPressed({13, false})){
			switch(death.selectedEntry){
				case 0:{
					return true;
				}
				case 1:{
					window.resetKey({13, false});
					return false;
				}
			}
		}
	}
	exit(0);
}



