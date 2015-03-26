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
    
    const int getWidth(){return m_cameraPs3Eye.getWidth();}
    
    const int getHeight(){return m_cameraPs3Eye.getHeight();}
    
    const bool isNewFrame(){return m_cameraPs3Eye.isFrameNew();}
    
    const ofFbo& getCameraFbo(){return m_cameraFbo;}
    
    //! Gui Callback functions
    void onAutoGainAndShutterChange(bool & value);
    
    void onGainChange(float & value);
    
    void onShutterChange(float & value);
    
    void onGammaChange(float & value);
    
    void onBrightnessChange(float & value);
    
    void onContrastChange(float & value);
    
    void onHueChange(float & value);
    
    void onHueAlphaChange(float & value);
    
    void onLedChange(bool & value);
    
    void onFlickerChange(int & value);
    
    void onWhiteBalanceChange(int & value);
    
    
private:
    
    //! Set-up the camera tracking
    void setupCamera();
    
    void updateCamera();
    
    void drawCamera();
    
    void drawHueColor();
    
private:
    
    ofxMacamPs3Eye      m_cameraPs3Eye;
    ofVideoGrabber 		m_videoGrabber;
    
    ofColor             m_hueColor;
    ofRectangle         m_cameraArea;
    
    ofFbo				m_cameraFbo;
    
};

//==========================================================================


