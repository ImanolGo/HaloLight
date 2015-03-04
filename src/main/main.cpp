#include "ofMain.h"
#include "ofAppGLFWWindow.h"
#include "HaloLightApp.h"

//========================================================================
int main( ){

    ofAppGLFWWindow window;
	ofSetupOpenGL(&window,1280,800,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new HaloLightApp());

}
