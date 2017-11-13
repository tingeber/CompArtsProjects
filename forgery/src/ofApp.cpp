#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(141,148,198);
    
    fadeIn = 255;  // for the animation from original to coded forgery

    picasso.load("picasso.jpg");    // Loading the original image
    
    //  ----------------------
    //  Let's draw the white neck - a straight base with slightly curved sides
    //  I declared "ofpath neck;" in the header, drawing my shape in setup,
    //  and sending it to draw with a simple neck.draw() command
    //  Same for all other parts of the drawing, except for the eyes
    //  I wanted to be fancy with the eyes
    
    neck.setColor(ofColor(223, 220, 218));

    
    // starting from the top, going right
    neck.curveTo(362, 482); // assigning start point twice, because catmull rom
    neck.curveTo(362,482);
    
    neck.curveTo(390,534);
    neck.curveTo(437,606);
    
    neck.curveTo(506,685); // assigning end point twice
    neck.curveTo(506,685);

    // the straight line to the left
    neck.lineTo(210,690);
    
    // curved shape from bottom left to the top, closing the triangle
    neck.curveTo(210,690);
    neck.curveTo(210,690);
    
    neck.curveTo(290,620);
    
    
    neck.curveTo(362,482);
    neck.curveTo(362,482);
    
    //  -------------------
    //  The Moon Face Part
    
    moon.setColor(ofColor(154, 171, 91));
    moon.curveTo(370,100); //top of moon
    moon.curveTo(370,100);
    
    moon.curveTo(408,183);
    moon.curveTo(420,340);
    moon.curveTo(333,463);
    
    moon.curveTo(244, 512);
    moon.curveTo(244, 512);
    
    moon.lineTo(244,512); // bottom of moon
    
    moon.curveTo(244, 512);
    moon.curveTo(244, 512);
    
    moon.curveTo(345,312);
    
    moon.curveTo(370,100);
    moon.curveTo(370,100);

    //  ---------------
    // The Hat
    
    hat.setColor(ofColor(111,67,117));
    
    hat.curveTo(369,100);
    hat.curveTo(369,100);
    
    hat.curveTo(323,191);
    hat.curveTo(268,221);
    hat.curveTo(196,222);
    hat.curveTo(166,195);
    hat.curveTo(180,130);
    hat.curveTo(253,77);
    hat.curveTo(339,58);
    hat.curveTo(394,57);
    hat.curveTo(472,72);
    hat.curveTo(549,125);
    hat.curveTo(561,196);
    hat.curveTo(537,227);
    hat.curveTo(458,206);
    hat.curveTo(415,161);
    
    hat.curveTo(369,100);
    hat.curveTo(369,100);
    
    hat.lineTo(369,100);
    
    
    //  ---------------
    // The Torso
    
    torso.setColor(ofColor(18,40,101));
    
    torso.moveTo(210,690);
    torso.lineTo(506,685);
    
    torso.curveTo(506,685);
    torso.curveTo(506,685);
    
    torso.curveTo(583,751);
    torso.curveTo(632,782);
    
    torso.curveTo(680,800);
    
    torso.curveTo(680,810);
    torso.curveTo(680,810);
    
    torso.lineTo(0,800);
    torso.lineTo(0,785);
    
    torso.curveTo(0,785);
    torso.curveTo(0,785);
    
    torso.curveTo(47,772);
    
    torso.curveTo(210, 690);
    torso.curveTo(210, 690);
    
    // ------------------
    // The hair (all the black hair, not the highlights
    // Starting from bottom left, going clockwise
    
    hair.setColor(ofColor(26,31,24));
    
    hair.curveTo(155,607);
    hair.curveTo(155,607);
    
    hair.curveTo(102,513);
    hair.curveTo(90,381);
    hair.curveTo(106,317);
    hair.curveTo(169,239);
   
    hair.curveTo(370,100);
    hair.curveTo(370,100);
    
    hair.lineTo(423,285);
    hair.lineTo(530,316);
    hair.lineTo(418,382);
    hair.lineTo(457,503);
    hair.lineTo(327,472);
    hair.lineTo(232,435);
    
    hair.curveTo(232,435);
    hair.curveTo(232,435);
    hair.curveTo(223,447);
    
    hair.curveTo(205,599);
    hair.curveTo(205,599);
    
    hair.lineTo(205,599);
   
    hair.curveTo(155,607); // Fin.
   
    //  -----------
    //  THe streaks in the hair
    
    streaks.setFilled(false);
    streaks.setStrokeColor(ofColor(100));
    streaks.setStrokeWidth(3);
    
    //first streak from the left
    streaks.curveTo(162,577);
    streaks.curveTo(162,577);
    streaks.curveTo(143,496);
    streaks.curveTo(136,439);
    streaks.curveTo(142,371);
    streaks.curveTo(162,300);
    streaks.curveTo(162,300);
    
    // second streak
    streaks.moveTo(180,577);
    
    streaks.curveTo(180,577);
    streaks.curveTo(180,577);
    
    streaks.curveTo(179,451);
    
    streaks.curveTo(192,390);
    streaks.curveTo(192,390);
    
    // third streak
    streaks.moveTo(272,252);
    streaks.lineTo(358,243);
    
    
    //  -------------------
    // The streak across the moon
    
    moonstreak.setFilled(false);
    moonstreak.setStrokeWidth(4);
    moonstreak.setStrokeColor(ofColor(45));
    moonstreak.moveTo(355,270);
    moonstreak.lineTo(423,287);
    
    //  --------
    //  The face
    
    face.setColor(ofColor(223, 220, 218));
    
    face.moveTo(242,462);
    face.lineTo(175,261);
    face.lineTo(267,252);
    face.lineTo(278,253);
    face.lineTo(370,274);
    face.lineTo(283,464);
    face.lineTo(242,462);
    
    //  --------
    //  The mouth
    
    mouth.setColor(ofColor(45));
    mouth.setFilled(true);
    
    mouth.curveTo(314,396);
    mouth.curveTo(314,396);
    mouth.curveTo(319,389);
    mouth.curveTo(342,394);
    mouth.curveTo(350,402);
    mouth.curveTo(337,403);
    mouth.curveTo(313,399);
    
    mouth.curveTo(314,396);
    mouth.curveTo(314,396);
    mouth.lineTo(314,396);
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    fadeIn --; // triggers fadeIn of the forgery. Well actually it triggers fade out of the picasso but hey let's not dwell on details.
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //  ------
    //  Let's draw all the bits and pieces! the order is important
    hair.draw();
    streaks.draw();
    face.draw();
    hat.draw();
    moon.draw();
    neck.draw();
    torso.draw();
    moonstreak.draw();
    mouth.draw();
    
    // ------
    // Let's draw the eyes! One is loopy so I used ofDrawEllipse
    eye(240,320, 20, 30);  // left eye
    eye(306, 304, 20, 20);  // right eye
    
    //  ------
    //  Rendering the original on top, so it will gradually fade out
    //  While working on the forgery, I commented out the fadeIn loop
    //  and kept the original at 80 alpha
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, fadeIn);
    picasso.draw(0,0);
    ofDisableAlphaBlending();
    
}

