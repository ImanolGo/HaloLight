/*
 *  CameraTrackingManager.h
 *  Halo Light
 *
 *  Created by Imanol Gómez on 10/03/15.
 *
 */

#pragma once

#include "Manager.h"
#include "ofxMacamPs3Eye.h"

#define PS3_EYE_CAMERA

//========================== class CameraTrackingManager ==============================
//============================================================================
/** \class CameraTrackingManager CameraTrackingManager.h
 *	\brief Class managing the camera tracking 
 *	\details It creates camera tracker and sends tracking information
 */

class CameraTrackingManager: public Manager
{
    
    static const int CAMERA_WIDTH;
    static const int CAMERA_HEIGHT;
    
public:

    //! Constructor
    CameraTrackingManager();

    //! Destructor
    ~CameraTrackingManager();

    //! Set-up the camera tracking
    void setup();

    //! Update the camera tracking
    void update();

     //! Draw camera tracking
    void draw();

private:

    //! Set-up the camera tracking
    void setupCamera();
    
    void updateCamera();
    
    void drawCamera();
 
private:

    ofxMacamPs3Eye      m_cameraPs3Eye;
    ofVideoGrabber 		m_videoGrabber;
    
    ofPoint     m_cameraPosition;

};

//==========================================================================


