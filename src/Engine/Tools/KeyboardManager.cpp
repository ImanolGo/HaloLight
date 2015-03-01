/*
 *  KeyboardManager.cpp
 *
 *  Created by Imanol Gomez on 23/02/15.
 *
 */


#include "KeyboardManager.h"
#include "StateManager.h"
#include "AppManager.h"


KeyboardManager::KeyboardManager(): Manager()
{
    //Intentionally left empty
}

KeyboardManager::~KeyboardManager()
{
   ofLogNotice() << "KeyboardManager::destructor";
}


//--------------------------------------------------------------

void KeyboardManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    ofLogNotice() <<"KeyboardManager::initialized" ;
    this->addListeners();
}

void KeyboardManager::addListeners()
{
    ofRegisterKeyEvents(this); // this will enable the InteractiveVisual class to listen to the key events.
}

void KeyboardManager::keyPressed(ofKeyEventArgs &e)
{
    int key = e.key;
    
    ofLogNotice() <<"KeyboardManager::keyPressed-> " + ofToString(key);
    
    if(key == '1'){
        //AppManager::getInstance().getStateManager()->changeState("SimpleVoronoiState");
        AppManager::getInstance().getSeedsManager()->setSeedsScale(20);
    }

    else if(key == '2'){
        AppManager::getInstance().getSeedsManager()->setSeedsScale(0);
    }
	else if(key == '3'){
        AppManager::getInstance().getSeedsManager()->setParticlesScale(4);
	}
	else if(key == '4'){
        AppManager::getInstance().getSeedsManager()->setParticlesScale(0);
	}
    
    else if(key == '5'){
        ofColor color = AppManager::getInstance().getSettingsManager()->getColor("RockColor1");
        AppManager::getInstance().getSeedsManager()->setColor(color);
    }
    
    else if(key == '6'){
        ofColor color = AppManager::getInstance().getSettingsManager()->getColor("RockColor2");
        AppManager::getInstance().getSeedsManager()->setColor(color);
    }
    
    else if(key == '7'){
        ofColor color = AppManager::getInstance().getSettingsManager()->getColor("RockColor3");
        AppManager::getInstance().getSeedsManager()->setColor(color);
    }
    
    else if(key == '8'){
        ofColor color = AppManager::getInstance().getSettingsManager()->getColor("RockColorBlack");
        AppManager::getInstance().getSeedsManager()->setColor(color);
    }
    
    else if(key == 'a'){
        AppManager::getInstance().getVoronoiManager()->enableJitter();
    }
    
    else if(key == 'q'){
        AppManager::getInstance().getVoronoiManager()->disableJitter();
    }
    
    else if(key == 's'){
        AppManager::getInstance().getVoronoiManager()->enableMagnifying();
    }
    
    else if(key == 'w'){
        AppManager::getInstance().getVoronoiManager()->disableMagnifying();
    }
    
    else if(key == 'd'){
        AppManager::getInstance().getVoronoiManager()->enableOrbit();
    }
    
    else if(key == 'e'){
        AppManager::getInstance().getVoronoiManager()->disableOrbit();
    }
    
}

void KeyboardManager::keyReleased(ofKeyEventArgs &e)
{
     //Intentionally left empty
}










