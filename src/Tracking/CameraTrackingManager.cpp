/*
 *  CameraTrackingManager.cpp
 *  Halo Light
 *
 *  Created by Imanol Gómez on 10/03/15.
 *
 */

#include "ofMain.h"
#include "CameraTrackingManager.h"

CameraTrackingManager::CameraTrackingManager(): Manager()
{
	//Intentionally left empty
}


CameraTrackingManager::~CameraTrackingManager()
{
    ofLogNotice() <<"CameraTrackingManager::Destructor";
}


void CameraTrackingManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"CameraTrackingManager::initialized";

	Manager::setup();
}


void CameraTrackingManager::update()
{
    ///To implement
}

void CameraTrackingManager::draw()
{
    ///To implement 
}

