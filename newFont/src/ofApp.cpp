#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetWindowTitle("newFont");
    
    ofSetLineWidth(1);
    ofEnableDepthTest();
    
    // colors
    top = ofColor::lightPink;
    bottom = ofColor::tomato;
    
    vLetter.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
//    top = top.lerp(ofColor::blue, 0.0000001);
//    bottom = bottom.lerp(ofColor::grey, 0.0000001);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(top, bottom, OF_GRADIENT_LINEAR);
    cam.begin();
    
    ofRotateY(ofGetElapsedTimef()* 100);
    vLetter.draw();
    
    cam.end();
    
    
    ofDisableDepthTest();
    vLetter.drawGui();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    if(key ==  's'){
        setup();
    }
    if(key == 'a')vLetter.c ='a';
    if(key == 'b')vLetter.c ='b';
    if(key == 'c')vLetter.c ='c';
    if(key == 'd')vLetter.c ='d';
    if(key == 'e')vLetter.c ='e';
    if(key == 'f')vLetter.c ='f';
    
    vLetter.makeLetterIntoVbo();
}
