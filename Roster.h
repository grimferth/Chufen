/*************************************************************************************************************************************
 * Roster.h - definitions for list of members
 *************************************************************************************************************************************/

#pragma once

// standard header files
#include <vector>
using namespace std;

// 3rd party header files
#include <wx/string.h>

// project header files
#include "Member.h"

/***************************************************************************************************************
 * symbolic definitions
 ***************************************************************************************************************/

/***************************************************************************************************************
 * class definition
 ***************************************************************************************************************/
class Roster
{
	public:
		// public data members
		// public method members
		Roster();
		~Roster();
		bool clearRoster(void);					// clear roster
		Member getMember(int);					// return member object
		int getMemberCount(void);				// return value of memberCount
		bool readFile(wxString);				// load Roster from csv-formatted file
	protected:
		// protected data members
		// protected method members
	private:
		// private data members
		int highMemberID;						// highest member ID assigned
		vector<Member> memberList;				// list of club members
		// private method members
};
