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
    
    static const string GUI_CAMERA_SETTINGS_FILE_NAME;
    static const string GUI_FLUID_SETTINGS_FILE_NAME;
    
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
    
    void toggleGui();
    
    void showGui(bool show){m_showGui=show;}
    
    void setHue(float hue);

private:

    void setupCameraGui();
    
    void setupFluidGui();
    
private:
    
    // Fluid GUI
    ofxPanel			gui;
    
    ofParameter<float>	guiFPS;
    ofParameter<bool>	doFullScreen;
    void				setFullScreen(bool& _value) { ofSetFullscreen(_value);}
    ofParameter<bool>	toggleGuiDraw;
    ofParameter<bool>	doFlipCamera;
    ofParameter<int>	visualisationMode;
    ofParameter<string> visualisationName;
    int					numVisualisationModes;
    string				*visualisationModeTitles;
    ofParameterGroup	visualisationParameters;
    
    ofParameter<bool>	doResetDrawForces;
    ofParameterGroup	leftButtonParameters;
    ofParameter<bool>	showScalar;
    ofParameter<bool>	showField;
    ofParameter<float>	displayScalarScale;
    ofParameter<float>	velocityFieldArrowScale;
    ofParameter<float>	temperatureFieldBarScale;
    ofParameter<bool>	visualisationLineSmooth;
    
    ofParameterGroup	pictureCalibrationParameters;
    ofParameter<float>	offsetX;
    ofParameter<float>	offsetY;
    ofParameter<float>	scaleX;
    ofParameter<float>	scaleY;
    
    ofxPanel    m_fluidGui;      //Class creating a fluid gui panel

    // Camera GUI
    ofxPanel    m_cameraGui;      //Class creating a camera gui panel
    bool        m_showGui;  //It defines the whether the gui should be shown or not
};

//==========================================================================


