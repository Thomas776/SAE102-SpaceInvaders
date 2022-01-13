/*!
 *
 * @file    configManagement.h
 * @date    January 2022
 * @version 1.0
 * @brief   config parser
 *
 */

#ifndef SPACE_CONFIGMANAGEMENT_H
#define SPACE_CONFIGMANAGEMENT_H

#include<climits>

/* This header will only be imported once, but Djalim told me he would hurt me
 * if I didn't move it into his own header file instead of the cpp file*/

/*!
 * @class ConfigBuilder
 * @brief temporary class used to populate a ConfigData object
 */
class ConfigBuilder{
public:

	/*!
	 * @brief Actual config data object
 	*/
	ConfigData collectedData;

	/*!
	 * @brief parse the file given, and put the keys/values in internalValues
	 * @fn void parseFile(const string& fname);
	 * @param[in] fname: file to read from
 	*/
	void parseFile(const string& fname);

	/*!
	 * @brief read the values in collectedData and put them in the collectedData object
	 * @fn void parseFile(const string& fname);
	 * @param[in] fname: file to read from
 	*/
	void readConfig();

	/*!
	 * @brief print internalValues pairs in the console (in case in error reporting)
 	*/
	void dumpInternalValues() const;
private:
	/*!
	 * @brief key/values (all strings) collected by the parser, and fed to the get* methods
 	*/
	map<string, string> internalValues;

	/*!
	 * @brief read a string, or return the default argument if not found (safe from config read errors)
	 * @fn const string& getString(const configKey& key, const string& def) const;
	 * @param[in] key: key to read from
	 * @param[in] def: default value to use
 	*/
	const string& getString(const configKey& key, const string& def) const;

	/*!
	 * @brief read a string
	 * @fn const string& getString(const configKey& key) const;
	 * @param[in] key: key to read from
 	*/
	const string& getString(const configKey& key) const;

	/*!
	 * @brief read a char, or return the default argument if not found (safe from config read errors)
	 * @fn char getChar(const configKey& key, char def) const;
	 * @param[in] key: key to read from
	 * @param[in] def: default value to use
 	*/
	char getChar(const configKey& key, char def) const;

	/*!
	 * @brief read a char
	 * @fn char getChar(const configKey& key) const;
	 * @param[in] key: key to read from
 	*/
	char getChar(const configKey& key) const;

	/*!
	 * @brief read an int, or return the default argument if not found (safe from config read errors). Bound checking possible
	 * @fn int getInt(const configKey& key, int def, int min=INT_MIN, int max=INT_MAX) const;
	 * @param[in] key: key to read from
	 * @param[in] def: default value to use
	 * @param[in] min: minimal bound checking
	 * @param[in] max: maximal bound checking
 	*/
	int getInt(const configKey& key, int def, int min=INT_MIN, int max=INT_MAX) const;

	/*!
	 * @brief read an int
	 * @fn int getInt(const configKey& key) const;
	 * @param[in] key: key to read from
 	*/
	int getInt(const configKey& key) const;

	/*!
	 * @brief read a color, or return the default argument if not found (safe from config read errors)
	 * @fn void getColor(const configKey& key, nsGraphics::RGBAcolor& color, const nsGraphics::RGBAcolor& def) const;
	 * @param[in] key: key to read from
	 * @param[out] color: returned color
	 * @param[in] def: default value to use
 	*/
	void getColor(const configKey& key, nsGraphics::RGBAcolor& color, const nsGraphics::RGBAcolor& def) const;

	/*!
	 * @brief read a color
	 * @fn void getColor(const configKey& key, nsGraphics::RGBAcolor& color) const;
	 * @param[in] key: key to read from
	 * @param[out] color: returned color
 	*/
	void getColor(const configKey& key, nsGraphics::RGBAcolor& color) const;

	/*!
	 * @brief read a list
	 * @fn void getList(const configKey& key, vector<string>& vec) const;
	 * @param[in] baseKey: key to read from
	 * @param[out] vec: vector to write list contents to
 	*/
	void getList(const configKey& baseKey, vector<string>& vec) const;


	/*!
	 * @brief read the invader grid
	 * @fn void readGrid(const configKey& baseKey);
	 * @param[in] baseKey: key to read from
 	*/
	void readGrid(const configKey& baseKey);

	/*!
	 * @brief read a player section
	 * @fn void readPlayer(const configKey& baseKey, PlayerDef&);
	 * @param[in] key: baseKey to read from
	 * @param[in] def: default value to use
 	*/
	void readPlayer(const configKey& baseKey, PlayerDef& def);

	/*!
	 * @brief read an invader type section
	 * @fn void readInvaderType(const configKey& baseKey, InvaderTypeDef&);
	 * @param[in] key: baseKey to read from
	 * @param[in] def: default value to use
 	*/
	void readInvaderType(const configKey& baseKey, InvaderTypeDef& def);
};

#endif
