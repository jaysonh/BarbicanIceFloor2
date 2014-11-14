//
//  MotionDetector.cpp
//  oscReceiveExample
//
//  Created by jayson on 10/11/14.
//
//

#include "MotionDetector.h"

void MotionDetector::init()
{
   	
	kinect.setRegistration(true);
    kinect.init();
	kinect.open();		// opens first available kinect
	
	colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	
    nearThreshold = 230;
	farThreshold = 10;
    
    // zero the tilt on startup
	angle = 0;
	kinect.setCameraTiltAngle(angle);
}
void MotionDetector::update(float farThreshVal_)
{
    farThreshold=farThreshVal_;
	
	kinect.update();
	
	// there is a new frame and we are connected
	if(kinect.isFrameNew())
    {
		
		// load grayscale depth image from the kinect source
		grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
		
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        grayThreshNear = grayImage;
        grayThreshFar = grayImage;
        grayThreshNear.threshold(nearThreshold, true);
        grayThreshFar.threshold(farThreshold);
        cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        
        grayImage.flagImageChanged();
		
		contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
   
	}
}

vector <ofxCvBlob> MotionDetector::getBlobs()
{
    return contourFinder.blobs;
}

void MotionDetector::shutDownBeforeExit()
{
    
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
	

}
void MotionDetector::drawDebugScreen()
{
    // draw from the live kinect
    kinect.drawDepth(215, 10, 400, 300);
    kinect.draw(625, 10, 400, 300);
    
    grayImage.draw(1035, 10, 400, 300);
    contourFinder.draw(1035, 10, 400, 300);
	 
    ofDrawBitmapString("Depth Image", 220, 25);
    ofDrawBitmapString("Colour Image", 630, 25);
    ofDrawBitmapString("Blob Depth Tracking", 1040, 25);
	

}
