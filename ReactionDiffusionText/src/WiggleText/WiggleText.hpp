//
//  WiggleText.hpp
//  LetterMoving
//
//  Created by Pierre Tardif on 04/07/2019.
//

#ifndef WiggleText_hpp
#define WiggleText_hpp

#include <stdio.h>
#include "ofMain.h"

class WiggleText{
    public :
    WiggleText(){
        
    }
    
    
    void setup();
    void update();
    void draw();
    
    //font
    ofTrueTypeFont font;
    
    char c;
    int indexLetter;
    ofVboMesh outline, outlineNoise;
    ofVec2f position;
    
    void setupMeshLetter(char c);
    void setupMeshWord(string word);
    ofVec2f positionLetter(char c);
    ofVboMesh createVboLetter(char c);
    ofVboMesh createVboWord(string word);
    vector < ofVec3f> addToVector( int amount, ofVec3f p1, ofVec3f p2);
    float depthLetterMoves, depthNoise, speedNoise;
    float freqNoise;
    void addDepth(ofVec3f* vec, int index);
    
    //segments divisions
    int segmentsDivs;
    
    // padding
    int padding;
    
    
    // noise
    vector < ofVec3f > noise;
    void addNoiseToLetter(ofVboMesh* vLetters, ofVboMesh* vNoise, ofVec3f* noise);
    void updateNoise(ofVec3f* noisePointer );
    
    
    void pickRandomLetter();
    void pickLetter();
    
    
    
    
};
#endif /* WiggleText_hpp */
