#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "AbstractSource.h"

class WhiteSource : public AbstractSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
    
};
