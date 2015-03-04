/*
 *  HaloVisuals.h
 *  Halo Light
 *
 *  Created by Imanol Gomez on 04/03/15.
 *
 */


#pragma once

#include "BasicVisual.h"
#include "ImageVisual.h"

//========================== class HaloVisuals ==============================
//============================================================================
/** \class HaloVisuals HaloVisuals.h
 *	\brief Class managing the halo light rings
 *	\details it creates and updates the halo rings
 */


class HaloVisuals: public BasicVisual {
    
    public:

        //! Constructor
        HaloVisuals();

        //! Destructor
        ~HaloVisuals();

        //! Setup the Halo Visuals
        void setup();

        //! Update the Halo Visuals
        void update();
    
        //! Draw the Halo Visuals
        void draw();
    
        //! Set the mode of the Halo Visuals
        void setMode(int mode) {m_mode = mode;}


    private:
    
        void createImageVisuals();
    
        void drawEffects();
    
    private:
    
        int m_mode;
    
        ofPtr<ImageVisual>  m_imageVisual;

};



