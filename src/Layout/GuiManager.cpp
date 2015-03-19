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


#include "GuiManager.h"

GuiManager::GuiManager(): Manager()
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

}
