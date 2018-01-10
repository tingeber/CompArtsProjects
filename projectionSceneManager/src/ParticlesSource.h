#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "AbstractSource.h"
#include "Macros.h"

class ParticlesSource : public AbstractSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
    
        float time;
    
        void setParticleCount(int _part_count);
        void setMode(int _part_mode);
    
        float vel_max {1.0};
    
        int part_count {100};
        float part_size {10.0};
        vector<ofPoint> positions;
        vector<ofPoint> vels;
        vector<ofPoint> accs;
    
        void draw_particle_squiggle_1();
        void draw_particle_squiggle_2();
        void draw_particle_squiggle_3();
        void draw_particle_lines_1();
        void draw_particle_lines_2();
        void draw_particle_lines_3();
        void draw_particle_balls();
        void draw_particle_mesh();
        void draw_corner_flares();
        void draw_corner_web();
        void draw_grid_web();
        void draw_grid_flares();
        void draw_grid_flares_pulse();
    
        int mode {P_MODE_BALLS};
    
        void trigger_edge_run(float after);
        float trigger_time {-1};
    
        void trigger_edge_run();
        bool has_triggered {false};
    
        bool bounce {true};
    
    
};
