/*!
 *
 * @file    ScoreManager.cpp
 * @date    January 2022
 * @version 1.0
 * @brief   Score file manager
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "scoresManager.h"

// Our own format : kustom
#define SCORE_FILE "scores.kus"

#define SECRET_KEY "HelloWorld"

void readWholeFile(const ifstream& ifs, string& str){
	stringstream ss;
	ss << ifs.rdbuf();
	str.assign(ss.str());
}

static std::hash<string> hasher;

bool verifyHash(size_t savedHash, const string& content){
	// non-cryptographic hash, but it is part of the std, and openssl is REALLY difficult
	// to use in C++ while keeping semantic, because there are no wrappers...
	size_t actualHash = hasher(content+SECRET_KEY);
	return actualHash==savedHash;
}

void ScoresManager::readFile() {
	ifstream ifs(SCORE_FILE);
	if(!ifs.is_open())return; // file can not exist

	/* the first line is the hash sum of (the following content + a secret key)
	 * We use it to generate a data signature to prevent users
	 * from tampering with the save file*/
	size_t hash;
	ifs >> hash;
	ifs.get(); // remove \n

	string content;
	readWholeFile(ifs, content);

	scores.clear();
	if(verifyHash(hash, content)){
		stringstream ss(content);

		string line;
		while(true){
			getline(ss, line);
			if(ss.eof())break;

			size_t index = line.find(',');
			scores.emplace_back(line.substr(0, index), stoi(line.substr(index+1)));
		}
	}else{
		cerr << "Integrity check of the save file failed. Has it been tampered ?" << endl;
	}
}

void ScoresManager::writeFile() const {
	ofstream ofs(SCORE_FILE);

	string str; // this one must be counted in the hash too
	for(const ScoreLink& sc : scores){
		str.append(sc.name);
		str.append(",");
		str.append(to_string(sc.score));
		str.append("\n");
	}

	ofs << hasher(str+SECRET_KEY) << endl << str;
}

#define SCORE_LIMIT 10

/**
 * Insertion sort, probably the most efficient here
 */
void ScoresManager::inputScore(string name, unsigned score) {
	auto ite = scores.begin();
	while(ite!=scores.end()){
		if(score > ite->score) {
			scores.emplace(ite, move(name), score);
			break;
		}
		++ite;
	}

	if(ite==scores.end())scores.emplace(ite, move(name), score);

	if(scores.size()>SCORE_LIMIT)scores.erase(scores.begin()+SCORE_LIMIT);

}

ScoreLink::ScoreLink(string name, unsigned int score) {
	this->name = move(name);
	this->score = score;
}
