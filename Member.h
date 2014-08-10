/*************************************************************************************************************************************
 * Member.h - definitions for member class
 *************************************************************************************************************************************/
#pragma once

// standard header files
#include <string>
using namespace std;

// project header files

/***************************************************************************************************************
 * symbolic definitions
 ***************************************************************************************************************/

/***************************************************************************************************************
 * class definition
 ***************************************************************************************************************/
class Member
{
	public:
		// public data members
		// public method members
		Member();
		~Member();
		int getCurrentRating();					// retrieve current rating
        string getFirstName();                  // retrieve first name
        string getLastDate();                   // retrieve date (yy/mm/dd) of last participation
        string getLastName();                   // retrieve last name
        string getLastNameFirst();              // retrieve full name (last name first)
		int getMemberID();                      // retrieve member ID
		bool setString(string);                 // set data members based on input string
	protected:
		// protected data members
		// protected method members
	private:
		// private data members
		int memberID;
		string lastName;
		string firstName;
		int currentRating;
		int prevRating;
		int lastYear;
		int lastMonth;
		int lastDay;
		// private method members

};
