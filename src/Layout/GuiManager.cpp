/*
 *  GuiManager.cpp
 *  Halo Light
 *
 *  Created by Imanol Gomez on 19/03/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"

#include "GuiManager.h"

const string GuiManager::GUI_CAMERA_SETTINGS_FILE_NAME = "xmls/CameraGuiSettings.xml";
const string GuiManager::GUI_FLUID_SETTINGS_FILE_NAME = "xmls/FluidGuiSettings.xml";


GuiManager::GuiManager(): Manager(), m_showGui(true)
{
	//Intentionally left empty
}


GuiManager::~GuiManager()
{
    ofLogNotice() <<"GuiManager::Destructor";
}


void GuiManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"GuiManager::initialized";

	Manager::setup();
    
    this->setupFluidGui();
    this->setupCameraGui();
    
}
void GuiManager::setupFluidGui()
{
    
    HaloVisuals& haloVisuals = AppManager::getInstance().getHaloManager()->getHaloVisuals();
    
    m_fluidGui.setup(GUI_FLUID_SETTINGS_FILE_NAME);
    m_fluidGui.setDefaultBackgroundColor(ofColor(0, 0, 0, 127));
    m_fluidGui.setDefaultFillColor(ofColor(160, 160, 160, 160));
    m_fluidGui.add(guiFPS.set("FPS", 0, 0, 60));
    
    int guiColorSwitch = 0;
    ofColor guiHeaderColor[2];
    guiHeaderColor[0].set(160, 160, 80, 200);
    guiHeaderColor[1].set(80, 160, 160, 200);
    ofColor guiFillColor[2];
    guiFillColor[0].set(160, 160, 80, 200);
    guiFillColor[1].set(80, 160, 160, 200);
    
    m_fluidGui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    m_fluidGui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    m_fluidGui.add(haloVisuals.m_opticalFlow.parameters);
    
    m_fluidGui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    m_fluidGui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    m_fluidGui.add(haloVisuals.m_velocityMask.parameters);
    
    m_fluidGui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    m_fluidGui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(haloVisuals.m_fluid.parameters);
    
    visualisationParameters.setName("visualisation");
    visualisationParameters.add(showScalar.set("show scalar", true));
    visualisationParameters.add(showField.set("show field", true));
    visualisationParameters.add(displayScalarScale.set("display scalar scale", 0.25, 0.05, 0.5));
    displayScalarScale.addListener(&haloVisuals, &HaloVisuals::setDisplayScalarScale);
    visualisationParameters.add(velocityFieldArrowScale.set("arrow scale", 0.6, 0.2, 1));
    velocityFieldArrowScale.addListener(&haloVisuals, &HaloVisuals::setVelocityFieldArrowScale);
    visualisationParameters.add(temperatureFieldBarScale.set("temperature scale", 0.25, 0.05, 0.5));
    temperatureFieldBarScale.addListener(&haloVisuals, &HaloVisuals::setTemperatureFieldBarScale);
    visualisationParameters.add(visualisationLineSmooth.set("line smooth", false));
    visualisationLineSmooth.addListener(&haloVisuals, &HaloVisuals::setVisualisationLineSmooth);
    
    m_fluidGui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    m_fluidGui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    m_fluidGui.add(visualisationParameters);
    
    leftButtonParameters.setName("mouse left button");
    for (int i=0; i<3; i++) {
        leftButtonParameters.add(haloVisuals.m_flexDrawForces[i].parameters);
    }
    m_fluidGui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    m_fluidGui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    m_fluidGui.add(leftButtonParameters);
    
    rightButtonParameters.setName("mouse right button");
    for (int i=3; i<6; i++) {
        rightButtonParameters.add(haloVisuals.m_flexDrawForces[i].parameters);
    }
    m_fluidGui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    m_fluidGui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    m_fluidGui.add(rightButtonParameters);
    
    m_fluidGui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    m_fluidGui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    m_fluidGui.add(doResetDrawForces.set("reset draw forces (D)", false));
    doResetDrawForces.addListener(&haloVisuals,  &HaloVisuals::resetDrawForces);
    
    m_fluidGui.loadFromFile(GUI_FLUID_SETTINGS_FILE_NAME);
    m_fluidGui.minimizeAll();
}

void GuiManager::setupCameraGui()
{
    
    m_cameraGui.setup("Camera GUI", GUI_CAMERA_SETTINGS_FILE_NAME);
    m_cameraGui.setPosition(ofGetWidth()*0.5 + 100,40);
    
    ofPtr<CameraTrackingManager> cameraTrackingManager = AppManager::getInstance().getCameraTrackingManager();
    
    
    ofxToggle * autoGainAndShutter = new ofxToggle();
    autoGainAndShutter->setup("Auto Gain and Shutter", false);
    autoGainAndShutter->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onAutoGainAndShutterChange);
    m_cameraGui.add(autoGainAndShutter);
    
    ofxFloatSlider * gain = new ofxFloatSlider();
    gain->setup("Gain", 0.5, 0.0, 1.0);
    gain->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onGainChange);
    m_cameraGui.add(gain);
    
    ofxFloatSlider * shutter = new ofxFloatSlider();
    shutter->setup("Shutter", 0.5, 0.0, 1.0);
    shutter->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onShutterChange);
    m_cameraGui.add(shutter);
    
    ofxFloatSlider * gamma = new ofxFloatSlider();
    gamma->setup("Gamma", 0.5, 0.0, 1.0);
    gamma->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onGammaChange);
    m_cameraGui.add(gamma);
    
    ofxFloatSlider * brightness = new ofxFloatSlider();
    brightness->setup("Brightness", 0.5, 0.0, 1.0);
    brightness->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onBrightnessChange);
    m_cameraGui.add(brightness);
    
    ofxFloatSlider * contrast = new ofxFloatSlider();
    contrast->setup("Contrast", 0.5, 0.0, 1.0);
    contrast->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onContrastChange);
    m_cameraGui.add(contrast);
    
    ofxFloatSlider * hue = new ofxFloatSlider();
    hue->setup("Hue", 0.5, 0.0, 1.0);
    hue->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onHueChange);
    m_cameraGui.add(hue);
    
    ofxIntSlider * flicker = new ofxIntSlider();
    flicker->setup("Flicker Type", 0, 0, 2);
    flicker->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onFlickerChange);
    m_cameraGui.add(flicker);
    
    ofxIntSlider * wb = new ofxIntSlider();
    wb->setup("White Balance Mode", 4, 1, 4);
    wb->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onFlickerChange);
    m_cameraGui.add(wb);
    
    ofxToggle * led = new ofxToggle();
    led->setup("LED", true);
    led->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onLedChange);
    m_cameraGui.add(led);
    
    //this->loadCameraValues();
}

void GuiManager::loadCameraValues()
{
    
    ofPtr<CameraTrackingManager> cameraTrackingManager = AppManager::getInstance().getCameraTrackingManager();
    
    m_cameraGui.loadFromFile(GUI_CAMERA_SETTINGS_FILE_NAME);
    bool b;
    float f;
    int i;
    b = m_cameraGui.getToggle("Auto Gain and Shutter");
    cameraTrackingManager->onAutoGainAndShutterChange(b);
    f = m_cameraGui.getFloatSlider("Gain");
    cameraTrackingManager->onGainChange(f);
    f = m_cameraGui.getFloatSlider("Shutter");
    cameraTrackingManager->onShutterChange(f);
    f = m_cameraGui.getFloatSlider("Gamma");
    cameraTrackingManager->onGammaChange(f);
    f = m_cameraGui.getFloatSlider("Brightness");
    cameraTrackingManager->onBrightnessChange(f);
    f = m_cameraGui.getFloatSlider("Contrast");
    cameraTrackingManager->onContrastChange(f);
    f = m_cameraGui.getFloatSlider("Hue");
    cameraTrackingManager->onHueChange(f);
    b = m_cameraGui.getToggle("LED");
    cameraTrackingManager->onLedChange(b);
    i = m_cameraGui.getIntSlider("Flicker Type");
    cameraTrackingManager->onFlickerChange(i);
    i = m_cameraGui.getIntSlider("White Balance Mode");
    cameraTrackingManager->onWhiteBalanceChange(i);
}

void GuiManager::draw()
{
    if(!m_showGui)
        return;
    
    m_cameraGui.draw();
    guiFPS = ofGetFrameRate();
    m_fluidGui.draw();
    
}


void GuiManager::saveGuiValues()
{
    m_cameraGui.saveToFile(GUI_CAMERA_SETTINGS_FILE_NAME);
    m_fluidGui.saveToFile(GUI_FLUID_SETTINGS_FILE_NAME);
}

void GuiManager::loadGuiValues()
{
    this->loadCameraValues();
}

void GuiManager::toggleGui()
{
    m_showGui = !m_showGui;
}
