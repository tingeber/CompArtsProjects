#include "ConsciousCompetence.h"


//--------------------------------------------------------------
// SETUP
//--------------------------------------------------------------
void ConsciousCompetence::setup(){
    
	// Default name of source
    name = "Conscious Competence";
    
    // Size of FBO
    allocate(1000, 1000);
    
    font.load("arial", 50, false, false, true);
    
    // populate star positions and size of triangles
    for (int i = 0; i< maxStars; i++) {
        starPos1.push_back(ofRandom(100,fbo->getWidth()-100));
        starPos2.push_back(ofRandom(100,fbo->getHeight()-100));
        scaleTriangle.push_back(ofRandom(0.1,1.0));
    }
    
    // init settings
    initDraw();
    
    ofBackground(30);
    beatsInMinute = 107; // the BPM that trigger all the animations
    
    
    beatCounter = 0;
    barCounter = 0;
    halfBeatCounter = 0;

}

//--------------------------------------------------------------
void ConsciousCompetence::setName(string _name){
    name = _name;
}

//--------------------------------------------------------------
// UPDATE
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
    initDraw();
}


//--------------------------------------------------------------
// DRAW
//--------------------------------------------------------------
void ConsciousCompetence::draw(){

    
    ofPushStyle();
    ofClear(0);
    
    starTriangles();

    ofPopStyle();
    
   printHelperText(); // helper info printed at mouse position
}


//--------------------------------------------------------------
// UTILITY FUNCTIONS
//--------------------------------------------------------------
void ConsciousCompetence::initDraw() {
    // clears all counters, runs at setup and reset
    
    startFrameCounter = ofGetFrameNum();
    barCounter = 0;
    beatCounter = 0;
    halfBeatCounter = 0;
    frameCounter = 0;
    currentMaxStars = 0;
    noiseValue = ofRandom(0,100);
    ofClear(0);
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

//--------------------------------------------------------------
void ConsciousCompetence::printHelperText() {
    // print helper text at mouse position (frame rate, milis, etc)
    
    ofPushMatrix();
    ofSetColor(255);
    font.drawString(ofToString(barCounter)+"."+ofToString(beatCounter)+" - "+ofToString(currentMaxStars)+" stars "+ofToString(ofGetFrameRate()), ofGetMouseX(), ofGetMouseY());
    ofPopMatrix();
}


//--------------------------------------------------------------
// MAIN ANIMATIONS
//--------------------------------------------------------------
void ConsciousCompetence::starTriangles() {
   
    ofPushMatrix();
    ofPushStyle();
    
    // for loop only prints the current max stars
    for (int k=0; k<currentMaxStars; k++) {
        ofPushMatrix();
        
        // triangleStar positions, with a slight wobble
        float shiftX = ofMap(ofSignedNoise(noiseValue+starPos2[k]),-1,1,-5,5);
        float shiftY = ofMap(ofSignedNoise(noiseValue+starPos1[k]),-1,1,-5,5);
        ofTranslate(starPos1[k]+shiftX, starPos2[k]+shiftY);
        
        // let's make them of different sizes as well
        ofScale(scaleTriangle[k], scaleTriangle[k]);
        
        // print 30 overlapping rotating triangles for each position
        for (int i=0; i<30; i++) {
            
            // each slightly delayed
            float delay = ofMap(i, 0, 30, 0.1, 0.3);
            // in movement
            float noiseSeed = ofMap(ofSignedNoise(noiseValue*starSpeed+delay+starPos1[k]),-1,1,0,1440);
            //and in opacity
            float opacityNoise = ofMap(ofSignedNoise(noiseValue*0.2+delay+i*20+k*5),-1,1,0,20);
            
            //let's get them to pulse, but only on the very top of the sine wave, and each at its own time
            float scaleSingle = ofMap(sin(ofDegToRad(ofGetFrameNum()+k)),0.8,0.9, 0.5,1.0, true );
            
            // colors shift through shades of purple
            ofSetColor(30+ofMap(i, 0,8, -50,50), 100, 100+ofMap(i, 0,8, -50,50), opacityNoise);
            
            // well let's draw them then
            ofPushMatrix();
            ofScale(scaleSingle,scaleSingle);
            ofRotate(noiseSeed);
            ofDrawTriangle(0, -100, 100, 50, -100, 50);
            
            // and let's add a tiny red dot, our leit motif
            ofSetColor(200, 100, 0);
            ofDrawCircle(0, 0, 5);
            ofPopMatrix();
        }
        ofPopMatrix();
    }
    
    ofPopMatrix();
    ofPopStyle();
}










