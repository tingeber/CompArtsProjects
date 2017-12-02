#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
        void keyReleased(int key);
    
        void valueHelper();
    
        void sas0(int phase, bool selector);
        void sas1(int phase, bool selector);
        void sas2(int phase, bool selector);
        void sas3(int phase, bool selector);
        void sas4(int phase, bool selector);
    
        float counter = 0;
        bool selector = true;
        int showDraw = 4;
        int totSaskias = 4;
    
        bool valueHelperBool = false;
        float rangeTestX = 0;
        float rangeTestY = 0;
    
		
};
