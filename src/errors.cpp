/*!
 *
 * @file    configData.h
 * @date    January 2022
 * @version 1.0
 * @brief   error handling
 *
 */

#include "errors.h"

config_error::config_error(const string& msg) : runtime_error(msg) {

}