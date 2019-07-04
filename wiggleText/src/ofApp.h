#pragma once

#include "ofMain.h"

using namespace std;

#include "WiggleText/WiggleText.hpp"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
    
    //background colors
    ofColor top, bottom;
    ofEasyCam cam;
    
    WiggleText wiggleText;

    
    
    
    
    
};
