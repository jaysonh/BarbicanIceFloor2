//
//  crack.cpp
//  iceCrack
//
//  Created by Tom Szirtes on 09/11/2014.
//
//

#include <stdio.h>
#include "ofMain.h"
#include "CrackManager.h"


const float HotSpot::triggerResetTime = 8.0f;            // This is the time it takes for a hotspot to re-trigger should be the total of these below?
const float CrackManager::fadeTime = 2.0f;
const float CrackManager::holdTime = 6.0f;



CrackManager::CrackManager(){

    
    m_crackShader.load("crack.vert","crack.frag");
    
    // Init our crack types
    m_crackTypes_size = 0;
    m_crackTypes = NULL;
    
    // set up the UVs lazily
 //   m_crackPlane.mapTexCoords( 0.0f,0.0f,1.0f,1.0f);
    m_crackPlane.set(ofGetWidth()*0.5f,ofGetHeight()*0.5f);
    m_crackPlane.setResolution(2,2);
    m_crackPlane.setPosition(0.0f,0.0f,0.1f);
    
    m_cracks = NULL;
    CreateHotspots(120);     // size of hotspots
}

void CrackManager::SetType(int ID,const char* crackTexture,const char* maskTexture, float growTime, const char* audioFile){
    m_crackTypes[ID].mainTexture.loadImage(crackTexture);
    m_crackTypes[ID].mainTexture.getTextureReference().setTextureWrap( GL_CLAMP, GL_CLAMP );
    m_crackTypes[ID].maskTexture.loadImage(maskTexture);
    m_crackTypes[ID].maskTexture.getTextureReference().setTextureWrap( GL_CLAMP, GL_CLAMP );
    m_crackTypes[ID].growTime = growTime;
    m_crackTypes[ID].appearSound.loadSound(audioFile);
}

void CrackManager::Allocate(int size){
    if (m_cracks!=NULL)
        delete m_cracks;
    
    m_cracks = new Crack[size];
    m_cracks_size = size;
}

CrackManager::~CrackManager(){
    if (m_cracks!=NULL)
        delete m_cracks;
    m_cracks = NULL;
    m_cracks_size = 0;
}

/*
    Create a new crack at the given position
 */

Crack* CrackManager::CreateCrack(float x, float y){
    float t = ofGetElapsedTimef();
    
    for(int i=0;i<m_cracks_size;i++){
        if (t>m_cracks[i].endTime){
            
            // pick a random type
            m_cracks[i].type = (int)ofRandom(m_crackTypes_size);
            m_cracks[i].startTime = t;
            m_cracks[i].endTime = t+holdTime+fadeTime;
            m_cracks[i].x = x;
            m_cracks[i].y = y;
            //playsound
            m_crackTypes[m_cracks[i].type].appearSound.play();
            
        //    ofLog(OF_LOG_NOTICE,"created crack at "+ofToString(m_cracks[i].startTime)+" pos "+ofToString(x)+" , "+ofToString(y));
            return &m_cracks[i];
        }
    }
}

/*
    Pre-allocate the crack types - replace this with a VECTOR instead of stupid array
 I was a bit preoccupied with a talk on Data Orientated Design just before writing this :)
 */

void CrackManager::AllocateTypes(int size){
    if (m_crackTypes!=NULL)
            delete m_crackTypes;
    m_crackTypes = new CrackType[size];
    m_crackTypes_size = size;
}



/*
    Process all the cracks - main loop
*/

