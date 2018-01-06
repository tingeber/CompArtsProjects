#pragma once

#include "ofMain.h"
#include "FboSource.h"

class sas1Source : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void setName(string _name);
    
        void sas0(int phase, bool selector);
        void sas1(int phase, bool selector);
        void sas2(int phase, bool selector);
        void sas3(int phase, bool selector);
        void sas4(int phase, bool selector);
        void sas5(int phase, bool selector);
    
        void setSelector(bool);
        void setShowDraw(int);
    
        float counter = 0;
        bool selector = true;
        int showDraw = 0;

};
