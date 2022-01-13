/*!
 *
 * @file    configManagement.cpp
 * @date    January 2022
 * @version 1.0
 * @brief   config parser
 *
 */

#include <fstream>
#include "game.h"
#include "configManagement.h"
#include "errors.h"


void trimSpaces(string& str){
	str.erase(0, str.find_first_not_of(' '));
}

void sanitizeValue(string& val) {
	trimSpaces(val);
	for (char c: {'\'', '"'}) {
		if (val[0] == c && val[val.size() - 1] == c) {
			val.erase(val.begin());
			val.pop_back();
			break;
		}
	}
}

void ConfigBuilder::dumpInternalValues() const {
	for(const auto& ite : internalValues){
		cerr << ite.first << " -> " << ite.second << endl;
	}
}

/* WARNING : This implementation of YAML is not meant to be complete, but to work with our specific needs
 * It also can't detect and report errors in a non-YAML-compliant file*/

void ConfigBuilder::parseFile(const string& fname) {
	ifstream file(fname);
	if(!file.is_open())throw config_error("Error while opening config.yml. Check file location ?");

	vector<string> keyParts;
	unsigned listIndex;
	unsigned lineno = 0; // for error handling purposes
	while (!file.eof()) {
		string line;
		getline(file, line);
		++lineno;
		auto match = line.find('#');
		if (match != string::npos)line.erase(match);
		if (line.find_first_not_of(' ')==string::npos)continue;

		unsigned currentIndent = 0;
		while (line[currentIndent] == ' ')++currentIndent;

		if(line[currentIndent]=='-'){
			string value = line.substr(currentIndent+1);
			sanitizeValue(value);

			string fullKey;
			for (unsigned i = 0; i < currentIndent; ++i) {
				fullKey.append(keyParts[i]);
				fullKey.append(".");
			}
			// lists are just treated as sections with key 0,1,2...
			fullKey.append(to_string((listIndex)));
			++listIndex;
			internalValues[fullKey] = value;

		}else{
			listIndex = 0;
			match = line.find(':');
			if (match == string::npos)throw config_error("Line "+ to_string(lineno)+" invalid : |"+line+"|");
			string localKey = line.substr(0, match);
			string value = line.substr(match + 1);
			trimSpaces(localKey);
			sanitizeValue(value);
			if (value.empty()) {
				keyParts.resize(currentIndent);
				keyParts.push_back(localKey);
			} else {
				string fullKey;
				for (unsigned i = 0; i < currentIndent; ++i) {
					fullKey.append(keyParts[i]);
					fullKey.append(".");
				}
				fullKey.append(localKey);
				internalValues[fullKey] = value;
			}
		}
	}

	file.close();
}

void ConfigBuilder::readGrid(const configKey& baseKey) {
	vector<string> tmp;
	getList("grid", tmp);

	// we are essentially going to translate a line-oriented config to a column-oriented grid

	unsigned maxSize = 0;
	for(string& s : tmp){
		if(s.size()>maxSize)maxSize = s.size();
	}
	collectedData.grid.resize(maxSize);

	for(string& s : tmp){
		unsigned i=0;
		for(;i<s.size();++i){
			switch(toupper(s[i])){
				case 'A':{
					collectedData.grid[i].push_back(InvaderType::TYPEA);
					break;
				}
				case 'B':{
					collectedData.grid[i].push_back(InvaderType::TYPEB);
					break;
				}
				case 'C':{
					collectedData.grid[i].push_back(InvaderType::TYPEC);
					break;
				}
				case ' ':{
					collectedData.grid[i].push_back(InvaderType::NONE);
					break;
				}
				default:{
					throw config_error("Invalid invader ID in grid definition : "+ to_string(s[i]));
				}
			}
		}
		while(i<maxSize){
			collectedData.grid[i].push_back(InvaderType::NONE);
			++i;
		}
	}
}

