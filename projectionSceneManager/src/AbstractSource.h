#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "Macros.h"

class AbstractSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
        void setName(string _name);
        void setFadeIn(int _fadeMode);
        void setFadeOut(int _fadeMode, float after);
    
        float c_min {C_MIN};
        float c_max {C_MAX};
    
        int fadeInMode {0};
        int fadeOutMode {0};
        float fadeOutAfter {-1};
        float startTime;
    
};
