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

HaloManager::HaloManager(): Manager(), m_ringSize(0.0)
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
    
    m_haloRings.clear();
    this->setupHaloRings();
    this->setupOPC();
    
    m_haloVisuals.setup();
    
}


void HaloManager::setupHaloRings()
{
    this->createHaloRingsPositions();
    this->createHaloRings();
}

void HaloManager::createHaloRingsPositions()
{
    float margin = 10;
    float wallWidth = ofGetWidth()*0.5 - 2*margin;
    float wallHeight = ofGetHeight()*0.5 - 2*margin;
    float x = ofGetWidth()*0.5 + margin;
    float y = ofGetHeight() + margin;
    ofVec3f wallPosition = ofVec3f(x,y,0);
    
    int maxRingsInRow = 5;
    int minRingsInRow = 4;
    
    m_ringSize = wallWidth / (maxRingsInRow + maxRingsInRow);
    ofLogNotice() <<"HaloManager::createHaloRings->  m_ringSize = " << m_ringSize;
    m_ringSize-= (margin*2*maxRingsInRow);
    
    ofLogNotice() <<"HaloManager::createHaloRings->  m_ringSize = " << m_ringSize;
    
    RingSettingsVector ringsSettingsVector = AppManager::getInstance().getSettingsManager()->getRingsSettingsVector();
    
    
    int colInd = 0;
    int rowInd = 0;
    int colMax = minRingsInRow;
    float leftMargin = margin;
    float topMargin = margin;
    for (int i = 1; i <= ringsSettingsVector.size(); i++) {
        
        if(colInd>=colMax){
            colInd=0;
            rowInd++;
            
            if((rowInd%2==0)){
                colMax = minRingsInRow;
                leftMargin = 2*margin + m_ringSize;
                topMargin = margin;
            }
            else{
                colMax = minRingsInRow;
                leftMargin = margin;
                topMargin = 2*margin + m_ringSize;
            }
        }
        
        float x = wallPosition.x + leftMargin + m_ringSize*0.5 + (2*margin + 2*m_ringSize)*colInd;
        float y = wallPosition.y + topMargin +  m_ringSize*0.5 + (2*margin + 2*m_ringSize)*rowInd;
        
        m_haloRingsPositionMap[i] = ofVec3f(x,y,0);
        
        x-=(ofGetWidth()*0.5);
        m_haloRingsPreviewPositionMap[i] = ofVec3f(x,y,0);
        
        colInd++;
    }
    
    
}

void HaloManager::createHaloRings()
{
    
    RingSettingsVector ringsSettingsVector = AppManager::getInstance().getSettingsManager()->getRingsSettingsVector();
    
    for (int i = 0; i < ringsSettingsVector.size(); i++) {
        HaloRingSettings settings = ringsSettingsVector[i];
        
        ofVec3f ringPosition;
        ofVec3f ringPreviewPosition;
        int key = settings.positionIndex;
        if (m_haloRingsPositionMap.find(key)!= m_haloRingsPositionMap.end()) {
            ringPosition = m_haloRingsPositionMap[key];
            ringPreviewPosition = m_haloRingsPreviewPositionMap[key];
        }
        
        BasicVisual basicVisual = BasicVisual(ringPosition, m_ringSize, m_ringSize);
        ofPtr<HaloRing> haloRing = ofPtr<HaloRing>(new HaloRing(basicVisual,settings));
        haloRing->setPreviewPosition(ringPreviewPosition);
        m_haloRings[settings.id] = haloRing;
        
        ofLogNotice() <<"HaloManager::createHaloRings->  id = " << settings.id  <<", channel = " << settings.channel
        <<", fadeCandyInd = "<< settings.fadeCandyInd << ", numberLeds = " <<  settings.numberLeds <<
        ", x = " <<  ringPosition.x <<  ", y = " <<  ringPosition.y ;
    }
}

void HaloManager::setupOPC()
{
    string ipAddress = AppManager::getInstance().getSettingsManager()->getIpAddress();
    int port = AppManager::getInstance().getSettingsManager()->getPort();
    
    // Connect to the fcserver
    int numFC = 11;
    m_opcClient.setup(ipAddress, port, numFC);
    
    ofLogNotice() <<"HaloManager::setupOPC -> Connect OPC Client to IP Address: " << ipAddress << ", port: " << port;
    
}

void HaloManager::update()
{
    //this->updateHaloRings();
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
        m_opcClient.writeChannel( it->second->getChannel(), it->second->colorData(), it->second->getFadeCandyNum());
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
        it->second->draw();
    }
}
