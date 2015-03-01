/*
 *  HaloManager.cpp
 *  Halo Light
 *
 *  Created by Imanol Gomez on 01/03/15.
 *
 */


#include "ofMain.h"

#include "HaloManager.h"

HaloManager::HaloManager(): Manager(), m_appHeight(0.0), m_appWidth(0.0)
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

}

void HaloManager::update()
{
   
}
