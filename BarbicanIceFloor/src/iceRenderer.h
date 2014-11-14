//
//  ice.h
//  IcePlate
//
//  Created by Tom Szirtes on 13/11/2014.
//
//

#ifndef __IcePlate__ice__
#define __IcePlate__ice__

#include <stdio.h>
#include "ofMain.h"

class IceRenderer{
public:
    void init();
    void draw();

private:

    float           m_Scroll1,m_Scroll2,m_Scroll3;
    
    ofShader        m_iceShader;
    ofImage         m_backTexture;
    ofImage         m_normalMap;
    ofPlanePrimitive m_backPlane;
    
};

#endif /* defined(__IcePlate__ice__) */
