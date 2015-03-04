/*
 *  HaloVisuals.cpp
 *  Halo Light
 *
 *  Created by Imanol Gomez on 04/03/15.
 *
 */


#include "ofMain.h"

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
    this->createImageVisuals();
    
}


void HaloVisuals::createImageVisuals()
{
    string resourceName = "Dot";
    m_imageVisual = ofPtr<ImageVisual>(new ImageVisual(ofVec3f(0,0,0),resourceName,true));
}


void HaloVisuals::update()
{
    //To be implemented
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
            // Like the processing example draw dot images and rotate
            int size = 160;
            ofPushMatrix();
            ofTranslate(0, 0);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
            ofRotateZ(ofGetElapsedTimeMillis()/10);
            ofPushMatrix();
            ofTranslate(-size*0.5,-size*0.5);
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofColor color = ofColor::green;
            ofVec3f pos = ofVec3f(size/4, size/4);
            m_imageVisual->setWidth(size);
            m_imageVisual->setHeight(size);
            m_imageVisual->setColor(color);
            m_imageVisual->setPosition(pos);
            m_imageVisual->draw();
            
            color = ofColor::red;
            pos = ofVec3f((size/4*3), size/4);
            m_imageVisual->setColor(color);
            m_imageVisual->setPosition(pos);
            m_imageVisual->draw();
            
            color = ofColor::blue;
            pos = ofVec3f(size/4, (size/4*3));
            m_imageVisual->setColor(color);
            m_imageVisual->setPosition(pos);
            m_imageVisual->draw();
            
            color = ofColor(255,0,255);
            pos = ofVec3f((size/4*3),(size/4*3));
            m_imageVisual->setColor(color);
            m_imageVisual->setPosition(pos);
            m_imageVisual->draw();
                          

            ofDisableBlendMode();
            ofPopMatrix();
            ofPopMatrix();
            ofPopMatrix();
        }
            break;
            
        case 2:
        {
            // Changes the color of a Circle
            ofPushStyle();
            ofFill();
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofCircle(ofGetWidth()/2,ofGetHeight()/2,70);
            ofPopStyle();
        }
            break;
            
        case 3:
        {
            // Fade to full brightness then to zero
            ofPushStyle();
            ofFill();
            ofSetColor((int)(128 + 128 * sin(ofGetElapsedTimef())));
            ofCircle(ofGetWidth()/2,ofGetHeight()/2,70);
            ofPopStyle();
        }
            break;
            
        case 4:
        {
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofFill();
            float rotationAmount = ofGetElapsedTimeMillis()/10;
            ofSetColor(255, 0, 0);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(rotationAmount);
            ofPushMatrix();
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
            ofCircle(ofGetWidth()/2, ofGetHeight()/2-40, 40);
            ofPopMatrix();
            ofPopMatrix();
            ofSetColor(0, 0, 255);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(-rotationAmount);
            ofPushMatrix();
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
            ofCircle(ofGetWidth()/2, ofGetHeight()/2+40, 40);
            ofPopMatrix();
            ofPopMatrix();
            ofDisableBlendMode();
        }
            break;
            
        case 5:
        {
            ofPushStyle();
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            int size = 150;
            
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
        default:
            break;
    }
}