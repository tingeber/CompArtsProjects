#include "ConsciousCompetence.h"

//--------------------------------------------------------------
void ConsciousCompetence::setup(){
    
	// Give our source a decent name
    name = "Conscious Competence";
    
    // Allocate our FBO source, decide how big it should be
    allocate(1000, 1000);
    
    font.load("arial", 100, false, false, true);
    
    for (int i = 0; i< maxStars; i++) {
        starPos1.push_back(ofRandom(100,fbo->getWidth()-100));
        starPos2.push_back(ofRandom(100,fbo->getHeight()-100));
        scaleTriangle.push_back(ofRandom(0.1,1.0));
    }
    
    ofBackground(30);
    beatsInMinute = 107;
    beatCounter = 0;
    barCounter = 0;
    halfBeatCounter = 0;
    multiplier = 5;

    //if you want to draw something inside setup you need to make calls to this->beginFbo() / this->endFbo as below
    this->beginFbo();

    //ofClear(255,0,0);
    this->endFbo();
}

//--------------------------------------------------------------
void ConsciousCompetence::setName(string _name){
    
    name = _name;
}

//--------------------------------------------------------------
void ConsciousCompetence::update(){ // Don't do any drawing here
    
    runUtilityUpdates();
    
    // the number of stars grows until we reach max, in a dynamic pattern
    if (round(currentMaxStars) < maxStars) {
        if(beatCounter == 1 || beatCounter == 3) {
            currentMaxStars+=0.05; // slowly on beats 1 and 3 (no stars on beat 2)
        }
        if(beatCounter == 4) {
            currentMaxStars+=0.1; // faster on beat 4
        }
    }
    
   // remove all stars once time is up, for a clean transition
    if (barCounter >21 && currentMaxStars >0) {
        currentMaxStars--;
    }
    
}

//--------------------------------------------------------------
void ConsciousCompetence::reset(){
    //initialise frame county at the start of source
    startFrameCounter = ofGetFrameNum();
    beatCounter = 0;
    barCounter = 0;
    halfBeatCounter = 0;
    currentMaxStars = 0;
    frameCounter = 0;
    ofClear(0); // uncomment if you want canvas to be reset on the buffer when fbo source is called again
}



//--------------------------------------------------------------
void ConsciousCompetence::draw(){
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
    
    ofPushStyle();
    ofClear(0); // remove if you never want to update the background
    
    starTriangles();

    ofPopStyle();
    
    ofPushMatrix();
    ofSetColor(255);
    font.drawString(ofToString(barCounter)+"."+ofToString(beatCounter)+" - "+ofToString(currentMaxStars)+" stars "+ofToString(ofGetFrameRate()), ofGetMouseX(), ofGetMouseY());
    ofPopMatrix();
}


//--------------------------------------------------------------
void ConsciousCompetence::starTriangles() {
   
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
void ConsciousCompetence::runUtilityUpdates() {
    
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










