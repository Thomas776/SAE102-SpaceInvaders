/*!
 *
 * @file    invaderGrids.h
 * @date    January 2022
 * @version 1.0
 * @brief   invader matrix structure
 *
 */

#include<iostream>
#include "invadersGrid.h"

bool InvadersColumn::hasNoValid() const {
	return getOutterInvader()==size();
}

unsigned InvadersColumn::getOutterInvader() const {
	unsigned i=size();
	while(i>0){
		--i;
		if(at(i)!=InvaderType::NONE)return i;
	}
	return size();
}


// these are used to invoke rand() as less as possible

unsigned InvadersColumn::randomValidInv() const {


	unsigned validTotal = 0;
	for(InvaderType ite : *this){
		if(ite!=InvaderType::NONE)++validTotal;
	}

	unsigned rd = rand() % validTotal;

	unsigned validIndex = 0;
	for(unsigned i=0;i<size();++i){
		if(at(i)!=InvaderType::NONE){
			if(validIndex==rd)return i;
			++validIndex;
		}
	}
	throw runtime_error("SHOULD NOT HAPPEN : see randomValidInv()");
}

unsigned InvadersGrid::validColsNumber() const {
	unsigned validTotal = 0;
	for(const InvadersColumn& i : *this){
		if(!i.hasNoValid())++validTotal;
	}
	return validTotal;
}

unsigned InvadersGrid::randomValidCol() const {



	unsigned rd = rand() % validColsNumber();

	unsigned validIndex = 0;
	for(unsigned i=0;i<size();++i){
		if(!at(i).hasNoValid()){
			if(validIndex==rd)return i;
			++validIndex;
		}
	}
	throw runtime_error("SHOULD NOT HAPPEN : see randomValidCol()");
}