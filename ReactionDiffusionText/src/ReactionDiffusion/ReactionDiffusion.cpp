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
    current.allocate(sizeCanvas.x, sizeCanvas.y, GL_RGBA);
    next.allocate(sizeCanvas.x, sizeCanvas.y, GL_RGBA);
    
    shaderTexture.load("../../src/shaders/main/shader.vert", "../../src/shaders/main/shader.frag");
    
    guiDiffA = 1.0;
    guiDiffB = 0.5;
    alpha = 120;
}

void ReactionDiffusion::seedLocation(ofRectangle DiffuseLocation){
    
    int radius = 1;
    current.begin();
    for(int i = DiffuseLocation.x; i < DiffuseLocation.x + DiffuseLocation.width; i++){
        for(int j = DiffuseLocation.y; j < DiffuseLocation.y + DiffuseLocation.height; j++){
            
            ofSetColor(255, alpha);
            ofDrawCircle(i,j, radius);
            
        }
    }
    current.end();
    
}


void ReactionDiffusion::obstacleLocation(ofRectangle DiffuseLocation){
    
    int radius = 1;
    current.begin();
    for(int i = DiffuseLocation.x; i < DiffuseLocation.x + DiffuseLocation.width; i++){
        for(int j = DiffuseLocation.y; j < DiffuseLocation.y + DiffuseLocation.height; j++){
            
            ofSetColor(0, alpha);
            ofDrawCircle(i,j, radius);
            
        }
    }
    current.end();
    
}




void ReactionDiffusion::targetLocationMouse( int x, int y, bool left){
    
    int sizeMousecircle = 4;
    
    if(left){
        seedLocation(ofRectangle(y,x,4,4));
    }else{
        obstacleLocation(ofRectangle(y,x,4,4));
    }
    
}

void ReactionDiffusion::updateWithShader(float DiffA, float DiffB, ofVec3f kernel){
    
    next.begin();
    shaderTexture.begin();
    shaderTexture.setUniform1f("feed", feed(0,0));
    shaderTexture.setUniform1f("kill", kill(0,0));
    shaderTexture.setUniform1f("Du", DiffA);
    shaderTexture.setUniform1f("Dv", DiffB);
    shaderTexture.setUniform3f("kernelGUI", kernel);
    current.draw(0,0);
    shaderTexture.end();
    next.end();
}

void ReactionDiffusion::update(){
    
//    for(int i = 1; i < sizeCanvas.x-1; i++){
//        for(int j = 1; j < sizeCanvas.y-1; j++){
//
//            int indexVertex = i * WIDTH + j;
//
//            float a = current.getNormal(indexVertex).x;
//            float b = current.getNormal(indexVertex).y;
//
//            float nX = ( a + (diffA(i,j) * laPlaceA(i,j)) - a * b * b + ( feed(i,j) * (1.0 - a) ) )     * Delta;
////                             a + (dA * laplaceA(x, y)) - (a * b * b) + (feed * (1 - a));
//            float nY = ( b + (diffB(i,j) * laPlaceB(i,j)) + a * b * b - ( kill(i,j) + feed(i,j) ) * b ) * Delta;
////                             b + (dB *         laplaceB(x, y)) + (a * b * b) -((k + feed) * b);
//
//            nX = MAX((float)0.0,MIN((float)1.0, nX));
//            nY = MAX((float)0.0,MIN((float)1.0, nY));
//
//            next.setNormal(indexVertex, {nX, nY, 0});
//
//        }
//    }
}


float ReactionDiffusion::diffA(int i, int j){
    return guiDiffA;

//    float d =  pow( (i-WIDTH/2), 2) + pow( (j-HEIGHT/2), 2);
//    return 1.4 - (0.05 +  d/( pow( (WIDTH/2), 2) + pow( (HEIGHT/2), 2) ) );
}

float ReactionDiffusion::diffB(int i, int j){
    return guiDiffB;
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
//    sumA += getA(i, j, &current) * -1;
//    sumA += getA(i - 1, j, &current) * 0.2;
//    sumA += getA(i + 1, j, &current) * 0.2;
//    sumA += getA(i, j - 1, &current) * 0.2;
//    sumA += getA(i, j + 1, &current) * 0.2;
//    sumA += getA(i - 1, j - 1, &current) * 0.05;
//    sumA += getA(i + 1, j - 1, &current) * 0.05;
//    sumA += getA(i + 1, j + 1, &current) * 0.05;
//    sumA += getA(i - 1, j + 1, &current) * 0.05;
    return sumA;
}


float ReactionDiffusion::laPlaceB(int i, int j){
    float sumB = 0.0;
//    sumB += getB(i, j, &current) * -1;
//    sumB += getB(i - 1, j, &current) * 0.2;
//    sumB += getB(i + 1, j, &current) * 0.2;
//    sumB += getB(i, j - 1, &current) * 0.2;
//    sumB += getB(i, j + 1, &current) * 0.2;
//    sumB += getB(i - 1, j - 1, &current) * 0.05;
//    sumB += getB(i + 1, j - 1, &current) * 0.05;
//    sumB += getB(i + 1, j + 1, &current) * 0.05;
//    sumB += getB(i - 1, j + 1, &current) * 0.05;
    return sumB;
}


float ReactionDiffusion::getA(int i, int j, ofVboMesh* v){
    int indexVertex = i * WIDTH + j;
    return v->getNormal(indexVertex).x;
}

float ReactionDiffusion::getB(int i, int j, ofVboMesh* v){
    int indexVertex = i * WIDTH + j;
    return v->getNormal(indexVertex).y;
}

void ReactionDiffusion::updateFbo(){
    ofPixels mainPixels, currentPixels, nextPixels;
    f.readToPixels(mainPixels);
    current.readToPixels(currentPixels);
    next.readToPixels(nextPixels);
    for(int i = 1; i < sizeCanvas.x-1; i++){
        for(int j = 1; j < sizeCanvas.y-1; j++){
            
            
            int indexPixel = (i * WIDTH + j ) * 4;
            
            float diff = nextPixels[indexPixel] - nextPixels[indexPixel + 1];
//            float diff = next.getNormal(indexVertex).x - next.getNormal(indexVertex).y;
            float c = MAX(diff, 0.0)*255.0;
            
            mainPixels.setColor(i,j, ofColor(c, alpha));
        }
    }
    f.getTexture().loadData(mainPixels.getData(),sizeCanvas.x, sizeCanvas.y, GL_RGBA);
}

void ReactionDiffusion::draw(){
    
    f.draw(0,0);

}


void ReactionDiffusion::swap(){
   ofFbo temp = current;
    current = next;
    next = temp;
}
