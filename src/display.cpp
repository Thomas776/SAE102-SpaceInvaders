/*!
 *
 * @file    display.cpp
 * @date    January 2022
 * @version 1.0
 * @brief   game display
 *
 */

#include "game.h"


/** Displays the screen once, and returns
 * The more important stuff must be drawn last
 */
void Game::displayAll(unsigned fps) const {
	pm->drawSprite(pm->gameBackground, Position(0, 0));
	for (unsigned i = 0; i < this->grid.size(); ++i){
		for (unsigned j = 0; j < this->grid[i].size(); ++j){
			Position vec(
					baseInvPos.getX() + i * confData.invadersSize + i * confData.invadersDistance,
					baseInvPos.getY() + j * confData.invadersSize + j * confData.invadersDistance
			);
			displayInvader(vec, grid[i][j]);
		}
	}

	for(const missile& miss : missiles){
		pm->drawMissile(miss, confData.missilesWidth, confData.missilesColor);
	}
	for(const Torpedo& tor : torpedos){
		pm->drawTorpedo(tor, confData.torpedosWidth, confData.torpedosColor);
	}

	
	displayGod();

	DEBUG_INSTR(
		pm->drawText(Position(pm->getScreenWidth()-200, 20), "FPS : "+to_string(fps), nsGraphics::KWhite, Font::BITMAP_8_BY_13);
	)

	unsigned margin = 0;
	for(unsigned i=0;i<players.size();++i){
		pm->drawText(Position(0,10+margin),"player "+to_string(i+1)+" :",nsGraphics::KWhite,Font::BITMAP_8_BY_13);
		pm->drawText(Position(100,10+margin),to_string(players[i].score) ,nsGraphics::KWhite,Font::BITMAP_8_BY_13);
		margin +=15;

		if(!players[i].isEliminated()){
			if(players[i].deathAnimCounter%2==0){
				pm->drawPlayer(i, players[i].x, confData.playersWidth, confData.playerDefs[i].color);
			}
		}
		// out of the condition, because we still need to display the falling heart
		displayHearts(i);
	}
}

void Game::displayHearts(playerID pID) const {

	// As said before, the player loop is an illusion, 2 players max
	unsigned x;
	if(pID==PLAYER1)x = 0;
	else x = pm->getScreenWidth()-HEART_LENGTH;

	unsigned y = GOD_BENCH_SIZE+5;
	for(unsigned i=0;i<players[pID].lives;++i){
		pm->drawHeart(Position(x, y));
		y+=HEART_LENGTH+5;
	}
	if(players[pID].hasDeathAnimation()){
		pm->drawHeart(Position(x, y+players[pID].deathAnimCounter*5));
	}
}

void Game::displayInvader(const Position& pos, InvaderType type) const {
	if(type==InvaderType::NONE)return;
	const InvaderTypeDef& invDef = confData.invadersDef.at(type);
	switch(type){
		case InvaderType::TYPEA:{
			pm->drawInvaderA(pos, confData.invadersSize, invDef.color);
			return;
		}
		case InvaderType::TYPEB:{
			pm->drawInvaderB(pos, confData.invadersSize, invDef.color);
			return;
		}
		case InvaderType::TYPEC:{
			pm->drawInvaderC(pos, confData.invadersSize, invDef.color);
			return;
		}
	}
}

void applyBezierCurve(Position& pos, const Position& point, const double percent) {
	pos += (point-pos)*percent;
}

void Game::displayGod() const {
	switch (god.state) {
		case GodState::NONE:
			return;
		case GodState::AWAKE: {
			pm->drawGodBench(god.counter - GOD_BENCH_SIZE);

			Position leftHand(GOD_HAND_DISTANCE, god.counter-GOD_BENCH_SIZE);
			Position rightHand(pm->getScreenWidth()-GOD_HAND_DISTANCE-GOD_HAND_SIZE, god.counter-GOD_BENCH_SIZE);
			pm->drawSprite(pm->leftHand, leftHand);
			pm->drawSprite(pm->rightHand, rightHand);
			pm->drawGodFace(god.counter - GOD_BENCH_SIZE);
			break;
		}
		case GodState::WAIT:{
			pm->drawGodBench(0);
			Position leftHand(GOD_HAND_DISTANCE, 0);
			Position rightHand(god.getRightHandPos(pm->getScreenWidth()));
			pm->drawSprite(pm->leftHand, leftHand);
			pm->drawSprite(pm->rightHand, rightHand);
			pm->drawGodFace(0);
			break;
		}
		case GodState::RETRIEVE1:
		case GodState::RETRIEVE2:{
			// Bezier curve
			// counter goes [0-100]
			pm->drawGodBench(0);
			pm->drawSprite(pm->leftHand, Position(GOD_HAND_DISTANCE, 0));
			pm->drawGodFace(0);

			Position pos(god.getRightHandPos(pm->getScreenWidth()));
			Position endPos = invIndexToPos(god.thrownInvPosX, god.thrownInvPosY);

			applyBezierCurve(pos, god.thrownTransition, god.counter / 100.0);
			applyBezierCurve(pos, endPos, god.counter / 100.0);

			// pos is now the position we need to draw our hand to
			pm->drawSprite(pm->rightHand, pos);
			if(god.thrownInvType!=InvaderType::NONE){

				pos+=Position(GOD_HAND_SIZE/2, GOD_HAND_SIZE/2);
				pos-=Position(confData.invadersSize/2, confData.invadersSize/2);
				displayInvader(pos, god.thrownInvType);
			}
			break;
		}
		case GodState::THROW:{
			pm->drawGodBench(0);
			pm->drawSprite(pm->leftHand, Position(GOD_HAND_DISTANCE, 0));
			pm->drawGodFace(0);

			// compute start position (not sure if we should store it or compute it each time ?)
			Position handPos = god.getRightHandPos(pm->getScreenWidth());

			Position invaderPos = handPos;
			applyTransformation(invaderPos, GOD_HAND_SIZE, confData.invadersSize);
			Position a = god.thrownVector * (god.counter / 100.0);
			invaderPos = invaderPos + a;

			displayInvader(invaderPos, god.thrownInvType);
			if(god.counter<30){
				// handling hand retraction
				unsigned handCounter;
				if(god.counter<15)handCounter = god.counter;
				else handCounter = 30-god.counter;
				handPos = handPos + god.thrownVector * (handCounter / 100.0);
			}
			pm->drawSprite(pm->rightHand, handPos);

			break;
		}
	}
}
