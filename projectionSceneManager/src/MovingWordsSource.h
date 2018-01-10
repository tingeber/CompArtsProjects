#pragma once

#include "ofMain.h"
#include "FboSource.h"

class MovingWordsSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
      
        void setName(string _name);
        void setColor(ofColor);
        ofColor rectColor;
    
    
    float startTime;
    bool timerEnd;
    ofParameter<float>endTime;
    
    ofImage image;
    ofTrueTypeFont myFont;
    
    
    
    vector<int> locX, locY;
    vector<int> stepX, stepY;
};
