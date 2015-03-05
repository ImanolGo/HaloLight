//
//  HaloRing.h
//
//  Created by Imanol Gomez on 01/03/15.
//

#include <iostream>
#include "ofMain.h"
#include "BasicVisual.h"
#include "TextVisual.h"

class HaloRingSettings {
    
    public:
    
    HaloRingSettings(): numberLeds(0), id(0), fadeCandyInd(1), channel(1){}
    
    ~HaloRingSettings(){}
    
    public:
    
    // Variables
    int     numberLeds;
    int     id;
    int     fadeCandyInd;
    int     channel;

    
};

class HaloRing: public BasicVisual {
    
    public:
    
        HaloRing(const BasicVisual& visual, const HaloRingSettings& settings);
        virtual ~HaloRing();
    
        void setup();
        void update();
        void draw();
    
        void drawGrabRegion(bool hideArea = false);
        void drawRing();
    
        int getId(){return m_settings.id;}
    
        int getChannel(){return m_settings.channel;}
    
        int getFadeCandyNum(){return m_settings.fadeCandyInd;}
    
        void setPreviewPosition(const ofPoint& pos){m_previewPosition = pos;}

    
        // Return Data Method
        vector <ofColor> colorData();
    
    private:
    
        void grabImageData();
            
        void updateLeds();
    
        void setupLedRing();
    
        void setupTextVisual();
    
        // Draw Unit
        void ledRing();
    
    private:
            
        // Hold the Captured Colors
        vector <ofColor> m_ledColors;
    
        // Hold the Position of our Capture points
        vector <ofVec2f> m_ledPositions;
    
        // Capture Objects
        ofImage     m_screenImage;
        ofPixels    m_screenPixels;
    
        ofPtr<TextVisual>  m_textVisual;
    
        ofPoint   m_previewPosition;
    
        HaloRingSettings    m_settings;
    
};




