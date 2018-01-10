#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "Macros.h"
#include "AbstractSource.h"

class DepthSquaresSource : public AbstractSource {
	public:
    
        void setup();
		void update();
		void draw();
        void reset();
        void setNegative(bool _negative);
        
        float time;
    
        int loopLength {3000};
        int rectCount {10};
        int drift {400};
        bool negative {false};
        float seed1, seed2;

    
        
    
    
};
