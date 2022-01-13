/*!
 *
 * @file    main.cpp
 * @date    January 2022
 * @version 1.0
 * @brief  	main
 *
 * Welcome to SUPER Space Invader turbo apocalypse DX - VS GOD 
 */

#include <iostream>
#include "game.h"
using namespace std;

int main(){
	DEBUG_MSG("Starting program")
	srand(time(NULL));

	Game g;
	g.managedGames();
	DEBUG_MSG("Finished program. Goodbye !")

    return 0;
}