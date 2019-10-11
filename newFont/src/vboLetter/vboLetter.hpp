//
//  vboLetter.hpp
//  newFont
//
//  Created by Pierre Tardif on 10/10/2019.
//

#ifndef vboLetter_hpp
#define vboLetter_hpp

#include <stdio.h>
#include "ofMain.h"


#include "gothGUI.hpp"

class vboLetter{
    
    public :
    
    vboLetter(){
        
    }
    
    
    void setup();
    void update();
    void draw();
    void drawGui();
    
    gothGUI gui;
    
    ofVboMesh outline;
    
    // Event
    void newWHProp(float& newW_H);
    void newSliderAmount(ofVec2f& newAmount);
    
    void reWorkPropX(float* vec, float bound, float compression);
    void reWorkPropY(float* vec, float bound, float compression);
    
    void makeLetterIntoVbo();
    ofVboMesh createVboLetter(char c);
    vector < ofVec3f> addToVector(int amount, ofVec3f p2, ofVec3f p1);
    void slideVboLetter(ofVboMesh* v);
    
    void boundingBoxVbo(ofVboMesh* v);
    
    //font
    ofTrueTypeFont font;
    ofVec2f position;
    
    ofVec2f maxto0XY;
    ofVec2f minMaxX;
    ofVec2f minMaxY;
    
    char c;
};

#endif /* vboLetter_hpp */
