#include "ofMain.h"
#include "ofApp.h"
#include "ofGLProgrammableRenderer.h"

//========================================================================
int main( ){
    ofSetLogLevel(OF_LOG_NOTICE);

    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(1280,720,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
