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


HaloVisuals::HaloVisuals()
{
    //Intentionaly left empty
}


HaloVisuals::~HaloVisuals()
{
    //Intentionaly left empty
}


void HaloVisuals::setup()
{
    m_mode = 1;
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
    ofSetVerticalSync(false);
    
    int drawWidth = 1280;
    int drawHeight = 720;
    
    // process all but the density on 16th resolution
    int flowWidth = drawWidth/4;
    int flowHeight = drawHeight/4;
    
    // Flow & Mask
    m_opticalFlow.setup(flowWidth, flowHeight);
    m_velocityMask.setup(drawWidth, drawHeight);
    
    // m_fluid
#ifdef USE_FASTER_INTERNAL_FORMATS
    m_fluid.setup(flowWidth, flowHeight, drawWidth, drawHeight, true);
#else
    m_fluid.setup(flowWidth, flowHeight, drawWidth, drawHeight, false);
#endif
    
    
    // Visualisation
    m_displayScalar.allocate(flowWidth, flowHeight);
    m_velocityField.allocate(flowWidth / 4, flowHeight / 4);
    m_temperatureField.allocate(flowWidth / 4, flowHeight / 4);
    
    // Draw Forces
    m_numDrawForces = 6;
    m_flexDrawForces = new ftDrawForce[m_numDrawForces];
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
    
    setupGui();
    
    m_lastMouse.set(0,0);
    
}


void HaloVisuals::setupGui()
{
    gui.setup("settings");
    gui.setDefaultBackgroundColor(ofColor(0, 0, 0, 127));
    gui.setDefaultFillColor(ofColor(160, 160, 160, 160));
    gui.add(guiFPS.set("FPS", 0, 0, 60));
    
    int guiColorSwitch = 0;
    ofColor guiHeaderColor[2];
    guiHeaderColor[0].set(160, 160, 80, 200);
    guiHeaderColor[1].set(80, 160, 160, 200);
    ofColor guiFillColor[2];
    guiFillColor[0].set(160, 160, 80, 200);
    guiFillColor[1].set(80, 160, 160, 200);
    
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(m_opticalFlow.parameters);
    
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(m_velocityMask.parameters);
    
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(m_fluid.parameters);
    
    visualisationParameters.setName("visualisation");
    visualisationParameters.add(showScalar.set("show scalar", true));
    visualisationParameters.add(showField.set("show field", true));
    visualisationParameters.add(displayScalarScale.set("display scalar scale", 0.25, 0.05, 0.5));
    displayScalarScale.addListener(this, &HaloVisuals::setDisplayScalarScale);
    visualisationParameters.add(velocityFieldArrowScale.set("arrow scale", 0.6, 0.2, 1));
    velocityFieldArrowScale.addListener(this, &HaloVisuals::setVelocityFieldArrowScale);
    visualisationParameters.add(temperatureFieldBarScale.set("temperature scale", 0.25, 0.05, 0.5));
    temperatureFieldBarScale.addListener(this, &HaloVisuals::setTemperatureFieldBarScale);
    visualisationParameters.add(visualisationLineSmooth.set("line smooth", false));
    visualisationLineSmooth.addListener(this, &HaloVisuals::setVisualisationLineSmooth);
    
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(visualisationParameters);
    
    leftButtonParameters.setName("mouse left button");
    for (int i=0; i<3; i++) {
        leftButtonParameters.add(m_flexDrawForces[i].parameters);
    }
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(leftButtonParameters);
    
    rightButtonParameters.setName("mouse right button");
    for (int i=3; i<6; i++) {
        rightButtonParameters.add(m_flexDrawForces[i].parameters);
    }
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(rightButtonParameters);
    
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(doResetDrawForces.set("reset draw forces (D)", false));
    doResetDrawForces.addListener(this,  &HaloVisuals::resetDrawForces);
    
    gui.loadFromFile("settings.xml");
    gui.minimizeAll();
    
    toggleGuiDraw = true;
}


void HaloVisuals::update()
{
    this->updateFluid();
}

void HaloVisuals::updateFluid()
{
}

void HaloVisuals::draw()
{
    this->drawEffects();
}

