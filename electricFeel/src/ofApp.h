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
    
        void trianglePulse(float heightMultiplier, float numTriangles, float maxOpacity, float growth);
        void predatorTriangles();
        void starTriangles();
    
        ofTrueTypeFont font;
		
    
        int halfBeatCounter;
        int beatCounter;
        int barCounter;
        int beatsInMinute;
    
        float multiplier;
        float pulse;
    
    
    vector<float> trianglePos1;
    vector <float> trianglePos2;
    vector <float> triangleHeight;
    
    vector<float> triangle1x;
    vector<float> triangle1y;
    vector<float> triangle2x;
    vector<float> triangle2y;
    vector<float> triangle3x;
    vector<float> triangle3y;
    
    vector<float> transparency;
    
    vector<float> starPos1;
    vector<float> starPos2;
    vector<float> scaleTriangle;
    
    
    
    int startFrameCounter;
    int frameCounter;
    
    int maxTriangles = 50;
    
    float maxStars = 120;
    float currentMaxStars = 0;
    float starSpeed = 0.2;
    
    float noiseValue;
    
    float growth;
    
    float rColor;
    float gColor;
    float bColor;
    
    
};
