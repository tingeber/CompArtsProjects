#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(640, 480);
    slitHeight = 16;
    maxBufferSize = ofGetHeight()/slitHeight;
}


//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    
    if (vidGrabber.isFrameNew())
    {
        //add to buffer
        ofImage img;
        img.setFromPixels(vidGrabber.getPixels());
        img.mirror(false, true); // if you want to mirror input
        imgBuffer.push_front(img);
    }
    
    //remove from back if buffer has reached maximum size
    if (imgBuffer.size()>maxBufferSize) imgBuffer.pop_back();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    if (imgBuffer.size() > 0)
    {
        imgBuffer[0].draw(0,0);
    }
    
    for (int i = 0; i<imgBuffer.size(); i++) {
        imgBuffer[i].drawSubsection(0, i*slitHeight, ofGetWidth(), slitHeight, 0, i*slitHeight);
    }
    
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
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

