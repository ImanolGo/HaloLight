/*
 *  AppManager.cpp
 *  Halo Light
 *
 *  Created by Imanol Gomez on 27/02/15.
 *
 */

#include "ofMain.h"


#include "AppManager.h"

AppManager& AppManager::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	static AppManager    m_instance;
    return m_instance;

}

AppManager::AppManager(): Manager(), m_debugMode(false)
{
    this->createManagers();
}


AppManager::~AppManager()
{
    ofLogNotice() <<"AppManager::Destructor";
}


void AppManager::createManagers()
{
    m_settingsManager = ofPtr<SettingsManager>(new SettingsManager());
    m_resourceManager = ofPtr<ResourceManager>(new ResourceManager());
    m_visualEffectsManager = ofPtr<VisualEffectsManager>(new VisualEffectsManager());
    m_viewManager = ofPtr<ViewManager>(new ViewManager());
    m_layoutManager = ofPtr<LayoutManager>(new LayoutManager());
    m_keyboardManager = ofPtr<KeyboardManager>(new KeyboardManager());
    m_haloManager = ofPtr<HaloManager>(new HaloManager());
    m_cameraTrackingManager = ofPtr<CameraTrackingManager>(new CameraTrackingManager());
    m_guiManager = ofPtr<GuiManager>(new GuiManager());
}

void AppManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() << "AppManager::initialized";

	Manager::setup();

    setDebugMode(m_debugMode);
    
    this->setupOF();
	this->setupManagers();
}

void AppManager::setupOF()
{
   ofSetVerticalSync(false);
   ofDisableAlphaBlending();
   ofDisableSmoothing();
   ofDisableDepthTest();
   ofDisableLighting();
   ofDisableBlendMode();
   ofDisableAntiAliasing();
   ofShowCursor();
}


void AppManager::setupManagers()
{
    m_settingsManager->setup();
    m_resourceManager->setup();
    m_viewManager->setup();
    m_visualEffectsManager->setup();
    m_layoutManager->setup();
    m_keyboardManager->setup();
    m_cameraTrackingManager->setup();
    m_haloManager->setup();
    m_guiManager->setup();

}

void AppManager::update()
{
    m_visualEffectsManager->update();
    m_viewManager->update();
    m_haloManager->update();
    m_cameraTrackingManager->update();
}


void AppManager::draw()
{
    m_viewManager->draw();
    m_haloManager->draw();
    m_cameraTrackingManager->draw();
    m_guiManager->draw();
    
}

void AppManager::toggleDebugMode()
{
    m_debugMode = !m_debugMode;
    setDebugMode(m_debugMode);
}


void AppManager::setDebugMode(bool showDebug)
{
    m_debugMode = showDebug;
    
    ofLogNotice()<<"AppManager::setDebugMode-> " << m_debugMode;
    
    if(m_debugMode){
        ofSetLogLevel(OF_LOG_VERBOSE);
    }
    else{
        ofSetLogLevel(OF_LOG_NOTICE);
    }
    
    m_viewManager->showDebugMode(m_debugMode);
    
}



