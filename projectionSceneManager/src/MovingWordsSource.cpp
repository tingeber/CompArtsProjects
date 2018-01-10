#include "MovingWordsSource.h"

void MovingWordsSource::setup(){
	// Give our source a decent name
    name = "Moving Words Source";
    rectColor = ofColor(255);
	// Allocate our FBO source, decide how big it should be
    allocate(500, 500);
    
    myFont.load("Futura Std Medium Oblique.ttf", 50);
    //ofBackground(0);
    ofClear(0);
    //ofSetBackgroundAuto(false);// no background refresh
    
    //timer init
    timerEnd= false;
    startTime = ofGetElapsedTimeMillis();
    
    //location init
    for (int i=0; i<8; i++)
    {
        locX.push_back(ofRandom(fbo->getWidth()-200));
        locY.push_back(ofRandom(fbo->getHeight()));
        stepX.push_back(ofRandom(-2,2));
        stepY.push_back(ofRandom(-2,2));
        
    }
    
}

void MovingWordsSource::setName(string _name){
    name = _name;
}

void MovingWordsSource::setColor(ofColor c){
    rectColor = c;
}

// Don't do any drawing here
void MovingWordsSource::update(){
    
    //bounce location init
    for (int i = 0; i < stepX.size(); i++)
    {
        locX[i] = locX[i] + stepX[i];
        locY[i] = locY[i] + stepY[i];
        
        if (locX[i]>fbo->getWidth()-200 || locX[i] <0 ){
            stepX[i] = stepX[i] * -1;
        }
        if (locY[i]>fbo->getHeight()|| locY[i] <0 ){
            stepY[i] = stepY[i]* -1;
        }
    }
    
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void MovingWordsSource::draw(){
    //ofClear(0); //clear the buffer
    
    //timer
    float timer = ofGetElapsedTimeMillis() - startTime;
    
    if (timer>= endTime){
        timerEnd = true;
    }
    
    //at 50 sec, start printing helloooo
    if (timer>=80000){
        for (int i= 0; i<stepX.size(); i++) {
            ofSetColor(17, 7, 63);//dark
            myFont.drawString("helloooo", locX[i]+200, locY[i]-200);
        }
        for (int i= 0; i<stepX.size(); i++) {
            ofSetColor(181, 208, 255);//purple
            myFont.drawString("helloooo", locX[i]+200, locY[i]-200);
        }
    }
    
    
    //at 20 sec, start printing and here
    if (timer>=20000){
        for (int i= 0; i<stepX.size(); i++) {
            
            ofSetColor(17, 7, 63);//dark
            myFont.drawString("and here", locX[i]-200, locY[i]+200);
        }
        for (int i= 0; i<stepX.size(); i++) {
            
            ofSetColor(170, 255, 245);//blue
            myFont.drawString("and here", locX[i]-200, locY[i]+200);
        }
    }
    
    //at 1min sec, start printing here too
    if (timer>=50000){
        for (int i= 0; i<stepX.size(); i++) {
            
            ofSetColor(17, 7, 63);//dark
            myFont.drawString("here too!", locX[i]+150, locY[i]-150);
        }
        for (int i= 0; i<stepX.size(); i++) {
            
            ofSetColor(255, 255, 180);//yellow
            myFont.drawString("here too!", locX[i]+150, locY[i]-150);
        }
    }
    //at 2min, start printing ok bye
    if (timer>=90000){
        for (int i= 0; i<stepX.size(); i++) {
            
            ofSetColor(17, 7, 63);//dark
            myFont.drawString("ok bye", locX[i]+250, locY[i]-250);
        }
        for (int i= 0; i<stepX.size(); i++) {
            
            ofSetColor(179, 255, 196);//green
            myFont.drawString("ok bye", locX[i]+250, locY[i]-250);
        }
    }
    
    //print I'm here from start
    ofPushMatrix();
    
    for (int i = 0; i < stepX.size(); i++)
    {
        
        ofSetColor(17, 7, 63);//dark
        myFont.drawString("I'm here", locX[i], locY[i]-100);
    }
    
    
    for (int i = 0; i < stepX.size(); i++)
    {
        
        ofSetColor(255, 170, 224);//pink
        myFont.drawString("I'm here", locX[i], locY[i]-100);
    }
    ofPopMatrix();
    
    ofPushStyle();
    ofSetColor(255, 255, 255, 3);
    ofDrawRectangle(0, 0, 500, 500);
    ofPopStyle();


    
}

