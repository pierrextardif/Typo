#pragma once

#include "ofMain.h"

using namespace std;

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
    
    ofColor top, bottom;
    float incTop, incBottom;
    
    ofTrueTypeFont font;
    ofEasyCam cam;
    
    
    char c;
    int indexLetter;
    ofVboMesh outline, outlineNoise;
    ofVec2f position;
    
    
    ofVboMesh createVboLetter(char c);
    vector < ofVec3f> addToVector( int amount, ofVec3f p1, ofVec3f p2);
    float depthLetterMoves, depthNoise, speedNoise;
    float freqNoise;
    void addDepth(ofVec3f* vec, int index);

    
    void pickRandomLetter();
    void pickLetter(int indexLetter);
    
    
    // noise
    vector < ofVec3f > noise;
    void addNoiseToLetter(ofVboMesh* vLetters, ofVboMesh* vNoise, ofVec3f* noise);
    void updateNoise(ofVec3f* noisePointer );
    
    
};
