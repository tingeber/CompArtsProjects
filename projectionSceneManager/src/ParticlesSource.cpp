#include "ParticlesSource.h"

void ParticlesSource::setup(){
    AbstractSource::setup();
//    name = "Particles Source";

    allocate(800, 800);
    ofBackground(c_min);
    
    for(int i=0 ; i < part_count ; i++) {
        
        float r_x = ofRandom(fbo->getWidth());
        float r_y = ofRandom(fbo->getHeight());
        if(i%4 == 0) {
            positions.push_back(ofPoint(r_x, 0));
        } else if(i%4==1) {
            positions.push_back(ofPoint(r_x, fbo->getHeight()));
        } else if(i%4==2) {
            positions.push_back(ofPoint(0, r_y));
        } else {
            positions.push_back(ofPoint(fbo->getWidth(), r_y));
        }
        
        //        positions.push_back(ofPoint(fbo->getWidth()()/2.0, fbo->getHeight()()/2.0));
        //        positions.push_back(ofPoint(ofRandom(fbo->getWidth()()), ofRandom(fbo->getHeight()())));
        
        vels.push_back(ofPoint(ofRandom(-vel_max, vel_max), ofRandom(-vel_max, vel_max)));
        //        vels.push_back(ofPoint(0,0));
        accs.push_back(ofPoint(0,0));
    }
    
    
}

void ParticlesSource::reset(){
    AbstractSource::reset();
    //reset is called optionally. if you leave it empty nothing is happening
//    rectColor = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
    // setup
    has_triggered = false;
    positions.clear();
    vels.clear();
    accs.clear();
    for(int i=0 ; i < part_count ; i++) {
        
        float r_x = ofRandom(fbo->getWidth());
        float r_y = ofRandom(fbo->getHeight());
        if(i%4 == 0) {
            positions.push_back(ofPoint(r_x, 0));
        } else if(i%4==1) {
            positions.push_back(ofPoint(r_x, fbo->getHeight()));
        } else if(i%4==2) {
            positions.push_back(ofPoint(0, r_y));
        } else {
            positions.push_back(ofPoint(fbo->getWidth(), r_y));
        }
        
        //        positions.push_back(ofPoint(fbo->getWidth()()/2.0, fbo->getHeight()()/2.0));
        //        positions.push_back(ofPoint(ofRandom(fbo->getWidth()()), ofRandom(fbo->getHeight()())));
        
        vels.push_back(ofPoint(ofRandom(-vel_max, vel_max), ofRandom(-vel_max, vel_max)));
        //        vels.push_back(ofPoint(0,0));
        accs.push_back(ofPoint(0,0));
    }

}

void ParticlesSource::setParticleCount(int _part_count) {
    part_count = _part_count;
}

void ParticlesSource::setMode(int _part_mode) {
    mode = _part_mode;
}

void ParticlesSource::trigger_edge_run(float after) {
    trigger_time = after;
}

