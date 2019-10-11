//
//  warpText.cpp
//  warpText
//
//  Created by Pierre Tardif on 02/08/2019.
//

#include "warpText.hpp"

void warpText::setup(){
    depthLetterMoves = 20;
    segmentsDivs = 8;
    
    float dpi = 300;
    font.loadFont("fonts/Stockholm/Stockholm_Mono.ttf", dpi, true, true, true);
    
    // padding  between letters
    padding = dpi / 10;
    
    vboLetter = createVboWord("hello");
}
void warpText::update(){
    
}
void warpText::draw(){
    
    ofPushMatrix();
    
    ofRotateX(180);
    ofSetColor(255, 255);
    ofTranslate(positionWord);
    vboLetter.drawWireframe();
    ofPopMatrix();
    
}
ofVboMesh warpText::createVboWord(string word){
    
    ofVboMesh vbo;
    vbo.setMode(OF_PRIMITIVE_LINES);
    
    ofVec2f positionCurrLetter = {0,0};
    
    ofVboMesh tempVbo;
    for( int i = 0; i < word.length(); i++){
        char c = word[i];
        tempVbo = createVboLetter(c);
        addVerticalDepth(&tempVbo);
        ofVec2f posLetter = positionLetter(c);
        
        for( int j = 0; j < tempVbo.getNumVertices(); j++){
            ofVec3f pVert = tempVbo.getVertex(j);
            pVert.x += positionCurrLetter.x;
            vbo.addVertex(pVert);
            
        }
        positionCurrLetter.x += posLetter.x + padding;
        if(i == 0)positionCurrLetter.y += posLetter.y;
        
        if(c == ' ')positionCurrLetter.x += (positionCurrLetter.x + padding) / (i+1);
        
    }
    
    positionWord = {-positionCurrLetter.x / 2, positionCurrLetter.y / 4};
    
    return vbo;
}

void warpText::addVerticalDepth(ofVboMesh* vbo){
    
    ofVboMesh vboWarped;
    
    vboWarped.setMode(OF_PRIMITIVE_LINES);
    
    float min =  100000;
    float max = -100000;
    for(int i = 0; i < vbo->getNumVertices(); i++){
        ofVec3f pos = vbo->getVertex(i);
        if(pos.y < min)min = pos.y;
        if(pos.y > max)max = pos.y;
    }
    
    float middle = (max - min) / 2 + min;
    float tolerance = 2.0;
    
    int offsetY = 0;
    
    for(int i = 0; i < vbo->getNumVertices();i++){
        ofVec3f pos = vbo->getVertex(i);
        pos.y += offsetY;
        vboWarped.addVertex(pos);
        if( (pos.y < middle + tolerance) && (pos.y > middle - tolerance) ){
            for(int noiseIndex = 0; noiseIndex < 100; noiseIndex++){
                
                offsetY += noiseIndex * 0.05;
                
                ofVec3f newPos = pos;
                newPos.x += ofNoise(noiseIndex * 0.1) * 20;
                newPos.y += offsetY;
                
                vboWarped.addVertex(newPos);
            }
        }
    }
    
    
    *vbo = vboWarped;
}


ofVec2f warpText::positionLetter(char c){
    ofPath path = font.getCharacterAsPoints(c, true, false);
    
    return {font.getStringBoundingBox(ofToString(c), 0,0).width, font.getStringBoundingBox(ofToString(c), 0,0).height};
}

ofVboMesh warpText::createVboLetter(char c){
     ofPath path = font.getCharacterAsPoints(c, true, false);
    
    positionWord = {-font.getStringBoundingBox(ofToString(c), 0,0).width / 2, font.getStringBoundingBox(ofToString(c), 0,0).height / 2};
    
    
    vector < ofVec3f > points;
    
    for(int i = 0; i < path.getOutline().size(); i++){
        ofPolyline p = path.getOutline()[i];
        size_t l = p.getVertices().size();
        
        for(int j = 0; j < l; j++){
            
            ofVec3f vec = p.getVertices()[j];
            points.push_back(vec);
            if(j+1 < l){

                ofVec3f vec2 = p.getVertices()[j+1];
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
        line.addVertex(points[i]);
    }
    
    
    return line;
}


//--------------------------------------------------------------
void warpText::addDepth(ofVec3f* vec, int index){
    (*vec).z = ofNoise(index *  0.1) * depthLetterMoves;
    
}

vector < ofVec3f> warpText::addToVector(int amount, ofVec3f p2, ofVec3f p1){
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
