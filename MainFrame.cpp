/*************************************************************************************************************************************
 * Name:        MainFrame.cpp
 * Purpose:     top window for the project
 * Licence:     GNU GPL v3.0 (29 June 2007)
 * -----------------------------------------------------------------------------------------------------------------------------------
 * Copyright (C) 2014, Stephen Wunschel
 *************************************************************************************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

// standard header files

//3rd party header files
#include <wx/grid.h>
#include <wx/notebook.h>

// project header files
#include "MainFrame.h"
#include "Roster.h"

// declarations
wxString rosterDirectory;						// directory of selected roster file
wxString rosterFilename;						// file name of selected roster file
wxString rosterPath;							// path name to selected roster file
Roster thisClub;								// the roster of this club
wxNotebook* notebook;
wxGrid* grid1;

/*************************************************************************************************************************************
 * helper functions
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 1xx   07/24/2014   SDW   created by CodeBlocks project wizard
 *************************************************************************************************************************************/
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

/*************************************************************************************************************************************
 * Event Table
 *************************************************************************************************************************************/
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CLOSE(MainFrame::OnClose)
    EVT_MENU(idMenuQuit, MainFrame::OnQuit)
    EVT_MENU(idMenuAbout, MainFrame::OnAbout)
    EVT_MENU(ID_RosterClose, MainFrame::OnRosterClose)
	EVT_MENU(ID_RosterDisplay, MainFrame::OnRosterDisplay)
	EVT_MENU(ID_RosterNew, MainFrame::OnRosterNew)
    EVT_MENU(ID_RosterOpen, MainFrame::OnRosterOpen)
    EVT_MENU(ID_RosterSave, MainFrame::OnRosterSave)
    EVT_MENU(ID_RosterSaveAs, MainFrame::OnRosterSaveAs)
    EVT_MENU(ID_EventNew, MainFrame::OnEventNew)
    EVT_MENU(ID_EventOpen, MainFrame::OnEventOpen)
    EVT_MENU(ID_EventSave, MainFrame::OnEventSave)
    EVT_MENU(ID_EventSaveAs, MainFrame::OnEventSaveAs)
END_EVENT_TABLE()

/*************************************************************************************************************************************
 * constructor
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 1xx   xx/xx/2014   SDW   xxx
 *************************************************************************************************************************************/
MainFrame::MainFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
	// create a menu bar
	wxMenu *menuFile = new wxMenu;               // File menu
    menuFile->Append(ID_Hello, _("&Hello...\tCtrl-H"), _("Help string shown in status bar for this menu item"));
    menuFile->AppendSeparator();
    menuFile->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    wxMenu *menuRoster = new wxMenu;             // Roster menu
    menuRoster->Append(ID_RosterNew, _("&New...\tCtrl-N"), _("Create new file of club members"));
    menuRoster->Append(ID_RosterOpen, _("&Open...\tCtrl-O"), _("Open file of club members"));
    menuRoster->Append(ID_RosterDisplay, _("&Display"), _("Display file of club members"));
    menuRoster->Append(ID_RosterSave, _("&Save...\tCtrl-S"), _("Save club membership file"));
    menuRoster->Append(ID_RosterSaveAs, _("&SaveAs...\tCtrl-S"), _("Save club membership file"));
    menuRoster->Append(ID_RosterClose, _("&Close...\tCtrl-W"), _("Close club membership file"));
    wxMenu *menuEvent = new wxMenu;              // Event menu
    menuEvent->Append(ID_EventNew, _("&New...\tCtrl-N"), _("Create new club event"));
    menuEvent->Append(ID_EventOpen, _("&Open...\tCtrl-O"), _("Open club event"));
    menuEvent->Append(ID_EventSave, _("&Save...\tCtrl-C"), _("Save club event"));
    menuEvent->Append(ID_EventSaveAs, _("&SaveAs...\tCtrl-C"), _("Save club event"));
    wxMenu *menuHelp = new wxMenu;               // Help menu
    menuHelp->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
    wxMenuBar *menuBar = new wxMenuBar;          // menubar
    menuBar->Append( menuFile, _("&File") );
    menuBar->Append( menuRoster, _("&Roster"));
    menuBar->Append( menuEvent, _("&Event"));
    menuBar->Append( menuHelp, _("&Help" ));
    SetMenuBar( menuBar );

    // create a status bar
	CreateStatusBar();
    SetStatusText(_("Welcome to Chufen!"));

    // create the notebook
    //wxNotebook* notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(300, 200));
    notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(300, 200));



}

