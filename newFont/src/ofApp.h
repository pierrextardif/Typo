#pragma once

#include "ofMain.h"
using namespace std;

#include "vboLetter/vboLetter.hpp"
#include "vboLetter/gothGUI/gothGUI.hpp"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
    
    //background colors
    ofColor top, bottom;
    ofEasyCam cam;
    
    vboLetter vLetter;
    
};
