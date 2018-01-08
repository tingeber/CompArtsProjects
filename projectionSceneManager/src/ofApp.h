#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"
#include "VideoSource.h"
#include "SceneManager.h"
#include "Incompetence.h"
#include "ConsciousCompetence.h"
#include "UnconsciousCompetence.h"
#include "ConflictingResolutions.h"

class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();
	
		void keyPressed(int key);
		void keyReleased(int key);
	
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseDragged(int x, int y, int button);

		ofxPiMapper piMapper;
    
        Incompetence * incompetence1;
        Incompetence * incompetence2;
        Incompetence * incompetence3;
    
        ConsciousCompetence * consciousCompetence;
    
        UnconsciousCompetence * unconsciousCompetence1;
        UnconsciousCompetence * unconsciousCompetence2;
        UnconsciousCompetence * unconsciousCompetence3;
    
        ofImage cubeIso;

        SceneManager sceneManager;
    
        ConflictingResolutions * conflictingResolutions;
};
