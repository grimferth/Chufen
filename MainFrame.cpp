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
#include <wx/filename.h>
#include <wx/grid.h>
#include <wx/msgdlg.h>
#include <wx/notebook.h>

// project header files
#include "common.h"
#include "MainFrame.h"
#include "Roster.h"

// declarations
U16 flags;														// control flags
wxMenuBar *menuBar = new wxMenuBar;								// menubar
wxString rosterDirectory;										// directory of selected roster file
wxString rosterFilename;										// file name of selected roster file
wxString rosterPath;											// path name to selected roster file
Roster thisClub;												// the roster of this club
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
        wxbuild << "-Windows";
#elif defined(__WXMAC__)
        wxbuild << "-Mac";
#elif defined(__UNIX__)
        wxbuild << "-Linux";
#endif

#if wxUSE_UNICODE
        wxbuild << "-Unicode build";
#else
        wxbuild << "-ANSI build";
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
	EVT_MENU(ID_RosterDeleteRow, MainFrame::OnRosterDeleteRow)
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
	wxMenu *menuFile = new wxMenu;								// File menu
    menuFile->Append(idMenuQuit, "&Quit\tAlt-F4", "Quit the application");
	menuBar->Append( menuFile, "&File");
    wxMenu *menuRoster = new wxMenu;							// Roster menu
	menuRoster->Append(ID_RosterNew, "&New...\tCtrl-N", "Create new file of club members");
	menuRoster->Append(ID_RosterOpen, "Open &Roster...\tCtrl-R", "Open file of club members");
	menuRoster->Append(ID_RosterSave, "&Save...\tCtrl-S", "Save club membership file");
	menuRoster->Append(ID_RosterSaveAs, "Save&As...\tCtrl-A", "Save club membership file");
	menuRoster->Append(ID_RosterClose, "&Close...\tCtrl-C", "Close club membership file");
	menuRoster->AppendSeparator();
	menuRoster->Append(ID_RosterDeleteRow, "&Delete Selected Row...\tCtrl-D", "Delete row from club membership");
	menuBar->Append(menuRoster, "&Roster");
	menuBar->Enable(ID_RosterNew,false);
	menuBar->Enable(ID_RosterSave,false);
	menuBar->Enable(ID_RosterSaveAs,false);
	menuBar->Enable(ID_RosterClose,false);	
	menuBar->Enable(ID_RosterDeleteRow,false);
	wxMenu *menuEvent = new wxMenu;								// Event menu
	menuEvent->Append(ID_EventNew, "&New...\tCtrl-N", "Create new club event");
	menuEvent->Append(ID_EventOpen, "Open &Event...\tCtrl-E", "Open club event");
	menuEvent->Append(ID_EventSave, "&Save...\tCtrl-C", "Save club event");
	menuEvent->Append(ID_EventSaveAs, "&SaveAs...\tCtrl-C", "Save club event");
	menuEvent->AppendSeparator();
	menuBar->Append( menuEvent, "&Event");
	menuBar->Enable(ID_EventNew,false);
	menuBar->Enable(ID_EventOpen,false);
	menuBar->Enable(ID_EventSave,false);
	menuBar->Enable(ID_EventSaveAs,false);
    wxMenu *menuHelp = new wxMenu;								// Help menu
    menuHelp->Append(idMenuAbout, "&About\tF1", "Show info about this application");
    menuBar->Append( menuHelp, "&Help");
    SetMenuBar( menuBar );

    // create a status bar
	CreateStatusBar();
    SetStatusText("Welcome to Chufen!");

    // create the notebook
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
    wxMessageBox(msg, "Welcome to...");
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
	wxLogMessage("Event New");
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
	wxLogMessage("Event Open");
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
	wxLogMessage("Event Save");
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
	wxLogMessage("Event SaveAs");
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
 * 100   08/14/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnRosterClose(wxCommandEvent& event)
{
	PerformRosterClose();
}

