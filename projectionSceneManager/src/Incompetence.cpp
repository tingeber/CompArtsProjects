#include "Incompetence.h"

//--------------------------------------------------------------
void Incompetence::setup(){
    
	// Give our source a decent name
    name = "Incompetence";
    
    // Allocate our FBO source, decide how big it should be
    allocate(1000, 1000);
    
    font.load("arial", 50, false, false, true);
    
    for (int i = 0; i< maxTriangles; i++) {
        trianglePos1.push_back(ofRandom(0,ofGetHeight()));
        trianglePos2.push_back(ofRandom(0,ofGetHeight()));
        triangleHeight.push_back((trianglePos1[i]+trianglePos2[i])*0.5 + ofRandom(-40,40));
    }
    
    ofBackground(30);
    startFrameCounter = ofGetFrameNum();
    beatsInMinute = 107;
    beatCounter = 0;
    barCounter = 0;
    halfBeatCounter = 0;
    multiplier = 5;
    
    growth = 0.3;
    
    noiseValue = ofRandom(0,100);
    
    rColor = 30;
    gColor = 100;
    bColor = 100;

    //if you want to draw something inside setup you need to make calls to this->beginFbo() / this->endFbo as below
    this->beginFbo();

    //ofClear(255,0,0);
    this->endFbo();
}

//--------------------------------------------------------------
void Incompetence::setName(string _name){
    
    name = _name;
}

void Incompetence::setStartPos(int b) {
    b = startPos;
}

//--------------------------------------------------------------
void Incompetence::update(){ // Don't do any drawing here
    
    runUtilityUpdates();
    
    if (barCounter > 5 && barCounter <10) {
        if (growth <= 3) {
            growth += 0.005;
        }
    }
    
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
    
    if (barCounter >= 20) {
        growth -= 0.005;
    }
    
    
    
}

//--------------------------------------------------------------
void Incompetence::reset(){
    //initialise frame county at the start of source
    startFrameCounter = ofGetFrameNum();
    beatCounter = 0;
    barCounter = 0;
    halfBeatCounter = 0;
    frameCounter = 0;
    growth = 0.3;
    noiseValue = ofRandom(0,100);
    
    startTime = ofGetElapsedTimeMillis();
    
    ofClear(0); // uncomment if you want canvas to be reset on the buffer when fbo source is called again
}



//--------------------------------------------------------------
void Incompetence::draw(){
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
    
    ofPushStyle();
    ofClear(0); // remove if you never want to update the background
    
    predator(startPos);
    trianglePulse(20, 7, 20);

    ofPopStyle();
    
    ofPushMatrix();
    ofSetColor(255);
    font.drawString(ofToString(barCounter)+"."+ofToString(beatCounter)+" - "+ofToString(ofGetElapsedTimeMillis()-startTime)+" "+ofToString(ofGetFrameRate()), ofGetMouseX(), ofGetMouseY());
    ofPopMatrix();
}



//--------------------------------------------------------------
void Incompetence::runUtilityUpdates() {
    
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
void Incompetence::predator(int startPos) {
    
    ofPushMatrix();
    ofPushStyle();
    float speed = 0.3;
    float minWidth = 0;
    float maxWidth = fbo->getWidth();
    float minHeight = 0;
    float maxHeight = fbo->getHeight();
    
    if (barCounter >6 && barCounter <9) {
        minWidth = ofMap(halfBeatCounter, 50,80,0,fbo->getWidth()/2, true);
        maxWidth = ofMap(halfBeatCounter, 50,80,fbo->getWidth(),fbo->getWidth()/2, true);
        minHeight = ofMap(halfBeatCounter, 50,80,0,fbo->getHeight()/2, true);
        maxHeight = ofMap(halfBeatCounter, 50,80,fbo->getHeight(),fbo->getHeight()/2, true);
    }
    
    if (barCounter >=9) {
        minWidth = fbo->getWidth()/2;
        minHeight = fbo->getHeight()/2;
        maxWidth = fbo->getWidth()/2;
        maxHeight = fbo->getHeight()/2;
    }
    
    float posX = ofMap(ofSignedNoise(noiseValue*speed+startPos),-1, 1, minWidth, maxWidth);
    float posY = ofMap(ofSignedNoise((noiseValue+209+startPos)*speed),-1, 1, minHeight, maxHeight);
    ofTranslate(posX, posY);
    
    ofSetColor(250, 100, 100);
    
//    for (int i = 0; i<3; i++) {
    
        float maxLen = 300;
        
        if (barCounter >6) {
            maxLen = ofMap(halfBeatCounter, 50,80,200,0, true);
            ofSetColor(250,100,100,ofMap(pulse,-1,1,30,255));
        }
        
        float seedX = ofMap(ofSignedNoise(noiseValue), -1,1, -maxLen,maxLen);
        float seedY = ofMap(ofSignedNoise(noiseValue+ 20), -1,1, -maxLen,maxLen);
        
        if (barCounter <11) {
            ofDrawCircle(seedX, seedY, 5);
        }
        
//    }
    
    ofPopMatrix();
    ofPopStyle();
    
}


//--------------------------------------------------------------
void Incompetence::trianglePulse(float heightMultiplier, float numTriangles, float maxOpacity){
    
    
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
                ofDrawTriangle(fbo->getWidth(), trianglePos1[i], fbo->getWidth(), trianglePos2[i], fbo->getWidth()-heightX, triangleHeight[i]+noiseSeed);
            }
            if (i >= maxTriangles*0.75 && i < maxTriangles) {
                ofDrawTriangle(trianglePos1[i], fbo->getHeight(), trianglePos2[i], fbo->getHeight(), triangleHeight[i]+noiseSeed, fbo->getHeight()-heightY);
            }
        }
    }
    
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







