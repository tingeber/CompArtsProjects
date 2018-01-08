#pragma once

#include "ofMain.h"
#include "FboSource.h"

class UnconsciousCompetence : public ofx::piMapper::FboSource {
    public:
        void setup();
        void update();
        void draw();
        void setName(string);

        void reset();

        void predatorTriangles(int startPos);
    
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
    
        vector<ofVec2f> triangle1;
        vector<ofVec2f> triangle2;
        vector<ofVec2f> triangle3;
        vector<float> transparency;
    
        float noiseValue;

        ofTrueTypeFont font;
    
};


