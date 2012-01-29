/*
 * =====================================================================================
 *
 *  Copyright 2012 Ankur Sinha
 *
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 3 of the License, or 
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *       Filename:  GetReport.h
 *
 *    Description:  Header to GetReport.cpp
 *
 *        Version:  1.0
 *        Created:  25/01/12 20:06:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ankur Sinha (FranciscoD), sanjay DOT ankur AT gmail DOT com
 *        Company:  None
 *
 * =====================================================================================
 */

#ifndef  GETREPORT_INC
#define  GETREPORT_INC


#include	<curlpp/Easy.hpp>
#include	<curlpp/cURLpp.hpp>
#include	<curlpp/Options.hpp>
#include	<iostream>
#include	<fstream>
#include	<unistd.h>
/*
 * =====================================================================================
 *        Class:  GetReport
 *  Description:  
 * =====================================================================================
 */
class GetReport
{
    public:
    /* ====================  LIFECYCLE     ======================================= */
    GetReport ();                             /* constructor */

    /* ====================  ACCESSORS     ======================================= */

    /* ====================  MUTATORS      ======================================= */
    void SetUsername(std::string username);
    int DownloadReport();
    void SetDownloadLocation(std::string);

    /* ====================  OPERATORS     ======================================= */

    protected:
    /* ====================  DATA MEMBERS  ======================================= */

    private:
    void init();
    int GetFASCredentials();
    /* ====================  DATA MEMBERS  ======================================= */
    cURLpp::Easy mcURLHandle;
    std::string mLoginURL;
    std::string mReportURL;
    std::string mFASUsername;
    std::string mFASPassword;
    std::string mDownloadLocation;
    std::ofstream mDataFileStream;


}; /* -----  end of class GetReport  ----- */

#endif   /* ----- #ifndef GETREPORT_INC  ----- */
