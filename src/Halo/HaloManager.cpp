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

HaloManager::HaloManager(): Manager(), m_ringSize(0.0), m_showRingsPreview(true)
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


	Manager::setup();
    
    m_haloFadeCandys.clear();
    this->setupHaloRings();
    this->setupOPC();
    
    m_haloVisuals.setup();
    
    ofLogNotice() <<"HaloManager::initialized" ;
    
}


void HaloManager::setupHaloRings()
{
    this->createHaloRingsPositions();
    this->createHaloRings();
}

void HaloManager::createHaloRingsPositions()
{
    
    int maxRingsInRow = 5;
    int minRingsInRow = 4;
    float numRingsHeight = 10;
    float numMarginsHeight = numRingsHeight - 1;
    float numMarginsWidth = maxRingsInRow + minRingsInRow - 1;
    float marginRatio = 0.3;
    
    
    float layoutMargin = 20;
    float wallWidth = ofGetWidth()*0.5 - layoutMargin*2;
    m_ringPreviewSize = wallWidth/(maxRingsInRow + minRingsInRow + numMarginsWidth*marginRatio);
    
    //float wallHeight = ofGetHeight() - layoutMargin*4;
    //m_ringPreviewSize = wallHeight/(numRingsHeight + marginRatio*numMarginsHeight);
    m_ringSize = 30;
    float scale = m_ringSize/m_ringPreviewSize;
    float margin = m_ringPreviewSize*marginRatio;
    float wallHeight = m_ringPreviewSize*(numRingsHeight) + numMarginsHeight*margin;
    
    float w = wallWidth;
    float h = wallHeight;
    float x = ofGetWidth()*0.25 - w*0.5;
    float y = ofGetHeight()*0.5 - h*0.5;
    
    m_previewRectangle = ofRectangle(x,y,w,h);
    
    
    w = wallWidth*scale;
    h = wallHeight*scale;
    x = ofGetWidth()*0.75 - w*0.5;
    y = ofGetHeight()*0.75 - h*0.5;
    
    m_imageSpaceRectangle = ofRectangle(x,y,w,h);
 
    
    ofLogNotice() <<"HaloManager::createHaloRingsPositions->  preview size = " << m_ringPreviewSize;
    ofLogNotice() <<"HaloManager::createHaloRingsPositions->  ring size = " << m_ringSize;
    
    ofLogNotice() <<"HaloManager::createHaloRingsPositions->  m_previewRectangle:  x = " << m_previewRectangle.x << ", y = " << m_previewRectangle.y << ", w = " << m_previewRectangle.width << ", h = " << m_previewRectangle.height;
    
    ofLogNotice() <<"HaloManager::createHaloRingsPositions->  m_imageSpaceRectangle:  x = " << m_imageSpaceRectangle.x << ", y = " << m_imageSpaceRectangle.y << ", w = " << m_imageSpaceRectangle.height << ", h = " << m_imageSpaceRectangle.width;
    
    RingSettingsVector ringsSettingsVector = AppManager::getInstance().getSettingsManager()->getRingsSettingsVector();
    
    int colInd = 0;
    int rowInd = 0;
    int colMax = minRingsInRow;
    float leftMargin = m_ringPreviewSize + margin;
    
    ofLogNotice() <<"HaloManager::createHaloRingsPositions->  ringsSettingsVector.size() = " << ringsSettingsVector.size();
    for (int i = 1; i < ringsSettingsVector.size()+1; i++) {
        
        if(colInd>=colMax){
            colInd=0;
            rowInd++;
            
            if((rowInd%2==0)){
                colMax = minRingsInRow;
                leftMargin = m_ringPreviewSize + margin;
            }
            else{
                colMax = maxRingsInRow;
                leftMargin = 0;
            }
        }
        
        float x = m_previewRectangle.x + leftMargin + m_ringPreviewSize*0.5 + (2*m_ringPreviewSize + 2*margin)*colInd;
        float y = m_previewRectangle.y + m_ringPreviewSize*0.5 + (m_ringPreviewSize*0.5 + margin*0.5)*rowInd;
        
        m_haloRingsPreviewPositionMap[i] = ofVec3f(x,y,0);
       
        
        //ofLogNotice() <<"HaloManager::createHaloRingsPreviewPositions->  i = " << i << ", x = " << x << ", y = " << y;
        
       
        x = (x - m_previewRectangle.x)*scale + m_imageSpaceRectangle.x;
        y = (y - m_previewRectangle.y)*scale + m_imageSpaceRectangle.y;
        
        m_haloRingsPositionMap[i] = ofVec3f(x,y,0);
        
        
        colInd++;
    }
    
    
}

