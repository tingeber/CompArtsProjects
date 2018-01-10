#include "TendrilsSource.h"

void TendrilsSource::setup(){
    AbstractSource::setup();
//    name = "Tendrils Squares Source";
//    rectColor = ofColor(255);
    allocate(800, 800);
    
    tendrilWidth = fbo->getWidth() / (float) tendrilCount;
    ofSetCircleResolution(100);
    
    // create seed particles
    for(int i=1 ; i < tendrilCount ; i+=2) {
        for(int j=0 ; j < tendrilCount ; j+=2) {
            bool shouldCreateParticle = ((int) ofRandom(CHANCE) == 0);
            if(shouldCreateParticle) {
                ofPoint part = ofPoint(i * tendrilWidth + tendrilWidth/2.0, j * tendrilWidth);
                parts_dark.push_back(part);
            }
        }
    }
    
}

void TendrilsSource::reset(){
    AbstractSource::reset();
}


void TendrilsSource::update(){
    AbstractSource::update();
    
    for(int i=0 ; i < parts_dark.size() ; i++) {
        parts_dark[i].y += VEL;
        // put it back to the top
        if(parts_dark[i].y > fbo->getHeight()) {
            parts_dark[i].y = 0;
        }
    }
}

void TendrilsSource::setNegative(bool _negative) {
    negative = _negative;
}

void TendrilsSource::setAngle(float _angle){
    angle = _angle;
}


void TendrilsSource::draw(){
    ofClear(0); //clear the buffer

    ofPushMatrix();
    ofTranslate(fbo->getWidth()/2.0, fbo->getHeight()/2.0);
    ofRotate(angle);
    ofTranslate(-fbo->getWidth()/2.0, -fbo->getHeight()/2.0);
    ofPushStyle();
    if(!negative) {
        ofBackground(c_max);
//        ofSetColor(c_min);
    } else {
        ofBackground(c_min);
//        ofSetColor(c_max);
    }
    
    draw_stripes();
    
    if(!negative) {
//        ofBackground(c_max);
        ofSetColor(c_max);
    } else {
//        ofBackground(c_min);
        ofSetColor(c_min);
    }
    
    float t = ofGetFrameNum() / 100.0;
    
    for(int i=0 ; i < parts_dark.size() ; i++) {
        float n = ofMap(ofNoise(t, i),0,1,0,20);
        ofDrawCircle(parts_dark[i].x, parts_dark[i].y, n);
    }
    
    ofPopStyle();
    ofPopMatrix();
    


}

void TendrilsSource::draw_stripes() {
    ofPushStyle();
    if(!negative) {
//        ofBackground(c_max);
        ofSetColor(c_min);
    } else {
//        ofBackground(c_min);
        ofSetColor(c_max);
    }
    for(int i=0 ; i < tendrilCount ; i+=2) {
        ofDrawRectangle(i * tendrilWidth, 0, tendrilWidth, fbo->getHeight());
    }
    ofPopStyle();
}

