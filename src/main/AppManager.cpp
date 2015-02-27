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

AppManager::AppManager(): Manager(), m_logVerbose(false)
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

}

void AppManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() << "AppManager::initialized";

	Manager::setup();

    this->setupOF();
	this->setupManagers();
}

void AppManager::setupOF()
{
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    //ofLogToFile("LogFile.txt");
    ofTrueTypeFont::setGlobalDpi(96);

    ofAddListener(ofEvents().keyPressed, this, &AppManager::keyPressed);
}


void AppManager::setupManagers()
{
    m_settingsManager->setup();
}

void AppManager::update()
{
    
}


void AppManager::draw()
{
}

void AppManager::keyPressed(ofKeyEventArgs &e)
{
    int key = e.key;
    if(key == ' ') {
        m_logVerbose = !m_logVerbose;
        if(m_logVerbose){
             ofSetLogLevel(OF_LOG_VERBOSE);
        }
        else{
             ofSetLogLevel(OF_LOG_NOTICE);
        }

    }
}


