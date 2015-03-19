/*
 *  CameraTrackingManager.cpp
 *  Halo Light
 *
 *  Created by Imanol Gómez on 10/03/15.
 *
 */

#include "ofMain.h"
#include "CameraTrackingManager.h"

const int CameraTrackingManager::CAMERA_WIDTH = 640;
const int CameraTrackingManager::CAMERA_HEIGHT = 480;

CameraTrackingManager::CameraTrackingManager(): Manager()
{
	//Intentionally left empty
}


CameraTrackingManager::~CameraTrackingManager()
{
    m_cameraPs3Eye.close();
    ofLogNotice() <<"CameraTrackingManager::Destructor";
}


void CameraTrackingManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"CameraTrackingManager::initialized";

	Manager::setup();
    
    this->setupCamera();
}

void CameraTrackingManager::setupCamera()
{
    m_cameraPs3Eye.listDevices();
    
    m_cameraPs3Eye.setDesiredFrameRate(60);
    m_cameraPs3Eye.initGrabber(CAMERA_WIDTH,CAMERA_HEIGHT);
    
    m_cameraPs3Eye.setAutoGainAndShutter(false); // otherwise we can't set gain or shutter
    m_cameraPs3Eye.setGain(1.0);
    m_cameraPs3Eye.setShutter(1.0);
    m_cameraPs3Eye.setGamma(0.4);
    m_cameraPs3Eye.setBrightness(0.6);
    m_cameraPs3Eye.setContrast(1.0);
    m_cameraPs3Eye.setHue(0.5);
    
    m_cameraPs3Eye.setFlicker(1);
    
    m_cameraPosition.x = ofGetWidth()*0.75 - CAMERA_WIDTH*0.5;
    m_cameraPosition.y = 20;
    
    
    m_videoGrabber.setDeviceID(0);
    m_videoGrabber.setDesiredFrameRate(60);
    m_videoGrabber.initGrabber(CAMERA_WIDTH,CAMERA_HEIGHT);
}

void CameraTrackingManager::update()
{
    this->updateCamera();
}

void CameraTrackingManager::updateCamera()
{

    m_videoGrabber.update();
    
    m_cameraPs3Eye.update();
    
    // Blink the led everytime there is a new frame
    if(m_cameraPs3Eye.isFrameNew()){
       m_cameraPs3Eye.setLed(true);
    }
    else m_cameraPs3Eye.setLed(false);
}


void CameraTrackingManager::draw()
{
    this->drawCamera();
}

void CameraTrackingManager::drawCamera()
{
    #ifdef PS3_EYE_CAMERA
        m_cameraPs3Eye.draw(m_cameraPosition.x,m_cameraPosition.y);
    #else
        m_videoGrabber.draw(m_cameraPosition.x,m_cameraPosition.y);
    #endif
}

