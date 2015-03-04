/*
 *  HaloManager.h
 *  Halo Light
 *
 *  Created by Imanol Gomez on 01/03/15.
 *
 */


#pragma once

#include "Manager.h"
#include "HaloRing.h"
#include "ofxOPC.h"

//========================== class HaloManager ==============================
//============================================================================
/** \class HaloManager HaloManager.h
 *	\brief Class managing the halo light rings
 *	\details it creates and updates the halo rings
 */


class HaloManager: public Manager
{
    static const int NUM_FADE_CANDYS;
    static const int NUM_HALO_RINGS;
    static const int NUM_HALO_LEDS;
    
    public:

        //! Constructor
        HaloManager();

        //! Destructor
        ~HaloManager();

        //! Setup the Halo Manager
        void setup();

        //! Update the Halo Manager
        void update();
    
        //! Draw the Halo Manager
        void draw();


    private:
    
        void createHaloRings();
    
        void setupOPC();
    
        void updateHaloRings();
    
    void drawHaloRings();
    
    private:
    
        typedef             ofPtr<HaloRing>                 HaloRingPtr;
        typedef             map<int,HaloRingPtr>            HaloRingMap;       ///< defines a map of Halo Rings attached to its id

        HaloRingMap         m_haloRings;
        ofxOPC              m_opcClient;            ///< instance of the Open Pixel Control client

};



