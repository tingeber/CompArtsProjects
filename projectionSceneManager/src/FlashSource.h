#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "AbstractSource.h"

class FlashSource : public AbstractSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();

        void setDelay(float _delay);
        void setDuration(float _duration);
    
        float delay;
        float duration;
    
};
