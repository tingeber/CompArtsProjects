#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "AbstractSource.h"

class LineMoveSource : public AbstractSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();

        void setDuration(float _duration);
        void setAngle(float _angle);
        float duration;
        float width {50.0};
        float angle {0.0};
    
};
