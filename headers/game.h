/**
 *
 * @file    game.h
 * @date    January 2022
 * @version 1.0
 * @brief   full game logic and display management
 *
 **/


#ifndef GUARD_GAME_H
#define GUARD_GAME_H
#include <vector>
#include "mingl/mingl.h"
#include "pixelManager.h"
#include "utils.h"
#include "playerDef.h"
#include "player.h"
#include "playMode.h"
#include "configData.h"
#include "projectiles.h"
#include "scoresManager.h"
#include "god.h"
#include "invadersGrid.h"

using namespace std;

/*!
 * @class Game
 * @brief Main game class
 */
class Game {
private:
	
	/*!
 	* @brief the MinGL window in which the game will be drawn into
 	*/
	MinGL window;

	/*!
	* @brief Harcoded window size
	*/
	const Position winSize{1280,720};

	/*!
 	* @brief PixelManager : Class that contains and draws all the data that will be drawn on screen
	 * This is a pointer because the object is allocated at runtime, following the configuration
 	*/
    unique_ptr<PixelManager> pm;
	
	/*!
 	* @brief ConfigData : Struct that stores all the relevant data read from the configuration file 
 	*/
	ConfigData confData;
	
	/*!
 	 * @brief  ScoresManager : utility to handle score saving and signing
 	 */
	ScoresManager sm;
	
	/*!
 	* @brief Special entity : God
 	*/
	God god;
	
	/*!
 	* @brief base position for the invader crowd
 	*/
	Position baseInvPos;
	
	/*!
 	* @brief Invader position and type matrix
 	*/
	InvadersGrid grid;
	
	/*!
 	* @brief Invader scroll direction - true = right , false = left
 	*/
	bool direction;
	
	/*!
 	* @brief list of positions of all missiles shot by the invaders
 	*/
    vector<missile> missiles;
	
	/*!
 	* @brief list of positions of all torpedoes shot by the player(s)
 	*/
    vector<Torpedo> torpedos;
	
	/*!
 	* @brief Define the current type of the game
 	*/
	PlayMode playMode;
	
	/*!
 	* @brief list of all player data
 	*/
	vector<Player> players;

	// invaders related variables
	
	/*!
 	* @brief cooldown until the invaders can shoot again
 	*/
	unsigned fireCooldown=0;

	// basic methods

	/*!
 	* @brief check if there are invaders left in the grid
	* @return true if there are no more invaders in the grid, else false
	* @fn bool updateColumns();
 	*/
	bool areThereInvadersLeft();
	
	/*!
 	* @brief Asks the player(s) name(s) and write their score to the score file
	* @fn void handleScoreSaving();	
 	*/
	void handleScoreSaving();
	
	/*!
 	* @brief convert invader's matrix position to pixel coodinates
	* @param[in] x : column index of the invader in the grid
	* @param[in] y : invader index of the invader in the column
	* @return the pixel position of the invader
	* @fn Position invIndexToPos(unsigned x, unsigned y) const;
 	*/
	Position invIndexToPos(unsigned x, unsigned y) const;

	/*!
 	* @brief main display function, clear the window and calls sub display functions
	* @param[in] fps : current screen refresh rate
 	* @fn void displayAll() const;
	*/
	void displayAll(unsigned fps) const;
	
	/*!
 	* @brief display God related objets
	* @fn void displayGod() const;
 	*/
	void displayGod() const;
	
	/*!
 	* @brief display a singular invader
	* @param[in] basePos : invader's pixel coordinates
	* @param[in] type : invader's type
	* @fn void displayInvader(const Position& baseInvPos, InvaderType type) const
 	*/
	void displayInvader(const Position& basePos, InvaderType type) const;
	
	/*!
 	* @brief displays a player's remaining lives
	* @fn void displayHearts(playerID) const;
 	*/
	void displayHearts(playerID) const;


	// managers
	
	/*!
 	* @brief Calls the function 'manageOnePlayer' for all players in player list
	* @fn void managePlayers(); 
 	*/
	void managePlayers();
	
	/*!
 	* @brief Handles a player keystrokes, makes them move and shoot a torpedo
	* @param[in] pID : Player id to manage
	* @fn void manageOnePlayer(playerID pID); 
 	*/
	void manageOnePlayer(playerID pID);
	
	/*!
 	* @brief Handles all invaders movements and when they'll shoot a missile 
	* @return true if the invaders went down from one line (and we should check lower boundary), else false
	* @fn bool manageInvaders(); 
 	*/
	bool manageInvaders();

	// collision things
	
	/*!
 	* @brief Removes torpedo and missiles that are colliding
	* @fn void remCollidingProjectiles(); 
 	*/
	void remCollidingProjectiles();
	
	/*!
 	* @brief Makes all missiles go downward
	* @fn void moveMissiles();
 	*/
	void moveMissiles();
	
	/*!
 	* @brief Makes all torpedos go upward
	* @fn void moveTorpedos();
 	*/
	void moveTorpedos();
	
	/*!
 	* @brief checks if a missile collides with a player 
	* @fn checkMissilesAndPlayers(); 
 	*/
	void checkMissilesAndPlayers();
	
	/*!
 	* @brief check if a torpedo collides with an invader
	* @return true if there is a collision, false otherwise
	* @fn bool checkTorpedosAndInvaders(); 
 	*/
	bool checkTorpedosAndInvaders();
	
	/*!
 	* @brief check if the invaders have reached the players
	* @return true if they have reached the player, false otherwise
	* @fn bool invadersTouchPlayer() const;
 	*/
	bool invadersTouchPlayer() const;

	/*!
 	* @brief Try to awake god, if not already awaken
	* @fn void tryAwakeGod();
 	*/
	void tryAwakeGod();
	
	/*!
 	* @brief make god behave
	* @return true if theres no invader left and god is in a valid state for the player to win, false otherwise
	* @fn bool manageGod();
 	*/
	bool manageGod();

public:
	// in case someone wants to mess with the code, here's a minimal public API, costs nothing to us
    
	/*!
 	* @brief constructor for the game class
	* @fn Game(); 
 	*/
	Game();
	
	/*!
 	* @brief start games managed by our class
	* @fn void managedGames(); 
 	*/
	void managedGames();

	/*!
 	* @brief Set or reset all the setting for a new game
	* @fn void initGame();
 	*/
	void initGame();

	/*!
 	* @brief enter the main gameplay game loop. Will block until the game ends
	* @return the value of the winners can be the players, the invaders or god 
	* @fn WinValue enterGameLoop(); 
 	*/
	WinValue enterGameLoop();

	/*!
 	* @brief reload the configuration file (not dynamically used currently, but it was planned to be)
	* @return false if an error occurred, true otherwise
	* @fn bool reloadConfig();
 	*/
	bool reloadConfig();

	/*!
 	* @brief tells if all players are dead
	* @return true if all player are dead, false otherwise
	* @fn bool arePlayersDead();
 	*/
	bool arePlayersDead();
};

#endif