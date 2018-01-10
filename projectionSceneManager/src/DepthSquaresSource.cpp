#include "DepthSquaresSource.h"

void DepthSquaresSource::setup(){
    AbstractSource::setup();
    allocate(800, 800);
    drift = fbo->getWidth() * 0.7;
    seed1 = ofRandom(5);
    seed2 = ofRandom(100, 300);
}

void DepthSquaresSource::reset(){
    AbstractSource::reset();
    seed1 = 0;
    seed2 = 200.0;
}

// Don't do any drawing here
void DepthSquaresSource::update(){
    AbstractSource::update();
    time = ofGetFrameNum()*5;
}

void DepthSquaresSource::setNegative(bool _negative) {
    negative = _negative;
}

void DepthSquaresSource::draw(){
    ofClear(0);
    
    float t = (ofGetFrameNum() % loopLength) / (float) loopLength;
    ofPushMatrix();
    ofPushStyle();
    ofBackground(c_min);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(c_max);
    ofTranslate(fbo->getWidth()/2.0,fbo->getHeight()/2.0);
    float x_offset = ofMap(ofNoise(ofGetFrameNum() / seed2 + seed1), 0, 1, -drift, drift);
    float y_offset = ofMap(ofNoise(ofGetFrameNum() / seed2 + seed1 + 40 ), 0, 1, -drift, drift);
    for(int i=rectCount ; i >= 0 ; i--) {
        float p = ofMap(i, 0, rectCount, 0, 1);
        float c = ofMap(sin(t * TWO_PI + p*5),-1,1,0.2,1);
        if(negative) c = (1-c);
        float x = (1-p) * x_offset;
        float y = (1-p) * y_offset;
        ofPushMatrix();
        ofTranslate(x, y);
        ofSetColor(ofMap(c, 0.2,1,c_min,c_max));
        float rectSize = p * fbo->getWidth();
        ofDrawRectangle(0, 0, rectSize, rectSize);
        ofPopMatrix();
    }
    ofPopStyle();
    ofPopMatrix();

}

