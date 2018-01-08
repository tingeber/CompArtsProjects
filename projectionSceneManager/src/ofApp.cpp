#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = true;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;
    
    incompetence1 = new Incompetence();
    incompetence1->setup();
    piMapper.registerFboSource(incompetence1);
    incompetence1->setName("Inc 1");
    incompetence1->setStartPos(400);
    
    incompetence2 = new Incompetence();
    incompetence2->setup();
    piMapper.registerFboSource(incompetence2);
    incompetence2->setName("Inc 2");
    incompetence2->setStartPos(555);
    
    incompetence3 = new Incompetence();
    incompetence3->setup();
    piMapper.registerFboSource(incompetence3);
    incompetence3->setName("Inc 3");
    incompetence3->setStartPos(340);
    
    
    consciousCompetence = new ConsciousCompetence();
    consciousCompetence->setup();
    piMapper.registerFboSource(consciousCompetence);
    
    
    unconsciousCompetence1 = new UnconsciousCompetence();
    unconsciousCompetence1->setup();
    piMapper.registerFboSource(unconsciousCompetence1);
    unconsciousCompetence1->setName("Unc Comp 1");
    unconsciousCompetence1->setStartPos(400);
    
    unconsciousCompetence2 = new UnconsciousCompetence();
    unconsciousCompetence2->setup();
    piMapper.registerFboSource(unconsciousCompetence2);
    unconsciousCompetence2->setName("Unc Comp 2");
    unconsciousCompetence2->setStartPos(555);
    
    unconsciousCompetence3 = new UnconsciousCompetence();
    unconsciousCompetence3->setup();
    piMapper.registerFboSource(unconsciousCompetence3);
    unconsciousCompetence3->setName("Unc Comp 3");
    unconsciousCompetence3->setStartPos(340);
    
    conflictingResolutions = new ConflictingResolutions();
    conflictingResolutions->setup();
    piMapper.registerFboSource(conflictingResolutions);
    
 
    
    piMapper.setup();

	// The info layer is hidden by default, press <i> to toggle
	// piMapper.showInfo();
	
	ofSetFullscreen(Settings::instance()->getFullscreen());
	ofSetEscapeQuitsApp(false);

    cubeIso.load("cube-iso.png");

    //setup sceneManager to handle scene/present changes automatically
    sceneManager.setup("scenes.json", &piMapper);
}

void ofApp::update(){
	piMapper.update();
    sceneManager.update();
}

void ofApp::draw(){
    cubeIso.draw(200,200);
    piMapper.draw();
}

void ofApp::keyPressed(int key){
    //press 5 to go to previous preset (scene)
    if (key=='5') {
        if (piMapper.getNumPresets()>1){
            int targetScene = piMapper.getActivePresetIndex() - 1;
            if (targetScene<0) targetScene = piMapper.getNumPresets()-1;
            piMapper.setPreset(targetScene);
            cout << "Switched to preset: " << piMapper.getActivePresetIndex() << endl;
        } else cout << "only one preset available" << endl;
    }
    //press 6 to go to next preset (scene)
    else if (key=='6') {
        if (piMapper.getNumPresets()>1){
            piMapper.setNextPreset();
            cout << "Switched to preset: " << piMapper.getActivePresetIndex() << endl;
        } else cout << "only one preset available" << endl;
    }
    else if (key == '7'){
        piMapper.cloneActivePreset();
        piMapper.setPreset(piMapper.getNumPresets()-1);
        cout << "Cloned and switched to preset: " << piMapper.getActivePresetIndex() << endl;
    }

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
