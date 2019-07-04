//
//  WiggleText.cpp
//  LetterMoving
//
//  Created by Pierre Tardif on 04/07/2019.
//

#include "WiggleText.hpp"

void WiggleText::setup(){
    font.loadFont("fonts/Cooper Black Regular.ttf", 300, true, true, true);
    
    
    c = 'A';
    
    //noise
    indexLetter = 0;
    freqNoise = 0.005;
    
    // noise param
    depthNoise = 20.0;
    speedNoise = 700.0;
    
    // letter segments depth
    depthLetterMoves = 4.0;
    // segements disivisions
    segmentsDivs = 10;
}

void WiggleText::update(){
    
    updateNoise(noise.data());
    addNoiseToLetter(&outline, &outlineNoise, noise.data());
    
}
void WiggleText::draw(){
    
    
    ofPushMatrix();
    
    ofRotateX(180);
    ofRotateY(ofGetElapsedTimef() * 30);
    ofTranslate(position.x, position.y);
    
    outlineNoise.drawWireframe();
    
    ofPopMatrix();
    
}

void WiggleText::setupMeshLetter(char c){
    
    outline = outlineNoise = createVboLetter(c);
    noise = vector < ofVec3f > (outline.getNumVertices());
}

void WiggleText::setupMeshWord(string word){
    
    outline = outlineNoise = createVboWord(word);
    noise = vector < ofVec3f > (outline.getNumVertices());
}

ofVboMesh WiggleText::createVboLetter(char c){
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
                vector< ofVec3f > p = addToVector( segmentsDivs, vec, vec2);
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
void WiggleText::addDepth(ofVec3f* vec, int index){
    (*vec).z = (index % 5) * depthLetterMoves;
    
}


//--------------------------------------------------------------
void WiggleText::updateNoise(ofVec3f* noisePointer ){
    for( int i = 0; i < noise.size(); i++){
        (*noisePointer).z = depthNoise * ofNoise((i + ofGetElapsedTimef() * speedNoise ) * freqNoise);
        *(noisePointer++);
    }
}


//--------------------------------------------------------------
void WiggleText::addNoiseToLetter(ofVboMesh* vLetters, ofVboMesh* vNoise, ofVec3f* noisePointer){
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

vector < ofVec3f> WiggleText::addToVector(int amount, ofVec3f p2, ofVec3f p1){
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

ofVec2f WiggleText::positionLetter(char c){
    ofPath path = font.getCharacterAsPoints(c, true, false);
    
    return {font.getStringBoundingBox(ofToString(c), 0,0).width, font.getStringBoundingBox(ofToString(c), 0,0).height};
}


ofVboMesh WiggleText::createVboWord(string word){
    
    ofVboMesh vbo;
    vbo.setMode(OF_PRIMITIVE_LINES);
    
    ofVec2f positionCurrLetter = {0,0};
    
    ofVboMesh tempVbo;
    for( int i = 0; i < word.length(); i++){
        char c = word[i];
        tempVbo = createVboLetter(c);
        ofVec2f posLetter = positionLetter(c);
        
        for( int j = 0; j < tempVbo.getNumVertices(); j++){
            ofVec3f pVert = tempVbo.getVertex(j);
            pVert.x += positionCurrLetter.x;
            vbo.addVertex(pVert);
            
        }
        positionCurrLetter.x += posLetter.x;
        if(i == 0)positionCurrLetter.y += posLetter.y;
        
    }
    
    position = {-positionCurrLetter.x / 2, positionCurrLetter.y / 4};
    
    return vbo;
}

void WiggleText::pickRandomLetter(){
    int n = (int)(ofRandom(26));
    c = (char)(n + 65);
    
    indexLetter = n;
}

void WiggleText::pickLetter(){
    c = (char)(indexLetter + 65);

}
