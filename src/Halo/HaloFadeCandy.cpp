//
//  HaloFadeCandy.cpp
//
//  Created by Imanol Gomez on 01/03/15.
//
//--------------------------------------------------------------

#include "ofxOPC.h"
#include "HaloFadeCandy.h"


HaloFadeCandy::HaloFadeCandy(int id): m_id(id)
{
    this->setup();
}

HaloFadeCandy::~HaloFadeCandy()
{
    //Intentionaly left empty
}


void HaloFadeCandy::setup()
{
    this->createLedColorVector();
}

void HaloFadeCandy::createLedColorVector()
{
    m_ledColors.clear();
    
    size_t size = FADE_CANDY_NUM_CHANNELS*LEDS_PER_CHANNEL;
    m_ledColors = vector <ofColor> (size,ofColor::black);
}

void HaloFadeCandy::addHaloRing(ofPtr<HaloRing> haloRing)
{
    if (haloRing!= NULL) {
        m_haloRings[haloRing->getId()] = haloRing;
    }
    
}

void HaloFadeCandy::updateHaloRings(const ofRectangle &grabArea, const ofPixels &screenPixels)
{
    for(HaloRingsMap::iterator it = m_haloRings.begin(); it != m_haloRings.end(); it++){
        
        int channel = it->second->getChannel();
        
        if (channel > 0 && channel <= FADE_CANDY_NUM_CHANNELS ) {
            int offset = (channel-1)*LEDS_PER_CHANNEL;
            
            it->second->setPixels(grabArea, screenPixels);
            vector<ofColor> colorData =  it->second->colorData();
            std::copy ( colorData.begin(), colorData.end(), m_ledColors.begin() + offset);

        }        
        
    }
    
}


void HaloFadeCandy::draw()
{
    this->drawHaloRings();
}

void HaloFadeCandy::drawHaloRings()
{
    for(HaloRingsMap::iterator it = m_haloRings.begin(); it != m_haloRings.end(); it++){
        it->second->draw();
    }
}


