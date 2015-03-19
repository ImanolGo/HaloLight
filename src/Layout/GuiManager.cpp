/*
 *  GuiManager.cpp
 *  Halo Light
 *
 *  Created by Imanol Gomez on 19/03/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "SettingsManager.h"
#include "ViewManager.h"
#include "CameraTrackingManager.h"


#include "GuiManager.h"

const string GuiManager::GUI_SETTINGS_FILE_NAME = "xmls/HaloLightGuiSettings.xml";

GuiManager::GuiManager(): Manager(), m_hideGui(false)
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
    
    m_gui.setup("HaloLight", GUI_SETTINGS_FILE_NAME);
    m_gui.setPosition(ofGetWidth()*0.5 + 100,40);
    
    this->setupCameraGui();

}

void GuiManager::setupCameraGui()
{
    
    ofPtr<CameraTrackingManager> cameraTrackingManager = AppManager::getInstance().getCameraTrackingManager();
    
    
    ofxToggle * autoGainAndShutter = new ofxToggle();
    autoGainAndShutter->setup("Auto Gain and Shutter", false);
    autoGainAndShutter->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onAutoGainAndShutterChange);
    m_gui.add(autoGainAndShutter);
    
    ofxFloatSlider * gain = new ofxFloatSlider();
    gain->setup("Gain", 0.5, 0.0, 1.0);
    gain->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onGainChange);
    m_gui.add(gain);
    
    ofxFloatSlider * shutter = new ofxFloatSlider();
    shutter->setup("Shutter", 0.5, 0.0, 1.0);
    shutter->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onShutterChange);
    m_gui.add(shutter);
    
    ofxFloatSlider * gamma = new ofxFloatSlider();
    gamma->setup("Gamma", 0.5, 0.0, 1.0);
    gamma->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onGammaChange);
    m_gui.add(gamma);
    
    ofxFloatSlider * brightness = new ofxFloatSlider();
    brightness->setup("Brightness", 0.5, 0.0, 1.0);
    brightness->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onBrightnessChange);
    m_gui.add(brightness);
    
    ofxFloatSlider * contrast = new ofxFloatSlider();
    contrast->setup("Contrast", 0.5, 0.0, 1.0);
    contrast->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onContrastChange);
    m_gui.add(contrast);
    
    ofxFloatSlider * hue = new ofxFloatSlider();
    hue->setup("Hue", 0.5, 0.0, 1.0);
    hue->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onHueChange);
    m_gui.add(hue);
    
    ofxIntSlider * flicker = new ofxIntSlider();
    flicker->setup("Flicker Type", 0, 0, 2);
    flicker->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onFlickerChange);
    m_gui.add(flicker);
    
    ofxIntSlider * wb = new ofxIntSlider();
    wb->setup("White Balance Mode", 4, 1, 4);
    wb->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onFlickerChange);
    m_gui.add(wb);
    
    ofxToggle * led = new ofxToggle();
    led->setup("LED", true);
    led->addListener(cameraTrackingManager.get(), &CameraTrackingManager::onLedChange);
    m_gui.add(led);
    
    //this->loadCameraValues();
}

void GuiManager::loadCameraValues()
{
    
    ofPtr<CameraTrackingManager> cameraTrackingManager = AppManager::getInstance().getCameraTrackingManager();
    
    m_gui.loadFromFile(GUI_SETTINGS_FILE_NAME);
    bool b;
    float f;
    int i;
    b = m_gui.getToggle("Auto Gain and Shutter");
    cameraTrackingManager->onAutoGainAndShutterChange(b);
    f = m_gui.getFloatSlider("Gain");
    cameraTrackingManager->onGainChange(f);
    f = m_gui.getFloatSlider("Shutter");
    cameraTrackingManager->onShutterChange(f);
    f = m_gui.getFloatSlider("Gamma");
    cameraTrackingManager->onGammaChange(f);
    f = m_gui.getFloatSlider("Brightness");
    cameraTrackingManager->onBrightnessChange(f);
    f = m_gui.getFloatSlider("Contrast");
    cameraTrackingManager->onContrastChange(f);
    f = m_gui.getFloatSlider("Hue");
    cameraTrackingManager->onHueChange(f);
    b = m_gui.getToggle("LED");
    cameraTrackingManager->onLedChange(b);
    i = m_gui.getIntSlider("Flicker Type");
    cameraTrackingManager->onFlickerChange(i);
    i = m_gui.getIntSlider("White Balance Mode");
    cameraTrackingManager->onWhiteBalanceChange(i);
}

void GuiManager::draw()
{
    if(m_hideGui)
        return;
    
    m_gui.draw();
    
}


void GuiManager::saveGuiValues()
{
    m_gui.saveToFile(GUI_SETTINGS_FILE_NAME);
}

void GuiManager::loadGuiValues()
{
    this->loadCameraValues();
}
