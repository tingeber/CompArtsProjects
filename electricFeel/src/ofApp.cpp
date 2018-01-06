#include "ofApp.h"


//--------------------------------------------------------------
//
//  Electric Feel (Justice cover) beat count
//  1-10: pre-intro
//  10-18: intro 1
//  18-26: intro 2
//  26-34: verse 1
//  34-42: verse 2
//  42-58: chorus
//  58-66: verse 1
//  66-74: verse 2
//  FIN (2min40sec approx)
//--------------------------------------------------------------


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(30);
    font.load("arial", 12, false, false, true);
    beatsInMinute = 107;
    beatCounter = 0;
    barCounter = 0;
    halfBeatCounter = 0;
    multiplier = 5;
    startFrameCounter = ofGetFrameNum();
    
    for (int i = 0; i< maxTriangles; i++) {
        trianglePos1.push_back(ofRandom(0,ofGetHeight()));
        trianglePos2.push_back(ofRandom(0,ofGetHeight()));
        triangleHeight.push_back((trianglePos1[i]+trianglePos2[i])*0.5 + ofRandom(-40,40));
    }
    
    for (int i = 0; i< maxStars; i++) {
        starPos1.push_back(ofRandom(100,ofGetWidth()-100));
        starPos2.push_back(ofRandom(100,ofGetHeight()-100));
        scaleTriangle.push_back(ofRandom(0.1,1.0));
    }
    
    growth = 0.3;
    
    noiseValue = ofRandom(0,100);
    
    rColor = 30;
    gColor = 100;
    bColor = 100;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    frameCounter = ofGetFrameNum() - startFrameCounter;
    pulse = sin(ofDegToRad(frameCounter*multiplier*0.5));
    noiseValue += 0.02;
    
    if (frameCounter%(3600/beatsInMinute) == 0) {
        if(beatCounter >=1 && beatCounter < 4) {
            beatCounter++;
        } else {
            beatCounter = 1;
        }
        if (beatCounter == 1) {
            barCounter++;
            startFrameCounter = ofGetFrameNum();
        }
    }
    
    
    
    if (ofGetFrameNum()%(1800/beatsInMinute) == 0) {
        halfBeatCounter++;
    }
    
    for(int i = 0; i<transparency.size(); i++) {
        if (barCounter<20) {
            transparency[i] = ofMap(i, 0, transparency.size(), 0, 50);
        } else {
            transparency[i] -= 0.05;
        }
    }
    
    
    if (barCounter > 20 && barCounter <30) {
        if (growth <= 3) {
            growth += 0.005;
        }
    }
    
    if (barCounter >=30) {
        if(beatCounter == 4 ) {
            if (growth > 0) {
                growth -= 0.1;
            }
        }
        else {
            if (growth <= 3) {
                growth += 0.3;
            }
        }
    }
    
//    if (barCounter >=40) {
        if (round(currentMaxStars) < maxStars) {
            if(beatCounter == 1 || beatCounter == 3) {
                currentMaxStars+=0.05;
            }
            if(beatCounter == 4) {
                currentMaxStars+=0.1;
            }
        }
