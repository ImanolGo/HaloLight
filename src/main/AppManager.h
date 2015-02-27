/*
 *  AppManager.h
 *  Halo Light
 *
 *  Created by Imanol Gomez on 27/02/15.
 *
 */

#pragma once

#include "ofMain.h"

#include "Manager.h"

#include "SettingsManager.h"

//========================== class AppManager ==============================
//============================================================================
/** \class AppManager AppManager.h
 *	\brief Class managing the whole application
 *	\details it set-ups, updates and renders all the different managers used for the application
 */

class AppManager: public Manager
{
public:

    //! Destructor
    ~AppManager();

    //! Returns the singleton instance.
    static AppManager& getInstance();

    //! Compares two transition objects
    void setup();

    //! updates the logic
    void update();

    //! calls the view manager to draw
    void draw();

    //! defines what happens if the key is pressed
    virtual void keyPressed(ofKeyEventArgs &e);

    //==========================================================================

    //! Returns the settings manager
    ofPtr<SettingsManager> getSettingsManager() { return m_settingsManager; }

private:

    //! Constructor
    AppManager();

	//! Stop the compiler generating methods of copy the object
	 AppManager(AppManager const& copy);              // Don't Implement

    //! Prevent operator= being generated.
     AppManager& operator=(AppManager const& copy);     // Don't implement

    //==========================================================================

    //! Create all the managers with shared pointers
    void createManagers();

    //! Set-up all the managers
    void setupManagers();

    //! Set-up openFrameworks
    void setupOF();

    //! update all the managers
    void updateManagers();


private:

    ofPtr<SettingsManager>          m_settingsManager;          ///< Manages the window settings

    bool                            m_logVerbose;
};

//==========================================================================


