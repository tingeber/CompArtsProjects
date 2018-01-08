#pragma once

#include "ofMain.h"
#include "FboSource.h"

class Incompetence : public ofx::piMapper::FboSource {
    public:
        void setup();
        void update();
        void draw();
        void setName(string);

        void reset();

        void predator(int startPos);
        void trianglePulse(float heightMultiplier, float numTriangles, float maxOpacity);
    
        void setStartPos(int);
        int startPos = 0;
    
        void initDraw();
        void runUtilityUpdates();
        void printHelperText();
    
        int halfBeatCounter;
        int beatCounter;
        int barCounter;
        int beatsInMinute;
        int startFrameCounter;
        int frameCounter;
        float startTime;
    
        vector <float> trianglePos1;
        vector <float> trianglePos2;
        vector <float> triangleHeight;
    
        int maxTriangles = 50;
    
        float noiseValue;
    
        float growth;
    
        float rColor;
        float gColor;
        float bColor;
    
        ofTrueTypeFont font;
    
};