/*************************************************************************************************************************************
 * destructor
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 1xx   xx/xx/2014   SDW   xxx
 *************************************************************************************************************************************/
MainFrame::~MainFrame()
{
}

/*************************************************************************************************************************************
 * OnAbout - handler for idMenuAbout event
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 1xx   xx/xx/2014   SDW   xxx
 *************************************************************************************************************************************/
void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

/*************************************************************************************************************************************
 * OnClose - handler for close event
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

/*************************************************************************************************************************************
 * OnEventNew - handler for ID_EventNew
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 1xx   xx/xx/2014   SDW   xxx
 *************************************************************************************************************************************/
void MainFrame::OnEventNew(wxCommandEvent& event)
{
	wxLogMessage(_("Event New"));
}

/*************************************************************************************************************************************
 * OnEventOpen - handler for ID_EventOpen
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 1xx   xx/xx/2014   SDW   xxx
 *************************************************************************************************************************************/
void MainFrame::OnEventOpen(wxCommandEvent& event)
{
	wxLogMessage(_("Event Open"));
}


/*************************************************************************************************************************************
 * OnEventSave - handler for ID_EventSave
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnEventSave(wxCommandEvent& event)
{
	wxLogMessage(_("Event Save"));
}

/*************************************************************************************************************************************
 * OnEventSaveAs - handler for ID_EventSaveAs
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnEventSaveAs(wxCommandEvent& event)
{
	wxLogMessage(_("Event SaveAs"));
}

/*************************************************************************************************************************************
 * OnQuit - handler for idMenuQuit event
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

/*************************************************************************************************************************************
 * OnRosterClose - handler for ID_RosterClose
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnRosterClose(wxCommandEvent& event)
{
	notebook->DeletePage(0);

	wxLogMessage(_("Roster Close"));
}

/*************************************************************************************************************************************
 * OnRosterDisplay - handler for ID_RosterDisplay
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnRosterDisplay(wxCommandEvent& event)
{
	// local variables
	int index;									// index into roster
	Member thisMember;							// Member currently being processed

	//
	grid1 = new wxGrid(notebook, wxID_ANY, wxDefaultPosition, wxSize(400, 300));
	grid1->CreateGrid(thisClub.getMemberCount(), 10);
	notebook->AddPage(grid1, _("Roster"), true);

	// iterate through roster while populating grid
	for(index = 0; index < thisClub.getMemberCount(); index++)
	{
		thisMember = thisClub.getMember(index);
		//grid1->SetCellValue(index,0,thisMember.getMemberID());
		grid1->SetCellValue(index,1,thisMember.getLastNameFirst());
	}



	wxLogMessage(_("Roster Display"));
}

/*************************************************************************************************************************************
 * OnRosterNew - handler for ID_RosterNew
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnRosterNew(wxCommandEvent& event)
{
	wxLogMessage(_("Roster New"));
}

/*************************************************************************************************************************************
 * OnRosterOpen - handler for ID_RosterOpen
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnRosterOpen(wxCommandEvent& event)
{
	int result;

    // select roster file to be opened
	wxFileDialog *openDialog = new wxFileDialog(this, wxT("Choose a roster file"), wxT(""), wxT(""), wxT("CSV (*.csv)|*.csv"), wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_CHANGE_DIR );
    result = openDialog->ShowModal();

    // load roster from selected file
    if (result == wxID_OK)
    {
        rosterDirectory = openDialog->GetDirectory();
        rosterFilename = openDialog->GetFilename();
        rosterPath = openDialog->GetPath();
        thisClub.readFile(rosterFilename);
        wxLogMessage(_("Roster Open"));
    }

	wxLogMessage(_("Roster Open"));

}

/*************************************************************************************************************************************
 * OnRosterSave - handler for ID_RosterSave
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnRosterSave(wxCommandEvent& event)
{
	wxLogMessage(_("Roster Save"));
}

/*************************************************************************************************************************************
 * OnRosterSaveAs - handler for ID_RosterSaveAs
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnRosterSaveAs(wxCommandEvent& event)
{
	wxLogMessage(_("Roster SaveAs"));
}

