#pragma once

#include "ofMain.h"
#include "ofxGui.h"

using namespace std;


#include "ReactionDiffusion/ReactionDiffusion.hpp"

#include "WiggleText/WiggleText.hpp"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
        void mouseDragged(int x, int y, int button);

    //background colors
    ofColor top, bottom;
    
    
    ReactionDiffusion RDArrays;
    
    // only used to get the outline of the text
    WiggleText wTextOutline;

    
    bool  guiON;
    ofxPanel gui;
    ofParameter < float > DiffA;
    ofParameter < float > DiffB;
    ofParameter < ofVec2f > kernel;
    
    
};
