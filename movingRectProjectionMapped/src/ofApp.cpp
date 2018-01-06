#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = true;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;

	// Add our CustomSource to list of fbo sources of the piMapper
	// FBO sources should be added before piMapper.setup() so the
	// piMapper is able to load the source if it is assigned to
	// a surface in XML settings.
    
    
    // --------------------------------------------
    //  Tin's comments:
    //  Running a bunch of sketches from a single class file;
    //  Took me a while to understand how to make this work
    //  but now I understand classes.
    //  :yasss:
    //
    //  each sketch has a "showDraw" value assigned to it;
    //  most sketches have an "original" and an "alt" version
    //  this was the most tedious home assignment to date
    //  I'm glad I did it, I learned a lot
    //  and got some FBO practice
    //  and learned lots about classes
    //  But it was sssssooo tediiiouuussss
    // --------------------------------------------

    
    // could these be constructed with a for loop? hmm...
    sas1a = new sas1Source();
    piMapper.registerFboSource(sas1a);
    sas1a->setSelector(true);
    sas1a->setShowDraw(0);
    sas1a-> setName("Saskia Pirate 1a");
    
    sas1b = new sas1Source();
    piMapper.registerFboSource(sas1b);
    sas1b->setSelector(false);
    sas1b->setShowDraw(0);
    sas1b-> setName("Saskia Pirate 1b");
    
    sas2a = new sas1Source();
    piMapper.registerFboSource(sas2a);
    sas2a->setSelector(true);
    sas2a->setShowDraw(1);
    sas2a-> setName("Saskia Pirate 2a");
    
    sas2b = new sas1Source();
    piMapper.registerFboSource(sas2b);
    sas2b->setSelector(false);
    sas2b->setShowDraw(1);
    sas2b-> setName("Saskia Pirate 2b");
    
    sas3a = new sas1Source();
    piMapper.registerFboSource(sas3a);
    sas3a->setSelector(true);
    sas3a->setShowDraw(2);
    sas3a-> setName("Saskia Pirate 3a");
    
    sas3b = new sas1Source();
    piMapper.registerFboSource(sas3b);
    sas3b->setSelector(false);
    sas3b->setShowDraw(2);
    sas3b-> setName("Saskia Pirate 3b");
    
    sas4a = new sas1Source();
    piMapper.registerFboSource(sas4a);
    sas4a->setSelector(true);
    sas4a->setShowDraw(3);
    sas4a-> setName("Saskia Pirate 4a");
    
    sas4b = new sas1Source();
    piMapper.registerFboSource(sas4b);
    sas4b->setSelector(false);
    sas4b->setShowDraw(3);
    sas4b-> setName("Saskia Pirate 4b");
    
    sas5a = new sas1Source();
    piMapper.registerFboSource(sas5a);
    sas5a->setSelector(true);
    sas5a->setShowDraw(4);
    sas5a-> setName("Saskia Pirate 5a");
    
    sas5b = new sas1Source();
    piMapper.registerFboSource(sas5b);
    sas5b->setSelector(false);
    sas5b->setShowDraw(4);
    sas5b-> setName("Saskia Pirate 5b");
    
    sas6 = new sas1Source();
    piMapper.registerFboSource(sas6);
    sas6->setSelector(true);
    sas6->setShowDraw(5);
    sas6-> setName("Saskia Pirate 6");

	piMapper.setup();

	// The info layer is hidden by default, press <i> to toggle
	// piMapper.showInfo();
	
	ofSetFullscreen(Settings::instance()->getFullscreen());
	ofSetEscapeQuitsApp(false);

    //dummyObjects.load("dummy-objects.png");
    projMapBg.load("projMapbg.jpg");
}

void ofApp::update(){
	piMapper.update();
}

void ofApp::draw(){
    projMapBg.draw(0,0);
    piMapper.draw();
}

void ofApp::keyPressed(int key){
	piMapper.keyPressed(key);
}

void ofApp::keyReleased(int key){
	piMapper.keyReleased(key);
}

void ofApp::mousePressed(int x, int y, int button){
	piMapper.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	piMapper.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button){
	piMapper.mouseDragged(x, y, button);
}
