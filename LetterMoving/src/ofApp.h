#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
    
    
    
    ofTrueTypeFont font;
    ofEasyCam cam;
    
    
    char c;
    int indexLetter = 0;
    ofVboMesh outline;
    ofVec2f position;
    
    ofVboMesh createVboLetter(char c);
    vector < ofVec3f> addToVector( int amount, ofVec3f p1, ofVec3f p2);
    
    void pickRandomLetter();
    void pickLetter(int indexLetter);
    
    
    
};
