#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(255);
    ofSetColor(80,0,130,100);
    ofNoFill();
    ofSetLineWidth(lineThickness);
    

}

//--------------------------------------------------------------
void ofApp::update(){
    angle = angle+angleSpeed;
    ofSetLineWidth(lineThickness);

    // The two variable changes below are if we want
    // the mouse position to regulate size and speed:
    //    shapeLength = ofMap(mouseY, 400, 0, 50, 200);
    //    angleSpeed = ofMap(mouseX, 0, 600, 0.0, 10);


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // on-screen key definitions - comment this out when creating snapshottable art
    ofDrawBitmapString(" 1-4: predefined colors \n A: random color \n UP/DOWN: radius \n LEFT/RIGHT: speed \n Z: random radius \n l: line thickness toggle \n 0: radius to zero \n R: reset canvas \n S: take snapshot", 10, 10 );
    
    if (drawIsOn == true) {
        ofTranslate(mouseX, mouseY);
        // the ofTranslate below works when we use mousex and mousey as regulators
        // of shape sizes and speeds - comment out the above, and comment in the below
        // ofTranslate (ofGetWindowWidth()/2, ofGetWindowHeight()/2);
        ofRotate(angle);
        ofDrawLine(0, 0, shapeLength, shapeLength);

        // The part below is a segmented line being drawn, to comment in instead of the line above
//        ofDrawLine(0,0,shapeLength/2,shapeLength/2);
//        ofDrawLine(shapeLength/2,shapeLength/2, shapeLength, (shapeLength/2)*-1);
//        ofDrawLine(shapeLength, (shapeLength/2)*-1, shapeLength+(shapeLength/2), shapeLength/2);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'r') {
        ofSetBackgroundAuto(true);
    }
    if (key == 'a') {
        ofSetColor(ofRandom(20,200), ofRandom(20,200), ofRandom(20,200), 150);
    }
    if (key == 'z') {
        shapeLength = ofRandom(50, 250);
    }
    if (key == '1') { //blue
        ofSetColor(80,130,160, 100);
    }
    if (key == '2') { // green
        ofSetColor(0,180,0, 100);
    }
    if (key == '3') { // purple
        ofSetColor(80,0,130,100);
    }
    if (key == '4') { //yellow
        ofSetColor(200,200,0, 100);
    }
    
    if (key == '0') {
        shapeLength = 0;
    }
    
    if (key == OF_KEY_UP) {
        if (shapeLength >= 0) {
                shapeLength += 5;
        }
        else {
            shapeLength = 5;
        }
    }
    if (key == OF_KEY_DOWN) {
        if (shapeLength > 0) {
            shapeLength -= 5;
        }
        else {
            shapeLength = 5;
        }
    }
    if (key == OF_KEY_LEFT) {
        angleSpeed -= 0.1;
    }
    if (key == OF_KEY_RIGHT) {
        angleSpeed += 0.1;
    }
    
    if (key == 's') {
        ofSaveScreen(ofToString(ofGetFrameNum())+".png");
    }
    
    if (key == 'l') {
        if (lineThickness == 2) {
            lineThickness = 1;
        }
        else {
            lineThickness = 2;
        }
        
    }

}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 'r') {
        ofSetBackgroundAuto(false);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    drawIsOn = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    drawIsOn = false;

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
