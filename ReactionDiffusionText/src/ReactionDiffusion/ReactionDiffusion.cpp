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
    alpha = 120;
    
}

void ReactionDiffusion::seedLocation(ofVec2f seedOrigin, float  radius){
    
    current.begin();
        ofPushMatrix();
        ofSetColor(0, 0, 255, alpha);
        ofDrawCircle(seedOrigin.y, seedOrigin.x, radius);
        ofPopMatrix();
    current.end();
    
}


void ReactionDiffusion::obstacleLocation(ofVec2f seedOrigin, float  radius){
   
    current.begin();
        ofPushMatrix();
        ofSetColor(255, 0, 0, alpha);
        ofDrawCircle(seedOrigin.y, seedOrigin.x, radius);
        ofPopMatrix();
    current.end();
    
}




void ReactionDiffusion::targetLocationMouse( int x, int y, bool left){
    
    int sizeMousecircle = 4;
    
    if(left){
        seedLocation({(float)x, (float)y}, 4.0);
    }else{
        obstacleLocation({(float)x, (float)y}, 4.0);
    }
    
}

void ReactionDiffusion::shaderReact(float DiffA, float DiffB, ofVec2f kernel){
    
    next.begin();
    shaderTexture.begin();
    shaderTexture.setUniform1f("feed", 0.055);
    shaderTexture.setUniform1f("kill", 0.062);
    shaderTexture.setUniform1f("DiffA", DiffA);
    shaderTexture.setUniform1f("DiffB", DiffB);
    shaderTexture.setUniform2f("kernelGUI", kernel);
    current.draw(0,0);
    shaderTexture.end();
    next.end();
    
    // update the content of the Fbo;
    updateFbo();
}

void ReactionDiffusion::updateFbo(){
    ofPixels mainPixels, nextPixels;
    
    f.readToPixels(mainPixels);
    next.readToPixels(nextPixels);
    
    for(int i = 1; i < sizeCanvas.x-1; i++){
        for(int j = 1; j < sizeCanvas.y-1; j++){
            
            int indexPixel = (i * WIDTH + j ) * 4;
            float a = MAX(nextPixels[indexPixel + 0], 0.0);
            float b = MAX(nextPixels[indexPixel + 2], 0.0);
            
            ofColor tempCol = ofColor::mediumTurquoise;
            
            if(b < 84){
                tempCol = tempCol.lerp(ofColor::blueSteel, 1.0 - b / 84);
            }
            else if( (b > 84) && (b < 168) ){
              
                tempCol = tempCol.lerp(ofColor::orange, 1.0 - (b - 84) / 84);
            }
            else if(b > 168){
                
                tempCol = tempCol.lerp(ofColor::tan, 1.0 - (b - 168) / 84);
                
            }
            
            mainPixels.setColor(i,j, ofColor(tempCol, alpha));
        }
    }
    f.getTexture().loadData(mainPixels.getData(),sizeCanvas.x, sizeCanvas.y, GL_RGBA);
}

void ReactionDiffusion::draw(){
    
    f.draw(0,0);

    // swap is here!
    swap();

}


void ReactionDiffusion::swap(){
   ofFbo temp = current;
    current = next;
    next = temp;
}
