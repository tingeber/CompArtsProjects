#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i < speed1X.size(); i++) {
        
        if (loc1X[i] > ofGetWidth() || loc1X[i] < 0) {
            speed1X[i] = speed1X[i]*-1;
        }
        
        if (loc1Y[i] > ofGetHeight() || loc1Y[i] < 0) {
            speed1Y[i] = speed1Y[i]*-1;
        }
        
        if (loc2X[i] > ofGetWidth() || loc2X[i] < 0) {
            speed2X[i] = speed2X[i]*-1;
        }
        
        if (loc2Y[i] > ofGetHeight() || loc2Y[i] < 0) {
            speed2Y[i] = speed2Y[i]*-1;
        }
        
        
        loc1X[i] = loc1X[i] + speed1X[i];
        loc1Y[i] = loc1Y[i] + speed1Y[i];
        loc2X[i] = loc2X[i] + speed2X[i];
        loc2Y[i] = loc2Y[i] + speed2Y[i];
        
        
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for (int i = 0; i < speed1X.size(); i++) {
        ofSetColor(255, green[i], 0, 100);
        ofDrawTriangle(loc1X[i], loc1Y[i], loc2X[i], loc2Y[i], mouseX, mouseY);
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
    // ofDrawBitmapString(ofToString(button), mouseX, mouseY);
    
    if (button==0) {
        speed1X.push_back(ofRandom(-1,1));
        speed1Y.push_back(ofRandom(-1,1));
        loc1X.push_back(ofRandom(ofGetWidth()));
        loc1Y.push_back(ofRandom(ofGetHeight()));
        
        speed2X.push_back(ofRandom(-1,1));
        speed2Y.push_back(ofRandom(-1,1));
        loc2X.push_back(ofRandom(ofGetWidth()));
        loc2Y.push_back(ofRandom(ofGetHeight()));
        
        green.push_back(ofRandom(0,255));
        
    }
    
    if (button==2 && speed1X.size()>0) {
        speed1X.pop_back();
        speed1Y.pop_back();
        loc1X.pop_back();
        loc1Y.pop_back();
        
        speed2X.pop_back();
        speed2Y.pop_back();
        loc2X.pop_back();
        loc2Y.pop_back();
        
        green.pop_back();
        
    }
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
