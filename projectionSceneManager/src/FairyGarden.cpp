#include "FairyGarden.h"

//--------------------------------------------------------------
void FairyGarden::setup(){
    
    name = "Fairy Garden FBO Source";
    rectColor = ofColor(255);
    // Allocate our FBO source, decide how big it should be
    allocate(1000, 1000);
    ofSetBackgroundColor(255);
    ofSetColor(87,255,167);
    alpha = 20;
    alphaStep = 0.5;
    redAlpha = 20;
    redAlphaStep = 3;
    dmg = 50;
    font.load("arial", 12, true, false, false);
    curtain = 0;
    blueCurtain = 0;
    tick = 0;
    curtainTick = 0;
    mainTime = 0;

    //seed plants
    for(int j = 0; j<6; j++){
        for(int i = 0; i<4; i++){
            groundLoc.push_back(ofRandom(i*50,i*50+40)+25);
            trunk.push_back(0);
            maxTrunk.push_back(ofRandom(50,200));
            cap.push_back(ofRandom(20,40));
            capSize.push_back(0);
            shroomAlpha.push_back(255);
        }
    }

    for(int j = 0; j<4; j++){
        for(int i = 0; i<4; i++){
            sporeLineY.push_back(500-maxTrunk[i]);
            sporeLineX.push_back(groundLoc[i]+ofRandom(0.5-cap[i],cap[i]-0.5));
        }
        for(int i = 8; i<12; i++){
            sporeLineY.push_back(1000-maxTrunk[i]);
            sporeLineX.push_back(groundLoc[i]+ofRandom(0.5-cap[i],cap[i]-0.5));
        }
        for(int i = 16; i<20; i++){
            sporeLineY.push_back(500-maxTrunk[i]);
            sporeLineX.push_back(500+groundLoc[i]+ofRandom(0.5-cap[i],cap[i]-0.5));
        }
        for(int i = 4; i<8; i++){
            sporeLineY.push_back(groundLoc[i]+ofRandom(0.5-cap[i],cap[i]-0.5));
            sporeLineX.push_back(500-maxTrunk[i]);
        }
        for(int i = 12; i<16; i++){
            sporeLineY.push_back(groundLoc[i]+500+ofRandom(0.5-cap[i],cap[i]-0.5));
            sporeLineX.push_back(500-maxTrunk[i]);
        }
        for(int i = 20; i<24; i++){
            sporeLineY.push_back(groundLoc[i]+ofRandom(0.5-cap[i],cap[i]-0.5));
            sporeLineX.push_back(1000-maxTrunk[i]);
        }
    }
    
    for(int i = 0; i<96; i++){
        locX.push_back(sporeLineX[i]);
        locY.push_back(sporeLineY[i]);
        if(ofRandom(5)>=1){
            nature.push_back(0);
        }
        else{
            nature.push_back(1);
        }
        speedX.push_back(ofRandom(1)/10);
        speedY.push_back(0.1-speedX.back());
        if(ofRandom(2)>1){
            speedX[i]*=-1;
        }
        life.push_back(100);
        sporeSize.push_back(0);
        fade.push_back(0);
        explosion.push_back(0);
    }

}
void FairyGarden::reset(){
    //reset is called optionally. if you leave it empty nothing is happening
    rectColor = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}

void FairyGarden::setName(string _name){
    name = _name;
}

void FairyGarden::setColor(ofColor c){
    rectColor = c;
}

