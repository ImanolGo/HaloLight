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
    //this->setupFluid();
    this->setupFtFluid();
    
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

void HaloVisuals::setupFtFluid()
{
    int drawWidth =  AppManager::getInstance().getCameraTrackingManager()->getWidth();
    int drawHeight = AppManager::getInstance().getCameraTrackingManager()->getHeight();
    // process all but the density on 16th resolution
    int flowWidth = drawWidth/4;
    int flowHeight = drawHeight/4;
    
    
    // Flow & Mask
    m_opticalFlow.setup(flowWidth, flowHeight);
    m_velocityMask.setup(drawWidth, drawHeight);
    
    // Fluid
    #ifdef USE_FASTER_INTERNAL_FORMATS
        m_ftFluid.setup(flowWidth, flowHeight, drawWidth, drawHeight, true);
    #else
        m_ftFluid.setup(flowWidth, flowHeight, drawWidth, drawHeight, false);
    #endif
    
    // Visualisation
    m_temperatureField.allocate(flowWidth / 4, flowHeight / 4);
    
    
    // Draw Forces
    int numDrawForces = 6;
    m_flexDrawForces = new ftDrawForce[numDrawForces];
    m_flexDrawForces[0].setup(drawWidth, drawHeight, FT_DENSITY, true);
    m_flexDrawForces[0].setName("draw full res");
    m_flexDrawForces[1].setup(flowWidth, flowHeight, FT_VELOCITY, true);
    m_flexDrawForces[1].setName("draw flow res 1");
    m_flexDrawForces[2].setup(flowWidth, flowHeight, FT_TEMPERATURE, true);
    m_flexDrawForces[2].setName("draw flow res 2");
    m_flexDrawForces[3].setup(drawWidth, drawHeight, FT_DENSITY, false);
    m_flexDrawForces[3].setName("draw full res");
    m_flexDrawForces[4].setup(flowWidth, flowHeight, FT_VELOCITY, false);
    m_flexDrawForces[4].setName("draw flow res 1");
    m_flexDrawForces[5].setup(flowWidth, flowHeight, FT_TEMPERATURE, false);
    m_flexDrawForces[5].setName("draw flow res 2");
}

void HaloVisuals::update()
{
    //this->updateFluid();
}

void HaloVisuals::updateFluid()
{
    ofRectangle area = AppManager::getInstance().getHaloManager()->getRingArea();
    
    // Adding temporal Force
    //
    ofPoint m = ofPoint(ofGetMouseX(),ofGetMouseY());
    ofPoint d = (m - m_lastMouse)*10.0;
    m_lastMouse = m;
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
            
            //m_fluid.draw(area.x,area.y,area.width,area.height);
        }
            break;
            
        case 3:
        {
            bool newFrame = AppManager::getInstance().getCameraTrackingManager()->isFrameNew();
            double dt = ofGetLastFrameTime();
            
            if (newFrame) {
                ofFbo cameraFbo = AppManager::getInstance().getCameraTrackingManager()->getCameraFbo();
                m_opticalFlow.setSource(cameraFbo.getTextureReference());
                m_opticalFlow.update(dt);
                
                m_velocityMask.setDensity(cameraFbo.getTextureReference());
                m_velocityMask.setVelocity(m_opticalFlow.getOpticalFlow());
                m_velocityMask.update();
            }
            
            
            m_ftFluid.addVelocity(m_opticalFlow.getOpticalFlowDecay());
            m_ftFluid.addDensity(m_velocityMask.getColorMask());
            m_ftFluid.addTemperature(m_velocityMask.getLuminanceMask());
            
            
            for (int i=0; i<6; i++) {
                m_flexDrawForces[i].update();
                if (m_flexDrawForces[i].didChange()) {
                    // if a force is constant multiply by deltaTime
                    float strength = m_flexDrawForces[i].getStrength();
                    if (!m_flexDrawForces[i].getIsTemporary())
                        strength *=dt;
                    switch (m_flexDrawForces[i].getType()) {
                        case FT_DENSITY:
                            m_ftFluid.addDensity(m_flexDrawForces[i].getTextureReference(), strength);
                            break;
                        case FT_VELOCITY:
                            m_ftFluid.addVelocity(m_flexDrawForces[i].getTextureReference(), strength);
                            //particleFlow.addFlowVelocity(m_flexDrawForces[i].getTextureReference(), strength);
                            break;
                        case FT_TEMPERATURE:
                            m_ftFluid.addTemperature(m_flexDrawForces[i].getTextureReference(), strength);
                            break;
                        case FT_PRESSURE:
                            m_ftFluid.addPressure(m_flexDrawForces[i].getTextureReference(), strength);
                            break;
                        case FT_OBSTACLE:
                            m_ftFluid.addTempObstacle(m_flexDrawForces[i].getTextureReference());
                        default:
                            break;
                    }
                }
            }
            
            m_ftFluid.update();
            
            ofRectangle area = AppManager::getInstance().getHaloManager()->getRingArea();
            ofPushStyle();
                m_ftFluid.draw(area.x, area.y, area.width, area.height);
            ofPopStyle();
           
        }
            break;
            
        case 4:
        {
            ofVec2f mouse;
            
            mouse.set(ofGetMouseX() / (float)ofGetWindowWidth(), ofGetMouseY()  / (float)ofGetWindowHeight());
            ofVec2f velocity = mouse - m_lastMouse;
            
            for (int i=0; i<3; i++) {
                if (m_flexDrawForces[i].getType() == FT_VELOCITY)
                    m_flexDrawForces[i].setForce(velocity);
                m_flexDrawForces[i].applyForce(mouse);
            }
            
            m_lastMouse.set(mouse.x, mouse.y);
            
            double dt = ofGetLastFrameTime();
            for (int i=0; i<6; i++) {
                m_flexDrawForces[i].update();
                if (m_flexDrawForces[i].didChange()) {
                    // if a force is constant multiply by deltaTime
                    float strength = m_flexDrawForces[i].getStrength();
                    if (!m_flexDrawForces[i].getIsTemporary())
                        strength *=dt;
                    switch (m_flexDrawForces[i].getType()) {
                        case FT_DENSITY:
                            m_ftFluid.addDensity(m_flexDrawForces[i].getTextureReference(), strength);
                            break;
                        case FT_VELOCITY:
                            m_ftFluid.addVelocity(m_flexDrawForces[i].getTextureReference(), strength);
                            //particleFlow.addFlowVelocity(m_flexDrawForces[i].getTextureReference(), strength);
                            break;
                        case FT_TEMPERATURE:
                            m_ftFluid.addTemperature(m_flexDrawForces[i].getTextureReference(), strength);
                            break;
                        case FT_PRESSURE:
                            m_ftFluid.addPressure(m_flexDrawForces[i].getTextureReference(), strength);
                            break;
                        case FT_OBSTACLE:
                            m_ftFluid.addTempObstacle(m_flexDrawForces[i].getTextureReference());
                        default:
                            break;
                    }
                }
            }
            
            m_ftFluid.update();

            
            ofRectangle area = AppManager::getInstance().getHaloManager()->getRingArea();
            
            ofPushStyle();
                ofEnableBlendMode(OF_BLENDMODE_ADD);
                m_ftFluid.draw(0, 0, ofGetWidth(),ofGetHeight());
            ofPopStyle();
            
        }
            break;
            
        default:
            break;
    }
}