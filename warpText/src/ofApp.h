#pragma once

#include "ofMain.h"

using namespace std;

#include "warpText/warpText.hpp"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
    
    //background colors
    ofColor top, bottom;
    ofEasyCam cam;
    
    warpText warpText;

    
    
    
    
    
};
