//--------------------------------------------------------------
// This program creates mandalas of various sizes
// at the click of the mouse, under the cursor.
// click away for the win.
//--------------------------------------------------------------



#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(255);
}

//--------------------------------------------------------------
void ofApp::update(){
    // our rotation angle updates in real time
    rotAngle = angleStep+rotAngle;
}

//--------------------------------------------------------------
void ofApp::draw(){
    //drawing our mandalas
    for (int i = 0; i<posX.size(); i++) {
        mandala(i);
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
    
    //each left mouse click stores a bunch of vector values
    // to create a randomly generated mandala on the cursor position
    if(button==0) {
        resolution.push_back(ofRandom(3,20));
        radius1.push_back(ofRandom(100,200));
        radius2.push_back(ofRandom(50,300));
        noOfStars.push_back(ofRandom(10,20));
        posX.push_back(mouseX);
        posY.push_back(mouseY);
        mandalaColor.push_back(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));
        
    }
    
    // each right mouse click removes the last added mandala
    if(button==2) {
        resolution.pop_back();
        radius1.pop_back();
        radius2.pop_back();
        noOfStars.pop_back();
        posX.pop_back();
        posY.pop_back();
        mandalaColor.pop_back();
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

void ofApp::star(float x, float y, float radius1, float radius2, int npoints) {
    float angle = 360.0 / npoints;
    float halfAngle = angle/2.0;
    
    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    ofBeginShape();
    for (float a = 0; a < 360.0; a += angle)
    {
        float sx = x + cos(ofDegToRad(a)) * radius2;
        float sy = y + sin(ofDegToRad(a)) * radius2;
        ofVertex(sx, sy);
        sx = x + cos(ofDegToRad(a+halfAngle)) * radius1;
        sy = y + sin(ofDegToRad(a+halfAngle)) * radius1;
        ofVertex(sx, sy);
    }
    ofEndShape();
}


void ofApp::mandala(int index) {
    
    for (float i = 0; i < noOfStars[index]; i++) {
        ofPushMatrix();
        ofColor white(255,255,255);
        // color interpolates between white and a random color, slight opacity
        ofSetColor(white.lerp(mandalaColor[index], ofMap(i, 0, noOfStars[index], 1.0,0.0, true)),200);
        ofTranslate(posX[index], posY[index]);
        ofRotate(i*rotAngle+rotAngle);
        ofScale(1-i/noOfStars[index], 1-i/noOfStars[index]);
        star(0, 0, radius1[index], radius2[index], resolution[index]);
        ofPopMatrix();
    }
}
