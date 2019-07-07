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


#define WIDTH 200
#define HEIGHT 200

class ReactionDiffusion
{
    public:
    
    ReactionDiffusion(){
        
    };
    
    // reaction diffusion params
    float diffA(int i, int j);
    float diffB(int i, int j);
    float feed(int i, int j);
    float kill(int i, int j);
    
    float Delta = 1.0;
    
    ofFbo f;
    
    ofVec2f sizeCanvas;
    
    void setup(ofVec2f _sizeCanvas);
    void targetLocation(ofRectangle DiffuseLocation);
    void targetLocationMouse( int x, int y);

    void update();
    
    void updateFbo();
    
    float laPlaceA(int i, int j);
    float laPlaceB(int i, int j);
    
    void draw();
    void swap();
    
    vector < vector < ofVec2f > > current;
    vector < vector < ofVec2f > > next;
    
    
    // try shader
    ofShader shaderTexture;
    void updateShader();
    
    
};
#endif /* ReactionDiffusion_hpp */
