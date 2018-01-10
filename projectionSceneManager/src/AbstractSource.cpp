#include "AbstractSource.h"
#include "Macros.h"

void AbstractSource::setup(){
    if(fadeInMode == FADE_MAX) {
        c_min = C_MAX;
    } else if(fadeInMode == FADE_MIN) {
        c_max = C_MIN;
    }
}

void AbstractSource::setName(string _name){
    cout << "name set: " << _name << endl;
    name = _name;
}

void AbstractSource::setFadeIn(int _fadeMode){
    fadeInMode = _fadeMode;
}

void AbstractSource::reset(){
    startTime = ofGetElapsedTimeMillis();
    if(fadeInMode == FADE_MAX) {
        c_min = C_MAX;
        c_max = C_MAX;
    } else if(fadeInMode == FADE_MIN) {
        c_max = C_MIN;
        c_min = C_MIN;
    } else {
        c_min = C_MIN;
        c_max = C_MAX;
    }
}

void AbstractSource::setFadeOut(int _fadeMode, float after) {
    fadeOutMode = _fadeMode;
    fadeOutAfter = after;
}

void AbstractSource::update(){
    float t = ofGetElapsedTimeMillis() - startTime;
    if(fadeInMode != NONE) {
        if(t < FADE_IN) {
            if(fadeInMode==FADE_MAX) {
                c_min = ofMap(t, 0, FADE_IN, C_MAX, C_MIN);
            } else {
                c_max = ofMap(t, 0, FADE_IN, C_MIN, C_MAX);
            }
        } else {
            c_min = C_MIN;
            c_max = C_MAX;
        }
    }
    if(fadeOutMode != NONE) {
        if(t > fadeOutAfter) {
            t -= fadeOutAfter;
            if((t) < FADE_OUT) {
                if(fadeOutMode==FADE_MAX) {
                    c_min = ofMap(t, 0, FADE_OUT, C_MIN, C_MAX);
                } else {
                    c_max = ofMap(t, 0, FADE_OUT, C_MAX, C_MIN);
                }
            } else {
                c_min = (fadeOutMode==FADE_MAX) ? C_MAX : c_min;
                c_max = (fadeOutMode==FADE_MIN) ? C_MIN : c_max;
            }
        }
    }
    
}


void AbstractSource::draw(){
}

