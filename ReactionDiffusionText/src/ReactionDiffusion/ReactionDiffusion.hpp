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
    
    // reaction diffusion params
    float diffA(int i, int j);
    float diffB(int i, int j);
    float feed(int i, int j);
    float kill(int i, int j);
    
    float Delta = 1.0;
    float guiDiffA, guiDiffB;
    
    ofVec2f sizeCanvas;
    
    void setup(ofVec2f _sizeCanvas);
    void seedLocation(ofVec2f seedOrigin, float  radius);
    void obstacleLocation(ofVec2f obstacleOrigin, float  radius);
    void targetLocationMouse( int x, int y, bool left);

    void update();
    void updateWithShader(float DiffA, float DiffB, ofVec2f kernel);
    void updateFbo();
    void updateVboMesh();
    
    float laPlaceA(int i, int j);
    float laPlaceB(int i, int j);
    
    void draw();
    void swap();
    
    ofFbo f;
    ofFbo current;
    ofFbo next;
    
    ofVboMesh vbo;
    
    float getA(int i, int j, ofVboMesh* v);
    float getB(int i, int j, ofVboMesh* v);

    
    
    // try shader
    ofShader shaderTexture;
    
    
};
#endif /* ReactionDiffusion_hpp */
