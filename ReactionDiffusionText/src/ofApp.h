#pragma once

#include "ofMain.h"
#include "ofxGui.h"

using namespace std;


#include "ReactionDiffusion/ReactionDiffusion.hpp"

//#include "WiggleText/WiggleText.hpp"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
    void mouseDragged(int x, int y, int button);

    
    //background colors
    ofColor top, bottom;
    ofEasyCam cam;
    
//    WiggleText wiggleText;
    
    ReactionDiffusion RDArrays;

    bool  guiON;
    ofxPanel gui;
    ofParameter < float > DiffA;
    ofParameter < float > DiffB;
    ofParameter < ofVec3f > kernel;
    
    
};
