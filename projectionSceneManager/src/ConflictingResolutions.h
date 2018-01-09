#pragma once

#include "ofMain.h"
#include "FboSource.h"

class ConflictingResolutions : public ofx::piMapper::FboSource{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void clearWindow();
    void detection();
    void recognition();
    void identification();
    void changeScene();


    int bgColor;
    int numOfXTiles;
    int numOfYTiles;
    int spacingX;
    int spacingY;
    int startingX;
    int startingY;
    int objSize;
    int objMovementDist;

    int initialWidth;
    int initialHeight;

    ofImage face;

    bool growth;
    bool analyze;
    int growthSpeed;
    int sceneFactor;
    int elapsedTime;
    int pixelAlpha;
    float pixelBorder;
    int faceIt;
    int elapsed;
};
