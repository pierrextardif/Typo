//
//  vboLetter.cpp
//  newFont
//
//  Created by Pierre Tardif on 10/10/2019.
//

#include "vboLetter.hpp"


void vboLetter::setup(){
    float dpi = 300;
    font.loadFont("fonts/Stockholm/Stockholm_Mono.ttf", dpi, true, true, true);
    
    // gui
    gui.sectionIntensity.resize(1);
    gui.setup();
    
    // letter
    c = 'a';

    outline = createVboLetter(c);
    
    ofAddListener(gui.w_hNewVal, this, &vboLetter::newWHProp);
    ofAddListener(gui.amountNewVal, this, &vboLetter::newSliderAmount);
    
}
void vboLetter::newWHProp(float& newW_H){
    //cout << "getting a new W & H " << endl;
    outline = createVboLetter(c);
    makeLetterIntoVbo();
}
void vboLetter::newSliderAmount(ofVec2f& newAmount){
    cout << "change on the amount : " << ofToString(newAmount.x) << " - > " << ofToString(newAmount.y) << endl;
//    makeLetterIntoVbo();
}



void vboLetter::update(){
    
}

void vboLetter::draw(){
    ofPushMatrix();
    
    ofRotateX(180);
    ofTranslate(position.x, position.y);
    outline.drawWireframe();
    ofPopMatrix();
}

void vboLetter::drawGui(){
    gui.draw();
}

void vboLetter::makeLetterIntoVbo(){
    outline = createVboLetter(c);
    boundingBoxVbo(&outline);
    slideVboLetter(&outline);
    
    
}


ofVboMesh vboLetter::createVboLetter(char c){
    
    ofPath path = font.getCharacterAsPoints(c, true, false);
    
    ofVec2f boundingBoxLetter = { font.getStringBoundingBox(ofToString(c), 0,0).width,
        font.getStringBoundingBox(ofToString(c), 0,0).height
    };
//    cout << "bounding letter is  : " << ofToString(boundingBoxLetter) << endl;
    
    position = {-font.getStringBoundingBox(ofToString(c), 0,0).width / 2, font.getStringBoundingBox(ofToString(c), 0,0).height / 2};
    
    vector < ofVec3f > points;
    int indexVertex = 0;
    
    for(int i = 0; i < path.getOutline().size(); i++){
        ofPolyline p = path.getOutline()[i];
        size_t l = p.getVertices().size();
        
        bool even = true;
        for(int j = 0; j < l; j++){
            
            ofVec3f vec = p.getVertices()[j];
            
            ofVec2f propCompression = ofVec2f(gui.w_h, gui.w_h);
            
            reWorkPropX(&vec.x, boundingBoxLetter.x, propCompression.x);
            reWorkPropY(&vec.y, boundingBoxLetter.y, propCompression.y);
            
            points.push_back(vec);
            if(j+1 < l){

                ofVec3f vec2 = p.getVertices()[j+1];
                reWorkPropX(&vec2.x, boundingBoxLetter.x, propCompression.x);
                reWorkPropY(&vec2.y, boundingBoxLetter.y, propCompression.y);

                points.push_back(vec2);

            }
            if(j == l-1){
                vec = p.getVertices()[0];
                reWorkPropX(&vec.x, boundingBoxLetter.x, propCompression.x);
                reWorkPropY(&vec.y, boundingBoxLetter.y, propCompression.y);
                
                points.push_back(vec);
            }
            indexVertex ++;
        }
    }
    
    ofVboMesh line;
    line.setMode(OF_PRIMITIVE_LINES);
    for( int i = 0; i < points.size(); i++){
        line.addVertex({points[i].x, points[i].y, 0});
    }
    
    
    return line;
}

void vboLetter::reWorkPropX(float* vec, float bound, float compression){
    if(*vec < bound / 2){
        float prop = ofMap(*vec, 0, bound / 2, 1, 0);
        *vec += pow(prop, gui.power) * compression * gui.intensity;
        if(*vec > bound / 2)*vec = bound / 2;
        if(*vec < 0)*vec = 0;
    }
    if(*vec > bound / 2){
        float prop = ofMap(*vec, bound / 2, bound, 0, 1);
        *vec -= pow(prop, gui.power) * (compression) * gui.intensity;
        if(*vec > bound)*vec = bound;
        if(*vec < bound / 2)*vec = bound / 2;
    }
}


void vboLetter::reWorkPropY(float* vec, float bound, float compression){
    if(*vec < 0){
        float prop = ofMap(*vec, -bound, 0, 1, 0);
        *vec -= pow(prop, gui.power) * compression * gui.intensity;
//        if(*vec < -bound)*vec = -bound;
        if(*vec > 0)*vec = 0;
    }
    if(*vec > 0){
        float prop = ofMap(*vec, 0, bound, 0, 1);
        *vec += pow(prop, gui.power) * (compression) * gui.intensity;
//        if(*vec > bound)*vec = bound;
        if(*vec < 0)*vec = 0;
    }
}


vector < ofVec3f> vboLetter::addToVector(int amount, ofVec3f p2, ofVec3f p1){
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

void vboLetter::slideVboLetter(ofVboMesh* v){
    
    
//    position = {0, 0};
    
    vector < ofVec3f > points;
    int indexVertex = 0;
        
    for(int i = 0; i < v->getNumVertices(); i++){
        ofVec3f pos = v->getVertex(i);
        for( int sec = 0; sec < gui.amountOfSections; sec++){
            
            int posValX = round(abs(pos.x - minMaxX.x) / maxto0XY.x * (gui.amountOfSections - 1));
//            cout << "posVal = " << ofToString(posVal) << endl;
            if((posValX >= sec) && (posValX < sec + 1) ){
//                cout << "section picked : " << ofToString(sec) << endl;
                pos.y += 100 * gui.sectionIntensity[sec];
                v->setVertex(i, pos);
            }
            int posValY = abs(pos.y - minMaxY.x) / maxto0XY.y;
//            cout << "posValY = " << ofToString(posValY) << endl;
             if((posValY >= sec) && (posValY < sec + 1) ){
            //                cout << "section picked : " << ofToString(sec) << endl;
                            pos.x += 100 * gui.sectionIntensity[sec];
                            v->setVertex(i, pos);
              }
        }
        
    }
}


void vboLetter::boundingBoxVbo(ofVboMesh* v){
    
    minMaxX = {1000, -1000};
    minMaxY = {1000, -1000};
    for( int i = 0; i < v->getNumVertices(); i++){
        
        ofVec3f vec = v->getVertex(i);
        
        if(vec.x < minMaxX.x)minMaxX.x = vec.x;
        if(vec.x > minMaxX.y)minMaxX.y = vec.x;
        
        if(vec.y < minMaxY.x)minMaxY.x = vec.y;
        if(vec.y > minMaxY.y)minMaxY.y = vec.y;
    }
    maxto0XY = {abs(minMaxX.y - minMaxX.x), abs(minMaxY.y - minMaxY.x)};
    
//    cout << "minMaxY = " << ofToString(minMaxY) << endl;
//    cout << "maxto0XY.y = " << ofToString(maxto0XY.y) << endl;
}
