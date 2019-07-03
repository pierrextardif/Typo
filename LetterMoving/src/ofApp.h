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
    
    ofPath path;
    ofVboMesh outline;
    ofVec2f position;
    
    vector < ofVec3f> addToVector( int amount, ofVec3f p1, ofVec3f p2);
    
    
};
