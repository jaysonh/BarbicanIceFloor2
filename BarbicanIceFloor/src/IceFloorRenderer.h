//
//  IceRenderer.h
//  BarbicanMotionDetection
//
//  Created by jayson on 10/11/14.
//
//

#ifndef __BarbicanMotionDetection__IceRenderer__
#define __BarbicanMotionDetection__IceRenderer__

#include <iostream>
#include "ofMain.h"
#include "ofxOpenCv.h"

class IceFloorRenderer
{
public:
    void init();
    void update(vector <ofxCvBlob> blobList);
    void draw();
    
private:
    
    ofFbo   fbo;
    ofImage crackOverlayImg;
    
};
#endif /* defined(__BarbicanMotionDetection__IceRenderer__) */
