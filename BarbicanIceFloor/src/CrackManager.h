//
//  crack.h
//  iceCrack
//
//  Created by Tom Szirtes on 09/11/2014.
//
//

#ifndef iceCrack_crack_h
#define iceCrack_crack_h
#include <iostream>
#include "ofMain.h"
#include "ofxOpenCv.h"


struct Crack {
    float   x,y;        // coordinates
    float   startTime;  // time this crack was formed
    float   endTime;   // length this crack stays around for
    int     type;    // image id

    Crack(){
        x = 0.0f;
        y = 0.0f;
        startTime = 0.0f;
        endTime = 0.0f;
        type = 0;
    }
};


class CrackType {
public:
    ofImage         mainTexture;
    ofImage         maskTexture;        // may collapse into one for efficiency
    float           growTime;
    ofSoundPlayer   appearSound;
    
};



// This class represents an area on the surface which can be triggered by movement in it

class HotSpot {
public:
    
    HotSpot();
    void Set(float x, float y, float r);
    
    
    
    // Helper Is in hotspot
    bool IsIn(ofPoint pt) const;
    void BeginDetect();             // call this at beginning of detect loop
    void Occupy();                    // call this
    bool HasTripped() const;
    void EndDetect();
    void DebugDisplay() const;
    
    static const float triggerResetTime;
    enum TriggerState { Primed, Tripped, Occupied, Vacated };

    ofPoint     center;
    float       radius;

protected:
    TriggerState  state;
    
private:
    bool        occupied;
    float       resetTime;
    
};


class CrackManager {
public:

    
    CrackManager();    // ctor
    ~CrackManager();
    void Process();
    
    void AllocateTypes(int size);
    void SetType(int ID,const char* crackTexture,const char* maskTexture, float growTime, const char* audio);
    
    void Allocate(int size);
    Crack* CreateCrack(float x, float y);
    void DetectMovement(vector<ofxCvBlob> blobs);
    
    void CreateHotspots(float minsize);         // size of the hotspo
    
    void drawDebug();
    
    enum CrackMode {
        Master,
        Individual
    };
    
    void SetMode(CrackMode mode) { m_mode = mode; }
    
    static const float fadeTime;
    static const float holdTime;
    
protected:
    CrackMode            m_mode;
    ofShader            m_crackShader;
    ofPlanePrimitive    m_crackPlane;
    CrackType*          m_crackTypes;       // array
    int                 m_crackTypes_size;
    Crack*              m_cracks;           // array
    int                 m_cracks_size;
    
    vector<HotSpot>     m_hotspots;
};



#endif
