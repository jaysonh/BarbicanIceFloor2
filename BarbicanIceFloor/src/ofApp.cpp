#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    showDebug=false;
    
    motionDetector.init();
    iceFloorRenderer.init();
    
    backgroundSound.loadSound("atmo 2.mp3");
    backgroundSound.play();
    
    ofEnableAlphaBlending();
    
    // Set up our cracks
    crackManager.Allocate(100);
    crackManager.AllocateTypes(3);
    crackManager.SetType(0,"crack1.jpg","crackalpha1.jpg",1.0f,"Ice crack 1.mp3");
    crackManager.SetType(1,"mastercrack.jpg","mask1.jpg",1.0f,"Ice crack 3.mp3");
    crackManager.SetType(2,"crack1.jpg","crackalpha1.jpg",1.0f,"Ice crack 5.mp3");
    crackManager.SetMode(CrackManager::Individual);

    iceRenderer.init();
    ofSetFrameRate(25);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    motionDetector.update(userInterface.getFarThreshold());
    iceFloorRenderer.update(motionDetector.getBlobs());
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0,0,0);
    iceRenderer.draw();  // toms renderer
    iceFloorRenderer.draw();
    
    if(showDebug)
        motionDetector.drawDebugScreen();
    
    userInterface.draw();
    
    crackManager.Process();
    
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
crackManager.CreateCrack(x,y);
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
