//
//  crack.h
//  iceCrack
//
//  Created by Tom Szirtes on 09/11/2014.
//
//

#ifndef iceCrack_crack_h
#define iceCrack_crack_h



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

class CrackManager {
public:

    
    CrackManager();    // ctor
    ~CrackManager();
    void Process();
    
    void AllocateTypes(int size);
    void SetType(int ID,const char* crackTexture,const char* maskTexture, float growTime, const char* audio);
    
    void Allocate(int size);
    Crack* CreateCrack(float x, float y);
    
    enum CrackMode {
        Master,
        Individual
    };
    
    void SetMode(CrackMode mode) { m_mode = mode; }
    
    const float fadeTime = 2.0f;
    const float holdTime = 6.0f;
    
protected:
    CrackMode            m_mode;
    ofShader            m_crackShader;
    ofPlanePrimitive    m_crackPlane;
    CrackType*          m_crackTypes;       // array
    int                 m_crackTypes_size;
    Crack*              m_cracks;           // array
    int                 m_cracks_size;
};



#endif