void HaloManager::createHaloRings()
{
    RingSettingsVector ringsSettingsVector = AppManager::getInstance().getSettingsManager()->getRingsSettingsVector();
    
    for (int i = 0; i < ringsSettingsVector.size(); i++) {
        HaloRingSettings settings = ringsSettingsVector[i];
        ofPtr<HaloRing> haloRing= this->createSingleHaloRing(settings);
        this->addHaloRing(haloRing);
        
    }
}

ofPtr<HaloRing> HaloManager::createSingleHaloRing(const HaloRingSettings& settings)
{
    ofVec3f ringPosition;
    ofVec3f ringPreviewPosition;
    int key = settings.positionIndex;
    if (m_haloRingsPositionMap.find(key)!= m_haloRingsPositionMap.end()) {
        ringPosition = m_haloRingsPositionMap[key];
        ringPreviewPosition = m_haloRingsPreviewPositionMap[key];
    }
    
    //ofLogNotice() <<"HaloManager::createHaloRings->  id = " << settings.id  <<", channel = " << settings.channel
    //<<", fadeCandyInd = "<< settings.fadeCandyInd << ", numberLeds = " <<  settings.numberLeds <<
    // ", x = " <<  ringPosition.x <<  ", y = " <<  ringPosition.y ;
    
    BasicVisual basicVisual = BasicVisual(ringPosition, m_ringSize, m_ringSize);
    ofPtr<HaloRing> haloRing = ofPtr<HaloRing>(new HaloRing(basicVisual,settings));
    
    
    basicVisual = BasicVisual(ringPreviewPosition, m_ringPreviewSize, m_ringPreviewSize);
    haloRing->setHaloRingPreview(basicVisual);
    
    return haloRing;
}

void HaloManager::addHaloRing(ofPtr<HaloRing> haloRing)
{
    int fadeCandyId = haloRing->getFadeCandyNum();
    
    if(m_haloFadeCandys.find(fadeCandyId)==m_haloFadeCandys.end()){
         ofPtr<HaloFadeCandy> haloFadeCandy = ofPtr<HaloFadeCandy>(new HaloFadeCandy(fadeCandyId));
         m_haloFadeCandys[fadeCandyId] = haloFadeCandy;
    }
   
    m_haloFadeCandys[fadeCandyId]->addHaloRing(haloRing);
}

void HaloManager::setupOPC()
{
    string ipAddress = AppManager::getInstance().getSettingsManager()->getIpAddress();
    int port = AppManager::getInstance().getSettingsManager()->getPort();
    
    // Connect to the fcserver
    m_opcClient.setup(ipAddress, port, NUM_FADE_CANDYS);
    
    ofLogNotice() <<"HaloManager::setupOPC -> Connect OPC Client to IP Address: " << ipAddress << ", port: " << port;
    
}

void HaloManager::update()
{
    this->grabImageData();
    this->updateFadeCandys();
    m_haloVisuals.update();
}


void HaloManager::grabImageData()
{
    m_screenPixels.clear();
    m_screenImage.clear();
    m_screenImage.grabScreen(m_imageSpaceRectangle.x,m_imageSpaceRectangle.y,m_imageSpaceRectangle.width,m_imageSpaceRectangle.height);
    m_screenPixels = m_screenImage.getPixelsRef(); // Transfer grab data to the pixel array
}

void HaloManager::updateFadeCandys()
{
    // If the client is not connected do not try and send information
    if (!m_opcClient.isConnected()){
        // Will continue to try and reconnect to the Pixel Server
        m_opcClient.tryConnecting();
        return;
    }
  
    for(HaloFadeCandyMap::iterator it = m_haloFadeCandys.begin(); it != m_haloFadeCandys.end(); it++){
        it->second->updateHaloRings(m_imageSpaceRectangle, m_screenPixels);
        m_opcClient.writeFadeCandy( it->second->getId(), it->second->getColorData());
    }
    
}

void HaloManager::draw()
{
    m_haloVisuals.draw();
    
    if (m_showRingsPreview) {
        this->drawRectangles();
        this->drawHaloFadeCandys();
    }
   
}

void HaloManager::drawHaloFadeCandys()
{
    for(HaloFadeCandyMap::iterator it = m_haloFadeCandys.begin(); it != m_haloFadeCandys.end(); it++){
        it->second->draw();
    }
}

void HaloManager::drawRectangles()
{
    ofPushMatrix();
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(1);
    
    ofSetColor(255);
    ofRect(m_imageSpaceRectangle);
    
    ofFill();
    ofSetColor(150);
    ofRect(m_previewRectangle);
    
    ofPopStyle();
    ofPopMatrix();

}

