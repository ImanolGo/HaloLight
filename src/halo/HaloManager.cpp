/*
 *  HaloManager.cpp
 *  Halo Light
 *
 *  Created by Imanol Gomez on 01/03/15.
 *
 */


#include "ofMain.h"

#include "HaloManager.h"
#include "AppManager.h"
#include "SettingsManager.h"


const int HaloManager::NUM_FADE_CANDYS = 11;
const int HaloManager::NUM_HALO_RINGS = 85;
const int HaloManager::NUM_HALO_LEDS = 48;

HaloManager::HaloManager(): Manager()
{
	//Intentionally left empty
}


HaloManager::~HaloManager()
{
    ofLogNotice() <<"HaloManager::Destructor" ;
}


void HaloManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"HaloManager::initialized" ;

	Manager::setup();
    
    this->createHaloRings();
    this->setupOPC();
    
    m_haloVisuals.setup();
    
}


void HaloManager::createHaloRings()
{
    
    ofPoint position = ofPoint(ofGetWidth()*0.5, ofGetHeight()*0.5);
    int width = 100;
    int height = 100;
    BasicVisual basicVisual = BasicVisual(position, width, height);
    
    int index = 1;
    int numLeds = 48;
    ofPtr<HaloRing> haloRing = ofPtr<HaloRing>(new HaloRing(basicVisual, index, numLeds));
    m_haloRings[index] = haloRing;
}

void HaloManager::setupOPC()
{
    string ipAddress = AppManager::getInstance().getSettingsManager()->getIpAddress();
    int port = AppManager::getInstance().getSettingsManager()->getPort();
    
    // Connect to the fcserver
    m_opcClient.setup(ipAddress, port);
    
    ofLogNotice() <<"HaloManager::setupOPC -> Connect OPC Client to IP Address: " << ipAddress << ", port: " << port;
    
}

void HaloManager::update()
{
    this->updateHaloRings();
    m_haloVisuals.update();
}

void HaloManager::updateHaloRings()
{
    // If the client is not connected do not try and send information
    if (!m_opcClient.isConnected()){
        // Will continue to try and reconnect to the Pixel Server
        m_opcClient.tryConnecting();
        return;
    }
  
    for(HaloRingMap::iterator it = m_haloRings.begin(); it != m_haloRings.end(); it++){
        it->second->update();
        m_opcClient.writeChannelOne( it->second->colorData());
    }
    
}

void HaloManager::draw()
{
    m_haloVisuals.draw();
    this->drawHaloRings();
}

void HaloManager::drawHaloRings()
{
    for(HaloRingMap::iterator it = m_haloRings.begin(); it != m_haloRings.end(); it++){
        it->second->drawGrabRegion(true);
    }
}
