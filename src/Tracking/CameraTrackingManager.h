/*
 *  CameraTrackingManager.h
 *  Halo Light
 *
 *  Created by Imanol Gómez on 10/03/15.
 *
 */

#pragma once

#include "Manager.h"

//========================== class CameraTrackingManager ==============================
//============================================================================
/** \class CameraTrackingManager CameraTrackingManager.h
 *	\brief Class managing the camera tracking 
 *	\details It creates camera tracker and sends tracking information
 */

class CameraTrackingManager: public Manager
{
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


 

private:



};

//==========================================================================


