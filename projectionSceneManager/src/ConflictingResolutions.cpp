
#include "ConflictingResolutions.h"

//--------------------------------------------------------------
void ConflictingResolutions::setup(){
    
    name = "Conflicting Resolutions";
    
    // Size of FBO
    allocate(800, 800);

    // initialize background
    bgColor = 150;
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(bgColor);
    ofSetColor(255);

    //initialize grid resolution
    numOfXTiles = 80;
    numOfYTiles = 80;

    growthSpeed = 40;

    // initialize 'pixels'
    ofSetCircleResolution(50);
    objSize = 2;

    // initialize grid spacing
    // 600/81 = 7.4
    spacingX = fbo->getWidth()/numOfXTiles;
    spacingY = fbo->getHeight()/numOfYTiles;

    face.load("ts-eliot-crop.jpeg");

    growth = true;
    
    ofClear(0);
}


//--------------------------------------------------------------
void ConflictingResolutions::setName(string _name){
    name = _name;
}

//--------------------------------------------------------------
void ConflictingResolutions::update(){
}

//--------------------------------------------------------------
void ConflictingResolutions::reset(){
    //initialise frame county at the start of source
    
    ofClear(0);
    
}

//--------------------------------------------------------------
void ConflictingResolutions::draw(){
    
    //ofClear(0);

    // background ghosting
    ofPushStyle();
    ofSetColor(bgColor,50);
    ofDrawRectangle(0,0,fbo->getWidth(),fbo->getHeight());
    ofPopStyle();

    //pixels
    // iterate over rows
    for(int x = 1; x <= numOfXTiles; x++)
    {
        // iterate over current row's columns
        for(int y = 1; y <= numOfYTiles; y++)
        {
            // determine location of current pixel
            float locX = x*spacingX -spacingX/2;
            float locY = y*spacingY -spacingY/2;

            ofPushMatrix();
            ofPushStyle();
            ofTranslate(locX,locY);
            float angle = atan2(fbo->getHeight()/2 - locY,fbo->getWidth()/2 - locX);
            float shapeDist = ofDist(fbo->getWidth()/2,fbo->getHeight()/2,locX,locY);


            // growth pixels
            // rotate in the (opposite + 180) direction from the window center
            // translate sinusoidally from the direction of the window's center

            //ENTER
            if(growth){
            ofPushMatrix();
            ofRotate(ofRadToDeg(angle) + 180);
            // different timing scaling for each stage
            // start time over at each new iteration
            float liner = shapeDist - ofGetElapsedTimef()*growthSpeed ;
            float siner = sin(liner);
            ofColor gray = face.getColor(x*(80/numOfXTiles),y*(80/numOfYTiles));
            if(liner > 0){
            ofTranslate(liner,0);
            ofSetColor(255,30);
//            ofSetColor(gray,30);
            }else{
            ofSetColor(gray);
            }
            ofDrawCircle(0,0,objSize);
            // rotate object orientation back to standard
//            ofRotate(-1*(ofRadToDeg(angle) + 180));
//            ofSetRectMode(OF_RECTMODE_CENTER);
//            ofDrawRectangle(0,0,objSize,objSize);
            ofPopMatrix();

            //EXIT
            }else{

                ofPushMatrix();
                ofRotate(ofRadToDeg(angle) + 180);
                // different timing scaling for each stage
                // start time over at each new iteration
                float liner = ofMap(shapeDist,0,fbo->getWidth()/2,0,HALF_PI) + ofGetElapsedTimef()*3 ;
                float siner = sin(liner);
                ofColor gray = face.getColor(x*(80/numOfXTiles),y*(80/numOfYTiles));

                if(liner < shapeDist){
                ofTranslate(liner,0);
                ofSetColor(255,30);
                ofRotate(-1*(ofRadToDeg(angle) + 180));
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofDrawRectangle(0,0,objSize,objSize);
                ofPopMatrix();
                }
            }


            ofPopStyle();
            ofPopMatrix();
        }
    }


    // center seed circle
//    ofSetColor(255);
//    ofDrawCircle(fbo->getWidth()/2,fbo->getHeight()/2,objSize);
}

void ConflictingResolutions::clearWindow(){
    ofSetColor(150);
    ofDrawRectangle(0,0,fbo->getWidth(),fbo->getHeight());
}

void ConflictingResolutions::validate(){
    ofSetColor(255);
}

void ConflictingResolutions::invalidate(){
    ofSetColor(0);
}

//--------------------------------------------------------------
void ConflictingResolutions::keyPressed(int key){
    // save screenshot as png
    if(key == 's'){
        ofSaveScreen(ofToString(ofGetFrameNum())+".png");
    }

    if(key == '1'){
        clearWindow();
        numOfXTiles = 4;
        numOfYTiles = 4;
        objSize = 70;
        spacingX = fbo->getWidth()/numOfXTiles;
        spacingY = fbo->getHeight()/numOfYTiles;
        growthSpeed = 40;
    }
    if(key == '2'){
        clearWindow();
        numOfXTiles = 20;
        numOfYTiles = 20;
        spacingX = fbo->getWidth()/numOfXTiles;
        spacingY = fbo->getHeight()/numOfYTiles;
        objSize = 10;
        growthSpeed = 20;
    }
    if(key == '3'){
        clearWindow();
        numOfXTiles = 80;
        numOfYTiles = 80;
        spacingX = fbo->getWidth()/numOfXTiles;
        spacingY = fbo->getHeight()/numOfYTiles;
        objSize = 2;
        growthSpeed = 10;
    }
    if(key == '4'){
        growth = !growth;
    }


}

