/*!
 *
 * @file    scoresManager.h
 * @date    January 2022
 * @version 1.0
 * @brief   Score file manager
 *
 */

#ifndef GUARD_SCORESMANAGER_H
#define GUARD_SCORESMANAGER_H

#include<utility>
#include<vector>
#include<string>
#include "utils.h"

using namespace std;

/*!
 * @struct ScoreLink
 * @brief Makes a link between a player username and their score
 */
struct ScoreLink{

	/*!
	* @brief player username
	*/
	string name;
	
	/*!
	* @brief player score
	*/
	unsigned score;

	/*!
	* @brief constructor of the struct
	* @param[in] name : player username
	* @param[in] score : player score
	* @fn ScoreLink(string name, unsigned score); 
	*/
	ScoreLink(string name, unsigned score);
};


/*!
 * @class ScoresManager
 * @brief manage the score in the game and inside the score file 
 */
class ScoresManager {
public:

	/*!
	* @brief list of pairs of player names and their score
	*/
	vector<ScoreLink> scores;
	
	/*!
	* @brief add player name and their score in the list of scores
	* @param[in] name : player name
	* @param[in] score : player score
	* @fn void inputScore(string name, unsigned score); 
	*/
	void inputScore(string name, unsigned score);

	/*!
	* @brief read the score file and put all of its data inside the list of score
	* @fn void readFile(); 
	*/
	void readFile();
	
	/*!
	* @brief write the score list into the score file
	* @fn void writeFile() const; 
	*/
	void writeFile() const;
};


#endif
