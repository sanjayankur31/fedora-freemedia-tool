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
 *
 *       Filename:  GetReport.cpp
 *
 *    Description:  Get the report from the fedorahosted trac
 *
 *        Version:  1.0
 *        Created:  25/01/12 20:06:25
 *       Revision:  1
 *       Compiler:  gcc
 *
 *         Author:  Ankur Sinha (FranciscoD), sanjay DOT ankur AT gmail DOT com
 *        Company:  None
 *
 * =====================================================================================
 */

#include	"GetReport.h"


/*
 *--------------------------------------------------------------------------------------
 *       Class:  GetReport
 *      Method:  GetReport
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
GetReport::GetReport ()
{
    init();
}  /* -----  end of method GetReport::GetReport  (constructor)  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  GetReport
 *      Method:  GetReport :: SetUsername
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    void
GetReport::SetUsername (std::string username )
{
    mFASUsername = username;
    return ;
}		/* -----  end of method GetReport::SetUsername  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  GetReport
 *      Method:  GetReport :: init
 * Description:  stuff common in the two constructors
 *--------------------------------------------------------------------------------------
 */
    void
GetReport::init ( )
{
    mLoginURL = "https://fedorahosted.org/freemedia/login";
    mReportURL = "https://fedorahosted.org/freemedia/report/7?asc=1&format=csv&USER=";
    return ;
}		/* -----  end of method GetReport::init  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  GetReport
 *      Method:  GetReport :: GetFASCredentials
 * Description:  Get FAS username and password
 *--------------------------------------------------------------------------------------
 */
    int
GetReport::GetFASCredentials ( )
{
    if (mFASUsername.empty())
    {
        std::cout << "Username: ";
        std::cin >> mFASUsername ;
    }
    else
    {
        std::cout << "Username: " << mFASUsername << std::endl;
    }
    
    mFASPassword = std::string(getpass("Password: "));


    if(mFASPassword.empty() || mFASUsername.empty())
    {
        std::cout << "[X] Either the password or username was not entered.\nPlease re run the tool and provide correct credentials!" << std::endl;
        return -1;
    }
    mReportURL += mFASUsername;
    return 0;
}		/* -----  end of method GetReport::GetFASCredentials  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  GetReport
 *      Method:  GetReport :: DownloadReport
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    int
GetReport::DownloadReport ( )
{
    GetFASCredentials();

    mDataFileStream.open(mDownloadLocation.c_str());

//    curlpp::Options::WriteStream ws(&mDataFileStream);

    mcURLHandle.setOpt(cURLpp::Options::CookieFile(""));
    mcURLHandle.setOpt(cURLpp::Options::Url(mLoginURL));
    mcURLHandle.setOpt(cURLpp::Options::NoProgress(0));
    mcURLHandle.setOpt(cURLpp::Options::UserAgent("Fedora freemedia tool using curlpp: " LIBCURLPP_VERSION));
    mcURLHandle.setOpt(curlpp::Options::SslVerifyHost(1L));
    mcURLHandle.setOpt(curlpp::Options::UserPwd(mFASUsername + ":" + mFASPassword));
    mcURLHandle.perform();

    mcURLHandle.setOpt(cURLpp::Options::Url(mReportURL));
    mcURLHandle.setOpt(cURLpp::Options::WriteStream(&mDataFileStream));
    mcURLHandle.perform();
    mDataFileStream.close();

    return 0;
}		/* -----  end of method GetReport::DownloadReport  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  GetReport
 *      Method:  GetReport :: SetDownloadLocation
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    void
GetReport::SetDownloadLocation (std::string downloadLocation )
{
    mDownloadLocation = downloadLocation;
    return ;
}		/* -----  end of method GetReport::SetDownloadLocation  ----- */

