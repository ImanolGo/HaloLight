#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "HaloLightApp.h"

#include "ofGLProgrammableRenderer.h"


//========================================================================
int main( ){

    ofPtr<ofBaseRenderer> renderer(new ofGLProgrammableRenderer(false));
    ofSetCurrentRenderer(renderer, false);
    //	ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
    ofSetupOpenGL(1680, 1050, OF_WINDOW);
    
    //ofAppGlutWindow window;
	// ofSetupOpenGL(&window,1680,1050,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new HaloLightApp());

}
