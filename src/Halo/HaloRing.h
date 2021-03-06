//
//  HaloRing.h
//
//  Created by Imanol Gomez on 01/03/15.
//
#pragma once

#include "ofMain.h"
#include "BasicVisual.h"
#include "TextVisual.h"

class HaloRingSettings {
    
    public:
    
    HaloRingSettings(): numberLeds(0), id(""), fadeCandyInd(1), channel(1), positionIndex(0){}
    
    ~HaloRingSettings(){}
    
    public:
    
    // Variables
    int         numberLeds;
    string      id;
    int         fadeCandyInd;
    int         channel;
    int         positionIndex;

    
};

class HaloRingPreview: public BasicVisual {
    
public:
    
    HaloRingPreview(const BasicVisual& visual, string id);
    
    virtual ~HaloRingPreview();
    
    virtual void draw();
    
    void setColors(const vector <ofColor>& colors ) {m_ledColors = colors;}
    
private:
    
    void setup();
    
    void setupTextVisual();
    
    void drawLedRing();
    
    void drawID(bool hideText = false);
    
private:
    
    vector <ofColor> m_ledColors;
    
    string     m_id;
    
    ofPtr<TextVisual>  m_textVisual;
    
};

class HaloRing: public BasicVisual {
    
    public:
    
        HaloRing(const BasicVisual& visual, const HaloRingSettings& settings);
        virtual ~HaloRing();
    
        void setup();
        void setPixels(const ofRectangle& grabArea, const ofPixels& screenPixels);
        void draw();
    
        string getId(){return m_settings.id;}
    
        int getChannel(){return m_settings.channel;}
    
        int getFadeCandyNum(){return m_settings.fadeCandyInd;}
    
        void setHaloRingPreview(const BasicVisual& visual);

    
        // Return Data Method
        const vector <ofColor>& colorData(){return m_ledColors;}
    
    private:
    
        void setupLedRing();
    
        void setupTextVisual();
    
        void drawGrabRegion(bool hideArea = false);
    
        void drawID(bool hideText = false);
    
    private:
            
        // Hold the Captured Colors
        vector <ofColor> m_ledColors;
    
        // Hold the Position of our Capture points
        vector <ofVec2f> m_ledPositions;
    
        HaloRingSettings            m_settings;
        ofPtr<HaloRingPreview>     m_haloRingPreview;
    
        ofPtr<TextVisual>  m_textVisual;
    
        float m_margin;
    
};




