//
//  UserInterface.cpp
//  oscReceiveExample
//
//  Created by jayson on 10/11/14.
//
//

#include "UserInterface.h"


void UserInterface::init()
{
    gui.setup(); // most of the time you don't need a name
	gui.add(farThreshSlider.setup("far thresh", 147,0 , 255));

}

void UserInterface::draw()
{
    gui.draw();
}

float UserInterface::getFarThreshold()
{
    return farThreshSlider;
}