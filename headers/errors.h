/*!
 *
 * @file    configData.h
 * @date    January 2022
 * @version 1.0
 * @brief   error handling
 *
 */

#ifndef GUARD_ERRORS_H
#define GUARD_ERRORS_H

#include<string>
#include<stdexcept>

using namespace std;

/*!
 * @class config_error
 * @brief Simple clone of runtime_error to help us handle errors in config management.
 */
class config_error : public runtime_error {
public:
	explicit config_error(const string& msg);
};

#endif
