#include "UnconsciousCompetence.h"

//--------------------------------------------------------------
void UnconsciousCompetence::setup(){
    
	// Give our source a decent name
    name = "UnconsciousCompetence";
    
    // Allocate our FBO source, decide how big it should be
    allocate(1000, 1000);
    
    font.load("arial", 100, false, false, true);
    
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
void UnconsciousCompetence::setName(string _name){
    
    name = _name;
}

void UnconsciousCompetence::setStartPos(int b) {
    b = startPos;
}

//--------------------------------------------------------------
void UnconsciousCompetence::update(){ // Don't do any drawing here
    
    runUtilityUpdates();
    
    for(int i = 0; i<transparency.size(); i++) {
        if (barCounter<25) {
            transparency[i] = ofMap(i, 0, transparency.size(), 0, 50);
        } else {
            transparency[i] -= 0.05;
        }
    }
    
}

//--------------------------------------------------------------
void UnconsciousCompetence::reset(){
    //initialise frame county at the start of source
    startFrameCounter = ofGetFrameNum();
    beatCounter = 0;
    barCounter = 0;
    halfBeatCounter = 0;
    frameCounter = 0;
    noiseValue = ofRandom(0,100);
    
    triangle1.clear();
    triangle2.clear();
    triangle3.clear();
    
    ofClear(0); // uncomment if you want canvas to be reset on the buffer when fbo source is called again
}



//--------------------------------------------------------------
void UnconsciousCompetence::draw(){
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
    
    ofPushStyle();
    ofClear(0); // remove if you never want to update the background
    
    predatorTriangles(startPos);

    ofPopStyle();
    
    helperText();
}



//--------------------------------------------------------------
void UnconsciousCompetence::runUtilityUpdates() {
    
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
void UnconsciousCompetence::predatorTriangles(int startPos) {
    
    
    for(int i = 0; i<triangle1.size(); i++) {
        float randomAdd;
        if (barCounter > 15) {
            float randomSeed = ofMap(halfBeatCounter, 160,220, 0,100, true);
            randomAdd = ofRandom(-randomSeed, randomSeed);
        }
        
        ofSetColor(30, 100, 100, transparency[i]);
        ofDrawTriangle(triangle1[i].x+randomAdd, triangle1[i].y, triangle2[i].x, triangle2[i].y, triangle3[i].x, triangle3[i].y);
    }
    
    ofPushMatrix();
    ofPushStyle();
    float speed = 0.3;
    float minWidth = 0;
    float maxWidth = fbo->getWidth();
    float minHeight = 0;
    float maxHeight = fbo->getHeight();
    
    if (barCounter >20 && barCounter <30) {
        minWidth = ofMap(halfBeatCounter, 160,230,0,fbo->getWidth()/2, true);
        maxWidth = ofMap(halfBeatCounter, 160,230,fbo->getWidth(),fbo->getWidth()/2, true);
        minHeight = ofMap(halfBeatCounter, 160,230,0,fbo->getHeight()/2, true);
        maxHeight = ofMap(halfBeatCounter, 160,230,fbo->getHeight(),fbo->getHeight()/2, true);
    }
    
    if (barCounter >=30) {
        minWidth = fbo->getWidth()/2;
        minHeight = fbo->getHeight()/2;
        maxWidth = fbo->getWidth()/2;
        maxHeight = fbo->getHeight()/2;
    }
    
    float posX = ofMap(ofSignedNoise(noiseValue*speed),-1, 1, minWidth, maxWidth);
    float posY = ofMap(ofSignedNoise((noiseValue+209)*speed),-1, 1, minHeight, maxHeight);
    ofTranslate(posX, posY);
    
    ofSetColor(250, 100, 100);
    
    for (int i = 0; i<3; i++) {
        
        float maxLen = 300;
        
        if (barCounter >20) {
            maxLen = ofMap(halfBeatCounter, 200,230,200,0, true);
            ofSetColor(250,100,100,ofMap(pulse,-1,1,30,255));
        }
        
        float seedX = ofMap(ofSignedNoise(noiseValue + i*20), -1,1, -maxLen,maxLen);
        float seedY = ofMap(ofSignedNoise(noiseValue + i*20 + 20), -1,1, -maxLen,maxLen);
        
        if (barCounter < 30) {
            ofDrawCircle(seedX, seedY, 5);
        }
        
        if ((beatCounter == 2 || beatCounter == 3) && barCounter <= 23) {
            transparency.push_back(30); // feeding transparency to triangle so we can reduce it in update
            if (i == 0) {
                triangle1.push_back(ofVec2f(seedX+posX, seedY+posY));
            }
            if (i == 1) {
                triangle2.push_back(ofVec2f(seedX+posX, seedY+posY));
            }
            if (i == 2) {
                triangle3.push_back(ofVec2f(seedX+posX, seedY+posY));
            }
            
        }
    }
    
    ofPopMatrix();
    ofPopStyle();
    
}

//--------------------------------------------------------------
void UnconsciousCompetence::helperText() {

    ofPushMatrix();
    ofSetColor(255);
    font.drawString(ofToString(barCounter)+"."+ofToString(beatCounter)+" - "+ofToString(halfBeatCounter)+" "+ofToString(ofGetFrameRate()), ofGetMouseX(), ofGetMouseY());
    ofPopMatrix();

}


