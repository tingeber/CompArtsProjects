#include "LineMoveSource.h"

void LineMoveSource::setup(){
    AbstractSource::setup();
    allocate(800, 800);
}

void LineMoveSource::reset(){
    AbstractSource::reset();
}

void LineMoveSource::setDuration(float _duration){
    duration = _duration;
}

void LineMoveSource::setAngle(float _angle){
    angle = _angle;
}

// Don't do any drawing here
void LineMoveSource::update(){
    AbstractSource::update();
}

void LineMoveSource::draw(){
    ofClear(0);
    ofPushMatrix();
    ofTranslate(fbo->getWidth()/2.0, fbo->getHeight()/2.0);
    ofRotate(angle);
    ofTranslate(-fbo->getWidth()/2.0, -fbo->getHeight()/2.0);
    ofPushStyle();
    ofBackground(c_min);
    ofSetColor(c_max);
    int t = (ofGetElapsedTimeMillis() - (int)startTime) % (int)duration;
    float norm_time = t / duration;
    ofDrawRectangle(norm_time * (fbo->getWidth()+width) - width, 0, width, fbo->getHeight());
    ofPopStyle();
    ofPopMatrix();
}

