/*
 *  GuiManager.h
 *  Halo Light
 *
 *  Created by Imanol Gomez on 19/03/15.
 *
 */

#pragma once

#include "Manager.h"
#include "ofxGui.h"
//========================== class GuiManager ==============================
//============================================================================
/** \class GuiManager GuiManager.h
 *	\brief Class managing the application´s grapical user interface (GUI)
 *	\details It creates the gui and the callback functions that will be affected
 *    by the gui
 */

class GuiManager: public Manager
{
    
    static const string GUI_SETTINGS_FILE_NAME;
    
public:

    //! Constructor
    GuiManager();

    //! Destructor
    ~GuiManager();

    //! Set-up the gui
    void setup();
    
    //! Draw the gui
    void draw();
    
    void saveGuiValues();
    
    void loadGuiValues();
    
    void showGui(bool show){m_showGui=show;}

private:

    void setupCameraGui();
    
    void loadCameraValues();
    
private:

    ofxPanel    m_gui;      //Class creating a gui panel
    bool        m_showGui;  //It defines the whether the gui should be shown or not
};

//==========================================================================