void HaloVisuals::drawEffects()
{
    switch (m_mode) {
        case 1:
        {
            this->drawCircle();
        }
            break;
            
        case 2:
        {
            this->drawParticle();
        }
            break;
            
        case 3:
        {
            this->drawFluid();
        }
            break;
            
        case 4:
        {
            this->drawPaintFluid();
        }
            break;
            
    }
}

void HaloVisuals::drawCircle()
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

void HaloVisuals::drawParticle()
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

void HaloVisuals::drawFluid()
{
    
    bool newFrame = AppManager::getInstance().getCameraTrackingManager()->isNewFrame();
    double dt = ofGetLastFrameTime();
    
    if (newFrame) {
        ofFbo cameraFbo = AppManager::getInstance().getCameraTrackingManager()->getCameraFbo();
        
        m_opticalFlow.setSource(cameraFbo.getTextureReference());
        m_opticalFlow.update(dt);
        
        m_velocityMask.setDensity(cameraFbo.getTextureReference());
        m_velocityMask.setVelocity(m_opticalFlow.getOpticalFlow());
        m_velocityMask.update();
    }
    
    
    m_fluid.addVelocity(m_opticalFlow.getOpticalFlowDecay());
    m_fluid.addDensity(m_velocityMask.getColorMask());
    m_fluid.addTemperature(m_velocityMask.getLuminanceMask());
    
    for (int i=0; i<m_numDrawForces; i++) {
        m_flexDrawForces[i].update();
        if (m_flexDrawForces[i].didChange()) {
            // if a force is constant multiply by deltaTime
            float strength = m_flexDrawForces[i].getStrength();
            if (!m_flexDrawForces[i].getIsTemporary())
                strength *=dt;
            switch (m_flexDrawForces[i].getType()) {
                case FT_DENSITY:
                    m_fluid.addDensity(m_flexDrawForces[i].getTextureReference(), strength);
                    break;
                case FT_VELOCITY:
                    m_fluid.addVelocity(m_flexDrawForces[i].getTextureReference(), strength);
                    break;
                case FT_TEMPERATURE:
                    m_fluid.addTemperature(m_flexDrawForces[i].getTextureReference(), strength);
                    break;
                case FT_PRESSURE:
                    m_fluid.addPressure(m_flexDrawForces[i].getTextureReference(), strength);
                    break;
                case FT_OBSTACLE:
                    m_fluid.addTempObstacle(m_flexDrawForces[i].getTextureReference());
                default:
                    break;
            }
        }
    }
    
    m_fluid.update();
    
    //ofClear(0,0);
    
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    //cameraFbo.draw(windowWidth*0.5,40, 640, 480);
    
    const ofRectangle& ringArea = AppManager::getInstance().getHaloManager()->getRingArea();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    m_fluid.draw(ringArea.x, ringArea.y, ringArea.width,ringArea.height);
    ofPopStyle();
    
    if (toggleGuiDraw) {
        guiFPS = ofGetFrameRate();
        gui.draw();
    }
    
}

void HaloVisuals::drawPaintFluid()
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
                    m_fluid.addDensity(m_flexDrawForces[i].getTextureReference(), strength);
                    break;
                case FT_VELOCITY:
                    m_fluid.addVelocity(m_flexDrawForces[i].getTextureReference(), strength);
                    //particleFlow.addFlowVelocity(m_flexDrawForces[i].getTextureReference(), strength);
                    break;
                case FT_TEMPERATURE:
                    m_fluid.addTemperature(m_flexDrawForces[i].getTextureReference(), strength);
                    break;
                case FT_PRESSURE:
                    m_fluid.addPressure(m_flexDrawForces[i].getTextureReference(), strength);
                    break;
                case FT_OBSTACLE:
                    m_fluid.addTempObstacle(m_flexDrawForces[i].getTextureReference());
                default:
                    break;
            }
        }
    }
    
    m_fluid.update();
    
    
    ofRectangle area = AppManager::getInstance().getHaloManager()->getRingArea();
    
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    m_fluid.draw(0, 0, ofGetWidth(),ofGetHeight());
    ofPopStyle();
}