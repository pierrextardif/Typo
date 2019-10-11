//
//  gothGUI.cpp
//  newFont
//
//  Created by Pierre Tardif on 10/10/2019.
//

#include "gothGUI.hpp"


void gothGUI::setup(){    
    
    // GUI
    guiPanel.setup("control section");
    letterSizes.setName("letter Sizes");
    sections.setName("sections");
    
    
    letterSizes.add(w_h.set("width_height", 0, 0, 1));
    letterSizes.add(power.set("power", 1, 0, 10));
    letterSizes.add(intensity.set("intensity", 100, 1, 1000));
    
    sections.add(amountOfSections.set("amount", sectionIntensity.size(), 1, 10));
    
    int amount = sectionIntensity.size();
    sectionIntensity.clear();
    
    for( int intensityIndex = 0; intensityIndex < amount; intensityIndex++){
        
        
        string name = "amount_" + ofToString(intensityIndex);
        cout << "name = " << name << endl;
        ofParameter < float > newAmount;
        sections.add(newAmount.set(name, 0, -1, 1));
        sectionIntensity.push_back(newAmount);
        
    }
    
    guiPanel.setPosition(4, 4);
    guiPanel.add(letterSizes);
    guiPanel.add(sections);
    
    ofBackground(0);
    ofSetVerticalSync(false);
    guiPanel.minimizeAll();
    guiON = true;
    
    
    // listeners
    ofParamListener = w_h.newListener([this](float&){
        float newW_h = w_h;
        ofNotifyEvent(w_hNewVal, newW_h, this);
//        this->fireOfParam(newW_h);
        
    });
    amountOfSections.addListener(this, &gothGUI::sectionAmountChanged);
}
void gothGUI::sectionAmountChanged(int& amount){
    
    sectionIntensity.clear();
    
    ofParameter< float > newSectionAmount;
    for(int i = 0; i < amount; i++){
        string name = "amount_" + ofToString(i);
        sectionIntensity.push_back(newSectionAmount);
    }
    guiPanel.clear();
    letterSizes.clear();
    sections.clear();
    setup();
    
}
void gothGUI::fireOfParam(float w_hNewVal){
    //cout << "new Value Fired" << endl;
}

void gothGUI::update(){
}

//--------------------------------------------------------------
void gothGUI::keyPressed(int key){
    if(key == 'g') guiON = !guiON;
}

void gothGUI::draw(){
    if(guiON){
        ofPushMatrix();
        guiPanel.draw();
        ofPopMatrix();
    }
}
