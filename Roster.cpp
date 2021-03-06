/*************************************************************************************************************************************
 * Name:        Roster.cpp
 * Purpose:     list of members
 * Licence:     GNU GPL v3.0 (29 June 2007)
 * -----------------------------------------------------------------------------------------------------------------------------------
 * Copyright (C) 2014, Stephen Wunschel
 *************************************************************************************************************************************/

// standard header files
#include <fstream>
using namespace std;

// 3rd party header files

// project header files
#include "Roster.h"

/*************************************************************************************************************************************
 * constructor
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
Roster::Roster()
{
	clearRoster();
}

/*************************************************************************************************************************************
 * destructor
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
Roster::~Roster()
{
	//dtor
}

/*************************************************************************************************************************************
 * clearRoster - clear roster
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
bool Roster::clearRoster()
{
    highMemberID = 0;											// clear high member id
    memberList.clear();											// clear member list

    return true;
}

/*************************************************************************************************************************************
 * getMember - return member from member list
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
Member Roster::getMember(int index)
{
	return memberList[index];
}


/*************************************************************************************************************************************
 * getMemberCount - return value of memberCount
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
int Roster::getMemberCount()
{
	return memberList.size();
}

/*************************************************************************************************************************************
 * isLoaded - returns true if values are loaded into roster
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/30/2014   SDW   initial coding
 *************************************************************************************************************************************/
bool Roster::isLoaded()
{
	return (!memberList.empty());
}

/*************************************************************************************************************************************
 * readFile - load Roster from csv-formatted file
 *
 * TODO: convert input parm from wxString
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
bool Roster::readFile(wxString filename)
{
    // local variables
	ifstream infile;											// file object
    string inputrec;											// input record
    Member inputMember;											// input member

    // open roster file
	infile.open(filename.mb_str(wxConvUTF8) );

    // load roster file if open
	if (infile.is_open())
	{
        clearRoster();											// clear roster
		while (getline(infile,inputrec))
		{
			inputMember.setString(inputrec);					// format input record into member
            memberList.push_back(inputMember);					// push input member onto back of member list
            if (highMemberID < inputMember.getMemberID())		// copy member ID if highest
                highMemberID = inputMember.getMemberID();
		}
		infile.close();											// close file
		return true;
	}

    return false;

}

/*************************************************************************************************************************************
 * saveFile - save Roster into csv-formatted file
 *
 * TODO: convert input parm from wxString
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/01/2014   SDW   initial coding
 *************************************************************************************************************************************/
bool Roster::saveFile(wxString filename)
{
    // local variables
	ofstream savefile;											// file object
    string saverec;												// record line
	int index;													// loop counter

    // open roster file
	savefile.open(filename.mb_str(wxConvUTF8),std::ofstream::out|std::ofstream::trunc);
	if (!savefile.is_open())
		return false;

	// loop through roster writing records
	for(index = 0; index < getMemberCount(); index++)
	{
		saverec = memberList[index].getString();				// format save record
		savefile << saverec << endl;  							// write record to save file
	}

	savefile.close();											// close file
	return true;


}