void ConfigBuilder::readPlayer(const configKey& baseKey, PlayerDef& pdef) {
	getColor(baseKey+".color", pdef.color);
	pdef.keys.left = getChar(baseKey+".keys.left");
	pdef.keys.right = getChar(baseKey+".keys.right");
	pdef.keys.shoot = getChar(baseKey+".keys.shoot");
}

void ConfigBuilder::readInvaderType(const configKey& baseKey, InvaderTypeDef& invDef) {
	invDef.points = getInt(baseKey+".points");
	getColor(baseKey+".color", invDef.color);
}

void ConfigBuilder::readConfig() {

	collectedData.theme = getString("general.theme", "bad");
	collectedData.maxFPS = getInt("general.maxFPS", 30, 1, 60);

	readGrid("grid");

	if (collectedData.theme != "bad"){
		collectedData.playersWidth = 90;
		collectedData.invadersSize = 30;
		collectedData.missilesWidth = 32;
		collectedData.torpedosWidth = 11;

	}
	else{
		collectedData.playersWidth = getInt("players.width", 100, 50, 500);
		collectedData.invadersSize = getInt("invaders.size",30,10,100);
		collectedData.missilesWidth = getInt("projectiles.missiles.width",10,5,100);
		collectedData.torpedosWidth = getInt("projectiles.torpedos.width",10,1,100);
	}

	// players
	
	collectedData.startXPosition = getInt("players.startXPosition",600 ,0 ,1200);
	collectedData.playersSpeed = getInt("players.speed",1,1,100);
	collectedData.playersFireCooldown = getInt("players.fireCooldown",10,1,100);
	collectedData.playersLives = getInt("players.lives",3,1,100);

	// the scalability behind the vector of players is only an illusion, because we force player count to be 1 or 2
	// It was done so the 2+ players implementation could be easier in the future, if wanted
	collectedData.playerDefs.resize(2);
	readPlayer("players.user1", collectedData.playerDefs[0]);
	readPlayer("players.user2", collectedData.playerDefs[1]);

	// invaders

	collectedData.invadersSpeed = getInt("invaders.speed",7,1,100);
	collectedData.invadersDistance = getInt("invaders.distance",15,5,100);
	collectedData.invadersFireCooldown = getInt("invaders.fireCooldown",0,0,100);

	readInvaderType("invaders.typeA", collectedData.invadersDef[InvaderType::TYPEA]);
	readInvaderType("invaders.typeB", collectedData.invadersDef[InvaderType::TYPEB]);
	readInvaderType("invaders.typeC", collectedData.invadersDef[InvaderType::TYPEC]);

	// projectiles
	collectedData.missilesLength = collectedData.missilesWidth*PROJ_LENGTH_FACTOR;
	collectedData.missilesSpeed = getInt("projectiles.missiles.speed",10,5,100);
	getColor("projectiles.missiles.color", collectedData.missilesColor);

	collectedData.torpedosLength = collectedData.torpedosWidth*PROJ_LENGTH_FACTOR;
	collectedData.torpedosSpeed = getInt("projectiles.torpedos.speed",10,1,100);
	getColor("projectiles.torpedos.color", collectedData.torpedosColor);
}

const string& ConfigBuilder::getString(const configKey& key, const string& def) const {
	try{
		return getString(key);
	}catch(config_error& e){
		cerr << e.what() << " . Using default value" << endl;
		return def;
	}
}

const string& ConfigBuilder::getString(const configKey& key) const {
	DEBUG_MSG("Querying config key " << key)
	if(internalValues.find(key)==internalValues.end())throw config_error("Non-existent key requested : "+key);

	// We don't really care about querying the key two time since we are... well, in debug mode
	DEBUG_MSG("Got config value " << internalValues.at(key))
	return internalValues.at(key);
}