//    }
    
    if (barCounter >21 && currentMaxStars >0) {
        currentMaxStars--;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//
   predatorTriangles();
//
//    trianglePulse(20, 7, 20, growth);
    
    
//    starTriangles();
    

    
    
 
    
    ofPushMatrix();
    ofSetColor(255);
    font.drawString(ofToString(barCounter)+"."+ofToString(beatCounter)+" - x"+ofToString(halfBeatCounter)+" "+ofToString(ofGetFrameRate()), ofGetMouseX(), ofGetMouseY());
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::predatorTriangles() {
    
    
    if(barCounter <=25) {
    for(int i = 0; i<triangle1x.size(); i++) {
        float randomAdd;
        if (barCounter > 9) {
            float randomSeed = ofMap(halfBeatCounter, 100,200, 0,100, true);
            randomAdd = ofRandom(-randomSeed, randomSeed);
        }
        
        ofSetColor(30, 100, 100, transparency[i]);
        ofDrawTriangle(triangle1x[i]+randomAdd, triangle1y[i], triangle2x[i], triangle2y[i], triangle3x[i], triangle3y[i]);
    }
    
}
    
    ofPushMatrix();
    ofPushStyle();
    float speed = 0.3;
    float minWidth = 0;
    float maxWidth = ofGetWidth();
    float minHeight = 0;
    float maxHeight = ofGetHeight();
    
    if (barCounter >20) {
        minWidth = ofMap(halfBeatCounter, 160,230,0,ofGetWidth()/2);
        maxWidth = ofMap(halfBeatCounter, 160,230,ofGetWidth(),ofGetWidth()/2);
        minHeight = ofMap(halfBeatCounter, 160,230,0,ofGetHeight()/2);
        maxHeight = ofMap(halfBeatCounter, 160,230,ofGetHeight(),ofGetHeight()/2);
    }
    
    float posX = ofMap(ofSignedNoise(noiseValue*speed),-1, 1, minWidth, maxWidth);
    float posY = ofMap(ofSignedNoise((noiseValue+209)*speed),-1, 1, minHeight, maxHeight);
    ofTranslate(posX, posY);
    
    ofSetColor(250, 100, 100);
    
    for (int i = 0; i<3; i++) {
        
        float maxLen = 300;
        
        if (barCounter >20) {
            maxLen = ofMap(halfBeatCounter, 200,230,200,0);
            ofSetColor(250,100,100,ofMap(pulse,-1,1,30,255));
        }
        
        float seedX = ofMap(ofSignedNoise(noiseValue + i*20), -1,1, -maxLen,maxLen);
        float seedY = ofMap(ofSignedNoise(noiseValue + i*20 + 20), -1,1, -maxLen,maxLen);
        ofDrawCircle(seedX, seedY, 5);
        
       // if (barCounter%2 == 0 && barCounter <= 25) {
        if ((beatCounter == 2 || beatCounter == 3) && barCounter <= 23) {
            transparency.push_back(30); // feeding transparency to triangle so we can reduce it in update
            if (i == 0) {
                triangle1x.push_back(seedX+posX);
                triangle1y.push_back(seedY+posY);
            }
            if (i == 1) {
                triangle2x.push_back(seedX+posX);
                triangle2y.push_back(seedY+posY);
            }
            if (i == 2) {
                triangle3x.push_back(seedX+posX);
                triangle3y.push_back(seedY+posY);
            }
            
        }
    }
    
    ofPopMatrix();
    ofPopStyle();
    
}


//--------------------------------------------------------------
void ofApp::trianglePulse(float heightMultiplier, float numTriangles, float maxOpacity, float growth){
    
    
    ofPushMatrix();
    ofPushStyle();
    
    
    for(int k = 0; k<numTriangles; k++) {
        for(int i = 0; i<maxTriangles; i++) {
            float noiseSeed = ofMap(ofSignedNoise(noiseValue+i*20+k*5),-1,1,-500,500);
            float heightSeed = ofMap(noiseSeed, -500,500, 0.0, 1.0);
            float trOp = ofMap(k, 0,3,maxOpacity,maxOpacity*0.2);
            
            float heightX = heightMultiplier*growth*(ofMap(k, 0,numTriangles, 1.0, 15.0));
            float heightY = heightMultiplier*growth*(ofMap(k, 0,numTriangles, 1.0, 15.0));
            
            if (growth <= 0.1) {
                rColor = ofRandom(20,50);
                gColor = ofRandom(80,120);
                bColor = ofRandom(80,120);
            }

            
            ofSetColor(rColor, gColor, bColor, trOp);
            
            if (i < maxTriangles*0.25) {
                ofDrawTriangle(0, trianglePos1[i], 0, trianglePos2[i], heightX , triangleHeight[i]+noiseSeed);
            }
            if (i >= maxTriangles*0.25 && i < maxTriangles*0.5) {
                ofDrawTriangle(trianglePos1[i], 0, trianglePos2[i], 0, triangleHeight[i]+noiseSeed, heightY);
            }
            if (i >= maxTriangles*0.5 && i < maxTriangles*0.75) {
                ofDrawTriangle(ofGetWidth(), trianglePos1[i], ofGetWidth(), trianglePos2[i], ofGetWidth()-heightX, triangleHeight[i]+noiseSeed);
            }
            if (i >= maxTriangles*0.75 && i < maxTriangles) {
                ofDrawTriangle(trianglePos1[i], ofGetHeight(), trianglePos2[i], ofGetHeight(), triangleHeight[i]+noiseSeed, ofGetHeight()-heightY);
            }
        }
    }
    
    if (growth <= 0.1) {
        
        
        trianglePos1.clear();
        trianglePos2.clear();
        triangleHeight.clear();
        for (int i = 0; i< maxTriangles; i++) {
            trianglePos1.push_back(ofRandom(0,ofGetHeight()));
            trianglePos2.push_back(ofRandom(0,ofGetHeight()));
            triangleHeight.push_back((trianglePos1[i]+trianglePos2[i])*0.5 + ofRandom(-40,40));
        }
    }
    
    
    ofPopStyle();
    ofPopMatrix();
    
}


//--------------------------------------------------------------
void ofApp::starTriangles() {
    ofPushMatrix();
    ofPushStyle();
    
    
    for (int k=0; k<currentMaxStars; k++) {
        ofPushMatrix();
        float shiftX = ofMap(ofSignedNoise(noiseValue+starPos2[k]),-1,1,-5,5);
        float shiftY = ofMap(ofSignedNoise(noiseValue+starPos1[k]),-1,1,-5,5);
        ofTranslate(starPos1[k]+shiftX, starPos2[k]+shiftY);
        ofScale(scaleTriangle[k], scaleTriangle[k]);
        
        for (int i=0; i<30; i++) {
            float delay = ofMap(i, 0, 30, 0.1, 0.3);
            float noiseSeed = ofMap(ofSignedNoise(noiseValue*starSpeed+delay+starPos1[k]),-1,1,0,1440);
            float opacityNoise = ofMap(ofSignedNoise(noiseValue*0.2+delay+i*20+k*5),-1,1,0,20);
            float scaleSingle = ofMap(sin(ofDegToRad(ofGetFrameNum()+k)),0.8,0.9, 0.5,1.0, true );
            
            ofSetColor(30+ofMap(i, 0,8, -50,50), 100, 100+ofMap(i, 0,8, -50,50), opacityNoise);
            ofPushMatrix();
            ofScale(scaleSingle,scaleSingle);
            ofRotate(noiseSeed);
            ofDrawTriangle(0, -100, 100, 50, -100, 50);
            ofSetColor(200, 100, 0);
            ofDrawCircle(0, 0, 5);
            ofPopMatrix();
        }
        ofPopMatrix();
    }
    
    ofPopMatrix();
    ofPopStyle();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'x') {
        multiplier -= 0.01;
    }
    if (key == 'c') {
        multiplier += 0.01;
    }
    
    if (key == 'r') {
        barCounter = 0;
    }
    
    if (key == 'b') {
        barCounter ++;
    }
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
