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
 *       Filename:  Session.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/01/12 14:20:04
 *       Revision:  1
 *       Compiler:  g++
 *
 *         Author:  Ankur Sinha (FranciscoD), sanjay DOT ankur AT gmail DOT com
 *        Company:  None
 *
 * =====================================================================================
 */


#ifndef  SESSION_INC
#define  SESSION_INC


#include	"config.h"
#include    <boost/program_options.hpp>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<string>
#include	<cstdlib>
#include	<errno.h>
#include	<vector>
#include	<cstdio>
#include	<curlpp/cURLpp.hpp>
#include	<curlpp/Options.hpp>
#include	"ImportData.h"
#include	"ExportData.h"
#include	"GetReport.h"

/*
 * =====================================================================================
 *        Class:  Session
 *  Description:  Data related to the application's currently running
 *  session
 * =====================================================================================
 */
class Session
{
    public:
    /* ====================  LIFECYCLE     ======================================= */
    Session ();                             /* constructor */
    ~Session ();

    /* ====================  ACCESSORS     ======================================= */
    std::string DatabaseFileLocation();
    std::string InputReportFileLocation();
    std::string OutputDirectory();
    std::string PrintListAsString();
    std::string EnvelopeTemplateLocation();
    std::string SendersName();
    std::string SendersAddress();
    int VerboseLevel();

    /* ====================  MUTATORS      ======================================= */
    int ParseCommandLine(int argc, char **argv);
    int PrepareSession();                       /* make the required directories etc */

    /* ====================  OPERATORS     ======================================= */

    protected:
    /* ====================  DATA MEMBERS  ======================================= */

    private:
    /* ====================  DATA MEMBERS  ======================================= */
    std::string mConfigDirectory;
    std::string mUserDataDirectory;
    std::string mFASUsername;
    std::string mDatabaseFileLocation;
    std::string mInputReportFileLocation;
    std::string mConfigFileLocation;
    std::string mOutputDirectory;
    std::string mSendersAddress;
    std::string mSendersName;
    std::string mListWhat;
    std::string mListLongWhat;
    std::string mEnvelopeTemplateLocation;
    std::vector<int> mListToPrint;
    std::vector<int> mResolveTicketNumbers;
    std::vector<int> mResetTicketNumbers;
    std::vector<int> mAssignLCNumbers;
    int mVerboseLevel;
    int mModifyTicket;
    boost::program_options::variables_map mVariableMap;
    boost::program_options::options_description mDesc;


}; /* -----  end of class Session  ----- */


#endif   /* ----- #ifndef SESSION_INC  ----- */
