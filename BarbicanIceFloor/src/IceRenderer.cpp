//
//  IceRenderer.cpp
//  IcePlate
//
//  Created by Tom Szirtes on 13/11/2014.
//
//

#include "IceRenderer.h"

void IceRenderer::init(){
    // Dosomething
    m_iceShader.load("ice.vert","ice.frag");
    
    m_backTexture.loadImage("cloudmultiple.png");
    m_backTexture.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    
    m_normalMap.loadImage("1005-normal.jpg");
    m_normalMap.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    
    // set up background Plane
    m_backPlane.mapTexCoordsFromTexture(m_backTexture.getTextureReference());
    m_backPlane.set(ofGetWidth(),ofGetHeight());
    m_backPlane.setResolution(2,2);
    m_backPlane.setPosition(ofGetWidth()*0.5f,ofGetHeight()*0.5f,0.0f);
    m_Scroll1 = 0.0f;
    m_Scroll2 = 0.0f;
    m_Scroll3 = 0.0f;
}

void IceRenderer::draw(){
    
    m_iceShader.begin();
    m_iceShader.setUniformTexture("mainTex",m_backTexture.getTextureReference(),0);
    m_iceShader.setUniformTexture("bumpTex",m_normalMap.getTextureReference(),1);
    m_iceShader.setUniform1f("bumpAmount",20.0f);
    m_iceShader.setUniform1f("scroll1",m_Scroll1);
    m_iceShader.setUniform1f("scroll2",m_Scroll2);
    m_iceShader.setUniform1f("scroll3",m_Scroll3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // nasty magic values here - adjust these to change the relative speeds
    m_Scroll1   += 0.11f;
    m_Scroll2   -= 0.25f;
    m_Scroll3   += 0.32f;
    
    m_backPlane.draw();
    
    m_iceShader.end();
}