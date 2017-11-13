#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetBackgroundAuto(false);
    spacingX = ofGetWidth()/numX;
    spacingY = ofGetHeight()/numY;
    stepSize = 20;
    startingX = spacingX/2;
    startingY = spacingY/2;
    
    for (int i = 0; i<numX; i++) {
        for (int z = 0; z<numY; z++) {
            noiseSeeds[i][z] = ofRandom(1000);
        }
    }
    
    goCrazy = false;
    noiseAmount = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    // let's constantly change the noise values
    for (int i = 0; i<numX; i++) {
        for (int z = 0; z<numY; z++) {
            noiseSeeds[i][z] += 0.02;
        }
    }
 
    // let's have a gradual change into the shake
    if (goCrazy==true) {
        if (noiseAmount < 20) {
            noiseAmount +=1;
        }
    }
    
   // let's also have a gradual calming down
    if (goCrazy == false) {
        if (noiseAmount > 0) {
            noiseAmount -=1;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, 20);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    ofSetColor(255, 255);
    
    for (int i = 0; i<numX; i++) {
        for (int z = 0; z<numY; z++) {
            
            int locX = i*spacingX+stepSize;
            int locY = z*spacingY+stepSize;
            
            // make the color of the balls change based on distance from mouse
            ofColor harlemColor (ofMap(ofDist(locX,locY,mouseX,mouseY),0,400,200,0,true),40,ofMap(ofDist(locX,locY,mouseX,mouseY),0,400,0,200,true));
            
            ofColor whiteHarlem (255,255);
            
            // make the overall color change gradually from white to harlemColor,
            // by lerping it with white based on the noiseAmount value
            float harlemLerp = ofMap(noiseAmount, 0,20,1.0,0.0);
            
            if (i==20 && z==20) {
                locX = locX + ofSignedNoise(noiseSeeds[i][z])*stepSize;
                locY = locY + ofSignedNoise(noiseSeeds[i][z]+500)*stepSize;
                // our first harlem shaker is always colorful
                ofSetColor(harlemColor);
            }
            
            else {
                locX = locX + ofSignedNoise(noiseSeeds[i][z])*noiseAmount;
                locY = locY + ofSignedNoise(noiseSeeds[i][z]+500)*noiseAmount;
                // the other shakers only change color when they start to shake
                ofSetColor(harlemColor.lerp(whiteHarlem,harlemLerp));
            }
            
            
            // let's draw our shakers!
            ofDrawEllipse(locX, locY, 5,5);
        }
    }
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // click the mouse, start/stop the shake
    goCrazy = !goCrazy;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
