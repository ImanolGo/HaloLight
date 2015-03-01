/*
 *  HaloManager.h
 *  Halo Light
 *
 *  Created by Imanol Gomez on 01/03/15.
 *
 */


#pragma once

#include "Manager.h"

//========================== class HaloManager ==============================
//============================================================================
/** \class HaloManager HaloManager.h
 *	\brief Class managing the halo light rings
 *	\details it creates and updates the halo rings
 */


class HaloManager: public Manager
{
    public:

        //! Constructor
        HaloManager();

        //! Destructor
        ~HaloManager();

        //! Setup the Halo Manager
        void setup();

        //! Update the Halo Manager
        void update();


    private:



    private:
    
        typedef             ofPtr<HaloRing>                 HaloRingPtr;
        typedef             map<id,HaloRingPtr>               HaloRingMap;       ///< defines a map of Halo Rings attached to its id

    
        ofxOPC                  m_opcClient;            ///< instance of the Open Pixel Control client

};



