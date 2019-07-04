#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetWindowTitle("openFrameworks");
    
    ofBackground(239);
    ofSetLineWidth(3);
    ofEnableDepthTest();
    
    this->font.loadFont("fonts/Cooper Black Regular.ttf", 300, true, true, true);
    
    
    c = 'A';
    
    outline = outlineNoise = createVboLetter(c);
    
    outline = outlineNoise = createVboWord("YO");
    
    noise = vector < ofVec3f > (outline.getNumVertices());
    
    // colors
    top = 555930;
    bottom = 50003;
    incTop = incBottom = 0.05;
    
    
    //noise
    indexLetter = 0;
    freqNoise = 0.005;
    
    depthLetterMoves = 8.0;
    depthNoise = 40.0;
    speedNoise = 700.0;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    updateNoise(noise.data());
    addNoiseToLetter(&outline, &outlineNoise, noise.data());
    
    // gradiant colors
    top += incTop;
    if(top.r == 255)incTop = -incTop;
    bottom.g -= incBottom;
    if(bottom.g == 0)incBottom = -incBottom;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(top, bottom, OF_GRADIENT_LINEAR);
    this->cam.begin();
    ofRotateX(180);
    
    
    ofRotateY(ofGetElapsedTimef() * 30);
    
    ofPushMatrix();
    ofTranslate(position.x, position.y);
    outlineNoise.drawWireframe();
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
    outline = outlineNoise = createVboLetter(c);
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
    int indexVertex = 0;
    
    for(int i = 0; i < path.getOutline().size(); i++){
        ofPolyline p = path.getOutline()[i];
        size_t l = p.getVertices().size();
        
        bool even = true;
        for(int j = 0; j < l; j++){
            
            ofVec3f vec = p.getVertices()[j];
            addDepth(&vec, indexVertex);
            points.push_back(vec);
            if(j+1 < l){
                
                ofVec3f vec2 = p.getVertices()[j+1];
                addDepth(&vec2, indexVertex + 1);
                vector< ofVec3f > p = addToVector( 30, vec, vec2);
                for(int k = 0;k < p.size();k++){
                    points.push_back(p[k]);
                }
                
                points.push_back(vec2);
                
            }
            if(j == l-1){
                points.push_back(p.getVertices()[0]);
            }
            indexVertex ++;
        }
    }
    
    ofVboMesh line;
    line.setMode(OF_PRIMITIVE_LINES);
    for( int i = 0; i < points.size(); i++){
        line.addVertex(points[i]);
    }
    
    
    return line;
}

//--------------------------------------------------------------
void ofApp::addDepth(ofVec3f* vec, int index){
    (*vec).z = (index % 5) * depthLetterMoves;
    
}


//--------------------------------------------------------------
void ofApp::updateNoise(ofVec3f* noisePointer ){
    for( int i = 0; i < noise.size(); i++){
        (*noisePointer).z = depthNoise * ofNoise((i + ofGetElapsedTimef() * speedNoise ) * freqNoise);
        *(noisePointer++);
    }
}


//--------------------------------------------------------------
void ofApp::addNoiseToLetter(ofVboMesh* vLetters, ofVboMesh* vNoise, ofVec3f* noisePointer){
    for(int i = 0; i < vLetters->getNumVertices(); i++){
        ofVec3f pos = vLetters->getVertex(i);
        pos.z  += (*noisePointer).z;
        vNoise->setVertex(i, pos);
        if(i%2 == 1){
            pos = vLetters->getVertex(i);
            pos.z  += ( *( noisePointer+1) ).z;
            vNoise->setVertex(i, pos);
            
        }
        if(i == vLetters->getNumVertices() - 1){
            pos = vLetters->getVertex(i);
            pos.z  += (noise[0]).z;
            vNoise->setVertex(i, pos);
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

ofVec2f ofApp::positionLetter(char c){
    ofPath path = font.getCharacterAsPoints(c, true, false);
    
    ofVec2f pos = {-font.getStringBoundingBox(ofToString(c), 0,0).width, font.getStringBoundingBox(ofToString(c), 0,0).height};
    
    return pos;
}


ofVboMesh ofApp::createVboWord(string word){
    
    ofVboMesh vbo;
    vbo.setMode(OF_PRIMITIVE_LINES);
    
    ofVboMesh tempVbo;
    for( int i = 0; i < word.size(); i++){
        char c = word[i];
        tempVbo = createVboLetter(c);
//        positionLetter
        
        for( int j = 0; j < tempVbo.getNumVertices(); j++){
            vbo.addVertex(tempVbo.getVertex(j));
        }
    }
    
    return vbo;
}