// Don't do any drawing here
void FairyGarden::update(){
    time = ofGetFrameNum()*2;
    if(state==1){
        for(int i = 0; i<locX.size(); i++){
            if(life[i]<=0){
                explosion[i]+=0.01;
                speedX[i]=0;
                speedY[i]=0;
            }
            //kill lifeless shapes
            if(explosion[i]>=10){
                locX.erase(locX.begin()+i);
                locY.erase(locY.begin()+i);
                speedX.erase(speedX.begin()+i);
                speedY.erase(speedY.begin()+i);
                nature.erase(nature.begin()+i);
                life.erase(life.begin()+i);
                explosion.erase(explosion.begin()+i);
                fade.erase(fade.begin()+i);
            }
        }
        
        //roll for spawn-deprecated
        //if(ofRandom(20)>=19.99){
        
        //}
        
        //shape actions
        for(int i = 0; i<locX.size(); i++){
            
            //bounds control
            if(locX[i]<=0){
                speedX[i]*=-1;
            }
            if(locY[i]<=0){
                speedY[i]*=-1;
            }
            
            //bottom bound damage
            if(locX[i]>=500 && locY[i]>=500){
                if(locX[i]-speedX[i]<500){
                    speedX[i]*=-1;
                    life[i]-=dmg;
                }
                if(locY[i]-speedY[i]<500){
                    speedY[i]*=-1;
                    life[i]-=dmg;
                }
                
            }
            if(locX[i]>=1000){
                speedX[i]*=-1;
                life[i]-=dmg;
            }
            if(locY[i]>=1000){
                speedY[i]*=-1;
                life[i]-=dmg;
            }
            
            fade[i] = ofMap(life[i], 0, 100, 0, 255);
            
            //transfers for empty square 1 (seams for top cube and centre of bottom cubes)
            if(locX[i]>=250 && locX[i]<=500 && locY[i]>=250 && locY[i]<=500){
                if(locX[i]-speedX[i]<250){
                    locX[i]=locY[i];
                    locY[i]=250;
                    swap = speedY[i];
                    speedY[i]=speedX[i]*-1;
                    speedX[i]=swap;
                }
                if(locY[i]-speedY[i]<250){
                    locY[i]=locX[i];
                    locX[i]=250;
                    swap = speedX[i];
                    speedX[i]=speedY[i]*-1;
                    speedY[i]=swap;
                }
                if(locX[i]-speedX[i]>500){
                    locX[i]=locY[i];
                    locY[i]=500;
                    swap = speedY[i];
                    speedY[i]=speedX[i]*-1;
                    speedX[i]=swap;
                }
                if(locY[i]-speedY[i]>500){
                    locY[i]=locX[i];
                    locX[i]=500;
                    swap = speedX[i];
                    speedX[i]=speedY[i]*-1;
                    speedY[i]=swap;
                }
            }
            
            //transfers for right cube seam
            if(locX[i]>=750 && locY[i]>=250 && locY[i]<=500){
                if(locX[i]-speedX[i]<750){
                    locX[i]=locY[i]+500;
                    locY[i]=250;
                    swap = speedY[i];
                    speedY[i]=speedX[i]*-1;
                    speedX[i]=swap;
                }
                if(locY[i]-speedY[i]<250){
                    locY[i]=locX[i]-500;
                    locX[i]=750;
                    swap = speedX[i];
                    speedX[i]=speedY[i]*-1;
                    speedY[i]=swap;
                }
            }
            
            //transfers for left cube seam
            if(locY[i]>=750 && locX[i]>=250 && locX[i]<=500){
                if(locY[i]-speedY[i]<750){
                    locY[i]=locX[i]+500;
                    locX[i]=250;
                    swap = speedX[i];
                    speedX[i]=speedY[i]*-1;
                    speedY[i]=swap;
                }
                if(locX[i]-speedX[i]<250){
                    locX[i]=locY[i]-500;
                    locY[i]=750;
                    swap = speedY[i];
                    speedY[i]=speedX[i]*-1;
                    speedX[i]=swap;
                }
            }
            
            //membrane saving throws
            if(ofRandom(20)>=(nature[i]*6)+5){
                if(locX[i]<250){
                    for(int s = 250; s<=750; s+=500){
                        if(locY[i]>=s && locY[i]-speedY[i]<s){
                            speedY[i]*=-1;
                        }
                    }
                }
                if(locY[i]<250){
                    for(int s = 250; s<=750; s+=500){
                        if(locX[i]>=s && locX[i]-speedX[i]<s){
                            speedX[i]*=-1;
                        }
                    }
                }
                if(locX[i]>500 && locX[i]<=750 && locY[i]>=250 && locY[i]-speedY[i]<250){
                    speedY[i]*=-1;
                }
            }
            
            //ball moves
            locX[i]+=speedX[i];
            locY[i]+= speedY[i];
            
        }
    }
    
    //wall strobe and ending checker
    if(state==1){
        if(mainTime<20000){
            if(alpha>=250 || alpha<=10){
                alphaStep*=-1;
            }
            if(redAlpha>=250 || redAlpha<=10){
                redAlphaStep*=-1;
            }
            alpha+=alphaStep;
            redAlpha+=redAlphaStep;
        }
        else{
            if(alpha>0 || redAlpha>0){
                alpha-=0.5;
                redAlpha-=3;
            }
            else{
                for(int i = 0; i<locX.size(); i++){
                    if(life[i]<=0){
                        locX.erase(locX.begin()+i);
                        locY.erase(locY.begin()+i);
                        speedX.erase(speedX.begin()+i);
                        speedY.erase(speedY.begin()+i);
                        nature.erase(nature.begin()+i);
                        life.erase(life.begin()+i);
                        explosion.erase(explosion.begin()+i);
                        fade.erase(fade.begin()+i);
                    }
                }
                state=2;
            }
        }
        mainTime++;
    }
    
    noiseStep+=0.001;
    
    if(state==3){
        
        //shroom animation
        for(int i = 0; i<24; i++){
            if(trunk[i]<maxTrunk[i]){
                trunk[i]+=0.1;
            }
            else{
                if(capSize[i]<cap[i]){
                    capSize[i]+=0.01;
                }
                else{
                    for(int j = i; j<96; j+=24){
                        if(sporeSize[j]<4){
                            sporeSize[j]+=0.001;
                        }
                        else{
                            if(shroomAlpha[i]>0){
                                shroomAlpha[i]-=0.05;
                            }
                        }
                    }
                }
            }
        }
        
        //animation completion checker
        bool complete = false;
        for(int i = 0; i<24; i++){
            if(shroomAlpha[i]<=0){
                complete=true;
            }
            else{
                complete=false;
                break;
            }
        }
        if(complete == true){
            state=1;
        }
    }
    
    //text phase
    if(state==2){
        tick++;
        for(int i = 0; i<locX.size(); i++){
            if(nature[i]==0){
                for(int j = 0; j<1000; j+=250){
                    for(int k = 0; k<1000; k+=250){
                        if(locX[i]<125+j && locX[i]>=j && locY[i]<125+k && locY[i]>=k){
                            locX[i]+=0.5;
                            locY[i]+=0.5;
                        }
                        if(locX[i]<250+j && locX[i]>=125+j && locY[i]<125+k && locY[i]>=k){
                            locX[i]-=0.5;
                            locY[i]+=0.5;
                        }
                        if(locX[i]<125+j && locX[i]>=j && locY[i]<250+k && locY[i]>=125+k){
                            locX[i]+=0.5;
                            locY[i]-=0.5;
                        }
                        if(locX[i]<250+j && locX[i]>=125+j && locY[i]<250+k && locY[i]>=125+k){
                            locX[i]-=0.5;
                            locY[i]-=0.5;
                        }
                    }
                }
            }
            
            if(nature[i]==0){
                //top top
                if(locX[i]<250 && locY[i]<250){
                    box[0][0]=1;
                }
                
                //right top
                if(locX[i]>=250 && locX[i]<500 && locY[i]<250){
                    box[0][1]=1;
                }
                
                //left top
                if(locY[i]>=250 && locY[i]<500 && locX[i]<250){
                    box[0][2]=1;
                }
                
                //right top
                if(locX[i]>=500 && locX[i]<750 && locY[i]<250){
                    box[0][3]=1;
                }
                
                //left top
                if(locY[i]>=500 && locY[i]<750 && locX[i]<250){
                    box[0][4]=1;
                }
                
                //right right
                if(locX[i]>=750 && locX[i]<1000 && locY[i]<250){
                    box[0][5]=1;
                }
                
                //left left
                if(locY[i]>=750 && locY[i]<1000 && locX[i]<250){
                    box[0][6]=1;
                }
                
                //left right
                if(locX[i]>=500 && locX[i]<750 && locY[i]<500 && locY[i]>=250){
                    box[0][7]=1;
                }
                
                //right left
                if(locY[i]>=500 && locY[i]<750 && locX[i]<500 && locX[i]>=250){
                    box[0][8]=1;
                }
            }
            if(nature[i]==1){
                //top top
                if(locX[i]<250 && locY[i]<250){
                    box[1][0]=1;
                }
                
                //right top
                if(locX[i]>=250 && locX[i]<500 && locY[i]<250){
                    box[1][1]=1;
                }
                
                //left top
                if(locY[i]>=250 && locY[i]<500 && locX[i]<250){
                    box[1][2]=1;
                }
                
                //right top
                if(locX[i]>=500 && locX[i]<750 && locY[i]<250){
                    box[1][3]=1;
                }
                
                //left top
                if(locY[i]>=500 && locY[i]<750 && locX[i]<250){
                    box[1][4]=1;
                }
                
                //right right
                if(locX[i]>=750 && locX[i]<1000 && locY[i]<250){
                    box[1][5]=1;
                }
                
                //left left
                if(locY[i]>=750 && locY[i]<1000 && locX[i]<250){
                    box[1][6]=1;
                }
                
                //left right
                if(locX[i]>=500 && locX[i]<750 && locY[i]<500 && locY[i]>=250){
                    box[1][7]=1;
                }
                
                //right left
                if(locY[i]>=500 && locY[i]<750 && locX[i]<500 && locX[i]>=250){
                    box[1][8]=1;
                }
            }
        }
        if(tick>1000){
            curtain+=0.1;
        }
        if(curtain>500 && greenFade<255){
            greenFade+=0.1;
        }
        if(greenFade>=255){
            for(int i = 0; i<locX.size(); i++){
                if(nature[i]==1){
                    for(int j = 0; j<1000; j+=250){
                        for(int k = 0; k<1000; k+=250){
                            if(locX[i]<125+j && locX[i]>=j && locY[i]<125+k && locY[i]>=k){
                                if(locX[i]<locY[i]){
                                    locX[i]+=0.5;
                                    locY[i]+=0.5;
                                }
                                else{
                                    locY[i]+=0.5;
                                    locX[i]+=0.5;
                                }
                            }
                            if(locX[i]<250+j && locX[i]>=125+j && locY[i]<125+k && locY[i]>=k){
                                if(locX[i]>-locY[i]){
                                    locX[i]-=0.5;
                                    locY[i]+=0.5;
                                }
                                else{
                                    locY[i]+=0.5;
                                    locX[i]-=0.5;
                                }
                            }
                            if(locX[i]<125+j && locX[i]>=j && locY[i]<250+k && locY[i]>=125+k){
                                if(-locX[i]<locY[i]){
                                    locX[i]+=0.5;
                                    locY[i]-=0.5;
                                }
                                else{
                                    locY[i]-=0.5;
                                    locX[i]+=0.5;
                                }
                            }
                            if(locX[i]<250+j && locX[i]>=125+j && locY[i]<250+k && locY[i]>=125+k){
                                if(-locX[i]>-locY[i]){
                                    locX[i]-=0.5;
                                    locY[i]-=0.5;
                                }
                                else{
                                    locY[i]-=0.5;
                                    locX[i]-=0.5;
                                }
                            }
                        }
                    }
                }
                else{
                    fade[i]--;
                }
            }
            curtainTick++;
        }
        if(curtainTick>1000){
            blueCurtain+=0.1;
        }
        if(blueCurtain>125){
            blueFade+=0.1;
            for(int i = 0; i<locX.size(); i++){
                fade[i]-=0.1;
            }
        }
    }
    cout<<curtain<<endl;
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void FairyGarden::draw(){
    ofClear(0); //clear the buffer
    
    //do it with static values
    //since the buffer is 500x500, then...
    //drawMovingRect(250, 250, 500, 500);
    
    //or pass it dynamic values (ie. ask the fbo how big it is)
    drawMovingRect(fbo->getWidth()/2, fbo->getHeight()/2, fbo->getWidth(), fbo->getHeight(), time);
}

void FairyGarden::drawMovingRect(int x, int y, int w, int h, float time){
    //draw background
    ofPushStyle();
    ofSetColor(0);
    ofDrawRectangle(0,0,250,250);
    ofDrawRectangle(250,0,250,250);
    ofDrawRectangle(0,250,250,250);
    ofDrawRectangle(500,0,250,250);
    ofDrawRectangle(750,0,250,250);
    ofDrawRectangle(0,500,250,250);
    ofDrawRectangle(0,750,250,250);
    ofDrawRectangle(500,250,250,250);
    ofDrawRectangle(250,500,250,250);
    ofPopStyle();
    
    if(state==1 || state==2){
        //draw membrane
        ofPushStyle();
        ofSetColor(87,255,167,alpha);
        ofSetLineWidth(5);
        ofNoFill();
        ofDrawRectangle(0,0,250,250);
        ofDrawRectangle(250,0,250,250);
        ofDrawRectangle(0,250,250,250);
        ofDrawRectangle(500,0,250,250);
        ofDrawRectangle(750,0,260,250);//no right edge
        ofDrawRectangle(0,500,250,250);
        ofDrawRectangle(0,750,250,260);//no bottom edge
        //ofDrawRectangle(500,250,250,250);//no right edge
        ofDrawLine(750,250,750,500);
        ofDrawLine(500,250,500,500);
        //ofDrawRectangle(250,500,250,250);//no bottom edge
        ofDrawLine(250,500,500,500);
        ofDrawLine(250,750,500,750);
        ofPopStyle();
        
        //draw bottom strobe
        ofPushStyle();
        ofSetLineWidth(5);
        ofSetColor(255,0,0,redAlpha);
        ofDrawLine(0,1000,250,1000);
        ofDrawLine(500,500,500,750);
        ofDrawLine(500,500,750,500);
        ofDrawLine(1000,0,1000,250);
        ofPopStyle();
    }
    
    if(state==2){
        
        //BLUE
        if(blueCurtain>0 && blueFade<255){
            ofSetColor(50,150,255,255-blueFade);
            
            //top top
            if(box[1][0]==1){
                ofPushMatrix();
                ofRotate(-45);
                font.drawString("I mean obviously YOU'RE okay\n"
                                "it's the ones that rub your\n"
                                "nose in it I can't stand", -90,160);
                ofPopMatrix();
            }
            
            //right top
            if(box[1][1]==1){
                ofPushMatrix();
                ofRotate(-90);
                font.drawString("What's so much more\n"
                                "interesting on your phone\n"
                                "than talking to your family? ", -220, 355);
                ofPopMatrix();
            }
            
            //left top
            if(box[1][2]==1){
                font.drawString("If you don't get on\n"
                                "with her why are you\n"
                                "still with her?", 30, 355);
            }
            
            //right top
            if(box[1][3]==1){
                ofPushMatrix();
                ofRotate(-45);
                font.drawString("You can do whatever you like in\n"
                                "your house but while you're under\n"
                                "my roof you'll behave like a lady", 270,522);
                ofPopMatrix();
            }
            
            //left top
            if(box[1][4]==1){
                ofPushMatrix();
                ofRotate(-45);
                font.drawString("Is your 'friend' coming?", -450,522);
                ofPopMatrix();
            }
            
            //right right
            if(box[1][5]==1){
                ofPushMatrix();
                ofRotate(-90);
                font.drawString("Well when you take starting a\n"
                                "family more seriously we might be\n"
                                "more willing to support you", -220, 855);
                ofPopMatrix();
            }
            
            //left left
            if(box[1][6]==1){
                font.drawString("Do you think it didn't work\n"
                                "out because you actually\n"
                                "like boys?", 30, 855);
            }
            
            //left right
            if(box[1][7]==1){
                font.drawString("So you want a one bedroom\n"
                                "flat, but for both of you?", 530, 355);
            }
            
            //right left
            if(box[1][8]==1){
                ofPushMatrix();
                ofRotate(-90);
                font.drawString("I'm sorry, the flat has\n"
                                "been taken. Yes, since\n"
                                "this morning.", -720, 355);
                ofPopMatrix();
            }
            
            //draw BLUE curtains
            if(blueCurtain<125){
                ofPushStyle();
                ofFill();
                ofSetColor(0,0,0,255);
                ofDrawRectangle(0,250,125-blueCurtain,250);
                ofDrawRectangle(0,750,125-blueCurtain,250);
                ofDrawRectangle(125+blueCurtain,250,125-blueCurtain,250);
                ofDrawRectangle(125+blueCurtain,750,125-blueCurtain,250);
                ofDrawRectangle(500,250,125-blueCurtain,250);
                ofDrawRectangle(625+blueCurtain,250,125-blueCurtain,250);
                ofDrawRectangle(250,500,250,125-blueCurtain);
                ofDrawRectangle(250,625+blueCurtain,250,125-blueCurtain);
                ofDrawRectangle(250,0,250,125-blueCurtain);
                ofDrawRectangle(750,0,250,125-blueCurtain);
                ofDrawRectangle(250,125+blueCurtain,250,125-blueCurtain);
                ofDrawRectangle(750,125+blueCurtain,250,125-blueCurtain);
                ofDrawTriangle(0,blueCurtain*2,250-blueCurtain*2,250,0,250);
                ofDrawTriangle(blueCurtain*2,0,250,250-blueCurtain*2,250,0);
                ofDrawTriangle(500,blueCurtain*2,750-blueCurtain*2,250,500,250);
                ofDrawTriangle(blueCurtain*2,500,250,750-blueCurtain*2,250,500);
                ofDrawTriangle(0,500+blueCurtain*2,250-blueCurtain*2,750,0,750);
                ofDrawTriangle(500+blueCurtain*2,0,750,250-blueCurtain*2,750,0);
                ofPopStyle();
            }
        }
        
        
        //GREEN
        if(curtainTick<800 && greenFade<255){
            //top top
            ofPushStyle();
            ofSetColor(87,255,167, 255-greenFade);
            if(box[0][0]==1){
                ofPushMatrix();
                ofRotate(-45);
                font.drawString("It's so nice you stayed local\n"
                                "so we could support you,\n"
                                "family is so important", -90,160);
                ofPopMatrix();
            }
            
            //right top
            if(box[0][1]==1){
                ofPushMatrix();
                ofRotate(-90);
                font.drawString("So when's he popping the\n"
                                "question? I can't wait to\n"
                                "welcome him into the family!", -220, 355);
                ofPopMatrix();
            }
            
            //left top
            if(box[0][2]==1){
                font.drawString("Well we did save some of it\n"
                                "but mum and dad helped out too", 30, 355);
            }
            
            //right top
            if(box[0][3]==1){
                ofPushMatrix();
                ofRotate(-45);
                font.drawString("Boyfriend sounds so juvenile\n"
                                "You know it's really serious when\n"
                                "you can say fiancee or husband", 270,522);
                ofPopMatrix();
            }
            
            //left top
            if(box[0][4]==1){
                ofPushMatrix();
                ofRotate(-45);
                font.drawString("We'll come and see you every\n"
                                "day until the hospital releases\n"
                                "you. You'll be fine", -450,522);
                ofPopMatrix();
            }
            
            //right right
            if(box[0][5]==1){
                ofPushMatrix();
                ofRotate(-90);
                font.drawString("For such an adorable couple\n"
                                "I'm sure we can work\n"
                                "something out", -220, 855);
                ofPopMatrix();
            }
            
            //left left
            if(box[0][6]==1){
                font.drawString("I knew you'd fit right in\n"
                                "here as soon as you came\n"
                                "can in for the interview", 30, 855);
            }
            
            //left right
            if(box[0][7]==1){
                font.drawString("I'm sure you can work it out\n"
                                "you're so good for each other!", 530, 355);
            }
            
            //right left
            if(box[0][8]==1){
                ofPushMatrix();
                ofRotate(-90);
                font.drawString("Why don't you move back\n"
                                "in with us? Just until you\n"
                                "get back on your feet.", -720, 355);
                ofPopMatrix();
            }
            ofPopStyle();
        }
        
        //draw GREEN curtains
        if(curtain<125){
            ofPushStyle();
            ofFill();
            ofSetColor(0,0,0,255);
            ofDrawRectangle(0,250,125-curtain,250);
            ofDrawRectangle(0,750,125-curtain,250);
            ofDrawRectangle(125+curtain,250,125-curtain,250);
            ofDrawRectangle(125+curtain,750,125-curtain,250);
            ofDrawRectangle(500,250,125-curtain,250);
            ofDrawRectangle(625+curtain,250,125-curtain,250);
            ofDrawRectangle(250,500,250,125-curtain);
            ofDrawRectangle(250,625+curtain,250,125-curtain);
            ofDrawRectangle(250,0,250,125-curtain);
            ofDrawRectangle(750,0,250,125-curtain);
            ofDrawRectangle(250,125+curtain,250,125-curtain);
            ofDrawRectangle(750,125+curtain,250,125-curtain);
            ofDrawTriangle(0,curtain*2,250-curtain*2,250,0,250);
            ofDrawTriangle(curtain*2,0,250,250-curtain*2,250,0);
            ofDrawTriangle(500,curtain*2,750-curtain*2,250,500,250);
            ofDrawTriangle(curtain*2,500,250,750-curtain*2,250,500);
            ofDrawTriangle(0,500+curtain*2,250-curtain*2,750,0,750);
            ofDrawTriangle(500+curtain*2,0,750,250-curtain*2,750,0);
            ofPopStyle();
        }
    }
    
    //particles
    for(int i = 0; i<locX.size(); i++){
        if(state==1 || state==2){
            if(nature[i] == 0){
                if(fade[i]>0){
                    ofPushStyle();
                    ofPushMatrix();
                    ofTranslate(locX[i],locY[i]);
                    ofSetColor(ofMap(fade[i],0,255,0,87),fade[i],ofMap(fade[i],0,255,0,167)-greenFade/10);
                    ofDrawCircle(0,0,3);
                    ofSetColor(ofMap(fade[i],0,255,0,50),ofMap(fade[i],0,255,0,220),ofMap(fade[i],0,255,0,80)-greenFade/10);
                    for(int j = 0; j<6; j++){
                        ofRotate(360/6);
                        ofDrawCircle(0,1+ofNoise(noiseStep+(i*50)+(j*50))*4,2);
                    }
                    ofPopMatrix();
                    ofPopStyle();
                }
            }
            else{
                ofPushStyle();
                ofPushMatrix();
                ofTranslate(locX[i],locY[i]);
                ofSetColor(ofMap(fade[i],0,255,0,50),ofMap(fade[i],0,255,0,150),ofMap(fade[i],0,255,0,255)-blueFade/10);
                ofDrawCircle(0,0,3);
                ofSetColor(ofMap(fade[i],0,255,0,50),ofMap(fade[i],0,255,0,100),ofMap(fade[i],0,255,0,230)-blueFade/10);
                for(int j = 0; j<6; j++){
                    ofRotate(360/6);
                    ofDrawCircle(0,1+ofNoise(noiseStep+(i*50)+(j*50))*4,2);
                }
                ofPopMatrix();
                ofPopStyle();
            }
            if(explosion[i]>0 && state==1){
                ofPushStyle();
                ofSetColor(255,0,0,ofMap(explosion[i],0,10,255,0));
                ofDrawCircle(locX[i], locY[i], explosion[i]*3.5);
                ofSetColor(255,255,0,ofMap(explosion[i],0,10,255,0));
                ofDrawCircle(locX[i], locY[i], explosion[i]*3);
                ofPopStyle();
            }
        }
    }
    
    //mushroom growth
    if(state==3){
        ofPushStyle();
        for(int i = 0; i<96; i++){
            if(nature[i]==0){
                ofSetColor(87,255,167);
            }
            else{
                ofSetColor(50,150,255);
            }
            ofDrawCircle(sporeLineX[i], sporeLineY[i], sporeSize[i]);
        }
        ofSetLineWidth(2);
        for(int i = 0; i<4; i++){
            ofSetColor(255, 255, 255, shroomAlpha[i]);
            ofDrawLine(groundLoc[i],500,groundLoc[i],500-trunk[i]);
            if(trunk[i]>=maxTrunk[i]){
                ofDrawCurve(groundLoc[i]-capSize[i], 500+capSize[i]*3-trunk[i], groundLoc[i]-capSize[i], 500-trunk[i], groundLoc[i]+capSize[i], 500-trunk[i], groundLoc[i]+capSize[i], 500+capSize[i]*3-trunk[i]);
            }
        }
        for(int i = 4; i<8; i++){
            ofSetColor(255, 255, 255, shroomAlpha[i]);
            ofDrawLine(500, groundLoc[i], 500-trunk[i], groundLoc[i]);
            if(trunk[i]>=maxTrunk[i]){
                ofDrawCurve(500+capSize[i]*3-trunk[i], groundLoc[i]-capSize[i], 500-trunk[i], groundLoc[i]-capSize[i], 500-trunk[i], groundLoc[i]+capSize[i], 500+capSize[i]*3-trunk[i], groundLoc[i]+capSize[i]);
            }
        }
        for(int i = 8; i<12; i++){
            ofSetColor(255, 255, 255, shroomAlpha[i]);
            ofDrawLine(groundLoc[i], 1000, groundLoc[i], 1000-trunk[i]);
            if(trunk[i]>=maxTrunk[i]){
                ofDrawCurve(groundLoc[i]-capSize[i], 1000+capSize[i]*3-trunk[i], groundLoc[i]-capSize[i], 1000-trunk[i], groundLoc[i]+capSize[i], 1000-trunk[i], groundLoc[i]+capSize[i], 1000+capSize[i]*3-trunk[i]);
            }
        }
        for(int i = 12; i<16; i++){
            ofSetColor(255, 255, 255, shroomAlpha[i]);
            ofDrawLine(500, groundLoc[i]+500, 500-trunk[i],groundLoc[i]+500);
            if(trunk[i]>=maxTrunk[i]){
                ofDrawCurve(500+capSize[i]*3-trunk[i], groundLoc[i]+500-capSize[i], 500-trunk[i], groundLoc[i]+500-capSize[i], 500-trunk[i], groundLoc[i]+500+capSize[i], 500+capSize[i]*3-trunk[i], groundLoc[i]+500+capSize[i]);
            }
        }
        for(int i = 16; i<20; i++){
            ofSetColor(255, 255, 255, shroomAlpha[i]);
            ofDrawLine(500+groundLoc[i], 500, groundLoc[i]+500, 500-trunk[i]);
            if(trunk[i]>=maxTrunk[i]){
                ofDrawCurve(groundLoc[i]+500-capSize[i], 500+capSize[i]*3-trunk[i], groundLoc[i]+500-capSize[i], 500-trunk[i], groundLoc[i]+500+capSize[i], 500-trunk[i], groundLoc[i]+500+capSize[i], 500+capSize[i]*3-trunk[i]);
            }
        }
        for(int i = 20; i<24; i++){
            ofSetColor(255, 255, 255, shroomAlpha[i]);
            ofDrawLine(1000, groundLoc[i], 1000-trunk[i], groundLoc[i]);
            if(trunk[i]>=maxTrunk[i]){
                ofDrawCurve(1000+capSize[i]*3-trunk[i], groundLoc[i]-capSize[i], 1000-trunk[i], groundLoc[i]-capSize[i], 1000-trunk[i], groundLoc[i]+capSize[i], 1000+capSize[i]*3-trunk[i], groundLoc[i]+capSize[i]);
            }
        }
        ofPopStyle();
    }
}

