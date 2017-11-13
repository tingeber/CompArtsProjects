#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        // this makes the star object
        void star(float x, float y, float radius1, float radius2, int npoints);
    
        // this pops a mandala out on the screen
        void mandala(int index);
    
    
        float rotAngle = 0;
        float angleStep = 0.1;
    
        // all the vector points for all the mandalas
        vector<int>resolution;
        vector<int>radius1;
        vector<int>radius2;
        vector<float>noOfStars;
        vector<int>posX;
        vector<int>posY;
        vector<ofColor>mandalaColor;
    
    
};
