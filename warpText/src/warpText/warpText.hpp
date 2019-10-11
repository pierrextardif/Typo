//
//  warpText.hpp
//  warpText
//
//  Created by Pierre Tardif on 02/08/2019.
//

#ifndef warpText_hpp
#define warpText_hpp

#include <stdio.h>
#include "ofMain.h"

class warpText{
    public :
    warpText(){
    }
    
    
    void setup();
    void update();
    void draw();
    
    //font
    ofTrueTypeFont font;
    ofVboMesh createVboLetter(char c);
    ofVboMesh createVboWord(string word);
    ofVec2f positionLetter(char c);
    void addDepth(ofVec3f* vec, int index);
    vector < ofVec3f> addToVector(int amount, ofVec3f p2, ofVec3f p1);
    
    ofVec2f positionWord;
    int segmentsDivs;
    float depthLetterMoves;
    
    void addVerticalDepth(ofVboMesh* vbo);
    
    // padding
    int padding;
    
    ofVboMesh vboLetter;
    
};
#endif /* warpText_hpp */
