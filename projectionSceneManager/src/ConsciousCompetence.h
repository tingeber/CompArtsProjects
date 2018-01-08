#pragma once

#include "ofMain.h"
#include "FboSource.h"

class ConsciousCompetence : public ofx::piMapper::FboSource {
    public:
        void setup();
        void update();
        void draw();
        void setName(string);

        void reset();

        void starTriangles();
    
        void initDraw();
        void runUtilityUpdates();
        void printHelperText();
    
        int halfBeatCounter;
        int beatCounter;
        int barCounter;
        int beatsInMinute;
        int startFrameCounter;
        int frameCounter;
            
        float maxStars = 120;
        float currentMaxStars = 0;
        float starSpeed = 0.2;
    
        float noiseValue;
    
    
        vector<float> starPos1;
        vector<float> starPos2;
        vector<float> scaleTriangle;
    
        ofTrueTypeFont font;
    
};


