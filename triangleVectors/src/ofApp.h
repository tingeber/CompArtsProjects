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
    
    
    vector<float> speed1X;
    vector<float> speed1Y;
    vector<float> loc1X;
    vector<float> loc1Y;
    
    vector<float> speed2X;
    vector<float> speed2Y;
    vector<float> loc2X;
    vector<float> loc2Y;
    
    vector<float> green;
    
		
};
