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
 *       Filename:  Session.cpp
 *
 *    Description:  A class around the session's variables
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


#include	"Session.h"

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Session
 *      Method:  Session
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Session::Session ()
    : mDesc("Options")
{
    mDesc.add_options()
        ("help,h", "print usage message")
        ("input-file,i",boost::program_options::value<std::string>(&mInputReportFileLocation),"complete input file path\n(default: ~/.local/share/fedora-freemedia-tool/report.csv)")
        ("database,d",boost::program_options::value<std::string>(&mDatabaseFileLocation),"complete output file path\n(default: ~/.local/share/fedora-freemedia-tool/freemedia-database.db)")
        ("output-dir,o",boost::program_options::value<std::string>(&mOutputDirectory),"directory to put the printed envelopes\n(default: ./ (current directory))")
        ("v-level,v",boost::program_options::value<int>(&mVerboseLevel),"Debug level: 1,2,3\n(default: 0)")
        ;

}  /* -----  end of method Session::Session  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Session
 *      Method:  Session :: ParseCommandLine
 * Description:  Parse the command line
 *--------------------------------------------------------------------------------------
 */
    int
Session::ParseCommandLine (int argc, char **argv)
{
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, mDesc), mVariableMap);
    /*  notify required to save the values into my variables. */
    /*  TODO: confirm this behaviour */
    boost::program_options::notify(mVariableMap);

    if (mVariableMap.count("help")) 
    {
        std::cout << mDesc << std::endl;
        return -1;
    }
    return 0;
}		/* -----  end of method Session::ParseCommandLine  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Session
 *      Method:  Session :: DatabaseFileLocation
 * Description:  Accessor method
 *--------------------------------------------------------------------------------------
 */
    std::string
Session::DatabaseFileLocation  ()
{
    return mDatabaseFileLocation;
}		/* -----  end of method Session::DatabaseFileLocation  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Session
 *      Method:  Session :: InputReportFileLocation
 * Description:  Accessor method
 *--------------------------------------------------------------------------------------
 */
    std::string
Session::InputReportFileLocation ( )
{
    return mInputReportFileLocation;
}		/* -----  end of method Session::InputReportFileLocation  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Session
 *      Method:  Session :: OutputDirectory
 * Description:  Accessor method
 *--------------------------------------------------------------------------------------
 */
    std::string
Session::OutputDirectory ( )
{
    return mOutputDirectory;
}		/* -----  end of method Session::OutputDirectory  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Session
 *      Method:  Session :: VerboseLevel
 * Description:  Accessor
 *--------------------------------------------------------------------------------------
 */
    int
Session::VerboseLevel ( )
{
    return mVerboseLevel;
}		/* -----  end of method Session::VerboseLevel  ----- */

