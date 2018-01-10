#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "AbstractSource.h"

class SquidSource : public AbstractSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
    
        float time;
    
        float counter;
        float control_x1, control_y1;
        float control_x2, control_y2;
    
        float n = 10;
        float spacing = 10;
        bool second_control = true;
    
        bool negative {false};
        void setNegative(bool _negative);
    

};
