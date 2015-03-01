/*
 *  LayoutManager.cpp
 *  The Other
 *
 *  Created by Imanol Gómez on 16/02/15.
 *
 */

#include "ofMain.h"

#include "../Main/AppManager.h"
#include "../Main/SettingsManager.h"
#include "../Visuals/ViewManager.h"


#include "LayoutManager.h"

LayoutManager::LayoutManager(): Manager()
{
	//Intentionally left empty
}


LayoutManager::~LayoutManager()
{
    ofLogNotice() <<"LayoutManager::Destructor";
}


void LayoutManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"LayoutManager::initialized";

	Manager::setup();

    this->createTextVisuals();
    this->createSvgVisuals();
    this->createImageVisuals();

    this->addVisuals();

}


void LayoutManager::createTextVisuals()
{
    ///To implement in case we have text visuals
}

void LayoutManager::createSvgVisuals()
{
    ///To implement in case we have text visuals
}


void LayoutManager::createImageVisuals()
{
    //this->createBackground();
}

void LayoutManager::createBackground()
{
    float appWidth =  AppManager::getInstance().getSettingsManager()->getAppWidth();
    float appHeight = AppManager::getInstance().getSettingsManager()->getAppHeight();
    
    ofVec3f position(0,0);
    string resourceName = "Background";
    ofPtr<ImageVisual> imageVisual = ofPtr<ImageVisual>(new ImageVisual(position,resourceName));
    imageVisual->setWidth(appWidth);
    imageVisual->setHeight(appHeight);
    
    m_imageVisuals[resourceName] = imageVisual;
    
    int depthLevel = -2;
    AppManager::getInstance().getViewManager()->addOverlay(m_imageVisuals[resourceName],depthLevel);
}

void LayoutManager::addVisuals()
{
    int depthLevel = -1;
    for(SvgMap::iterator it = m_svgVisuals.begin(); it!= m_svgVisuals.end(); ++it){
        AppManager::getInstance().getViewManager()->addOverlay(it->second,depthLevel);
    }

    for(TextMap::iterator it = m_textVisuals.begin(); it!= m_textVisuals.end(); ++it){
        AppManager::getInstance().getViewManager()->addOverlay(it->second,depthLevel);
    }

    for(ImageMap::iterator it = m_imageVisuals.begin(); it!= m_imageVisuals.end(); ++it){
        AppManager::getInstance().getViewManager()->addOverlay(it->second,depthLevel);
    }
}


