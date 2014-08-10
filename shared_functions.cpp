/*************************************************************************************************************************************
 * Name:        shared_functions.cpp
 * Purpose:     methods shared by entire project
 * Licence:     GNU GPL v3.0 (29 June 2007)
 * -----------------------------------------------------------------------------------------------------------------------------------
 * Copyright (C) 2014, Stephen Wunschel
 *************************************************************************************************************************************/

// standard header files
#include <sstream>
using namespace std;

// 3rd party header files

// project header files
#include "shared_functions.h"

/*************************************************************************************************************************************
 * split - parse subject string into vector of substrings
 *
 * reference: programmingexamples.net
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   08/09/2014   SDW   initial coding
 *************************************************************************************************************************************/
vector<string> split(const string &s, char delim)
{
	// local variables
	vector<string> elems;
    stringstream ss(s);
    string item;

    // loop through subject string
    while(getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}
