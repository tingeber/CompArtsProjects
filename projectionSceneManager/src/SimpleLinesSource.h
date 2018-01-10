#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "AbstractSource.h"

#define WIDTH_DEFAULT 10.0
#define VEL_MAX 3.0
#define VEL_MIN 0.0
#define WIDTH_MAX 30.0
#define WIDTH_MIN 1.0

class SimpleLinesSource : public AbstractSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
        float time;
        int lineCount {50};
        void setAngle(float _angle);
        float angle;
        vector<float> positions;
        vector<float> vels;
        vector<float> accs;
        vector<float> widths;
        vector<float> alphas;
};
