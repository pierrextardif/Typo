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


#define WIDTH 1024
#define HEIGHT 1024

class ReactionDiffusion
{
    public:
    
    ReactionDiffusion(){
        
    };
    
    float alpha;
    
    ofVec2f sizeCanvas;
    
    void setup(ofVec2f _sizeCanvas);
    
    void seedLocation(ofVec2f seedOrigin, float  radius);
    void obstacleLocation(ofVec2f obstacleOrigin, float  radius);
    void targetLocationMouse( int x, int y, bool left);

    void shaderReact(float DiffA, float DiffB, ofVec2f kernel);
    void updateFbo();
    
    void draw();
    void swap();
    
    ofFbo f;
    ofFbo current;
    ofFbo next;

    
    
    // try shader
    ofShader shaderTexture;
    
    
};
#endif /* ReactionDiffusion_hpp */
