//
//  ReactionDiffusion.hpp
//  ReactionDiffusionText
//
//  Created by Pierre Tardif on 05/07/2019.
//
//

#pragma once

#ifndef ReactionDiffusion_hpp
#define ReactionDiffusion_hpp

#include <stdio.h>
#include "ofMain.h"

class ReactionDiffusion
{
    public:
    
    ReactionDiffusion(){
        
    };
    
    // reaction diffusion params
    
    float dA = 1;
    float dB = 0.5;
    float feed = 0.055;
    float k = 0.062;
    
    ofFbo f;
    
    ofVec2f sizeCanvas;
    
    void setup(ofVec2f _sizeCanvas);
    void targetLocation(ofRectangle DiffuseLocation);
    void update();
    
    void updateFbo();
    
    float laPlaceA(int i, int j);
    float laPlaceB(int i, int j);
    
    void draw();
    void swap();
    
    vector < vector < ofVec2f > > current;
    vector < vector < ofVec2f > > next;
    
    
};
#endif /* ReactionDiffusion_hpp */
