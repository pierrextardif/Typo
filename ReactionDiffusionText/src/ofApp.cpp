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
    
    int sizeSquare = WIDTH / 20;
    RDArrays.setup({WIDTH, HEIGHT});
    RDArrays.targetLocation(ofRectangle(WIDTH / 2 - sizeSquare, HEIGHT / 2 - sizeSquare, sizeSquare * 2, sizeSquare * 2) );
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    top = top.lerp(ofColor::blue, 0.0000001);
    bottom = bottom.lerp(ofColor::grey, 0.0000001);
    
    RDArrays.update();
    RDArrays.updateFbo();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofBackgroundGradient(top, bottom, OF_GRADIENT_LINEAR);
    
    RDArrays.draw();
    
    RDArrays.swap();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key ==  's'){
        setup();
    }

}