/*************************************************************************************************************************************
 * OnRosterDeleteRow - handler for ID_RosterDeleteRow
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnRosterDeleteRow(wxCommandEvent& event)
{
	if ( grid1->IsSelection() )
    {
        wxGridUpdateLocker locker(grid1);
        for ( int n = 0; n < grid1->GetNumberRows(); )
        {
            if ( grid1->IsInSelection( n , 0 ) )
                grid1->DeleteRows( n, 1 );
            else
                n++;
        }
    }


	wxLogMessage("Roster Delete Row");
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
	wxLogMessage("Roster New");
}

/*************************************************************************************************************************************
 * OnRosterOpen - handler for ID_RosterOpen
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/14/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnRosterOpen(wxCommandEvent& event)
{
	// local variables
	int result;													// value returned from dialogs
	int index;													// index into roster
	Member thisMember;											// Member currently being processed

	// check to see if roster is already open
	if (thisClub.isLoaded())
	{
		result = wxMessageBox("Close existing roster?","Confirm", wxYES_NO, this);
		if (result == wxYES)
			PerformRosterClose();
		else
			return;
	}

	// select roster file to be opened
	wxFileDialog *openDialog = new wxFileDialog(this, "Choose a roster file", "", "", "CSV (*.csv)|*.csv", wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_CHANGE_DIR );
    result = openDialog->ShowModal();
	if (result != wxID_OK)
		return;

    // load roster from selected file
	rosterDirectory = openDialog->GetDirectory();				// keep directory of selected file
    rosterFilename = openDialog->GetFilename();					// keep file name
    rosterPath = openDialog->GetPath();							// keep path
    thisClub.readFile(rosterFilename);							// perform the load of the file into roster

	// define roster grid
	grid1 = new wxGrid(notebook, wxID_ANY, wxDefaultPosition, wxSize(400, 300));
	grid1->CreateGrid(thisClub.getMemberCount(), 5);
	
	// iterate through roster while populating grid
	for(index = 0; index < thisClub.getMemberCount(); index++)
	{
		thisMember = thisClub.getMember(index);
		grid1->SetCellValue(index,0,thisMember.getMemberID_s());
		grid1->SetCellValue(index,1,thisMember.getLastNameFirst());
		grid1->SetCellValue(index,2,thisMember.getCurrentRating_s());
		grid1->SetCellValue(index,3,thisMember.getPreviousRating_s());
		grid1->SetCellValue(index,4,thisMember.getLastDate());
	}

	// format and add to notebook
	grid1->SetColFormatNumber(0);
	grid1->SetColFormatNumber(2);
	grid1->SetColFormatNumber(3);
	grid1->SetColLabelValue(0, "Member ID");
	grid1->SetColLabelValue(1, "Name");
	grid1->SetColLabelValue(2, "Current Rating");
	grid1->SetColLabelValue(3, "Previous Rating");
	grid1->SetColLabelValue(4, "Last");
	grid1->AutoSizeColumns(true);
	notebook->AddPage(grid1, "Roster", true);

	// set status
	SetStatusText("Roster Opened");

	// enable menubar
	menuBar->Enable(ID_RosterSave,true);
	menuBar->Enable(ID_RosterSaveAs,true);
	menuBar->Enable(ID_RosterClose,true);
	menuBar->Enable(ID_RosterDeleteRow,true);
}

/*************************************************************************************************************************************
 * OnRosterSave - handler for ID_RosterSave
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/02/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnRosterSave(wxCommandEvent& event)
{
	// check that file still exists
	wxFileName savefile = rosterPath;
	if (!savefile.IsFileWritable())
		return;

	// save roster to selected file
	thisClub.saveFile(rosterFilename);							// perform the save of the roster into the file
	SetStatusText("Roster Saved");
	return;
}

/*************************************************************************************************************************************
 * OnRosterSaveAs - handler for ID_RosterSaveAs
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/01/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::OnRosterSaveAs(wxCommandEvent& event)
{
	// local variables
	int result;													// value returned from dialogs

	// select roster file to be opened
	wxFileDialog *openDialog = new wxFileDialog(this, "Choose a roster file", "", "", "CSV (*.csv)|*.csv", wxFD_SAVE|wxFD_OVERWRITE_PROMPT|wxFD_CHANGE_DIR );
    result = openDialog->ShowModal();
	if (result != wxID_OK)
		return;

	// save roster to selected file
	rosterDirectory = openDialog->GetDirectory();				// keep directory of selected file
    rosterFilename = openDialog->GetFilename();					// keep file name
    rosterPath = openDialog->GetPath();							// keep path
    thisClub.saveFile(rosterFilename);							// perform the save of the roster into the file

	SetStatusText("Roster Saved");
}

/*************************************************************************************************************************************
 * PerformRosterClose - actually closes roster
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2014   SDW   initial coding
 *************************************************************************************************************************************/
void MainFrame::PerformRosterClose()
{
	notebook->DeletePage(0);									// remove roster page from notebook   //TODO
	thisClub.clearRoster();										// clear roster
	// TODO clear strings with file and path names
	SetStatusText("Roster Closed");
	// disable menubar
	menuBar->Enable(ID_RosterSave,false);
	menuBar->Enable(ID_RosterSaveAs,false);
	menuBar->Enable(ID_RosterClose,false);
	menuBar->Enable(ID_RosterDeleteRow,false);
}

