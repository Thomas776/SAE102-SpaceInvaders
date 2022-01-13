/*!
 *
 * @file    gameBasics.cpp
 * @date    January 2022
 * @version 1.0
 * @brief   game basic mechanisms
 *
 */

#include <chrono>
#include <thread>
#include <algorithm>
#include "game.h"
#include "playMode.h"
#include "goodPixelManager.h"

#define WININIT window("SUPER Space Invader : Turbo Apocalypse DX - VS GOD", Position(1280, 720) /*for some reason I can't use the winSize member here*/, Position(128, 128), nsGraphics::KBlack)

Game::Game() : WININIT {

	if(!reloadConfig()){ // Config
		throw runtime_error("Initial config loading failed. Please check the error above and fix the configuration");
	}

	// Pixel Manager
	if(confData.theme=="good"){
		pm = std::make_unique<GoodPixelManager>(window);
	}else if(confData.theme=="bad"){
		pm = std::make_unique<PixelManager>(window);
	}else throw runtime_error("Invalid theme value : "+confData.theme+
	"\nValid values are : good,bad");

	cout << "Loading sprites..." << endl;
	vector<Task> tasks;
	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

	pm->loadSprites(tasks);
	for(Task& f : tasks)f.wait();

	// We just do that for one sprite, so I didn't bother creating an 'API' for that
	pm->leftHand.mirror(pm->rightHand);

	chrono::high_resolution_clock::duration elapsed = chrono::high_resolution_clock::now()-start;
	cout << "Done ! Time : " << chrono::duration_cast<chrono::milliseconds>(elapsed).count() << "ms" << endl;

	sm.readFile(); // Score manager
}

bool Game::areThereInvadersLeft(){
	return grid.validColsNumber() > 0;
}

void Game::handleScoreSaving(){
	for(unsigned i=0;i<players.size();++i){
		string pName;
		pm->askPlayerNameMenu(i, players[i].score, pName);
		sm.inputScore(move(pName), players[i].score);
	}
	sm.writeFile();
}

void Game::managedGames() {

	playMode = PlayMode::NONE;
	WinValue whoWon; 

	while(playMode!=PlayMode::EXIT){
		if(playMode==PlayMode::NONE){
			playMode = pm->showInitialMenu();
		}else{
			DEBUG_MSG("Starting game")
			initGame();
			whoWon = enterGameLoop(); // will read the playMode
			DEBUG_MSG("END End of game")
			handleScoreSaving();
			if(!pm->showDeathMenu(sm.scores, whoWon))playMode = PlayMode::NONE;
		}
	}
}

// we assume the game has been played before, and so we need to clean used members
void Game::initGame(){
	grid = confData.grid; // will copy the grid

	// we re-construct players objects, we don't have to clear all members and can rely on the construction value (set in .h file)
	players.clear();

	missiles.clear();
	god.state = GodState::NONE;
	torpedos.clear();

	if(playMode==PlayMode::SINGLE){
		players.resize(1);
	}else{
		players.resize(2);
		// mirror the start X Position for the other
		players[1].x = pm->getScreenWidth() - confData.startXPosition - confData.playersWidth;
	}
	players[0].x = confData.startXPosition;

	for(unsigned i=0;i<players.size();++i){
		players[i].id = i;
		players[i].lives = confData.playersLives;
	}

	baseInvPos = Position(200, 0);
	direction = true;

}

#define START_TIMER() DEBUG_INSTR(debugTime = chrono::high_resolution_clock::now())
#define PRINT_TIMER(X) DEBUG_MSG((X) << ": " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-debugTime).count())

WinValue Game::enterGameLoop(){ // returns when game is finished
	// computed in advance for performance reasons
	chrono::milliseconds maxFrameTime = chrono::milliseconds(1000/confData.maxFPS);

	unsigned tmpFps = 0;
	unsigned fps = 0;
	typedef chrono::high_resolution_clock::time_point MyTimePoint;
	MyTimePoint fpsStartTime = {};

	while(window.isOpen()){

		MyTimePoint startTime = chrono::high_resolution_clock::now();
		if(fpsStartTime.time_since_epoch()==chrono::seconds(0)){
			fpsStartTime = startTime;
		}

		// force window size
		if(window.getWindowSize()!=winSize)window.setWindowSize(winSize);

		pm->startFrame();

		managePlayers();
		if(manageInvaders()) { // if they went down
			if (invadersTouchPlayer())return WinValue::INVADERS;
			tryAwakeGod();
		}

		if(manageGod())return WinValue::PLAYERS;
		if(arePlayersDead())return WinValue::GOD;

		moveMissiles();
		remCollidingProjectiles();
		moveTorpedos();
		remCollidingProjectiles();

		checkMissilesAndPlayers();
		if(checkTorpedosAndInvaders())return WinValue::PLAYERS;

		if(arePlayersDead())return WinValue::INVADERS;

		displayAll(fps);

		pm->endFrame();

		MyTimePoint endTime = chrono::high_resolution_clock::now();

		// This code is counted as part of frames, but that's not really something we can control
		if(fpsStartTime+chrono::seconds(1) < endTime){
			fps = tmpFps;
			tmpFps = 0;
			fpsStartTime = {};
		}else ++tmpFps;

		this_thread::sleep_until(startTime+maxFrameTime);
	}

	return WinValue::NOBODY;
}

Position Game::invIndexToPos(unsigned x, unsigned y) const {
	return baseInvPos + Position(INV_GET_SINGLE_POS(x), INV_GET_SINGLE_POS(y));
}



bool Game::arePlayersDead() {
	return all_of(players.begin(), players.end(), [](Player& p) -> bool {return p.isEliminated();});
}
