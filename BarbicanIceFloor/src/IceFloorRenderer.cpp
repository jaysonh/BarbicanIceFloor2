//
//  IceRenderer.cpp
//  BarbicanMotionDetection
//
//  Created by jayson on 10/11/14.
//
//

#include "IceFloorRenderer.h"

void IceFloorRenderer::init()
{
    crackOverlayImg.loadImage(ofToDataPath("cracked_ice.png"));
    
    fbo.allocate(ofGetWidth(),ofGetHeight());
    fbo.begin();
    ofClear(0,0,0);
    fbo.end();
}

void IceFloorRenderer::update(vector <ofxCvBlob> blobList)
{
    fbo.begin();
    ofEnableAlphaBlending();
    ofSetColor(0,0,0,2);
    ofRect(0,0,fbo.getWidth(),fbo.getHeight());
    
    ofSetColor(255,255,255);
    float scaleX = (float)ofGetWidth() / 640.0;
    float scaleY = (float)ofGetHeight()/  480.0;
    
    for(int i = 0; i < blobList.size();i++)
    {
        ofBeginShape();
        for(int j = 0; j < blobList[i].nPts;j++)
            ofVertex(blobList[i].pts[j].x * scaleX,blobList[i].pts[j].y * scaleY);
        
        ofEndShape(true);
        
        //ofCircle(blobList[i].centroid.x,blobList[i].centroid.y,150,150);
       
    }
    fbo.end();
}

void IceFloorRenderer::draw()
{
    fbo.draw(0,0);
    crackOverlayImg.draw(0,0,ofGetWidth(),ofGetHeight());
    
}