int ConfigBuilder::getInt(const configKey& key, int def, int min, int max) const {
	try{
		int val = getInt(key);
		if(val < min || val > max){
			throw config_error("Value for key " + key + " do not follow preconditions : " +
							   to_string(min) + "<=" + to_string(val) + "<=" + to_string(max));
		}
		return val;
	}catch(config_error& e){
		cerr << e.what() << " . Using default value" << endl;
		return def;
	}
}

int ConfigBuilder::getInt(const configKey& key) const {
	try{
		return stoi(getString(key));
	}catch(invalid_argument& e){
		throw config_error("Invalid int data for key "+key+" : |"+getString(key)+"|");
	}
}

char ConfigBuilder::getChar(const configKey& key, char def) const {
	try{
		return getChar(key);
	}catch(config_error& e){
		cerr << e.what() << " . Using default value" << endl;
		return def;
	}
}

char ConfigBuilder::getChar(const configKey& key) const {
	string s = getString(key);
	if(s.size()!=1)throw config_error("Invalid char data for key "+key+" : |"+s+"|");
	return s[0];
}

void ConfigBuilder::getColor(const configKey& key, nsGraphics::RGBAcolor& color, const nsGraphics::RGBAcolor& def) const {
	try{
		getColor(key, color);
	}catch(config_error& e){
		cerr << e.what() << " . Using default value" << endl;
		color = def;
	}
}

void ConfigBuilder::getColor(const configKey& key, nsGraphics::RGBAcolor& color) const {
	// switch do not work with strings, and I don't want to implement a constexpr hash function
	string colorStr = getString(key);
	if (colorStr == "black")color = nsGraphics::KBlack;
	else if (colorStr == "white")color = nsGraphics::KWhite;
	else if (colorStr == "red")color = nsGraphics::KRed;
	else if (colorStr == "lime")color = nsGraphics::KLime;
	else if (colorStr == "blue")color = nsGraphics::KBlue;
	else if (colorStr == "yellow")color = nsGraphics::KYellow;
	else if (colorStr == "cyan")color = nsGraphics::KCyan;
	else if (colorStr == "magenta")color = nsGraphics::KMagenta;
	else if (colorStr == "silver")color = nsGraphics::KSilver;
	else if (colorStr == "gray")color = nsGraphics::KGray;
	else if (colorStr == "maroon")color = nsGraphics::KMaroon;
	else if (colorStr == "olive")color = nsGraphics::KOlive;
	else if (colorStr == "green")color = nsGraphics::KGreen;
	else if (colorStr == "purple")color = nsGraphics::KPurple;
	else if (colorStr == "teal")color = nsGraphics::KTeal;
	else if (colorStr == "navy")color = nsGraphics::KNavy;
	else throw config_error("Invalid color string : "+colorStr);
}

void ConfigBuilder::getList(const configKey& baseKey, vector<string>& toPopulate) const {
	unsigned i=0;
	string fullKey = baseKey + ".0";
	if(internalValues.find(fullKey)==internalValues.end())throw config_error("Non-existent list baseKey requested : " + baseKey);

	do{
		toPopulate.push_back(internalValues.at(fullKey));
		++i;
		fullKey = baseKey + "." + to_string(i);
	}while(internalValues.find(baseKey + "." + to_string(i))!=internalValues.end());
}


bool Game::reloadConfig() {
	map<string, string> strValues;
	ConfigBuilder builder;
	bool parsed = false;
	try{
		builder.parseFile("config.yml");
		parsed = true;
		builder.readConfig();
	}catch(config_error& e){
		if(parsed)cerr << "An error occured while reading the configuration :" << endl;
		else cerr << "An error occured while parsing the configuration :" << endl;
		cerr << e.what() << endl;
		if(parsed){
			cerr << "Parsed keys :" << endl;
			builder.dumpInternalValues();
		}
		cerr << "(The old configuration was kept in memory)" << endl;
		return false;
	}
	confData = move(builder.collectedData);
	return true;
}
