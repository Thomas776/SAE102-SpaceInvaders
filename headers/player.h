/**
 *
 * @file    player.h
 * @date    January 2022
 * @version 1.0
 * @brief   player data storage
 *
 **/

#ifndef GUARD_PLAYER_H
#define GUARD_PLAYER_H

/*!
 * @struct Player
 * @brief player data structure
 */
struct Player{
	
	/*!
	 * @brief player life points
	 */
	unsigned lives = 3;
	
	/*!
	 * @brief  x coordinate of the player
	 */
	unsigned x;
	
	/*!
	 * @brief player's unique identidier 
	 */
	unsigned id;
	
	/*!
	 * @brief player's personal score 
	 */
	unsigned score=0;

	/*!
	 * @brief counter used for the death animation of players
	 * undefined once the player is eliminated
	 */
	unsigned deathAnimCounter=0;
	
	/*!
	 * @brief player's shooting cooldown  
	 */
	unsigned fireCooldown=0;


	/*!
	 * @brief Tells if the player has a death animation ongoing
	 * @fn bool hasDeathAnimation() const;
	 * @returns true is the player has a death animation ongoing
	 */
	bool hasDeathAnimation() const;

	/*!
	 * @brief Tells if the player is eliminated (no more lives)
	 * @fn bool isEliminated() const;
	 * @returns true is the player is eliminated (no more lives)
	 */
	bool isEliminated() const;

	/*!
	 * @brief Tells if the player is playing, or has a death animation/is eliminated
	 * @fn bool isPlaying() const
	 * @returns true is the player is playing
	 */
	bool isPlaying() const;

	/*!
	 * @brief Damage the player (no precondition on existing state)
	 * @fn void damage;
	 */
	void damage();
};

#endif