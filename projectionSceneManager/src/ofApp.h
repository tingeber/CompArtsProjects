#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"
#include "VideoSource.h"
#include "SceneManager.h"

//Tin
#include "Incompetence.h"
#include "ConsciousCompetence.h"
#include "UnconsciousCompetence.h"

//Luke
#include "ConflictingResolutions.h"

//Sam
#include "DepthSquaresSource.h"
#include "SquidSource.h"
#include "SimpleLinesSource.h"
#include "TendrilsSource.h"
#include "ParticlesSource.h"
#include "FlashSource.h"
#include "WhiteSource.h"
#include "BlackSource.h"
#include "LineMoveSource.h"

// Elinor
#include "FairyGarden.h"

//Ninon
#include "MovingWordsSource.h"


//#define GLOBAL_PADDING 80


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
    
        // Tin
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
    
        //Sam
        DepthSquaresSource * depthSquaresSource;
        DepthSquaresSource * depthSquaresSourceInWhiteOutBlack;
        DepthSquaresSource * depthSquaresSourceInBlackOutBlack;
        DepthSquaresSource * depthSquaresSourceNeg;
        vector<FlashSource*> flashSources;
        vector<LineMoveSource*> lineMoveSources;
    
        ParticlesSource * particlesSource0;
        ParticlesSource * particlesSource1;
        ParticlesSource * particlesSource2;
        vector<SimpleLinesSource*> simpleLinesSources;
    
        SquidSource * squidSourceIBOW;
        SquidSource * squidSourceIBOB;
        SquidSource * squidSourceIWOB;
    
        SquidSource * squidSourceNegIBOB;
        SquidSource * squidSourceNegIBOW;
    
        vector<TendrilsSource*> tendrilsSources;
    
        WhiteSource * whiteSource;
        WhiteSource * whiteSourceINOB;
        BlackSource * blackSource;
    
    
        //Elinor
        FairyGarden * fairyGarden;
    
        //Ninon
        MovingWordsSource * movingWordsSource;
};
