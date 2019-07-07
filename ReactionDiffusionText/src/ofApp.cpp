#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetWindowTitle("diffusionReactionText");
    
    // colors
    top = ofColor::lightPink;
    bottom = ofColor::tomato;
    
    int sizeSquare = 50;
    RDArrays.setup({WIDTH, HEIGHT});
    RDArrays.seedLocation(ofRectangle(WIDTH / 2 - sizeSquare, HEIGHT / 2 - sizeSquare, sizeSquare * 2, sizeSquare * 2) );
    
    gui.setup("gui");
    gui.add(DiffA.set("DiffA", 1.0, 0, 1.5));
    gui.add(DiffB.set("DiffB", 0.5, 0, 1.0));
    gui.add(kernel.set("kernel", {0.1, -1, 0.05}, {0,-1, 0}, {1.0, 1.0, 0.8}));
    guiON = true;
    
    RDArrays.guiDiffA = DiffA;
    RDArrays.guiDiffB = DiffB;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    top = top.lerp(ofColor::blue, 0.0000001);
    bottom = bottom.lerp(ofColor::grey, 0.0000001);
    
    
    RDArrays.updateWithShader(DiffA, DiffB, {kernel->x, kernel->y, kernel->z});
    RDArrays.updateFbo();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofBackgroundGradient(top, bottom, OF_GRADIENT_LINEAR);
    
    RDArrays.draw();
    
    RDArrays.swap();
    
    ofPushMatrix();
    if(guiON)gui.draw();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

    if(button == 0)RDArrays.targetLocationMouse(x, y, true);
    if(button == 2)RDArrays.targetLocationMouse(x, y, false);

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key ==  's'){
        setup();
    }
    if(key == 'g')guiON = !guiON;

}
