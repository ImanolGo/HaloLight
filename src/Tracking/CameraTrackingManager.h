/*
 *  CameraTrackingManager.h
 *  Halo Light
 *
 *  Created by Imanol Gómez on 10/03/15.
 *
 */

#pragma once

#include "Manager.h"

#include "ofxPS3EyeGrabber.h"


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
    
    void showCamera(bool show){m_showCamera = show;}
    
    const int getWidth(){return m_videoGrabber.getWidth();}
    
    const int getHeight(){return m_videoGrabber.getHeight();}
    
    const bool isNewFrame(){return m_videoGrabber.isFrameNew();}
    
    const ofFbo& getCameraFbo(){return m_cameraFbo;}
    
    void onHueChange(float & value);
    
    void onHueAlphaChange(float & value);
    
    void onHueChangeRate(float & value);
   
    
private:
    
    //! Set-up the camera tracking
    void setupCamera();
    
    void updateCamera();
    
    void updateHue();
    
    void drawCamera();
    
    void drawHueColor();
    
private:
    
    
    ofVideoGrabber      m_videoGrabber;
    
    float               m_hueChangeRate; //It tells you how many seconds do you need to have a unit hue change
    ofColor             m_hueColor;
    ofRectangle         m_cameraArea;
    
    ofFbo				m_cameraFbo;
    
    bool                m_showCamera;
    
};

//==========================================================================


