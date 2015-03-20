#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "HaloLightApp.h"


//========================================================================
int main( ){

    ofAppGlutWindow window;
    ofSetupOpenGL(&window,1680, 1050, OF_WINDOW);
    ofRunApp( new HaloLightApp());

}
