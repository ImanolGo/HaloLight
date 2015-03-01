//
//  HaloRing.cpp
//
//  Created by Imanol Gomez on 01/03/15.
//
//--------------------------------------------------------------

#include "HaloRing.h"


HaloRing::HaloRing(const BasicVisual& visual, int id, int numberLeds)
{
    m_position = BasicVisual.getPosition();
    m_width = BasicVisual.getWidth();
    m_height = BasicVisual.getHeight();
    m_id = id;
    m_numberLeds = numberLeds;
    
}

HaloRing::~HaloRing()
{
    //Intentionaly left empty
}


void HaloRing::setup()
{
    this->setupLedRing;
}

void HaloRing::setupLedRing()
{
    // Set the pixel data
    pixels.allocate(m_width, m_height,GL_RGB);
    
    for (int i = 0; i < m_numberLeds; i++)
    {
        float angle = (i * 2.0 * M_PI)/m_numberLeds;
        
        // Generate the position of the grabber points
        float rx = m_position.x  + 0.5 * m_width * cos(angle);
        float ry = m_position.y + 0.5 * m_height * sin(angle);
        m_ledPositions.push_back(ofVec2f(rx,ry));
    }
}
//--------------------------------------------------------------
void HaloRing::update()
{
    
    this->grabImageData();
    this->updateLeds();
}

void HaloRing::updateLeds()
{
    
    m_ledColors.clear();
    m_screenPixels.clear();
    
    // Transfer grab data to the pixel array
    m_screenPixels = m_screenImage.getPixelsRef();
    
    for (int i = 0; i < m_ledPositions.size(); i++)
    {
        m_ledColors.push_back(m_screenPixels.getColor(m_ledPositions[i].x, m_ledPositions[i].y));
    }
}
//--------------------------------------------------------------
vector <ofColor> HaloRing::colorData()
{
    // Transmit Data
    return m_ledColors;
}
//--------------------------------------------------------------
void HaloRing::grabImageData()
{
    m_screenImage.clear();
    m_screenImage.grabScreen(m_position.x - m_width*0.5, m_position.y - m_height*0.5,m_width,m_height);
}
//--------------------------------------------------------------
void HaloRing::drawGrabRegion(bool hideArea)
{
    if (hideArea == true)
    {
        // Draw Interaction Area
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(255, 255);
        
        ofEllipse(float x, float y, float width, float height){
        ofEllipse();
        ofCircle(_pos.x, _pos.y, radius+12);
        ofCircle(_pos.x, _pos.y, radius-12);
        ofPopStyle();
        
        // Visualise the Grabber
        ofSetColor(255, 175);
        ofNoFill();
    }
    else
    {
        // Visualise the Grabber
        ofSetColor(0, 175);
        ofNoFill();
    }
    ofCircle(_pos.x, _pos.y, radius+6);
    ofCircle(_pos.x, _pos.y, radius-6);

    for (int i = 0; i < pos.size(); i++)
    {
        ofCircle(pos[i]+ofVec2f(_pos.x-x, _pos.y-y),2);
    }
}
//--------------------------------------------------------------
void HaloRing::ledRing()
{
    ofSetColor(0, 175);
    ofBeginShape();
    
        for (int i = 0; i < size; i++)
        {
            float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size-1);
            
            // Make Circle Points
            float rx = x-x + ((radius+6) * cos(angle));
            float ry = y-y + ((radius+6) * sin(angle));
            ofVertex(rx, ry);
        }
    
        for (int i = 0; i < size; i++)
        {
            float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size-1);
            
            // Make Circle Points
            float rx = x-x + ((radius-6)  * cos(angle));
            float ry = y-y + ((radius-6)  * sin(angle));
            ofVertex(rx, ry);
        }
    
    ofEndShape(true);
    
    for (int i = 0; i < size; i++)
    {
        ofFill();
        ofSetColor(colors[i]);
        ofCircle(pos[i].x-x, pos[i].y-y,4);
    }
}
//--------------------------------------------------------------
void HaloRing::drawRing(int x, int y)
{
    // Where to draw the ring!
    ofPushMatrix();
    ofTranslate(x, y);
    ofFill();
    ofSetColor(100);
    ofRect(-50,-50,100,100);
    ledRing();
    ofPopMatrix();
}