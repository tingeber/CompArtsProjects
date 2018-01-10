
#include "conflictingResolutions.h"

//--------------------------------------------------------------
void ConflictingResolutions::setup(){

    name = "Conflicting Resolutions";

    //size of FBO
    allocate(800,800);

    // initialize background
    bgColor = 150;
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(bgColor);
    ofSetColor(255);
    pixelAlpha = 255;

    //initialize grid resolution
    numOfXTiles = 80;
    numOfYTiles = 80;

    growthSpeed = 10;

    // initialize 'pixels'
    objSize = 4;

    // initialize grid spacing
    spacingX = fbo->getWidth()/numOfXTiles;
    spacingY = fbo->getHeight()/numOfYTiles;


    setImage();
    
    growth = true;
    
    ofClear(0);
}
    // initialize interaction
    growth = false;
    analyze = false;
    sceneFactor = 0;
    elapsed = ofGetElapsedTimef();

}

//--------------------------------------------------------------
void ConflictingResolutions::setName(string _name){
    name = _name;
}

void ConflictingResolutions::setImage(string b) {
    face.load(b);
}

//--------------------------------------------------------------
void ConflictingResolutions::update(){

    elapsed = ofGetElapsedTimef();

    // load random image on restart
    if(elapsed == 0 || elapsed == 1){

        face.clear();
//         faceIt = ofRandom(0,9);
//         face.load(ofToString(faceIt)+".jpeg");
        setImage();
    }

    if(elapsed < 30){
        // detection - 0-30 (30 sec)
        detection();
        if(elapsed > 12 && elapsed < 20){
            // visualize analysis
            analyze = elapsed % 3 ==0 ? true : false;
        }
        if(elapsed > 20 && elapsed < 30){
            // visualize analysis
            analyze = elapsed % 2 ==0 ? true : false;
        }
    }else if(elapsed > 29 && elapsed < 80){
        // recognition - 30 - 70 (40 sec)
        recognition();
        // visualize analysis
        if(elapsed > 65){
            analyze = elapsed % 3 ==0 ? true : false;
        }
    }else{
    // identification - 70 - 160 (90)
        identification();
        if(elapsed >= 130){
            growth = true;
        }
    }


    // prepare next classification
    if(ofGetElapsedTimeMillis() >= 0 && ofGetElapsedTimeMillis() < 60){
        changeScene();
    }
    if(ofGetElapsedTimeMillis() >= 30000 && ofGetElapsedTimeMillis() < 30060){
        changeScene();
    }
    if(ofGetElapsedTimeMillis() >= 80000 && ofGetElapsedTimeMillis() < 80060){
        changeScene();
    }
    if(elapsed >= 160){
        growth = false;
        changeScene();
        ofResetElapsedTimeCounter();
    }
}

//--------------------------------------------------------------
void ConflictingResolutions::reset(){
    //initialise frame county at the start of source
    
    ofClear(0);
    
}

//--------------------------------------------------------------
void ConflictingResolutions::draw(){

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

            // initial grid translation
            ofPushMatrix();
            ofPushStyle();
            ofTranslate(locX,locY);
            float angle = atan2(fbo->getHeight()/2 - locY,fbo->getWidth()/2 - locX);
            float shapeDist = ofDist(fbo->getWidth()/2,fbo->getHeight()/2,locX,locY);

            ofPushMatrix();
            // rotate in the (opposite + 180) direction from the window center
            ofRotate(ofRadToDeg(angle) + 180);
            float liner = shapeDist - (ofGetElapsedTimef()-sceneFactor)*growthSpeed;
            // color data from source image
            ofColor gray = face.getColor(x*(80/numOfXTiles),y*(80/numOfYTiles));

            // identifaction ornimentation
            if(growth){
                ofPushMatrix();
                // sinusoudally move towards in space in relation to window center
                float liner = ofMap(shapeDist,0,fbo->getWidth()/2,0,HALF_PI) - ofGetElapsedTimef() ;
                float siner = sin(liner);
                if(liner < shapeDist){
                ofTranslate(ofMap(siner, PI, HALF_PI, 0, spacingX/1.25)-(spacingX*0.5),0);
                ofSetColor(255,20);
                ofRotate(-1*(ofRadToDeg(angle) + 180));
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofDrawRectangle(0,0,objSize,objSize);
                ofPopMatrix();
                }
            }

            // translate white pixel if in the process of forming the grid
            if(liner > 0){
                ofTranslate(liner,0);
                ofSetColor(255,30);

            }else{
                // static, colored pixel
                ofSetColor(gray,pixelAlpha);
            }

            // rotate object orientation back to standard orientation
            ofRotate(-1*(ofRadToDeg(angle) + 180));
            ofSetRectMode(OF_RECTMODE_CENTER);

            // analysis visualization outlines
            if(analyze && liner <= 0){
                ofPushStyle();
                ofSetColor(200,40);
                ofDrawRectangle(0,0,objSize*pixelBorder,objSize*pixelBorder);
                ofPopStyle();
            }

            // the pixel
            ofDrawRectangle(0,0,objSize,objSize);

            ofPopMatrix();

            ofPopStyle();
            ofPopMatrix();
        }
    }
}

void ConflictingResolutions::clearWindow(){
    ofSetColor(150);
    ofDrawRectangle(0,0,fbo->getWidth(),fbo->getHeight());
}

void ConflictingResolutions::changeScene(){
    sceneFactor = ofGetElapsedTimef();
}

void ConflictingResolutions::detection(){
    clearWindow();
    numOfXTiles = 4;
    numOfYTiles = 4;
    objSize = 155;
    spacingX = fbo->getWidth()/numOfXTiles;
    spacingY = fbo->getHeight()/numOfYTiles;
    growthSpeed = 40;
    pixelBorder = 1.125;
}

void ConflictingResolutions::recognition(){
    clearWindow();
    numOfXTiles = 20;
    numOfYTiles = 20;
    spacingX = fbo->getWidth()/numOfXTiles;
    spacingY = fbo->getHeight()/numOfYTiles;
    objSize = 20;
    growthSpeed = 20;
    pixelBorder = 1.25;
}

void ConflictingResolutions::identification(){
    clearWindow();
    numOfXTiles = 80;
    numOfYTiles = 80;
    spacingX = fbo->getWidth()/numOfXTiles;
    spacingY = fbo->getHeight()/numOfYTiles;
    objSize = 4;
    growthSpeed = 10;
    pixelBorder = 2;
}
//--------------------------------------------------------------
void ConflictingResolutions::keyPressed(int key){
    // save screenshot as png
    if(key == 's'){
        ofSaveScreen(ofToString(ofGetFrameNum())+".png");
    }
    // testing image change
    if(key == '3'){
            faceIt = ofRandom(0,9);
            face.clear();
            face.load(ofToString(faceIt)+".jpeg");
    }
    // testing visualization ornimentation
    if(key == '4'){
        growth = !growth;
    }


}

