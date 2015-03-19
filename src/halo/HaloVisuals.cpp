/*
 *  HaloVisuals.cpp
 *  Halo Light
 *
 *  Created by Imanol Gomez on 04/03/15.
 *
 */


#include "ofMain.h"

#include "AppManager.h"
#include "HaloManager.h"

#include "HaloVisuals.h"


HaloVisuals::HaloVisuals(): BasicVisual()
{
    //Intentionaly left empty
}


HaloVisuals::~HaloVisuals()
{
    //Intentionaly left empty
}


void HaloVisuals::setup()
{
    m_mode = 0;
    //ofSetCircleResolution(100);
    this->createImageVisuals();
    this->setupFluid();
    
}


void HaloVisuals::createImageVisuals()
{
    string resourceName = "Dot";
    m_imageVisual = ofPtr<ImageVisual>(new ImageVisual(ofVec3f(0,0,0),resourceName,true));
}

void HaloVisuals::setupFluid()
{
    ofRectangle area = AppManager::getInstance().getHaloManager()->getRingArea();
    
    // Initial Allocation
    //
    m_fluid.allocate(area.width, area.height, 0.5);
    
    // Seting the gravity set up & injecting the background image
    //
    m_fluid.dissipation = 0.99;
    m_fluid.velocityDissipation = 0.99;
    
    m_fluid.setGravity(ofVec2f(0.0,0.0));
    m_fluid.setGravity(ofVec2f(0.0,0.0098));
    
    //  Set obstacle
    //
    m_fluid.begin();
    ofSetColor(0,0);
    ofSetColor(255);
    ofCircle(area.width*0.5, area.height*0.5, 80);
    m_fluid.end();
    m_fluid.setUseObstacles(false);
    
    // Adding constant forces
    //
    m_fluid.addConstantForce(ofPoint(area.width*0.5,area.height*0.95), ofPoint(0,-2), ofFloatColor(0.5,0.1,0.0), 10.f);
    //m_fluid.addConstantForce(ofPoint(area.width*0.5,area.height*0.95), ofPoint(-1,-2), ofFloatColor(0.5,0.1,1.0), 10.f);
}


void HaloVisuals::update()
{
    this->updateFluid();
}

void HaloVisuals::updateFluid()
{
    ofRectangle area = AppManager::getInstance().getHaloManager()->getRingArea();
    
    // Adding temporal Force
    //
    ofPoint m = ofPoint(ofGetMouseX(),ofGetMouseY());
    ofPoint d = (m - m_oldMouse)*10.0;
    m_oldMouse = m;
    ofPoint c = ofPoint(area.width*0.5, area.height*0.5) - m;
    c.normalize();
    m_fluid.addTemporalForce(m, d, ofFloatColor(c.x,c.y,0.5)*sin(ofGetElapsedTimef()),3.0f);
    
    //  Update
    //
    m_fluid.update();
}

void HaloVisuals::draw()
{
    this->drawEffects();
}

void HaloVisuals::drawEffects()
{
    switch (m_mode) {
        case 0:
        {
            // Mouse Circle
            ofPushStyle();
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofFill();
            ofCircle(ofGetMouseX(),ofGetMouseY(),70);
            ofPopStyle();
        }
            break;
            
        case 1:
        {
            ofPushStyle();
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            int size = 350;
            
            ofColor color = ofColor::fromHsb(hue, 255, 255);
            ofVec3f pos = ofVec3f(ofGetMouseX(), ofGetMouseY());
            m_imageVisual->setColor(color);
            m_imageVisual->setWidth(size);
            m_imageVisual->setHeight(size);
            m_imageVisual->setPosition(pos);
            m_imageVisual->setPosition(pos);
            m_imageVisual->draw();
            
            ofPopStyle();
        }
            break;
            
        case 2:
        {
            ofRectangle area = AppManager::getInstance().getHaloManager()->getRingArea();
            
            m_fluid.draw(area.x,area.y,area.width,area.height);
        }
            break;
            
        case 3:
        {
           
        }
            break;
            
        default:
            break;
    }
}