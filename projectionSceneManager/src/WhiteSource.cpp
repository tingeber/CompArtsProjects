#include "WhiteSource.h"

void WhiteSource::setup(){
    AbstractSource::setup();
//    name = "White Source";
    allocate(800, 800);
}

void WhiteSource::reset(){
    AbstractSource::reset();
}

void WhiteSource::update(){
    AbstractSource::update();
}

void WhiteSource::draw(){
    ofClear(0);
    ofPushStyle();
    ofBackground(c_max);
    ofPopStyle();
}