// Don't do any drawing here
void ParticlesSource::update(){
    AbstractSource::update();
    
    if(!has_triggered) {
        float timeMillis = ofGetElapsedTimeMillis()-startTime;
        if(timeMillis > trigger_time) {
            trigger_edge_run();
            has_triggered = true;
        }
    }
    
    float t = ofGetFrameNum() / 100.0;
    for(int i=0 ; i < part_count ; i++) {
        
        //update velocities
        vels[i] += accs[i] * 0.01;
        
        // check for turn arounds
        if(positions[i].x < 0) {
            if(bounce) {
                vels[i].x = abs(vels[i].x);
            } else {
                vels[i] = ofPoint(0,0);
            }
        }
        if(positions[i].x > fbo->getWidth()) {
            if(bounce) {
                vels[i].x = -abs(vels[i].x);
            } else {
                vels[i] = ofPoint(0,0);
            }
        }
        if(positions[i].y < 0) {
            if(bounce) {
                vels[i].y = abs(vels[i].y);
            } else {
                vels[i] = ofPoint(0,0);
            }
        }
        if(positions[i].y > fbo->getHeight()) {
            if(bounce) {
                vels[i].y = -abs(vels[i].y);
            } else {
                vels[i] = ofPoint(0,0);
            }
        }
        
        // update positions
        positions[i] += vels[i];
        
    }
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void ParticlesSource::draw(){
    ofClear(0); //clear the buffer
    ofPushStyle();
    ofSetColor(c_max);
    
    switch(mode) {
        case P_MODE_BALLS:
            draw_particle_balls();
            break;
        case P_MODE_SQUIGGLE1:
            draw_particle_squiggle_1();
            break;
        case P_MODE_SQUIGGLE2:
            draw_particle_squiggle_2();
            break;
        case P_MODE_SQUIGGLE3:
            draw_particle_squiggle_3();
            break;
        case P_MODE_MESH:
            draw_particle_mesh();
            break;
        case P_MODE_LINES1:
            draw_particle_lines_1();
            break;
        case P_MODE_LINES2:
            draw_particle_lines_2();
            break;
        case P_MODE_LINES3:
            draw_particle_lines_3();
            break;
        case P_MODE_CORNER_WEB:
            draw_corner_web();
            break;
        case P_MODE_CORNER_FLARES:
            draw_corner_flares();
            break;
        case P_MODE_GRID_WEB:
            draw_grid_web();
            break;
        case P_MODE_GRID_FLARES:
            draw_grid_flares();
            break;
        case P_MODE_GRID_FLARES_PULSE:
            draw_grid_flares_pulse();
            break;
        default:
            draw_particle_mesh();
    }
    
    ofPopStyle();
}

void ParticlesSource::draw_grid_web() {
    float count = 4;
    float spacing = fbo->getWidth() / count;
    float start = spacing/2.0;
    for(int i=0 ; i < count ; i++) {
        for(int j=0 ; j < count ; j++) {
            float x = start + i*spacing;
            float y = start + j*spacing;
            for(int k = 0 ; k < part_count ; k++) {
                ofDrawLine(x,y,positions[k].x,positions[k].y);
            }
        }
    }
}

void ParticlesSource::draw_grid_flares() {
    float count = 4;
    float spacing = fbo->getWidth() / count;
    float start = spacing/2.0;
    for(int i=0 ; i < count ; i++) {
        for(int j=0 ; j < count ; j++) {
            float x = start + i*spacing;
            float y = start + j*spacing;
            for(int k = 0 ; k < part_count ; k++) {
                // if it is close enough draw a line
                ofPoint delta = ofPoint(x,y) - positions[k];
                float dist = sqrt(delta.x*delta.x + delta.y*delta.y);
                if(dist < spacing*2.5) {
                    ofDrawLine(x,y,positions[k].x,positions[k].y);
                }
            }
        }
    }
}

void ParticlesSource::draw_grid_flares_pulse() {
    float t = ofGetFrameNum() / 200.0;
    float count = 5;
    float spacing = fbo->getWidth() / count;
    float start = spacing/2.0;
    for(int i=0 ; i < count ; i++) {
        for(int j=0 ; j < count ; j++) {
            float x = start + i*spacing + ofMap(ofNoise(t,i),0,1,-start,start);
            float y = start + j*spacing + ofMap(ofNoise(t+20,j),0,1,-start,start);
            for(int k = 0 ; k < part_count ; k++) {
                // if it is close enough draw a line
                ofPoint delta = ofPoint(x,y) - positions[k];
                float dist = sqrt(delta.x*delta.x + delta.y*delta.y);
                if(dist < spacing*2.5) {
                    ofDrawLine(x,y,positions[k].x,positions[k].y);
                }
            }
        }
    }
}

void ParticlesSource::draw_corner_web() {
    for(int i=0 ; i< part_count ; i++) {
        ofDrawLine(positions[i].x, positions[i].y, 0, 0);
        ofDrawLine(positions[i].x, positions[i].y, fbo->getWidth(), 0);
        ofDrawLine(positions[i].x, positions[i].y, 0, fbo->getHeight());
        ofDrawLine(positions[i].x, positions[i].y, fbo->getWidth(), fbo->getHeight());
    }
}

void ParticlesSource::draw_corner_flares() {
    for(int i=0 ; i< part_count ; i++) {
        // find nearest corner
        float corner_x = (positions[i].x < fbo->getWidth()/2.0) ? 0.0 : fbo->getWidth();
        float corner_y = (positions[i].y < fbo->getHeight()/2.0) ? 0.0 : fbo->getHeight();
        
        // draw line to it
        ofDrawLine(positions[i].x, positions[i].y, corner_x, corner_y);
    }
}

void ParticlesSource::draw_particle_mesh() {
    for(int i=0 ; i < part_count ; i++) {
        for(int j=i ; j < part_count ; j++) {
            ofPoint delta = positions[i] - positions[j];
            float dist = sqrt(delta.x*delta.x + delta.y*delta.y);
            if(dist < 300.0) {
                ofPushStyle();
                ofDrawLine(positions[i].x, positions[i].y, positions[j].x, positions[j].y);
                ofPopStyle();
            }
        }
    }
}

void ParticlesSource::draw_particle_squiggle_1() {
    ofPushStyle();
    ofSetColor(c_max);
    ofPolyline line;
    for(int i=0 ; i < part_count ; i++) {
        line.curveTo(positions[i]);
    }
    line.close();
    line.draw();
    ofPopStyle();
}

void ParticlesSource::draw_particle_squiggle_2() {
    ofPushStyle();
    ofSetColor(c_max);
    ofPolyline line;
    for(int i=0 ; i < part_count ; i+=2) {
        line.curveTo(positions[i]);
    }
    for(int i=1 ; i < part_count ; i+=2) {
        line.curveTo(positions[i]);
    }
    line.close();
    line.draw();
    ofPopStyle();
}

void ParticlesSource::draw_particle_squiggle_3() {
    ofPushStyle();
    ofSetColor(c_max);
    ofPolyline line;
    for(int i=0 ; i < part_count ; i+=3) {
        line.curveTo(positions[i]);
    }
    for(int i=1 ; i < part_count ; i+=3) {
        line.curveTo(positions[i]);
    }
    for(int i=2 ; i < part_count ; i+=3) {
        line.curveTo(positions[i]);
    }
    line.close();
    line.draw();
    ofPopStyle();
}

void ParticlesSource::draw_particle_lines_1() {
    ofPushStyle();
    ofSetColor(c_max);
    
    for(int i=0 ; i < part_count ; i++) {
        ofDrawLine(positions[i].x, positions[i].y, positions[(i+1)%positions.size()].x, positions[(i+1)%positions.size()].x);
    }
    
    ofPopStyle();
}

void ParticlesSource::draw_particle_lines_2() {
    ofPushStyle();
    ofSetColor(c_max);
    for(int i=0 ; i < part_count ; i+=2) {
        ofDrawLine(positions[i].x, positions[i].y, positions[(i+2)%positions.size()].x, positions[(i+2)%positions.size()].x);
    }
    for(int i=1 ; i < part_count ; i+=2) {
        ofDrawLine(positions[i].x, positions[i].y, positions[(i+2)%positions.size()].x, positions[(i+2)%positions.size()].x);
    }
    ofPopStyle();
}

void ParticlesSource::draw_particle_lines_3() {
    ofPushStyle();
    ofSetColor(c_max);
    for(int i=0 ; i < part_count ; i+=3) {
        ofDrawLine(positions[i].x, positions[i].y, positions[(i+3)%positions.size()].x, positions[(i+3)%positions.size()].x);
    }
    for(int i=1 ; i < part_count ; i+=3) {
        ofDrawLine(positions[i].x, positions[i].y, positions[(i+3)%positions.size()].x, positions[(i+3)%positions.size()].x);
    }
    for(int i=2 ; i < part_count ; i+=3) {
        ofDrawLine(positions[i].x, positions[i].y, positions[(i+3)%positions.size()].x, positions[(i+3)%positions.size()].x);
    }
    ofPopStyle();
}

void ParticlesSource::draw_particle_balls() {
    ofPushStyle();
    ofSetColor(c_max);
    for(int i=0 ; i < part_count ; i++) {
        ofDrawCircle(positions[i].x, positions[i].y, part_size);
    }
    ofPopStyle();
}

void ParticlesSource::trigger_edge_run(){
    
    bounce = false;
    float w = fbo->getWidth();
    float h = fbo->getHeight();
    for(int i=0 ; i < vels.size() ; i++) {
        float a = positions[i].x;
        float b = positions[i].y;
        float c = h-b;
        float d = w-a;
        float m = min(min(min(a,b),c),d);
        float fac = 0.1;
        if(m==a) {
            accs[i] = ofPoint(-1,0);
            vels[i] += ofPoint(-1,0) * fac;
        } else if(m==b) {
            accs[i] = ofPoint(0,-1);
            vels[i] += ofPoint(0,-1) * fac;
        } else if(m==c) {
            accs[i] = ofPoint(0,1);
            vels[i] += ofPoint(0,1) * fac;
        } else {
            accs[i] = ofPoint(1,0);
            vels[i] += ofPoint(1,0) * fac;
        }
        
    }
    
}

