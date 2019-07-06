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
}

void ReactionDiffusion::targetLocation(ofRectangle DiffuseLocation){
    
    for(int i = DiffuseLocation.x; i < DiffuseLocation.x + DiffuseLocation.width; i++){
        for(int j = DiffuseLocation.y; j < DiffuseLocation.y + DiffuseLocation.height; j++){
            
            current[i][j].y = 1.0;
//            next[i][j].y = 1.0;
            
        }
    }
    
}

void ReactionDiffusion::update(){
    
    for(int i = 1; i < sizeCanvas.x-1; i++){
        for(int j = 1; j < sizeCanvas.y-1; j++){
            
            double a = current[i][j].x;
            double b = current[i][j].y;
            
            next[i][j].x = a + (dA * laPlaceA(i,j)) - a * pow(b, 2) + ( feed * (1-a) );
            next[i][j].y = b + (dB * laPlaceB(i,j)) - a * pow(b, 2) - ( k + feed * b );
//            if(next[i][j].x > 1)next[i][j].x = 1;
//            if(next[i][j].x < 0)next[i][j].x = 0;
//            if(next[i][j].y > 1)next[i][j].y = 1;
//            if(next[i][j].y < 0)next[i][j].y = 0;
        }
    }
}

double ReactionDiffusion::laPlaceA(int i, int j){
    double sumA = 0;
    sumA += current[i][j].x * -1;
    sumA += current[i - 1][j].x * 0.2;
    sumA += current[i + 1][j].x * 0.2;
    sumA += current[i][j + 1].x * 0.2;
    sumA += current[i][j - 1].x * 0.2;
    sumA += current[i - 1][j - 1].x * 0.05;
    sumA += current[i + 1][j - 1].x * 0.05;
    sumA += current[i + 1][j + 1].x * 0.05;
    sumA += current[i - 1][j + 1].x * 0.05;
    return sumA;
}


double ReactionDiffusion::laPlaceB(int i, int j){
    double sumB = 0.0;
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
//            int indexPixel = ( (sizeCanvas.x - 1) * j + i ) * 4;
            double a = next[i][j].x;
            double b = next[i][j].y;
            double c = (a - b) * 255;
//            if(c > 255)c = 255;
//            if(c < 0)  c = 0;
            
            pixels.setColor(i,j, ofColor(c,c,c, 120.0));
        }
    }
    f.getTexture().loadData(pixels.getData(),sizeCanvas.x, sizeCanvas.y, GL_RGBA);
}

void ReactionDiffusion::draw(){
    
    f.draw(0,0);

}


void ReactionDiffusion::swap(){
    vector < vector < ofVec2f > > temp = current;
    current = next;
    next = temp;
}