void CrackManager::Process(){
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    float t = ofGetElapsedTimef();
    
    // Set up render state
    m_crackShader.begin();

    // will bring in the loop later
    float cutoff,alpha;
    int     lastCrackType = -1;
    
    for(int i=0;i<m_cracks_size;i++){
        Crack* crack = &m_cracks[i];
        if (t <= crack->endTime){
            alpha = 1.0f;
            if (crack->type != lastCrackType){
                lastCrackType = crack->type;
                // change the texture
                m_crackShader.setUniformTexture("tex0",m_crackTypes[lastCrackType].mainTexture.getTextureReference(),1);
                m_crackShader.setUniformTexture("tex1",m_crackTypes[lastCrackType].maskTexture.getTextureReference(),2);
                
                if (m_mode != Master){
                    m_crackPlane.mapTexCoords( 0.0f, 0.0f, m_crackTypes[lastCrackType].mainTexture.getTextureReference().getWidth(), m_crackTypes[lastCrackType].mainTexture.getTextureReference().getHeight());
                }
            }
            
            alpha = ofLerp(0.0f,1.0f,(crack->endTime-t) / fadeTime);
            cutoff = ofLerp(0.0f,1.0f,(t-crack->startTime) / m_crackTypes[lastCrackType].growTime);
            
            cutoff = ofClamp(cutoff,0.0f,1.0f);
            alpha = ofClamp(alpha,0.0f,1.0f);
            
            m_crackShader.setUniform1f("cutoff",cutoff);
            m_crackShader.setUniform1f("alpha",alpha);
          //  ofLog(OF_LOG_NOTICE,"%f",alpha);
        
            ofPushMatrix();
            ofTranslate(m_cracks[i].x,m_cracks[i].y);
            if (m_mode == Master){
                float u1 = crack->x - m_crackPlane.getWidth()*0.5f;
                float v1 = crack->y - m_crackPlane.getHeight()*0.5f;
                float u2 = crack->x + m_crackPlane.getWidth()*0.5f;
                float v2 = crack->y + m_crackPlane.getHeight()*0.5f;
                m_crackPlane.mapTexCoords(u1,v1,u2,v2);
                // m_crackPlane.mapTexCoords(0.0f,0.0f,0.0f,0.0f);
                // ofLog(OF_LOG_NOTICE,"crack %f,%f,%f,%f",u1,v1,u2,v2);

            }else{
            }
            m_crackPlane.draw();
            ofPopMatrix();
            
        }
        
    }
    m_crackShader.end();
}



// Helper Is in hotspot
inline bool HotSpot::IsIn(ofPoint pt) const{
    return (center.distance(pt)<radius);
}

void HotSpot::BeginDetect(){
    occupied = false;
    if (state==Tripped) {
        state=Occupied;
    }
}

void HotSpot::Occupy(){
    occupied = true;
    if (state==Primed){
        state = Tripped;
    }
}


bool HotSpot::HasTripped() const {
    return (state==Tripped);
}

// Call this per check
void HotSpot::EndDetect(){
    if (!occupied){
        if (state==Tripped || state==Occupied){
            state = Vacated;
            resetTime = ofGetElapsedTimef()+ triggerResetTime;
        }
        
        if (state==Vacated && resetTime<ofGetElapsedTimef()){
            state= Primed;
        }
        // do wait check
    }
}


HotSpot::HotSpot(){
    occupied = false;
    state = Primed;
}


void HotSpot::DebugDisplay() const {

    ofSetColor(255,255,255);
    
    if (state!=Primed)
        ofFill();
    else
        ofNoFill();
    
    if (state==Tripped)
        ofSetColor(255,0,0);
    
    if (state==Occupied)
        ofSetColor(0,0,255);
    
    if (state==Vacated)
        ofSetColor(0,255,0);
    
    ofCircle(center.x,center.y,radius);
}

void HotSpot::Set(float x, float y, float r){
    center.x = x;
    center.y = y;
    radius = r;
}

void CrackManager::CreateHotspots(float minsize){

    int icount = (int)(ofGetWidth()/minsize);
    int jcount = (int)(ofGetHeight()/minsize);
    float x,y;
    HotSpot h;
    // quickly fills the area with hotspots
    for(int i=0;i<icount;i++){
        for (int j=0;j<jcount;j++){
            x = (minsize * 0.5) + (i * minsize);
            y = (minsize * 0.5) + (j * minsize);
            h.Set(x,y,minsize*0.5);
            m_hotspots.push_back(h);
        }
    }
}


void CrackManager::drawDebug(){
    for(int i = 0; i< m_hotspots.size();i++)
        {
            m_hotspots[i].DebugDisplay();
   
        }
}

void CrackManager::DetectMovement(vector<ofxCvBlob> blobs) {

    // Go through hotspots
    
    for(int i = 0; i< m_hotspots.size();i++){
        m_hotspots[i].BeginDetect();
        
        for(int j = 0; j < blobs.size();j++){
            if (m_hotspots[i].IsIn(blobs[j].centroid)){
                m_hotspots[i].Occupy();
            }
        }
        m_hotspots[i].EndDetect();
        
        if (m_hotspots[i].HasTripped())
        {
            CreateCrack(m_hotspots[i].center.x,m_hotspots[i].center.y);
                    //ofLog(OF_LOG_NOTICE,"Hotspot is trigger");
        }
    }
    
  
}