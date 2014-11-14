//
//  UserInterface.h
//  oscReceiveExample
//
//  Created by jayson on 10/11/14.
//
//

#ifndef __oscReceiveExample__UserInterface__
#define __oscReceiveExample__UserInterface__

#include "ofxGui.h"
#include <iostream>

class UserInterface
{
public:
    void init();
    void draw();
    
    float getFarThreshold();
private:
    
    ofxPanel gui;
	ofxIntSlider farThreshSlider;
    
};
#endif /* defined(__oscReceiveExample__UserInterface__) */
