//
//  HaloRing.cpp
//
//  Created by Imanol Gomez on 01/03/15.
//
//--------------------------------------------------------------

#include "HaloRing.h"


HaloRing::HaloRing(const BasicVisual& visual, int id, int numberLeds): BasicVisual()
{
    m_position = visual.getPosition();
    m_width = visual.getWidth();
    m_height = visual.getHeight();
    m_id = id;
    m_numberLeds = numberLeds;
    this->setup();
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
        m_ledColors.push_back(ofColor::black);
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
    
    m_screenPixels.clear();
    m_screenPixels = m_screenImage.getPixelsRef(); // Transfer grab data to the pixel array
    
    for (int i = 0; i < m_ledPositions.size(); i++)
    {
        float x = m_ledPositions[i].x - m_position.x + m_width*0.5;
        float y = m_ledPositions[i].y - m_position.y + m_height*0.5;
        m_ledColors[i] = m_screenPixels.getColor(x, y);
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
    int margin = 2;
    m_screenImage.clear();
    m_screenImage.grabScreen(m_position.x - m_width*0.5, m_position.y - m_height*0.5,m_width+margin,m_height+margin);
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
        ofEllipse(m_position.x, m_position.y, m_width+innerSpace, m_height+innerSpace);
        ofEllipse(m_position.x, m_position.y, m_width-innerSpace, m_height-innerSpace);
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
    ofEllipse(m_position.x, m_position.y, m_width+innerSpace,m_height+innerSpace);
    ofEllipse(m_position.x, m_position.y, m_width-innerSpace,m_height-innerSpace);
    
    for (int i = 0; i < m_ledPositions.size(); i++)
    {
        ofCircle(m_ledPositions[i],2);
    }
}
//--------------------------------------------------------------
void HaloRing::ledRing()
{
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(0, 175);
    float innerSpace = 12;
    ofNoFill();
    ofEllipse(0, 0, m_width+innerSpace, m_height+innerSpace);
    ofEllipse(0, 0, m_width-innerSpace, m_height-innerSpace);
    ofFill();
    for (int i = 0; i < m_numberLeds; i++)
    {
        ofFill();
        ofSetColor(m_ledColors[i]);
        ofCircle(m_ledPositions[i] - m_position,2);
    }
    
    ofPopStyle();
    ofPopMatrix();
}
//--------------------------------------------------------------
void HaloRing::drawRing()
{
    // Where to draw the ring!
    ofPushMatrix();
    ofTranslate(m_previewPosition.x, m_previewPosition.y);
    ofFill();
    int width = m_width*1.2;
    int height = m_height*1.2;
    ofSetColor(100);
    ofRect(-width*0.5,-height*0.5,width,height);
    ledRing();
    ofPopMatrix();
}

void HaloRing::draw()
{
    this->drawGrabRegion();
    this->drawRing();
}