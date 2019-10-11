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
    
    warpText.setup();
//    warpText.setupMeshLetter("Masino Bay");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    top = top.lerp(ofColor::blue, 0.0000001);
    bottom = bottom.lerp(ofColor::grey, 0.0000001);
    
    // wiggle
    warpText.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(top, bottom, OF_GRADIENT_LINEAR);
    this->cam.begin();
    
    warpText.draw();
    
    this->cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key ==  ' '){
    }
    if(key == OF_KEY_LEFT){
    }
    if(key == OF_KEY_RIGHT){
    }
    
    
    if(key ==  's'){
        setup();
    }

}
