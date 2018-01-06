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
    
        void runUtilityUpdates();
    
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

    
        float multiplier;
        float pulse;
    
        int maxTriangles = 50;
    
        float noiseValue;
    
        float growth;
    
        float rColor;
        float gColor;
        float bColor;
    
    
        void helperText();
        ofTrueTypeFont font;
    
};


