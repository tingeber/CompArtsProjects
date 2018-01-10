#include "FlashSource.h"

void FlashSource::setup(){
    AbstractSource::setup();
    allocate(800, 800);
}

void FlashSource::reset(){
    AbstractSource::reset();
}

void FlashSource::setDelay(float _delay){
    delay = _delay;
}

void FlashSource::setDuration(float _duration){
    duration = _duration;
}

void FlashSource::update(){
    AbstractSource::update();
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void FlashSource::draw(){
    ofClear(0);
    ofPushStyle();
    ofBackground(c_min);
    ofSetColor(c_max);
    float t = ofGetElapsedTimeMillis() - startTime;
    if (t > delay && t <= delay + duration) {
        ofDrawRectangle(0, 0, fbo->getWidth(), fbo->getHeight());
    }
    ofPopStyle();

}

