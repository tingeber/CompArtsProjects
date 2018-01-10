#pragma once

#include "ofMain.h"
#include "FboSource.h"


class FairyGarden : public ofx::piMapper::FboSource {
    
public:
    void setup();
    void update();
    void draw();
    
    void setName(string);
    
    void reset();

    void drawMovingRect(int, int, int, int, float);
    void setColor(ofColor);
    ofColor rectColor;
    float time;
    
    //shape variables
    vector<float> locX;
    vector<float> locY;
    vector<float> speedX;
    vector<float> speedY;
    vector<int> nature;
    vector<float> life;
    vector<float> fade;
    vector<float> explosion;
    
    //side view plant variables
    vector<float> groundLoc;
    vector<float> trunk;
    vector<float> maxTrunk;
    vector<float> cap;
    vector<float> capSize;
    vector<float> sporeLineX;
    vector<float> sporeLineY;
    vector<float> sporeSize;
    vector<float> shroomAlpha;
    
    float dmg;
    float swap;
    float alpha;
    float alphaStep;
    float redAlpha;
    float redAlphaStep;
    float noiseStep;
    float curtain;
    float blueCurtain;
    int tick;
    float curtainTick;
    int mainTime;
    int box [2][9];
    float greenFade;
    float blueFade;
    
    int state = 3;
    ofTrueTypeFont font;
};

