//
//  HaloRing.cpp
//
//  Created by Imanol Gomez on 01/03/15.
//
//--------------------------------------------------------------

#include "HaloRing.h"


HaloRing::HaloRing(const BasicVisual& visual, int id, int numberLeds)
{
    m_position = visual.getPosition();
    m_width = visual.getWidth();
    m_height = visual.getHeight();
    m_id = id;
    m_numberLeds = numberLeds;
}

HaloRing::~HaloRing()
{
    //Intentionaly left empty
}


void HaloRing::setup()
{
    this->setupLedRing();
}

void HaloRing::setupLedRing()
{
    // Set the pixel data
    m_screenPixels.allocate(m_width, m_height,GL_RGB);
    
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
        float x = m_ledPositions[i].x - m_position.x + m_width*0.5;
        float y = m_ledPositions[i].y - m_position.y + m_height*0.5;
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
    float innerSpace = 24;
    
    if (hideArea == true)
    {
        // Draw Interaction Area
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(255, 255);
        ofEllipse(m_position.x, m_position.y, (m_width+innerSpace)*0.5,(m_height+innerSpace)*0.5);
        ofEllipse(m_position.x, m_position.y, (m_width-innerSpace)*0.5,(m_height-innerSpace)*0.5);
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
    
    innerSpace = 12;
    ofEllipse(m_position.x, m_position.y, (m_width+innerSpace)*0.5,(m_height+innerSpace)*0.5);
    ofEllipse(m_position.x, m_position.y, (m_width-innerSpace)*0.5,(m_height-innerSpace)*0.5);
    
    for (int i = 0; i < m_numberLeds; i++)
    {
        ofCircle(m_ledPositions[i],2);
    }
}
//--------------------------------------------------------------
void HaloRing::ledRing()
{
    ofSetColor(0, 175);
    float innerSpace = 12;
    ofEllipse(m_position.x, m_position.y, (m_width+innerSpace)*0.5,(m_height+innerSpace)*0.5);
    ofEllipse(m_position.x, m_position.y, (m_width-innerSpace)*0.5,(m_height-innerSpace)*0.5);
   
    for (int i = 0; i < m_numberLeds; i++)
    {
        ofFill();
        ofSetColor(m_ledColors[i]);
        ofCircle(m_ledPositions[i],4);
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