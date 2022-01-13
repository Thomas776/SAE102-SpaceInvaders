/*!
 *
 * @file    mySprite.cpp
 * @date    January 2022
 * @version 1.0
 * @brief  Custom sprite implementation (needed for async load)
 *
 */

#include "utils.h"
#include "mySprite.h"

Task MySprite::asyncLoad(const string& fname){
	DEBUG_MSG("Load file " << fname)
	return std::async(std::launch::async, [fname, this]() -> void {
		sp.emplace(fname);
	});
}

void MySprite::mirror(MySprite& msp) {
	const vector<RGBAcolor>& inPixels = msp.sp->getPixelData();
	unsigned rowSize = msp.sp->getRowSize();

	vector<RGBAcolor> outPixels;
	// we reserve size so the vector doesn't dynamically grows
	outPixels.reserve(inPixels.size());
	//for each line of pixel
	for(unsigned rowOffset=0; rowOffset < inPixels.size(); rowOffset+=rowSize){
		// for each pixel of that line
		for(unsigned j=0;j<rowSize;++j) {
			// push back the pixel opposed to this one (still in the same line)
			outPixels.push_back(inPixels[rowOffset + rowSize - j - 1]);
		}
	}
	sp.emplace(outPixels, rowSize);
}
