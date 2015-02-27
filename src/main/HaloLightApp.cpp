/*
 *  HaloLightApp.cpp
 *  Halo Light
 *
 *  Created by Imanol Gomez on 16/02/15.
 *
 */

#include "AppManager.h"

#include "HaloLightApp.h"

//--------------------------------------------------------------
void HaloLightApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void HaloLightApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void HaloLightApp::draw(){
    AppManager::getInstance().draw();
}

void HaloLightApp::exit()
{
    ofLogNotice() <<"TheOthersApp::exit";

}

//--------------------------------------------------------------
void HaloLightApp::keyPressed(int key){

}

//--------------------------------------------------------------
void HaloLightApp::keyReleased(int key){

}

//--------------------------------------------------------------
void HaloLightApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void HaloLightApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void HaloLightApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void HaloLightApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void HaloLightApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void HaloLightApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void HaloLightApp::dragEvent(ofDragInfo dragInfo){

}
