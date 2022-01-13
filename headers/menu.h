/*!
 *
 * @file    menu.h
 * @date    January 2022
 * @version 1.0
 * @brief   simple menu backend implementation
 *
 */


#ifndef GUARD_MENU_H
#define GUARD_MENU_H

#include<vector>
#include<string>

/*!
 * @struct Menu
 * @brief menu stuct
 */
struct Menu{
    /*!
	 * @brief list of all menu options 
	 */
    vector<string> entries;
    
     /*!
	 * @brief index of currently selected menu option 
	 */
    unsigned selectedEntry = 0;

    /*!
	 * @brief color of currently selected menu option
	 */
    nsGraphics::RGBAcolor selectedColor;
    /*!
	 * @brief color of unelected menu option
	 */
    nsGraphics::RGBAcolor unSelectedColor;
};

#endif