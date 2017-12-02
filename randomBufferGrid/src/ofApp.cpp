#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(320,240);
    numOfTiles = 10;
    maxBufferSize = numOfTiles * numOfTiles;
    
    for (int i=0; i<maxBufferSize-1;i++) {
        table.push_back(ofRandom(0, maxBufferSize));
    }
    
    
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
    
    int imgWidth = ofGetWidth()/numOfTiles;
    int imgHeight = ofGetHeight()/numOfTiles;
    int imgindex = 0;
    
    for (int x=0; x<numOfTiles; x++) {
        for(int y=0; y<numOfTiles; y++) {
            if (imgBuffer.size()==maxBufferSize)
            {
                imgBuffer[table[imgindex]].draw(x*imgWidth,y*imgHeight, imgWidth, imgHeight);
                imgindex++;
            }
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

