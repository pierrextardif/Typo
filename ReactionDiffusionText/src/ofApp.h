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

    ofTrueTypeFont font;
    //background colors
    ofColor top, bottom;
    ofEasyCam cam;
    
    
    ReactionDiffusion RDArrays;
    WiggleText wTextOutline;

    bool  guiON;
    ofxPanel gui;
    ofParameter < float > DiffA;
    ofParameter < float > DiffB;
    ofParameter < ofVec2f > kernel;
    
    
};
