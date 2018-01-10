#include "UnconsciousCompetence.h"

//--------------------------------------------------------------
// SETUP
//--------------------------------------------------------------
void UnconsciousCompetence::setup(){
    
	// Default name of source
    name = "UnconsciousCompetence";
    
    // Size of FBO
    allocate(1000, 1000);
    
    font.load("arial", 50, false, false, true);
    
    ofBackground(30);
    
    beatsInMinute = 107; // the BPM that trigger all the animations
    
    // init settings
    initDraw();

}

//--------------------------------------------------------------
void UnconsciousCompetence::setName(string _name){
    name = _name;
}

void UnconsciousCompetence::setStartPos(int b) {
    b = startPos;
}


//--------------------------------------------------------------
// UPDATE
//--------------------------------------------------------------
void UnconsciousCompetence::update(){
    
    runUtilityUpdates();
    
    // this one is neat. we slowly fade away the earliest triangles
    // by always keeping the range of transparency for all triangles between 50 (newest) and 0 (oldest)
    for(int i = 0; i<transparency.size(); i++) {
        if (barCounter<25) {
            transparency[i] = ofMap(i, 0, transparency.size(), 0, 50);
        } else {
            transparency[i] -= 0.05; // we fade them away at the end of the animation
        }
    }
    
}

//--------------------------------------------------------------
void UnconsciousCompetence::reset(){
    //initialise frame county at the start of source
    
    initDraw();
    
    // clearing our triangle buffers
    triangle1.clear();
    triangle2.clear();
    triangle3.clear();
    
}


//--------------------------------------------------------------
// DRAW
//--------------------------------------------------------------
void UnconsciousCompetence::draw(){

    
    ofPushStyle();
    ofClear(0);
    
    predatorTriangles(startPos);

    ofPopStyle();
    
    printHelperText(); // helper text at mouse position with frame rate, milis, bars etc
}


//--------------------------------------------------------------
// UTILITY FUNCTIONS
//--------------------------------------------------------------
void UnconsciousCompetence::initDraw() {
    // clears all counters, runs at setup and reset
    
    startFrameCounter = ofGetFrameNum();
    barCounter = 0;
    beatCounter = 0;
    halfBeatCounter = 0;
    frameCounter = 0;
    noiseValue = ofRandom(0,100);
    ofClear(0);
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
void UnconsciousCompetence::printHelperText() {
    // basic helper text
    
    ofPushMatrix();
    ofSetColor(255);
    font.drawString(ofToString(barCounter)+"."+ofToString(beatCounter)+" - "+ofToString(halfBeatCounter)+" "+ofToString(ofGetFrameRate()), ofGetMouseX(), ofGetMouseY());
    ofPopMatrix();
    
}


//--------------------------------------------------------------
// MAIN ANIMATIONS
//--------------------------------------------------------------
void UnconsciousCompetence::predatorTriangles(int startPos) {
    // three dots stroll through space, effortlessly leaving triangular tunnels in their wake

    
    // let's print the triangles trailing the dots
    for(int i = 0; i<triangle1.size(); i++) {
        float randomAdd; // let's add some glitch
        if (barCounter > 15) { // but only after bar 15
            float randomSeed = ofMap(halfBeatCounter, 160,220, 0,100, true); // and let's glitch incrementally
            randomAdd = ofRandom(-randomSeed, randomSeed); // so triangles start being increasingly jerky
        }
        
        // we're drawing triangles by pulling positions and opacity from the vectors
        ofSetColor(30, 100, 100, transparency[i]);
        ofDrawTriangle(triangle1[i].x+randomAdd, triangle1[i].y, triangle2[i].x, triangle2[i].y, triangle3[i].x, triangle3[i].y);
    }
    
    ofPushMatrix();
    ofPushStyle();
    float speed = 0.3;
    
    // we want our dots to travel all across the canvas
    float minWidth = 0;
    float maxWidth = fbo->getWidth();
    float minHeight = 0;
    float maxHeight = fbo->getHeight();
    
   // and slowly reduce their playground as we come closer to animation end
    if (barCounter >20 && barCounter <30) {
        minWidth = ofMap(halfBeatCounter, 160,230,0,fbo->getWidth()/2, true);
        maxWidth = ofMap(halfBeatCounter, 160,230,fbo->getWidth(),fbo->getWidth()/2, true);
        minHeight = ofMap(halfBeatCounter, 160,230,0,fbo->getHeight()/2, true);
        maxHeight = ofMap(halfBeatCounter, 160,230,fbo->getHeight(),fbo->getHeight()/2, true);
    }
    
    // until they can't move no more
    if (barCounter >=30) {
        minWidth = fbo->getWidth()/2;
        minHeight = fbo->getHeight()/2;
        maxWidth = fbo->getWidth()/2;
        maxHeight = fbo->getHeight()/2;
    }
    
    // let's have our triangle trio travel through time erm space
    float posX = ofMap(ofSignedNoise(noiseValue*speed),-1, 1, minWidth, maxWidth);
    float posY = ofMap(ofSignedNoise((noiseValue+209)*speed),-1, 1, minHeight, maxHeight);
    ofTranslate(posX, posY);
    
    ofSetColor(250, 100, 100);
    
    // three dots
    for (int i = 0; i<3; i++) {
        
        // also fluidly noisying around the translate point
        float maxLen = 300;
        
        // but their movement is reduced as we come closer to the end of the animation
        if (barCounter >20) {
            maxLen = ofMap(halfBeatCounter, 200,230,200,0, true);
        }
        
        float seedX = ofMap(ofSignedNoise(noiseValue + i*20), -1,1, -maxLen,maxLen);
        float seedY = ofMap(ofSignedNoise(noiseValue + i*20 + 20), -1,1, -maxLen,maxLen);
        
        // draw predator dots, unless the animation is about to end
        if (barCounter < 30) {
            ofDrawCircle(seedX, seedY, 5);
        }
        
        // and let's feed our vectors, but only on beats 2 and 3, the positions of our predator dots
        // to find the right position on the canvas, we sum the translate value with the dot value
        // three dots, so three sets of coordinates, for our three vectors
        if ((beatCounter == 2 || beatCounter == 3) && barCounter <= 23) {
            transparency.push_back(30); // feeding transparency to vector so we can reduce it in update
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


