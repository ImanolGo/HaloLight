/*
 *  HaloVisuals.h
 *  Halo Light
 *
 *  Created by Imanol Gomez on 04/03/15.
 *
 */


#pragma once

#include "ImageVisual.h"

#include "ofxGui.h"
#include "ofxFlowTools.h"

//#define USE_FASTER_INTERNAL_FORMATS			// about 15% faster but gives errors from ofGLUtils
using namespace flowTools;

//========================== class HaloVisuals ==============================
//============================================================================
/** \class HaloVisuals HaloVisuals.h
 *	\brief Class managing the halo light rings
 *	\details it creates and updates the halo rings
 */


class HaloVisuals {
    
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
    
    void setupGui();
    
    void setupFluid();
    
    void updateFluid();
    
    void drawFluid();
    
    void drawCircle();
    
    void drawParticle();
    
    void drawPaintFluid();
    
private:
    
    int m_mode;
    ofPtr<ImageVisual>  m_imageVisual;
    
    ofVec2f				m_lastMouse;
    
    // GUI
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
    
    ofParameterGroup	drawForceParameters;
    ofParameter<bool>	doResetDrawForces;
    void				resetDrawForces(bool& _value) { if (_value) {for (int i=0; i<m_numDrawForces; i++) m_flexDrawForces[i].reset();} doResetDrawForces.set(false);}
    ofParameterGroup	leftButtonParameters;
    ofParameterGroup	rightButtonParameters;
    ofParameter<bool>	showScalar;
    ofParameter<bool>	showField;
    ofParameter<float>	displayScalarScale;
    void				setDisplayScalarScale(float& _value) { m_displayScalar.setScale(_value); }
    ofParameter<float>	velocityFieldArrowScale;
    void				setVelocityFieldArrowScale(float& _value) { m_velocityField.setVectorSize(_value); }
    ofParameter<float>	temperatureFieldBarScale;
    void				setTemperatureFieldBarScale(float& _value) { m_temperatureField.setVectorSize(_value); }
    ofParameter<bool>	visualisationLineSmooth;
    void				setVisualisationLineSmooth(bool& _value) { m_velocityField.setLineSmooth(_value); }
    
    
    ftOpticalFlow		m_opticalFlow;
    ftVelocityMask		m_velocityMask;
    ftFluidSimulation	m_fluid;
    
    ftDisplayScalar		m_displayScalar;
    ftVelocityField		m_velocityField;
    ftTemperatureField	m_temperatureField;
    
    int					m_numDrawForces;
    ftDrawForce*		m_flexDrawForces;
    
};



