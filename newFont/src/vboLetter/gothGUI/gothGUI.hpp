//
//  gothGUI.hpp
//  newFont
//
//  Created by Pierre Tardif on 10/10/2019.
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class gothGUI: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    
    //// gui
    bool guiON;
    ofxPanel guiPanel;
    
    ofParameterGroup letterSizes;
    
    ofParameter < float > w_h;
    ofParameter < float > power;
    ofParameter < float > intensity;
    
    ofParameterGroup sections;
    ofParameter < int > amountOfSections;
    vector < ofParameter < float > > sectionIntensity;
    void sectionAmountChanged(int& amount);
    
    void fireOfParam(float w_hNewVal);
    
    ////
    
    //// Events
    ofEvent < float > w_hNewVal;
    ofEvent < ofVec2f > amountNewVal;
    
    private:
        ofEventListener ofParamListener;
    ofEventListener ofParamListenerAmount;
    
};
