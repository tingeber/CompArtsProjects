#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "AbstractSource.h"

#define VEL 5.0
#define CHANCE 7
#define SPACING 5

class TendrilsSource : public AbstractSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
    
        float time;
    
        int tendrilCount {50};
        float part_size {10.0};
        float tendrilWidth;
    
        vector<ofPoint> parts_dark;
    
        void draw_stripes();
    
        bool negative {true};
    void setNegative(bool _negative);
    
        float angle {0.0};
        void setAngle(float _angle);
};
