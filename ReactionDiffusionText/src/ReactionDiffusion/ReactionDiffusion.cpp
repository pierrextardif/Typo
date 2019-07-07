//
//  ReactionDiffusion.hpp
//  ReactionDiffusionText
//
//  Created by Pierre Tardif on 05/07/2019.
//
//

#include "ReactionDiffusion.hpp"


void ReactionDiffusion::setup(ofVec2f _sizeCanvas){
    
    sizeCanvas = _sizeCanvas;
    
    f.allocate(sizeCanvas.x, sizeCanvas.y, GL_RGBA);
    
    for(int i = 0; i < sizeCanvas.x; i++){
        vector < ofVec2f > currentLine;
        for(int j = 0; j < sizeCanvas.y; j++){
            ofVec2f pointVal = {1.0, 0.0};
            currentLine.push_back(pointVal);
        }
        current.push_back(currentLine);
        next.push_back(currentLine);
    }
    
    shaderTexture.load("../../src/shaders/main/shader.vert", "../../src/shaders/main/shader.frag");
}

void ReactionDiffusion::targetLocation(ofRectangle DiffuseLocation){
    
    for(int i = DiffuseLocation.x; i < DiffuseLocation.x + DiffuseLocation.width; i++){
        for(int j = DiffuseLocation.y; j < DiffuseLocation.y + DiffuseLocation.height; j++){
            
            current[i][j].y = 1.0;
//            next[i][j].y = 1.0;
            
        }
    }
    
}




void ReactionDiffusion::targetLocationMouse( int x, int y){
    
    int sizeMousecircle = 4;
    for(int i = x; i < x + sizeMousecircle; i++){
        for(int j = y; j < y + sizeMousecircle; j++){
            
            current[i][j].y = 1.0;
            //            next[i][j].y = 1.0;
            
        }
    }
    
}

void ReactionDiffusion::update(){
    
    for(int i = 1; i < sizeCanvas.x-1; i++){
        for(int j = 1; j < sizeCanvas.y-1; j++){
            
            float a = current[i][j].x;
            float b = current[i][j].y;
            
//                             a + (dA * laplaceA(x, y)) - (a * b * b) + (feed * (1 - a));
            next[i][j].x = ( a + (diffA(i,j) * laPlaceA(i,j)) - a * b * b + ( feed(i,j) * (1.0 - a) ) )     * Delta;
            next[i][j].y = ( b + (diffB(i,j) * laPlaceB(i,j)) + a * b * b - ( kill(i,j) + feed(i,j) ) * b ) * Delta;
//                             b + (dB *         laplaceB(x, y)) + (a * b * b) -((k + feed) * b);
            
            next[i][j].x = MAX((float)0.0,MIN((float)1.0,next[i][j].x));
            next[i][j].y = MAX((float)0.0,MIN((float)1.0,next[i][j].y));
            
        }
    }
}


float ReactionDiffusion::diffA(int i, int j){
    return 1.0;

//    float d =  pow( (i-WIDTH/2), 2) + pow( (j-HEIGHT/2), 2);
//    return 1.4 - (0.05 +  d/( pow( (WIDTH/2), 2) + pow( (HEIGHT/2), 2) ) );
}

float ReactionDiffusion::diffB(int i, int j){
    return 0.5;
//    float d =  pow( (i-WIDTH/2), 2) + pow( (j-HEIGHT/2), 2);
//    return 1.4 - (0.05 +  d/( pow( (WIDTH/2), 2) + pow( (HEIGHT/2), 2) ) );
}

float ReactionDiffusion::feed(int i, int j){
    return 0.055;
//    return 0.01 + 0.1 * ((float)i/WIDTH);
}


float ReactionDiffusion::kill(int i, int j){
    return 0.062;
//    return 0.055 + 0.01 * ((float)j/HEIGHT);
    
}

float ReactionDiffusion::laPlaceA(int i, int j){
    float sumA = 0;
    sumA += current[i][j].x * -1;
    sumA += current[i - 1][j].x * 0.2;
    sumA += current[i + 1][j].x * 0.2;
    sumA += current[i][j - 1].x * 0.2;
    sumA += current[i][j + 1].x * 0.2;
    sumA += current[i - 1][j - 1].x * 0.05;
    sumA += current[i + 1][j - 1].x * 0.05;
    sumA += current[i + 1][j + 1].x * 0.05;
    sumA += current[i - 1][j + 1].x * 0.05;
    return sumA;
}

float ReactionDiffusion::laPlaceB(int i, int j){
    float sumB = 0.0;
    sumB += current[i][j].y * -1;
    sumB += current[i - 1][j].y * 0.2;
    sumB += current[i + 1][j].y * 0.2;
    sumB += current[i][j + 1].y * 0.2;
    sumB += current[i][j - 1].y * 0.2;
    sumB += current[i - 1][j - 1].y * 0.05;
    sumB += current[i + 1][j - 1].y * 0.05;
    sumB += current[i + 1][j + 1].y * 0.05;
    sumB += current[i - 1][j + 1].y * 0.05;
    return sumB;
}

void ReactionDiffusion::updateFbo(){
    ofPixels pixels;
    f.readToPixels(pixels);
    for(int i = 1; i < sizeCanvas.x-1; i++){
        for(int j = 1; j < sizeCanvas.y-1; j++){
            float diff = next[i][j].x - next[i][j].y;
            float c = MAX( diff,0.0)*255.0;
            
            pixels.setColor(i,j, ofColor(c, 120.0));
        }
    }
    f.getTexture().loadData(pixels.getData(),sizeCanvas.x, sizeCanvas.y, GL_RGBA);
}

void ReactionDiffusion::updateShader(){
//    shaderTexture.begin();
//    shaderTexture.
}

void ReactionDiffusion::draw(){
    
    f.draw(0,0);

}


void ReactionDiffusion::swap(){
    vector < vector < ofVec2f > > temp = current;
    current = next;
    next = temp;
}
