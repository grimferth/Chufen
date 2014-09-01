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
		string getCurrentRating_s();			// retrieve current rating as a string
		string getFirstName();                  // retrieve first name
        string getLastDate();                   // retrieve date (yy/mm/dd) of last participation
        string getLastName();                   // retrieve last name
        string getLastNameFirst();              // retrieve full name (last name first)
		int getMemberID();                      // retrieve member ID
		string getMemberID_s();					// retrieve member ID as a string
		int getPreviousRating();				// retrieve previous rating
		string getPreviousRating_s();			// retrieve previous rating as a string
		string getString();						// get data members as csv-formatted string
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
