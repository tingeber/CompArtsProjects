#include "Incompetence.h"

//--------------------------------------------------------------
void Incompetence::setup(){
    
	// Default name of source
    name = "Incompetence";
    
    // Size of FBO
    allocate(1000, 1000);
    
    // loading fonts for helper text
    font.load("arial", 50, false, false, true);
    
    // populate the three vector arrays (position and height of triangles)
    for (int i = 0; i< maxTriangles; i++) {
        trianglePos1.push_back(ofRandom(0,ofGetHeight()));
        trianglePos2.push_back(ofRandom(0,ofGetHeight()));
        triangleHeight.push_back((trianglePos1[i]+trianglePos2[i])*0.5 + ofRandom(-40,40));
    }
    
    // init settings
    initDraw();
    
    ofBackground(30);
    beatsInMinute = 107; // the BPM that trigger all the animations
    
    // declaring color values in setup so there's a baseline
    rColor = 30;
    gColor = 100;
    bColor = 100;
}

//--------------------------------------------------------------
void Incompetence::setName(string _name){
    name = _name;
}

void Incompetence::setStartPos(int b) {
    b = startPos;
}

//--------------------------------------------------------------
void Incompetence::update(){
    
    runUtilityUpdates();
    
    // slow initial fade-in of border triangles
    if (barCounter > 0 && barCounter < 2) {
        if (growth <= 0.3) {
            growth += 0.005;
        }
    }
    
    // triangles expand to full size
    if (barCounter > 5 && barCounter <10) {
        if (growth <= 3) {
            growth += 0.005;
        }
    }
    
    // triangles start to pulse
    if (barCounter >=10 && barCounter<20) {
        if(barCounter%2==0 && beatCounter == 4 ) {
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
    
    // triangles fade out at end of animation
    if (barCounter >= 20) {
        growth -= 0.005;
    }
}

//--------------------------------------------------------------
void Incompetence::reset(){
    initDraw();
}


//--------------------------------------------------------------
void Incompetence::draw(){
    
    ofPushStyle();
    ofClear(0);
    
    predator(startPos); // the red traveling dots
    trianglePulse(20, 7, 20); // the border pulsating triangles

    ofPopStyle();
    
    // printHelperText(); // prints useful information (frame rate, milis, beats) at mouse position
}

//--------------------------------------------------------------
// UTILITY FUNCTIONS
//--------------------------------------------------------------
void Incompetence::initDraw() {
    // clears all counters, runs at setup and reset
    
    startFrameCounter = ofGetFrameNum();
    startTime = ofGetElapsedTimeMillis();
    barCounter = 0;
    beatCounter = 0;
    halfBeatCounter = 0;
    frameCounter = 0;
    growth = 0;
    noiseValue = ofRandom(0,100);
    ofClear(0);
}

//--------------------------------------------------------------
void Incompetence::runUtilityUpdates() {
    // updates counters
    
    frameCounter = ofGetFrameNum() - startFrameCounter; // our main time keeping variable
    noiseValue += 0.02; // basic noise seed
    
    
   //  let's have 4 repeating beats, and incrementing bars
    if (frameCounter%(3600/beatsInMinute) == 0) {
        if(beatCounter >=1 && beatCounter < 4) {
            beatCounter++;
        } else {
            beatCounter = 1;
        }
        if (beatCounter == 1) {
            barCounter++;
            startFrameCounter = ofGetFrameNum(); //resetting start point at each bar, to sync pulse/sine wave with time
        }
    }
    
    // half-beat measurements
    if (ofGetFrameNum()%(1800/beatsInMinute) == 0) {
        halfBeatCounter++;
    }
}

//--------------------------------------------------------------
void Incompetence::printHelperText() {
    // print helper text at mouse position (frame rate, milis, etc)
    ofPushMatrix();
    ofSetColor(255);
    font.drawString(ofToString(barCounter)+"."+ofToString(beatCounter)+" - "+ofToString(ofGetElapsedTimeMillis()-startTime)+" "+ofToString(ofGetFrameRate()), ofGetMouseX(), ofGetMouseY());
    ofPopMatrix();
}

//--------------------------------------------------------------
// MAIN ANIMATIONS
//--------------------------------------------------------------
void Incompetence::predator(int startPos) {
    // the red traveling dots
    
    ofPushMatrix();
    ofPushStyle();

    float speed = 0.3;
    
    // let's have dots run around the entire screen at the beginning
    float minWidth = 0;
    float maxWidth = fbo->getWidth();
    float minHeight = 0;
    float maxHeight = fbo->getHeight();
    
    // but let's start slowly narrowing down their area as their time comes
    if (barCounter >6) {
        minWidth = ofMap(ofGetElapsedTimeMillis()-startTime, 15000,19000,0,fbo->getWidth()/2, true);
        maxWidth = ofMap(ofGetElapsedTimeMillis()-startTime, 15000,19000,fbo->getWidth(),fbo->getWidth()/2, true);
        minHeight = ofMap(ofGetElapsedTimeMillis()-startTime, 15000,19000,0,fbo->getHeight()/2, true);
        maxHeight = ofMap(ofGetElapsedTimeMillis()-startTime, 15000,19000,fbo->getHeight(),fbo->getHeight()/2, true);
    }
    
    // a nice fluid movement through noise
    float posX = ofMap(ofSignedNoise(noiseValue*speed+startPos),-1, 1, minWidth, maxWidth);
    float posY = ofMap(ofSignedNoise((noiseValue+209+startPos)*speed),-1, 1, minHeight, maxHeight);
    ofTranslate(posX, posY);
    
    ofSetColor(250, 100, 100);
    
    // for a more fluid and unpredictable movement, the dot itself noises around its translate point
    float maxLen = 300;
    
   // and gradually comes to a stop
    if (barCounter >6) {
        maxLen = ofMap(ofGetElapsedTimeMillis()-startTime, 15000,19000,200,0, true);
    }
    
    float seedX = ofMap(ofSignedNoise(noiseValue), -1,1, -maxLen,maxLen);
    float seedY = ofMap(ofSignedNoise(noiseValue+ 20), -1,1, -maxLen,maxLen);
    
    if (barCounter <11) {
        ofDrawCircle(seedX, seedY, 5);
    }
    
    ofPopMatrix();
    ofPopStyle();
}


//--------------------------------------------------------------
void Incompetence::trianglePulse(float heightMultiplier, float numTriangles, float maxOpacity){
    // the pulsating triangles coming from the screen borders

    ofPushMatrix();
    ofPushStyle();
    
    
    // double for loop for multiple stacked triangles
    for(int k = 0; k<numTriangles; k++) {
        for(int i = 0; i<maxTriangles; i++) {
            float noiseSeed = ofMap(ofSignedNoise(noiseValue+i*20+k*5),-1,1,-500,500); // noisified movement of triangles
            float trOp = ofMap(k, 0,3,maxOpacity,maxOpacity*0.2); // each layer is slightly more transparent
            
            float heightX = heightMultiplier*growth*(ofMap(k, 0,numTriangles, 1.0, 15.0));
            float heightY = heightMultiplier*growth*(ofMap(k, 0,numTriangles, 1.0, 15.0));
            
            // color changes slightly when triangles are invisible
            if (growth <= 0.1) {
                rColor = ofRandom(20,50);
                gColor = ofRandom(80,120);
                bColor = ofRandom(80,120);
            }
            ofSetColor(rColor, gColor, bColor, trOp);
            
           // drawing a quarter of all the triangles for each border
            if (i < maxTriangles*0.25) {
                ofDrawTriangle(0, trianglePos1[i], 0, trianglePos2[i], heightX , triangleHeight[i]+noiseSeed);
            }
            if (i >= maxTriangles*0.25 && i < maxTriangles*0.5) {
                ofDrawTriangle(trianglePos1[i], 0, trianglePos2[i], 0, triangleHeight[i]+noiseSeed, heightY);
            }
            if (i >= maxTriangles*0.5 && i < maxTriangles*0.75) {
                ofDrawTriangle(fbo->getWidth(), trianglePos1[i], fbo->getWidth(), trianglePos2[i], fbo->getWidth()-heightX, triangleHeight[i]+noiseSeed);
            }
            if (i >= maxTriangles*0.75 && i < maxTriangles) {
                ofDrawTriangle(trianglePos1[i], fbo->getHeight(), trianglePos2[i], fbo->getHeight(), triangleHeight[i]+noiseSeed, fbo->getHeight()-heightY);
            }
        }
    }
    
    // let's have them change randomly - triggering the change only when they're invisible
    if (growth <= 0.1) {
        trianglePos1.clear();
        trianglePos2.clear();
        triangleHeight.clear();
        for (int i = 0; i< maxTriangles; i++) {
            trianglePos1.push_back(ofRandom(0,fbo->getHeight()));
            trianglePos2.push_back(ofRandom(0,fbo->getHeight()));
            triangleHeight.push_back((trianglePos1[i]+trianglePos2[i])*0.5 + ofRandom(-40,40));
        }
    }
    ofPopStyle();
    ofPopMatrix();
    
}







