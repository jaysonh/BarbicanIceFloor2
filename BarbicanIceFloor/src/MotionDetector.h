//
//  MotionDetector.h
//  oscReceiveExample
//
//  Created by jayson on 10/11/14.
//
//

#ifndef __oscReceiveExample__MotionDetector__
#define __oscReceiveExample__MotionDetector__

#include <iostream>

#include "ofxOpenCv.h"
#include "ofxKinect.h"

class MotionDetector
{
public:
    void init();
    void update(float farThreshVal_);
    void drawDebugScreen();
    void shutDownBeforeExit();
    
    vector <ofxCvBlob> getBlobs();
    
private:
    ofxKinect kinect;
	
	
	ofxCvColorImage colorImg;
	
	ofxCvGrayscaleImage grayImage; // grayscale depth image
	ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
	
	ofxCvContourFinder contourFinder;
		
	int nearThreshold;
	int farThreshold;
	
	int angle;

};

#endif /* defined(__oscReceiveExample__MotionDetector__) */
