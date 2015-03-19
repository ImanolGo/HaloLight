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
#include "HaloVisuals.h"
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
    
        //! Set the mode of the Halo Visuals
        void setMode(int mode) {m_haloVisuals.setMode(mode);}
    
        const ofRectangle& getRingArea() const {return m_imageSpaceRectangle;}

    private:
    
        void grabImageData();
    
        void setupHaloRings();
    
        void createHaloRings();
    
        void createHaloRingsPositions();
    
        void setupOPC();
    
        void updateHaloRings();
    
        void drawHaloRings();
    
        void drawRectangles();
    
    private:
    
        typedef             ofPtr<HaloRing>                 HaloRingPtr;
        typedef             map<int,HaloRingPtr>            HaloRingMap;            ///< defines a map of Halo Rings attached to its id
        typedef             map<int,ofVec3f>                HaloRingPositionMap;    ///< defines a map of Halo Rings position attached to relative position index
    
        HaloRingPositionMap m_haloRingsPositionMap;
        HaloRingPositionMap m_haloRingsPreviewPositionMap;

        HaloRingMap         m_haloRings;
        ofxOPC              m_opcClient;                    ///< instance of the Open Pixel Control client
        HaloVisuals         m_haloVisuals;
    
        // Capture Objects
        ofImage     m_screenImage;
        ofPixels    m_screenPixels;
    
        float               m_ringSize;
        float               m_ringPreviewSize;
        ofRectangle         m_imageSpaceRectangle;
        ofRectangle         m_previewRectangle;

};



