//
//  HaloRing.h
//
//  Created by Imanol Gomez on 01/03/15.
//

#include <iostream>
#include "ofMain.h"
#include "BasicVisual.h"
#include "HaloLed"


class HaloRing: public BasicVisual {
    
    public:
    
        HaloRing(const BasicVisual& visual, unsigned int id, int numberLeds);
        virtual ~HaloRing();
    
        void setup();
        void update();
    
        void drawGrabRegion(bool hideArea);
        void drawRing(int x, int y);
    
        int getId(){return m_id;}
    
        int getNumberLeds(){return int getId(){return m_id;}

    
        // Return Data Method
        vector <ofColor> colorData();
    
    private:
    
        void grabImageData();
    
        void setupLedRing();
    
        // Draw Unit
        void ledRing();
    
    private:
            
        typedef ofPtr<HaloLed>  HaloLedPtr;
        typedef vector<HaloLedPtr> HaloLedVector;
    
        // Hold the Captured Colors
        vector <ofColor> m_ledColors;
    
        // Hold the Position of our Capture points
        vector <ofVec2f> m_ledPositions;
    
        // Capture Objects
        ofImage     m_screenImage;
        ofPixels    m_screenPixels;
    
        // Variables
        int     m_numberLeds;
        int     m_id;
    
};




