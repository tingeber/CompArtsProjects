#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // For this project I preferred to start from scratch, and chose a couple of Saskia's
    // projects to play with. this was FUN.
    // the originals are linked below, next to their draw functions.
    // cycle through visualisations with left and right arrows;
    // each project has two variations - switch between them by pressing up or down
    // pressing "q" prints the value helper
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    counter++;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (valueHelperBool == true) {
        valueHelper();
    }
    
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
    
    
}
    

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_UP) {
        selector = !selector;
    }
    
    else if (key == OF_KEY_DOWN) {
        selector = !selector;
    }
    
    else if (key == OF_KEY_LEFT) {
        if(showDraw==0) {
         showDraw = totSaskias;
        }
        else {
            showDraw--;
        }
        selector = true;
    }
    
    else if (key == OF_KEY_RIGHT) {
        if(showDraw==totSaskias) {
            showDraw = 0;
        }
        else {
            showDraw++;
        }
        selector = true;
    }
    else if (key == 'q') {
            valueHelperBool = !valueHelperBool;
        }
}
    

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}


//--------------------------------------------------------------
void ofApp::valueHelper() {
    rangeTestX = ofMap(mouseX,0,ofGetWidth(),0,100);
    rangeTestY = ofMap(mouseY, 0, ofGetHeight(),0,100);
    ofDrawBitmapString(ofToString(rangeTestX) + " " + ofToString(rangeTestY), mouseX,mouseY);
}
    
    

//--------------------------------------------------------------
void ofApp::sas0 (int phase, bool selector) {
    ofColor green = ofColor(131, 181, 145);
    ofColor pink = ofColor(188, 60, 114);
    ofColor shadow = ofColor(42, 26, 64);

    int sphereSize = 15;
    
    int offsetX = sphereSize*2;
    int offsetY = sphereSize*2;
    int stepX = 20;
    int stepY = 20;
    
    int maxRows = (ofGetHeight()/2/(sphereSize+stepY));
    int maxColumns = (ofGetWidth()-offsetX*2)/(sphereSize+stepX);
    
    ofSetBackgroundColor(pink);
    
    ofTranslate(offsetX+stepX, ofGetHeight()/2-(maxRows*(sphereSize+stepY)/2-offsetY));
    
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
void ofApp::sas1(int phase, bool selector) {
    ofColor green = ofColor(0, 166, 151);
    ofColor blue = ofColor(124, 90, 213);
    ofColor orange = ofColor(255, 86, 0);
    
    ofSetBackgroundColor(green);
    for(int i = 0; i<44; i++) {
        ofPushMatrix();
        ofTranslate(80,0);
        ofTranslate(i*10+5, ofGetHeight()/2);
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
void ofApp::sas2(int phase, bool selector) {
    ofColor green = ofColor(0, 150, 150);
    ofColor blue = ofColor(120, 220, 200);
    ofColor yellow = ofColor(220, 220, 100);
    
    int maxDistX = ofGetWidth()/3;
    int maxDistY = ofGetHeight()/3;
    int shapeDist = maxDistY/8;
    int maxShapes = maxDistY/shapeDist;
    
    ofSetBackgroundColor(green);
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
void ofApp::sas3(int phase, bool selector) {
    ofColor red = ofColor(250,0,100);
    ofColor yellow = ofColor(230,255,200);
    
    ofSetBackgroundColor(red);
    
    
    int gridSize = ofGetHeight()/9;
    int maxBallSize = 10;
    
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
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
void ofApp::sas4(int phase, bool selector) {
    ofColor red = ofColor(200,20,0);
    ofSetBackgroundColor(0);
    ofSetLineWidth(4);
    
    ofPath path;
    path.setMode(ofPath::POLYLINES);
    path.setCircleResolution(200);
    path.setFilled(false);
    path.setStrokeWidth(4);
    path.setCurveResolution(200);
    
    float gridSize = ofGetWidth()/5;
    float arcDist = gridSize/18;

    float rotate = ofMap(sin(ofDegToRad(phase*2)),-1,1,0,360);
    
    int upArcBegin = 180-rotate;
    int upArcEnd = 360-rotate;
    int downArcBegin = 0+rotate;
    int downArcEnd = 180+rotate;
    
    // The background rectangles
    ofPushMatrix();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    ofDrawRectangle(ofGetWidth()/2, ofGetHeight()/2, gridSize*3, gridSize*3);
    ofSetColor(red);
    ofDrawRectangle(ofGetWidth()/2, ofGetHeight()/2, gridSize*2, gridSize*2);
    ofSetColor(255);
    ofDrawRectangle(ofGetWidth()/2, ofGetHeight()/2, gridSize, gridSize);
    ofFill();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(gridSize, gridSize);
    
    for(int j=0; j<4; j++) {
        for(int k=0; k<4; k++) {
            
            ofPushMatrix();
            ofTranslate(gridSize*k, gridSize*j);
            //int offset = ofMap(j*k, 0,16, 0, 90); // WHY OH WHY DOES IT NOT WORK HERE
            
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
            
        }
    }
    
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(gridSize+gridSize/2, gridSize+gridSize/2);
    
    for(int j=0; j<3; j++) {
        for(int k=0; k<3; k++) {
            ofPushMatrix();
            ofTranslate(gridSize*k, gridSize*j);
            //int offset = ofMap(j*k, 0,16, 0, 90); // WHY OH WHY DOES IT NOT WORK HERE
            
//            for (int i=0; i<4; i++) {
//                path.setStrokeColor(red);
//                path.newSubPath();
//                if (i%2 == 0) {
//                    path.arc(0,0, arcDist*i+arcDist, arcDist*i+arcDist, 0+rotate,180+rotate);
//                } else {
//                    path.arc(0,0, arcDist*i+arcDist, arcDist*i+arcDist, 180-rotate, 360-rotate);
//                }
//                path.draw();
//            }

            for (int i=0; i<4; i++) {
                path.setStrokeColor(red);
                path.newSubPath();
                if (i%1 == 0) {
                    path.arc(0,0, arcDist*i+arcDist, arcDist*i+arcDist, 180-rotate,360-rotate);
                } else {
                    path.arc(0,0, arcDist*i+arcDist, arcDist*i+arcDist, 0+rotate,180+rotate);
                }
                path.draw();
            }
            
            ofPopMatrix();
    
        }
    }
    ofPopMatrix();

    
    
}


















