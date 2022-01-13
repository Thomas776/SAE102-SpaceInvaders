/*!
 *
 * @file    gameBasics.cpp
 * @date    January 2022
 * @version 1.0
 * @brief   game basic mechanisms
 *
 */

#include<algorithm>
#include "game.h"

#define ISPRESSED(ID, X) window.isPressed({confData.playerDefs[ID].keys.X, false})
void Game::manageOnePlayer(playerID pID){
	Player& p = players[pID];
	if(p.hasDeathAnimation()) {
		++p.deathAnimCounter;
		if (p.deathAnimCounter == 75) {
			p.deathAnimCounter = 0;
		}
	}
	if(p.isEliminated())return;

	if (ISPRESSED(pID, left)){
		if(p.x < confData.playersSpeed) p.x = 0;
		else p.x -= confData.playersSpeed;
	}
	if (ISPRESSED(pID, right)){
		if(p.x + confData.playersWidth + confData.playersSpeed >= pm->getScreenWidth()) p.x = pm->getScreenWidth() - confData.playersWidth - 1;
		else p.x += confData.playersSpeed;
	}


	if(!p.hasDeathAnimation()) {
		if(p.fireCooldown==0) {
			if (ISPRESSED(pID, shoot)) {
				torpedos.emplace_back(p.x + confData.playersWidth / 2, pm->getScreenHeight() - PLAYER_HEIGHT, pID);
				p.fireCooldown = confData.playersFireCooldown;
			}
		}else --p.fireCooldown;
	}
}

void Game::managePlayers(){
	for(unsigned i=0;i<players.size();++i)manageOnePlayer(i);
}

bool Game::manageInvaders(){
	if(!areThereInvadersLeft())return false; // If there are no more invaders we don't need to manage them

	// shoot
	if(fireCooldown==0) {
		fireCooldown = confData.invadersFireCooldown + rand() % 25;

		unsigned rdCol = grid.randomValidCol();
		// fire !
		missiles.push_back(baseInvPos + Position(
				confData.invadersSize * rdCol + confData.invadersDistance * (rdCol + 0.5),
				confData.invadersSize * (grid[rdCol].size() - 1) + confData.invadersDistance * (grid[rdCol].size() - 1)
		));
	}else --fireCooldown;

	
	if(direction){ // go to the right
		int end = baseInvPos.getX(); // start Position
		end+= grid.size() * confData.invadersSize; // add the invaders
		end+= (grid.size()-1) * confData.invadersDistance; // add the invadersDistance between invaders
		// you got the end position of the invader crowd !

		size_t i = grid.size()-1;
		while (grid[i].hasNoValid()){
			end -= (confData.invadersSize + confData.invadersDistance);
			--i;
		}

		if(end + confData.invadersSpeed < pm->getScreenWidth()){
			baseInvPos.setX(baseInvPos.getX() + confData.invadersSpeed);
		}
		else{
			baseInvPos.setY(baseInvPos.getY() + confData.invadersSize + confData.invadersDistance);
			direction = !direction;
			return true;
		}
	}
	else{
		size_t i = 0;
		unsigned relativeBasePos = baseInvPos.getX();
		while (grid[i].hasNoValid()){
			relativeBasePos += confData.invadersSize + confData.invadersDistance;
			++i;
		}

		if(relativeBasePos >= confData.invadersSpeed){
			baseInvPos.setX(baseInvPos.getX() - confData.invadersSpeed);
		}else{
			baseInvPos.setY(baseInvPos.getY() + confData.invadersSize + confData.invadersDistance);
			direction = !direction;
			return true;
		}
	}
	return false;

}

void Game::remCollidingProjectiles(){

	auto miss = missiles.begin();

	while(miss != missiles.end()){
		bool wasColliding = false;

		auto tor = torpedos.begin();
		while(tor != torpedos.end()){

			// missiles can't be right under torpedos, so that must means they are colliding in Y
			if(miss->getY() + confData.missilesLength > tor->getY()){
				if(areLinesColliding( // now check if they collide in X
						miss->getX(), miss->getX() + confData.missilesWidth,
						tor->getX(), tor->getX() + confData.torpedosWidth)){
					missiles.erase(miss);
					torpedos.erase(tor);
					wasColliding = true;
					break;
				}
			}
			++tor;
		}
		/* if it was colling, it was removed and his Position is now replaced by the next.
		 * else, go to the next */
		if(!wasColliding)++miss;
	}
}

void Game::moveMissiles() {
	auto miss = missiles.begin();
	while (miss != missiles.end()) {
		if (miss->getY() >= pm->getScreenHeight())missiles.erase(miss);
		else {
			miss->setY(miss->getY()+confData.missilesSpeed);
			++miss;
		}
	}
}

void Game::moveTorpedos() {
	auto tor = torpedos.begin();
	while (tor != torpedos.end()) {
		if (tor->getY()+confData.torpedosLength <= 0)torpedos.erase(tor);
		else{
			tor->setY(tor->getY()-confData.torpedosSpeed);
			++tor;
		}
	}
}

void Game::checkMissilesAndPlayers() {
	auto miss_ite = missiles.begin();
	while(miss_ite!=missiles.end()){
		bool wasColliding = false;
		if(miss_ite->getY()>=pm->getScreenHeight()-PLAYER_HEIGHT){ // check collision on Y
			// now check collision on X (with both players)
			for(Player& p : players){
				if(p.isPlaying()){
					if(areLinesColliding(
							miss_ite->getX(), miss_ite->getX() + confData.missilesWidth,
							p.x, p.x + confData.playersWidth)){
						wasColliding = true;
						p.damage();
						// do not break, the second player also deserves to be hit
					}
				}
			}
		}
		if(wasColliding)missiles.erase(miss_ite);
		else ++miss_ite;
	}
}

bool Game::checkTorpedosAndInvaders() {
	auto tor_ite = torpedos.begin();
	while(tor_ite!=torpedos.end()){
		unsigned i=0;
		for(;i<grid.size();++i){

			unsigned alienIndex = grid[i].getOutterInvader();
			if(alienIndex==grid[i].size())continue;
			// calculate top-left Position of invader
			Position pos = baseInvPos + Position(
					confData.invadersSize*i+confData.invadersDistance*i,
					confData.invadersSize*alienIndex+confData.invadersDistance*alienIndex
			);
			// check collision on Y (invaders can actually be "under" torpedos, so we check both lower and upper bounds
			if(pos.getY()+confData.invadersSize>=tor_ite->getY() &&
					pos.getY()<=tor_ite->getY()+confData.torpedosLength){
				// now check collision on X
				if(areLinesColliding( // now check collision on X
						tor_ite->getX(), tor_ite->getX() + confData.torpedosWidth,
						pos.getX(), pos.getX() + confData.invadersSize)){


					InvaderType invType = grid[i][alienIndex];
					players[tor_ite->owner].score += confData.invadersDef.at(invType).points;
					torpedos.erase(tor_ite);

					grid[i][alienIndex] = InvaderType::NONE;

					if(!areThereInvadersLeft()) return true;
					break;
				}
			}
		}
		if(i==grid.size()) ++tor_ite;
	}
	return false;
}

bool Game::invadersTouchPlayer() const {
	return any_of(grid.begin(), grid.end(), [this](const InvadersColumn& line) -> bool {
		unsigned outter = line.getOutterInvader();
		return this->baseInvPos.getY() + confData.invadersSize * (outter + 1)
			   +confData.invadersDistance*outter
			>= pm->getScreenHeight() - PLAYER_HEIGHT;
	});
}
