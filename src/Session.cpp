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
    std::string home_dir ((const char *)getenv("HOME"));
    mOutputDirectory = "./";
    mConfigDirectory = home_dir + "/" + ".config/fedora-freemedia-tool/";
    mUserDataDirectory = home_dir + "/" + ".local/share/fedora-freemedia-tool/";
    mDatabaseFileLocation = home_dir + "/.local/share/fedora-freemedia-tool/freemedia-database.db";
    mInputReportFileLocation = home_dir + "/.local/share/fedora-freemedia-tool/report.csv";
    mDesc.add_options()
        ("help,h", "Print this usage message")
        ("input-file,i",boost::program_options::value<std::string>(&mInputReportFileLocation),"Complete input file path\n(default: ~/.local/share/fedora-freemedia-tool/report.csv)")
        ("database,d",boost::program_options::value<std::string>(&mDatabaseFileLocation),"Complete output file path\n(default: ~/.local/share/fedora-freemedia-tool/freemedia-database.db)")
        ("config-file,c",boost::program_options::value<std::string>(&mConfigFileLocation),"Configuration file")
        ("print,p",boost::program_options::value< std::vector<int> >(&mPrintList)->multitoken(),"List of records to print envelopes for")
        ("output-dir,o",boost::program_options::value<std::string>(&mOutputDirectory),"Directory to put the printed envelopes\n(default: ./ (current directory))")
        ("v-level,v",boost::program_options::value<int>(&mVerboseLevel),"Debug level: 1,2,3\n(default: 0)")
        ("sender-name,n",boost::program_options::value<std::string>(&mSendersName)->multitoken(),"Senders name")
        ("sender-add,s",boost::program_options::value<std::string>(&mSendersAddress)->multitoken(),"Senders address")
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


    int
Session::PrepareSession ( )
{
    std::string home_dir ((const char *)getenv("HOME"));
    std::string conf_dir = home_dir + "/.config/";
    std::string user_dir = home_dir + "/.local/share/";

    /*  make directories if not already present 
     *  continue if already present
     */
    if(mkdir(conf_dir.c_str(), 0700) == -1)
    {
        if(errno !=  EEXIST)
        {
            std::cout << "Error creating ~/.conf directory. Please report a bug" << std::endl;
            return -1;
        }
        else
        {
            if(mkdir(mConfigDirectory.c_str(), 0700) == -1)
            {
                if(errno != EEXIST)
                {
                    std::cout << "Error creating " << mConfigDirectory << " directory. Please report a bug" << std::endl;
                    return -1;
                }
                else
                    std::cout << mConfigDirectory << " already exists. Continuing.." << std::endl;
            }
            else
            {
                    std::cout << "Creating " << mConfigDirectory << " directory.." << std::endl;

            }
        }

    }

    if(mkdir(user_dir.c_str(), 0700) == -1)
    {
        if(errno != EEXIST)
        {
            std::cout << "Error creating ~/.local/share directory. Please report a bug" << std::endl;
            return -1;
        }
        else 
        {
            if(mkdir(mUserDataDirectory.c_str(), 0700) == -1)
            {
                if(errno != EEXIST)
                {
                    std::cout << "Error creating " << mUserDataDirectory << " directory. Please report a bug" << std::endl;
                    return -1;
                }
                else
                    std::cout << mUserDataDirectory << " already exists. Continuing.." << std::endl;
            }
            else
            {
                    std::cout << "Creating " << mUserDataDirectory << " directory.." << std::endl;

            }
        }
    }
    /*  all directories set up */
    return 0;
}		/* -----  end of method Session::PrepareSession  ----- */


    std::string
Session::PrintListAsString ( )
{
    std::string ret_val = "";
    char temp[50];
    for (int i = 0; i < mPrintList.size(); i++)
    {
        sprintf(temp,"%d",mPrintList[i]);
        ret_val += std::string(temp) + ",";
    }
    return ret_val;
}		/* -----  end of method Session::PrintList  ----- */

