#include "sas1Source.h"

void sas1Source::setup(){
	// Give our source a decent name
    name = "Saskia Pirate 1a";
	// Allocate our FBO source, decide how big it should be
    allocate(600, 600);
}

void sas1Source::setName(string _name){
    name = _name;
}

void sas1Source::setShowDraw(int b) {
    showDraw = b;
}

void sas1Source::setSelector(bool c){
    selector = c;
}



// Don't do any drawing here
void sas1Source::update(){
    counter++;
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void sas1Source::draw(){
    ofClear(0); //clear the buffer
    
    if (showDraw == 0) {
        sas0(counter, selector); // http://sasj.tumblr.com/post/148705230735/geometric-animations-160809
    }
    else if (showDraw == 1) {
        sas1(counter, selector); // http://sasj.tumblr.com/post/145065131225/geometric-animations-160528
    }
    else if (showDraw == 2) {
        sas2(counter, selector); // http://sasj.tumblr.com/post/144966183100/geometric-animations-160526
    }
    else if (showDraw == 3) {
        sas3(counter, selector); // http://sasj.tumblr.com/post/140521642500/geometric-animations-160305
    }
    else if (showDraw == 4) {
        sas4(counter, selector); // http://sasj.tumblr.com/post/162953278415/geometric-animations-170713
    }
    else if (showDraw ==5) {
        sas5(counter, selector); // http://sasj.tumblr.com/post/160085368820/geometric-animations-170428
    }

    
}

//--------------------------------------------------------------
void sas1Source::sas0 (int phase, bool selector) {
    ofColor green = ofColor(131, 181, 145);
    ofColor pink = ofColor(188, 60, 114);
    ofColor shadow = ofColor(42, 26, 64);
    
    int sphereSize = 15;
    
    int offsetX = sphereSize*2;
    int offsetY = sphereSize*2;
    int stepX = 20;
    int stepY = 20;
    
    int maxRows = (fbo->getHeight()/2/(sphereSize+stepY));
    int maxColumns = (fbo->getWidth()-offsetX*2)/(sphereSize+stepX);
    
    ofSetColor(pink);
    ofDrawRectangle(0,0, fbo->getWidth(), fbo->getHeight());
    
    ofTranslate(offsetX+stepX, fbo->getHeight()/2-(maxRows*(sphereSize+stepY)/2-offsetY));
    
    for (int j=0; j<maxColumns; j++) {
        for (int i=0; i<maxRows; i++) {
            float phaseSize;
            float phaseY;
            float sizeOffset = ofMap(i*j, 0, maxColumns*maxRows, -offsetY, offsetX);
            
            if (selector == true) {
                if (j%2 == 0) {
                    phaseY =  ofMap(cos(ofDegToRad(phase)), 1, -1, -offsetY, offsetY);
                    phaseSize = ofMap(sin(ofDegToRad(phase+(180/(i+1))+(360*j/8))), 1,-1, 0, sphereSize, true);
                } else {
                    phaseY =  ofMap(cos(ofDegToRad(phase)), -1, 1, -offsetY, offsetY);
                    phaseSize = ofMap(sin(ofDegToRad(phase+(180/(i+1))-(360*j/12))), -1,1, 0, sphereSize, true);
                }
                
                ofSetColor(shadow);
                ofDrawCircle((sphereSize+stepX)*j, (sphereSize+stepY)*i+phaseY+sphereSize/4, (phaseSize+sizeOffset)/2);
                ofSetColor(green);
                ofDrawCircle((sphereSize+stepX)*j, (sphereSize+stepY)*i+phaseY-sphereSize/4, (phaseSize+sizeOffset)/2);
            }
            
            if (selector == false) {
                if (j%2 == 0) {
                    phaseY =  ofMap(cos(ofDegToRad(phase)), 1, -1, -offsetY, offsetY);
                    phaseSize = ofMap(sin(ofDegToRad(phase+(180/(i+1))+(360*j/12))), 1,-1, 0, sphereSize, true);
                } else {
                    phaseY =  ofMap(cos(ofDegToRad(phase)), -1, 1, -offsetY, offsetY);
                    phaseSize = ofMap(sin(ofDegToRad(phase+(180/(i+1))-(360*j/8))), -1,1, 0, sphereSize, true);
                }
                
                ofSetColor(shadow);
                ofDrawCircle((sphereSize+stepY)*j+phaseY+sphereSize/4, (sphereSize+stepX)*i, (phaseSize+sizeOffset)/2);
                ofSetColor(green);
                ofDrawCircle((sphereSize+stepX)*j, (sphereSize+stepY)*i+phaseY-sphereSize/4, (phaseSize+sizeOffset)/2);
            }
            
            
        }
    }
    
}


//--------------------------------------------------------------
void sas1Source::sas1(int phase, bool selector) {
    ofColor green = ofColor(0, 166, 151);
    ofColor blue = ofColor(124, 90, 213);
    ofColor orange = ofColor(255, 86, 0);
    
    ofSetColor(green);
    ofDrawRectangle(0,0, fbo->getWidth(), fbo->getHeight());
    
    for(int i = 0; i<44; i++) {
        ofPushMatrix();
        ofTranslate(80,0);
        ofTranslate(i*10+5, fbo->getHeight()/2);
        if (selector == true) {
            ofRotate(counter+(i*5));
        }
        if (selector == false) {
            ofRotate(ofMap(sin(ofDegToRad(counter+(i*5))), 0, 1, 0, 90));
        }
        ofSetLineWidth(4);
        float batonLerp = ofMap(i, 0, 44, 0.0, 1.0);
        ofSetColor(blue.lerp(orange, batonLerp));
        ofDrawLine(0, 60, 0, -60);
        ofDrawCircle(0, -60, 5);
        ofDrawCircle(0, 60, 5);
        ofPopMatrix();
    }
}




//--------------------------------------------------------------
void sas1Source::sas2(int phase, bool selector) {
    ofColor green = ofColor(0, 150, 150);
    ofColor blue = ofColor(120, 220, 200);
    ofColor yellow = ofColor(220, 220, 100);
    
    int maxDistX = fbo->getWidth()/3;
    int maxDistY = fbo->getHeight()/3;
    int shapeDist = maxDistY/8;
    int maxShapes = maxDistY/shapeDist;
    
    ofSetColor(green);
    ofDrawRectangle(0,0, fbo->getWidth(), fbo->getHeight());
    ofTranslate(maxDistX, maxDistY);
    for(int i=0; i<=maxShapes; i++) {
        float colorLerp = ofMap(i, 0, maxShapes, 0.0, 1.0);
        float topVertex;
        float bottomVertex;
        
        if (selector == true) {
            topVertex = ofMap(sin(ofDegToRad(phase*0.8+i*10)), -1, 1, -maxDistY/2, maxDistY/2);
            bottomVertex = ofMap(sin(ofDegToRad(phase*1.4+i*10)), -1, 1, maxDistY/2, -maxDistY/2);
        }
        if (selector == false) {
            topVertex = ofMap(ofSignedNoise(phase*0.008+i*0.08), -1, 1, -maxDistY/2, maxDistY/2);
            bottomVertex = ofMap(ofSignedNoise(phase*0.014+i*0.08), -1, 1, maxDistY/2, -maxDistY/2);
        }
        
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(0, i*shapeDist);
        ofSetColor(blue.lerp(yellow, colorLerp));
        ofNoFill();
        ofSetLineWidth(5);
        ofBeginShape();
        ofVertex(0,0);
        ofVertex(maxDistX/2, topVertex);
        ofVertex(maxDistX, 0);
        ofVertex(maxDistX/2, bottomVertex);
        ofVertex(0, 0);
        ofEndShape();
        ofPopStyle();
        ofPopMatrix();
    }
    
}

//--------------------------------------------------------------
void sas1Source::sas3(int phase, bool selector) {
    ofColor red = ofColor(250,0,100);
    ofColor yellow = ofColor(230,255,200);
    
    ofSetColor(red);
    ofDrawRectangle(0,0, fbo->getWidth(), fbo->getHeight());
    
    
    int gridSize = fbo->getHeight()/9;
    int maxBallSize = 10;
    
    
    ofTranslate(fbo->getWidth()/2, fbo->getHeight()/2);
    for (int i=0; i<16; i++) {
        ofRotate(ofMap(i, 0,16, 0, 360));
        float inOutSine;
        float bigSmallSine;
        ofSetColor(yellow);
        
        
        for(int j=0; j<16; j++) {
            if (selector == true) {
                inOutSine = ofMap(sin(ofDegToRad(counter+j*25)), -1,1, -gridSize*3.5, -gridSize*1.5, true);
                bigSmallSine = ofMap(sin(ofDegToRad(counter*2+j*20+i)), 1,-1, 0, maxBallSize, true);
            }
            
            if (selector == false) {
                inOutSine = ofMap(sin(ofDegToRad(counter+j*66)), -1,1, -gridSize*3.5, -gridSize*1.5, true);
                bigSmallSine = ofMap(sin(ofDegToRad(counter*2+j*50)), 1,-1, 0, maxBallSize, true);
            }
            
            ofDrawCircle(inOutSine, j*4, bigSmallSine);
        }
        
    }
    
}

//--------------------------------------------------------------
void sas1Source::sas4(int phase, bool selector) {
    ofColor red = ofColor(200,20,0);
    ofSetLineWidth(4);
    
    float gridSize = fbo->getWidth()/5;
    float arcDist = gridSize/18;
    
    float rotate;
    
    int upArcBegin = 180-rotate;
    int upArcEnd = 360-rotate;
    int downArcBegin = 0+rotate;
    int downArcEnd = 180+rotate;
    
    // The background rectangles
    ofPushMatrix();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    ofTranslate(fbo->getWidth()/2, fbo->getHeight()/2);
    if (selector == true) {
        ofDrawRectangle(0, 0, gridSize*3, gridSize*3);
        ofSetColor(red);
        ofDrawRectangle(0,0, gridSize*2, gridSize*2);
        ofSetColor(255);
        ofDrawRectangle(0,0, gridSize, gridSize);
    } else {
        ofRotate(phase);
        ofDrawRectangle(0, 0, gridSize*3, gridSize*3);
        ofSetColor(red);
        ofRotate(phase);
        ofDrawRectangle(0, 0, gridSize*2, gridSize*2);
        ofSetColor(255);
        ofRotate(phase);
        ofDrawRectangle(0, 0, gridSize, gridSize);
    }
    
    ofFill();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(gridSize, gridSize);
    int offset = 0;
    
    for(int j=0; j<4; j++) {
        for(int k=0; k<4; k++) {
            
            ofPath path;
            path.setMode(ofPath::POLYLINES);
            path.setCircleResolution(200);
            path.setFilled(false);
            path.setStrokeWidth(4);
            path.setCurveResolution(200);
            
            ofPushMatrix();
            ofTranslate(gridSize*k, gridSize*j);
            if(selector == true) {
                rotate = ofMap(sin(ofDegToRad(phase*2-offset)),-1,1,0,360);
            } else {
                rotate = ofMap(ofSignedNoise(phase*0.02-offset),-1,1,0,360);
            }
            
            for (int i=0; i<4; i++) {
                path.setStrokeColor(255);
                path.newSubPath();
                if (i%2 == 0) {
                    path.arc(0,0, arcDist*i+arcDist, arcDist*i+arcDist, 180-rotate,360-rotate);
                } else {
                    path.arc(0,0, arcDist*i+arcDist, arcDist*i+arcDist, 0+rotate,180+rotate);
                }
                path.draw();
            }
            ofPopMatrix();
            
            offset+=2;
            
        }
    }
    
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(gridSize+gridSize/2, gridSize+gridSize/2);
    offset = 0;
    for(int j=0; j<3; j++) {
        for(int k=0; k<3; k++) {
            
            ofPath path;
            path.setMode(ofPath::POLYLINES);
            path.setCircleResolution(200);
            path.setFilled(false);
            path.setStrokeWidth(4);
            path.setCurveResolution(200);
            
            ofPushMatrix();
            ofTranslate(gridSize*k, gridSize*j);
            if(selector == true) {
                rotate = ofMap(sin(ofDegToRad(phase*2-offset)),-1,1,0,360);
            } else {
                rotate = ofMap(ofSignedNoise(phase*0.02-offset),-1,1,0,360);
            }
            
            
            
            for (int i=0; i<4; i++) {
                path.setStrokeColor(red);
                path.newSubPath();
                if (i%2 == 0) {
                    path.arc(0,0, arcDist*i+arcDist, arcDist*i+arcDist, 180-rotate,360-rotate);
                } else {
                    path.arc(0,0, arcDist*i+arcDist, arcDist*i+arcDist, 0+rotate,180+rotate);
                }
                path.draw();
            }
            
            ofPopMatrix();
            
            offset+=2;
        }
    }
    ofPopMatrix();
    
}



//--------------------------------------------------------------
void sas1Source::sas5(int phase, bool selector) {
    ofColor blue = ofColor(0,168,161);
    ofColor red = ofColor(198,68,126);
    ofNoFill();
    ofSetLineWidth(5);
    int maxDist = 100;
    float centerToMinus = ofMap(sin(ofDegToRad(counter)), -1,1,0, -maxDist);
    float centerToPlus = ofMap(sin(ofDegToRad(counter)), -1,1,0, maxDist);
    
    ofPushMatrix();
    ofTranslate(fbo->getWidth()/2-maxDist, fbo->getHeight()/2);
    ofRotate(45);
    ofSetColor(blue);
    ofBeginShape();
    ofVertex(-maxDist, centerToMinus);
    ofVertex(centerToMinus, centerToMinus);
    ofVertex(centerToMinus, -maxDist);
    ofVertex(centerToPlus, -maxDist);
    ofVertex(centerToPlus, centerToMinus);
    ofVertex(maxDist, centerToMinus);
    ofVertex(maxDist, centerToPlus);
    ofVertex(centerToPlus, centerToPlus);
    ofVertex(centerToPlus, maxDist);
    ofVertex(centerToMinus, maxDist);
    ofVertex(centerToMinus,centerToPlus);
    ofVertex(-maxDist, centerToPlus);
    ofVertex(-maxDist, centerToMinus);
    ofEndShape();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(fbo->getWidth()/2+maxDist, fbo->getHeight()/2);
    ofRotate(45);
    ofSetColor(red);
    ofBeginShape();
    ofVertex(-maxDist, maxDist);
    ofVertex(-maxDist, centerToPlus);
    ofVertex(maxDist, centerToPlus);
    ofVertex(maxDist, maxDist);
    ofVertex(centerToPlus, maxDist);
    ofVertex(centerToPlus, -maxDist);
    ofVertex(maxDist, -maxDist);
    ofVertex(maxDist, centerToMinus);
    ofVertex(-maxDist, centerToMinus);
    ofVertex(-maxDist, -maxDist);
    ofVertex(centerToMinus, -maxDist);
    ofVertex(centerToMinus, maxDist);
    ofVertex(-maxDist, maxDist);
    ofEndShape();
    ofPopMatrix();
    
    ofFill();
    
    
}

