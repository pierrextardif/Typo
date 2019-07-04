#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetWindowTitle("wiggleText");
    
    ofSetLineWidth(1);
    ofEnableDepthTest();
    
    // colors
    top = 555930;
    bottom = 50003;
    incTop = incBottom = 0.05;
    
    
    wiggleText.setup();
    wiggleText.setupMeshWord("Masino");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // gradiant colors
    top += incTop;
    if(top.r == 255)incTop = -incTop;
    bottom.g -= incBottom;
    if(bottom.g == 0)incBottom = -incBottom;
    
    // wiggle
    wiggleText.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(top, bottom, OF_GRADIENT_LINEAR);
    this->cam.begin();
    
    wiggleText.draw();
    
    this->cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key ==  ' '){
        wiggleText.pickRandomLetter();
    }
    if(key == OF_KEY_LEFT){
        wiggleText.indexLetter -= 1;
        wiggleText.pickLetter();
    }
    if(key == OF_KEY_RIGHT){
        wiggleText.indexLetter += 1;
        wiggleText.pickLetter();
    }
    wiggleText.setupMeshLetter(wiggleText.c);

}
