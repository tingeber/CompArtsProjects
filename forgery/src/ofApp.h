#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
    ofImage picasso; // the original
    ofPath neck;    // SO. MANY. OF. PATHS.
    ofPath moon;
    ofPath hat;
    ofPath torso;
    ofPath hair;
    ofPath face;
    ofPath streaks;
    ofPath moonstreak;
    ofPath mouth;
    
    int fadeIn; // declaring the integer for the fadein
   
    //  I decided to write the eyes as a function -
    //  probably should have made a separate .h file?
    void eye(int x, int y, int width, int height) {
        ofSetColor(26,31,24);
        ofDrawEllipse(x, y, width+30, height+30);
        
        ofSetColor(200,200,200);
        ofDrawEllipse(x, y, width+15, height+15);
        
        ofSetColor(26,31,24);
        ofDrawEllipse(x, y, width, height);
    }
    
};
