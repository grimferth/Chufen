/*************************************************************************************************************************************
 * MainFrame.h - definitions for the top window for the project
 *************************************************************************************************************************************/
#pragma once

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

// standard header files

// project header files
#include "MyApp.h"

/***************************************************************************************************************
 * symbolic definitions
 ***************************************************************************************************************/
																// flag definitions
#define FLAGS_EMPTY 0												// mask 0000 0000 0000 0000
#define FLAG_ROSTER_OPEN 1											// mask 0000 0000 0000 0001

/***************************************************************************************************************
 * class definitions
 ***************************************************************************************************************/
class MainFrame: public wxFrame
{
    public:
    	// public data members
		// public method members
        MainFrame(wxFrame *frame, const wxString& title);
        ~MainFrame();
	protected:
		// protected data members
		// protected method members
    private:
    	// ?
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout,
            ID_Hello = 1,
			ID_RosterClose,
			ID_RosterNew,
			ID_RosterOpen,
			ID_RosterAdd,
			ID_RosterSave,
			ID_RosterSaveAs,
			ID_EventNew,
			ID_EventOpen,
			ID_EventSave,
			ID_EventSaveAs
        };
        // private data members
		// private method members
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnEventNew(wxCommandEvent& event);
        void OnEventOpen(wxCommandEvent& event);
		void OnEventSave(wxCommandEvent& event);
		void OnEventSaveAs(wxCommandEvent& event);
		void OnQuit(wxCommandEvent& event);
		void OnRosterClose(wxCommandEvent& event);
		void OnRosterNew(wxCommandEvent& event);
		void OnRosterOpen(wxCommandEvent& event);
		void OnRosterSave(wxCommandEvent& event);
		void OnRosterSaveAs(wxCommandEvent& event);
		void PerformRosterClose(void);
		// ?
        DECLARE_EVENT_TABLE()
};
