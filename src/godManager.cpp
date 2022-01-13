/*!
 *
 * @file    gameBasics.cpp
 * @date    January 2022
 * @version 1.0
 * @brief   god's implementation
 *
 */

#include "game.h"

void Game::tryAwakeGod() {
	if (baseInvPos.getY() > 100 /*lambda value*/ && god.state == GodState::NONE) {
		god.counter = 0;
		god.state = GodState::AWAKE;
	}
}

/**
 * @returns true if we can finish the game
 */

/* This is a really long function, but I feel like it's still readable because of the switch, and...
 * Honestly I think splitting it into multiple small functions would be uglier
 * Each state is responsible for managing the counter*/
bool Game::manageGod() {
	switch (god.state) {
		case GodState::NONE: {
			return false;
		}
		case GodState::AWAKE: {
			if (god.counter == GOD_BENCH_SIZE) {
				god.counter = 0;
				god.state = GodState::WAIT;
			} else ++god.counter;
			return false;
		}
		case GodState::WAIT: {
			if (god.counter < 100) {
				++god.counter;
				return false;
			}

			// init throw
			god.counter = 0;
			god.state = GodState::RETRIEVE1;
			// We're sure there is at least one valid column/invader, else the game would have ended and we would not be here
			god.thrownInvPosX = grid.randomValidCol();
			god.thrownInvPosY = grid[god.thrownInvPosX].randomValidInv();
			god.thrownInvType = InvaderType::NONE;

			god.thrownTransition.setX(pm->getScreenWidth() - GOD_HAND_DISTANCE - GOD_HAND_SIZE);
			god.thrownTransition.setY(baseInvPos.getY() + INV_GET_SINGLE_POS(god.thrownInvPosY));
			return false;
		}
		case GodState::RETRIEVE1: {
			if (god.counter < 100) {
				god.counter += 2;
				return false;
			}

			if (grid[god.thrownInvPosX].size() > god.thrownInvPosY &&
					grid[god.thrownInvPosX][god.thrownInvPosY] != InvaderType::NONE) {
				god.thrownInvType = grid[god.thrownInvPosX][god.thrownInvPosY];
				grid[god.thrownInvPosX][god.thrownInvPosY] = InvaderType::NONE;
			}
			god.state = GodState::RETRIEVE2;
			return false;
		}
		case GodState::RETRIEVE2: {
			if (god.counter > 0) {
				god.counter -= 2;
				return false;
			}
			if (god.thrownInvType == InvaderType::NONE) {
				god.state = GodState::WAIT;
				return false;
			}
			god.state = GodState::THROW;

			// compute the launch vector

			Position invaderMiddlePos(pm->getScreenWidth() - GOD_HAND_DISTANCE - GOD_HAND_SIZE / 2,
									  GOD_HAND_SIZE / 2);


			playerID target;
			if (players.size() == 1)target = PLAYER1; // don't want to use random if not needed
			else target = rand() % players.size();
			/* Let's just pretend god is drunk and can fire at a player that have a death animation, because
			 * honestly at this point I want to re-code the whole game engine to allow a better handling of cases like this...*/

			Position playerMiddlePos(players[target].x + confData.playersWidth / 2,
									 pm->getScreenHeight() - PLAYER_HEIGHT / 2);

			god.thrownVector = playerMiddlePos - invaderMiddlePos;
			god.thrownVector = god.thrownVector / (god.thrownVector.computeMagnitude() / 1000.0);
			// let's normalize it, but keep it's length big so x and y and non-zero
			// We will divide it in displayAll
			return false;
		}
		case GodState::THROW: {
			++god.counter;

			Position invaderPos = god.getRightHandPos(pm->getScreenWidth());
			applyTransformation(invaderPos, GOD_HAND_SIZE, confData.invadersSize);
			Position a = god.thrownVector * (god.counter / 100.0);
			invaderPos = invaderPos + a;

			bool touched = false;

			// check if OOB (Out Of Bounds)
			if (invaderPos.getY() + confData.invadersSize >= pm->getScreenWidth() ||
				(invaderPos.getX() < 0 || invaderPos.getX() + confData.invadersSize >= pm->getScreenWidth())) {
				touched = true;

				/* there are no invaders in the grid anymore, and the one thrown just went out of bounds
				 * So... return true, the player wins*/
				if(!areThereInvadersLeft())return true;

				// check player collision
			} else if (invaderPos.getY() + confData.invadersSize >= pm->getScreenHeight() - PLAYER_HEIGHT) {
				for (Player &p: players) {
					if(p.isPlaying()){
						if (areLinesColliding(
								p.x, p.x + confData.playersWidth,
								invaderPos.getX(), invaderPos.getX() + confData.invadersSize
						)) {
							p.damage();
							touched = true;
							// do not break, the other player also deserves to be hit
						}
					}
				}
			}
			if (touched) {
				god.state = GodState::WAIT;
				god.counter = 0;
			}
			/* we do not need to reset other members, they'll be treated as non-initialized
			 * When we cycle back between states*/


			return false;
		}

	}
	throw runtime_error("SHOULD NOT HAPPEN : invalid action for god : ID="+ to_string(static_cast<int>(god.state)));
}

Position God::getRightHandPos(unsigned screenWidth) const {
	return {screenWidth - GOD_HAND_DISTANCE - GOD_HAND_SIZE, 0};
}