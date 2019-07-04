#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetWindowTitle("wiggleText");
    
    ofSetLineWidth(1);
    ofEnableDepthTest();
    
    // colors
    top = ofColor::lightPink;
    bottom = ofColor::tomato;
    
    wiggleText.setup();
    wiggleText.setupMeshWord("wiggle Text");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    top = top.lerp(ofColor::blue, 0.0000001);
    bottom = bottom.lerp(ofColor::grey, 0.0000001);
    
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
    
    
    if(key ==  's'){
        setup();
    }

}
