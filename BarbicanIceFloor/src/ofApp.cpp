#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    showDebug=false;
    
    motionDetector.init();
    iceRenderer.init();
    
    
    ofSetFrameRate(25);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    motionDetector.update(userInterface.getFarThreshold());
    iceRenderer.update(motionDetector.getBlobs());
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0,0,0);
    
    iceRenderer.draw();
    
    if(showDebug)
        motionDetector.drawDebugScreen();
    
    userInterface.draw();
    
}
void ofApp::exit() {
    
    motionDetector.shutDownBeforeExit();
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key)
    {
        case '\t':
            showDebug = !showDebug;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
