/*************************************************************************************************************************************
 * Name:        Member.cpp
 * Purpose:     member class
 * Licence:     GNU GPL v3.0 (29 June 2007)
 * -----------------------------------------------------------------------------------------------------------------------------------
 * Copyright (C) 2014, Stephen Wunschel
 *************************************************************************************************************************************/

// standard header files
#include <sstream>
#include <string>
#include <vector>
using namespace std;

//3rd party header files
#include <wx/log.h>

// project header files
#include "common.h"
#include "Member.h"
#include "shared_functions.h"

/*************************************************************************************************************************************
 * constructor
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
Member::Member()
{

}

/*************************************************************************************************************************************
 * destructor
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
Member::~Member()
{

}

/*************************************************************************************************************************************
 * getCurrentRating - retrieve current rating
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
int Member::getCurrentRating()
{
    return currentRating;
}

/*************************************************************************************************************************************
 * getCurrentRating_s - retrieve current rating as a string
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/10/2014   SDW   initial coding
 *************************************************************************************************************************************/
string Member::getCurrentRating_s()
{
	//TODO replace SS with better process?

	stringstream ss;
	string result;

	ss << currentRating;
	ss >> result;
    return result;
}

/*************************************************************************************************************************************
 * getFirstName - retrieve first name
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
string Member::getFirstName()
{
    return firstName;
}

/*************************************************************************************************************************************
 * getLastDate - retrieve date (yy/mm/dd) of last participation
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/10/2014   SDW   initial coding
 *************************************************************************************************************************************/
string Member::getLastDate()
{
	//TODO replace SS with better process?
	//TODO find better string addition

	// local variable
	stringstream ss, ss2, ss3;
	string temps;
	string result;

	// process
    ss << lastYear;
	ss >> result;
    result += "/";
	ss2 << lastMonth;
	ss2 >> temps;
    result += temps;
    result += "/";
	ss3 << lastDay;
	ss3 >> temps;
	result += temps;
    return result;
}

/*************************************************************************************************************************************
 * getLastName - retrieve last name
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
string Member::getLastName()
{
    return lastName;
}

/*************************************************************************************************************************************
 * getLastNameFirst - retrieve full name (last name first)
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
string Member::getLastNameFirst()
{
	//TODO find better string addition

    string result;
    result = lastName;
    result += ", ";
    result += firstName;
    return result;
}

/*************************************************************************************************************************************
 * getMemberID - retrieve member ID
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
int Member::getMemberID()
{
    return memberID;
}

/*************************************************************************************************************************************
 * getMemberID_s - retrieve member ID as a string
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/10/2014   SDW   initial coding
 *************************************************************************************************************************************/
string Member::getMemberID_s()
{
	//TODO replace SS with better process?

	stringstream ss;
	string result;

	ss << memberID;
	ss >> result;
    return result;
}

/*************************************************************************************************************************************
 * getPreviousRating - retrieve previous rating
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/10/2014   SDW   initial coding
 *************************************************************************************************************************************/
int Member::getPreviousRating()
{
    return prevRating;
}

/*************************************************************************************************************************************
 * getPreviousRating_s - retrieve previous rating as a string
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/10/2014   SDW   initial coding
 *************************************************************************************************************************************/
string Member::getPreviousRating_s()
{
	//TODO replace SS with better process?

	stringstream ss;
	string result;

	ss << prevRating;
	ss >> result;
    return result;
}

/*************************************************************************************************************************************
 * setString - set data members based on input string
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/10/2014   SDW   initial coding
 *************************************************************************************************************************************/
bool Member::setString(string inputrec)
{
	// parse input string into individual words
	vector<string> words = split(inputrec, ',');	
	// set object data members
	memberID = std::stoi(words[0]);				
	lastName = words[1];
	firstName = words[2];
	currentRating = stoi(words[3]);
	prevRating = stoi(words[4]);
	lastYear = stoi(words[5]);
	lastMonth = stoi(words[6]);
	lastDay = stoi(words[7]);
	// return to caller
    return true;
}

/*************************************************************************************************************************************
 * getString - get data members as csv-formatted string
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/01/2014   SDW   initial coding
 *************************************************************************************************************************************/
string Member::getString()
{
	// local variables
	char buffer[MAXBUFFER];
	string result;

	// format data variables into c-string
	sprintf(buffer, "%u,%s,%s,%u,%u,%u,%u,%u", memberID, lastName.c_str(), firstName.c_str(), currentRating, prevRating, lastYear, lastMonth, lastDay);
	result = buffer;
	// return to caller
    return result;
}