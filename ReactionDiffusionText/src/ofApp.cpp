#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetWindowTitle("diffusionReactionText");
    cam.setDistance(400);
    
    // colors
    top = ofColor::lightPink;
    bottom = ofColor::tomato;
    
    // reaction diffuse
    RDArrays.setup({WIDTH, HEIGHT});
    
    string word = "Diffuse";
    wTextOutline.setup();
    wTextOutline.setupMeshWord(word);
    ofVec2f pos = wTextOutline.positionWord(word);
    
    float sizePoint = 4.0;
    for( int i = 0; i < wTextOutline.outline.getNumVertices();i++){
        
        ofVec3f tmpVertLetter = wTextOutline.outline.getVertex(i);
        RDArrays.seedLocation( {tmpVertLetter.x - pos.x / 2 + WIDTH / 2, tmpVertLetter.y + HEIGHT / 2}, sizePoint );
    }
    
    gui.setup("gui");
    gui.add(DiffA.set("DiffA", 1.0, 0, 1.5));
    gui.add(DiffB.set("DiffB", 0.5, 0, 1.0));
    gui.add(kernel.set("kernel", {0.09, 0.15}, {0, 0}, {1.0, 0.8}));
    gui.loadFromFile("settings.xml");
    guiON = false;
    
    RDArrays.guiDiffA = DiffA;
    RDArrays.guiDiffB = DiffB;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    top = top.lerp(ofColor::blue, 0.0000001);
    bottom = bottom.lerp(ofColor::grey, 0.0000001);
    
    
    RDArrays.updateWithShader(DiffA, DiffB, {kernel->x, kernel->y});
    RDArrays.updateFbo();
//    RDArrays.updateVboMesh();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofBackgroundGradient(top, bottom, OF_GRADIENT_LINEAR);
//    ofEnableDepthTest();

//    cam.begin();

    RDArrays.draw();
//    ofSetColor(255, 255);
//    RDArrays.vbo.draw();
    
    
//    cam.end();
//    ofDisableDepthTest();

    
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
