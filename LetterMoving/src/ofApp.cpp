#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetWindowTitle("openFrameworks");
    
    ofBackground(239);
    ofSetLineWidth(3);
    ofEnableDepthTest();
    
    this->font.loadFont("fonts/Arial Black.ttf", 300, true, true, true);
    
    
    c = 'A';
    
    outline = createVboLetter(c);
    
    noise = vector < ofVec3f > (outline.getNumVertices());

}

//--------------------------------------------------------------
void ofApp::update(){
    
    updateNoise(noise.data());
    addNoiseToLetter(&outline, noise.data());
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(ofColor::darkCyan, ofColor::green, OF_GRADIENT_LINEAR);
    this->cam.begin();
    ofRotateX(180);
    
    
    ofRotateY(ofGetElapsedTimef() * 30);
    
    ofPushMatrix();
    ofTranslate(position.x, position.y);
    outline.drawWireframe();
//    path.draw(position.x, position.y);
    
    ofPopMatrix();
    
    this->cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key ==  ' '){
        pickRandomLetter();
    }
    if(key == OF_KEY_LEFT){
        indexLetter -= 1;
        pickLetter(indexLetter);
    }
    if(key == OF_KEY_RIGHT){
        indexLetter += 1;
        pickLetter(indexLetter);
    }
    outline = createVboLetter(c);
    noise = vector < ofVec3f > (outline.getNumVertices());

}
void ofApp::pickLetter(int indexLetter){
    c = (char)(indexLetter + 65);
}

void ofApp::pickRandomLetter(){
    int n = (int)(ofRandom(26));
    c = (char)(n + 65);
    
    indexLetter = n;
}


ofVboMesh ofApp::createVboLetter(char c){
    ofPath path = font.getCharacterAsPoints(c, true, false);
    
    position = {-font.getStringBoundingBox(ofToString(c), 0,0).width / 2, font.getStringBoundingBox(ofToString(c), 0,0).height / 2};
    
    
    vector < ofVec3f > points;
    vector < int > indicesForLoops;
    
    for(int i = 0; i < path.getOutline().size(); i++){
        ofPolyline p = path.getOutline()[i];
        size_t l = p.getVertices().size();
        
        bool even = true;
        for(int j = 0; j < l; j++){
            
            ofVec3f vec = p.getVertices()[j];
            points.push_back(vec);
            if(j+1 < l){
                
                ofVec3f vec2 = p.getVertices()[j+1];
                vector< ofVec3f > p = addToVector( 30, vec, vec2);
                for(int k = 0;k < p.size();k++){
                    points.push_back(p[k]);
                }
                
                points.push_back(vec2);
                
            }
            if(j == l-1){
                points.push_back(p.getVertices()[0]);
            }
        }
    }
    
    ofVboMesh line;
    line.setMode(OF_PRIMITIVE_LINES);
    for( int i = 0; i < points.size(); i++){
        line.addVertex({points[i].x, points[i].y,0});
    }
    
    
    return line;
}


//--------------------------------------------------------------
void ofApp::updateNoise(ofVec3f* noisePointer ){
    for( int i = 0; i < noise.size(); i++){
        (*noisePointer).z = 60 * ofNoise((i + ofGetElapsedTimef() * 40 ) * 0.01);
        *(noisePointer++);
    }
}


//--------------------------------------------------------------
void ofApp::addNoiseToLetter(ofVboMesh* v, ofVec3f* noisePointer){
    for(int i = 0; i < v->getNumVertices(); i++){
        ofVec3f pos = v->getVertex(i);
        pos.z  = (*noisePointer).z;
//        60 * ofNoise((i + ofGetElapsedTimef() * 40 ) * 0.01);
        v->setVertex(i, pos);
        if(i%2 == 1){
            pos = v->getVertex(i);
            pos.z  = ( *( noisePointer+1) ).z;
//            pos.z  = 60 * ofNoise((i+1 + ofGetElapsedTimef() * 40 ) * 0.01);
            v->setVertex(i, pos);
            
        }
        if(i == v->getNumVertices() - 1){
            pos = v->getVertex(i);
            pos.z  = (noise[0]).z;
            pos.z  = 60 * ofNoise((ofGetElapsedTimef() * 40 ) * 0.01);
            v->setVertex(i, pos);
        }
        *(noisePointer++);
    }
}

vector < ofVec3f> ofApp::addToVector(int amount, ofVec3f p2, ofVec3f p1){
    vector < ofVec3f > v;
    for(int i = 1; i < amount * 2 - 1; i++){
        float fractionVal = (float)(i) / (float)(2 * amount);
        ofVec3f p3 = {  static_cast<float>(p1.x * fractionVal  + p2.x * (1 - fractionVal)),
            static_cast<float>(p1.y * fractionVal  + p2.y * (1 - fractionVal)),
            static_cast<float>(p1.z * fractionVal  + p2.z * (1 - fractionVal))};
        v.push_back(p3);
        v.push_back(p3);
    }
    return v;
}
