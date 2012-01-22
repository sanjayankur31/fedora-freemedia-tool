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
    : mDesc("Usage: ffmt [Options] [args]...\nA tool to assist Fedora Freemedia contributors.\nWithout options, it prints pending envelopes to the current directory using default values of input and database files.\n\nOptions")
{
    std::string home_dir ((const char *)getenv("HOME"));
    mOutputDirectory = "./";
    mConfigDirectory = home_dir + "/" + ".config/fedora-freemedia-tool/";
    mConfigFileLocation = mConfigDirectory + "fedora-freemedia-tool.cfg";
    mUserDataDirectory = home_dir + "/" + ".local/share/fedora-freemedia-tool/";
    mDatabaseFileLocation = home_dir + "/.local/share/fedora-freemedia-tool/freemedia-database.db";
    mInputReportFileLocation = home_dir + "/.local/share/fedora-freemedia-tool/report.csv";
    mEnvelopeTemplateLocation = "/usr/share/fedora-freemedia-tool/Freemedia-mailer.png";
    mSendersName = "Free media contributors name comes here!";
    mSendersAddress = "Address with %precent sign as %line break comes here!%";
    mListWhat = "all";
    mListLongWhat = "all";
    mVerboseLevel = 0;
    mListToPrint.push_back(0);
    mDesc.add_options()
        ("help,h", "Print this usage message.")
        ("config-file,c",boost::program_options::value<std::string>(&mConfigFileLocation)->implicit_value(mConfigFileLocation),"Configuration file\n")
        ("database,d",boost::program_options::value<std::string>(&mDatabaseFileLocation)->implicit_value(mDatabaseFileLocation.c_str()),"Complete output file path\n")
        ("import,i",boost::program_options::value<std::string>(&mInputReportFileLocation)->implicit_value(mInputReportFileLocation.c_str()),"Import data\nOptional argument: Complete input file path\n")
        ("add-new,a",boost::program_options::value<std::string>()->implicit_value(""),"Manually add a new entry: unimplemented\n")
        ("output-dir,o",boost::program_options::value<std::string>(&mOutputDirectory)->implicit_value(mOutputDirectory.c_str()),"Directory to put the printed envelopes\n")
        ("print,p",boost::program_options::value< std::vector<int> >(&mListToPrint)->multitoken(),"List of ticket numbers to print envelopes for\n(default: 0 meaning all new tickets)\n")
        ("list,l",boost::program_options::value<std::string>(&mListWhat)->implicit_value(mListWhat.c_str()),"List records in database\nall,pending,complete\n")
        ("list-long,g",boost::program_options::value<std::string>(&mListLongWhat)->implicit_value(mListLongWhat.c_str()),"List records with description\nall,pending,complete\n")
        ("v-level,v",boost::program_options::value<int>(&mVerboseLevel)->implicit_value(mVerboseLevel),"Debug level: 1,2,3\n")
        ("sender-name,n",boost::program_options::value<std::string>(&mSendersName)->multitoken(),"Senders name\n")
        ("sender-add,s",boost::program_options::value<std::string>(&mSendersAddress)->multitoken(),"Senders address\nUse % as a line limiter\n")
        ("template,t",boost::program_options::value<std::string>(&mEnvelopeTemplateLocation)->implicit_value(mEnvelopeTemplateLocation.c_str()),"Location of envelope template\n")
        ("version,V",boost::program_options::value<std::string>()->implicit_value(""),"Package information: version etc.")
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
    int counter;

    if (mVariableMap.count("help")) 
    {
        std::cout << mDesc << std::endl;
    }
    else if(mVariableMap.count("version"))
    {
        std::cout << PACKAGE_NAME  << " Version: " << VERSION << std::endl;
        std::cout << "Please report all bugs to: " << PACKAGE_BUGREPORT << std::endl;
    }
    else {
        if(PrepareSession() == -1)
            return 0;

        if (mVariableMap.count("import"))
        {
            ImportData newInstance(mInputReportFileLocation,mDatabaseFileLocation);
            newInstance.ImportDataToDatabase();
        }
        else if(mVariableMap.count("print"))
        {
            ExportData newExportInstance(mDatabaseFileLocation,mOutputDirectory, mEnvelopeTemplateLocation);
            newExportInstance.ImportTemplate();
            newExportInstance.SetSendersName(SendersName());
            newExportInstance.SetSendersAddress(SendersAddress());
            for (counter = 0; counter < mListToPrint.size(); counter++)
            {
                if(newExportInstance.GetTicketInfoFromNumber(mListToPrint[counter]) == -1)
                    std::cout << "Could not find data on ticket " << mListToPrint[counter] << " in database." << std::endl;
                else
                {
                    if(newExportInstance.OverlayTemplate(mListToPrint[counter]) == -1)
                    {
                        std::cout << "Error printing envelope for ticket number: " << mListToPrint[counter] << std::endl;
                    }
                }
            }
        }
        else if(mVariableMap.count("list"))
        {
            ExportData newExportInstance(mDatabaseFileLocation,mOutputDirectory, mEnvelopeTemplateLocation);
            if(mListWhat == "pending")
            {
                newExportInstance.GetPendingTicketNumbers();
                newExportInstance.PrintPendingTicketNumbers();
            }
            else if(mListWhat == "complete")
            {
                newExportInstance.GetCompleteTicketNumbers();
                newExportInstance.PrintCompleteTicketNumbers();
            }
            else
            {
                newExportInstance.GetAllTicketNumbers();
                newExportInstance.PrintAllTicketNumbers();
            }

        }
        else if(mVariableMap.count("list-long"))
        {
            ExportData newExportInstance(mDatabaseFileLocation,mOutputDirectory, mEnvelopeTemplateLocation);
            if(mListLongWhat == "pending")
            {
                newExportInstance.GetPendingTicketNumbers();
                newExportInstance.PrintPendingTickets();
            }
            else if(mListLongWhat == "complete")
            {
                newExportInstance.GetCompleteTicketNumbers();
                newExportInstance.PrintCompleteTickets();
            }
            else
            {
                newExportInstance.GetAllTicketNumbers();
                newExportInstance.PrintAllTickets();
            }
        }
    }

    return -1;
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
    for (int i = 0; i < mListToPrint.size(); i++)
    {
        sprintf(temp,"%d",mListToPrint[i]);
        ret_val += std::string(temp) + ",";
    }
    return ret_val;
}		/* -----  end of method Session::PrintList  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Session
 *      Method:  Session :: EnvelopeTemplateLocation
 * Description:  
 *--------------------------------------------------------------------------------------
 */
std::string
Session::EnvelopeTemplateLocation ()
{
    return mEnvelopeTemplateLocation;
}		/* -----  end of method Session::EnvelopeTemplateLocation  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Session
 *      Method:  Session :: SendersName
 * Description:  
 *--------------------------------------------------------------------------------------
 */
std::string
Session::SendersName ( )
{
    return mSendersName;
}		/* -----  end of method Session::SendersName  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Session
 *      Method:  Session :: SendersAddress
 * Description:  
 *--------------------------------------------------------------------------------------
 */
std::string
Session::SendersAddress ( )
{
    return mSendersAddress;
}		/* -----  end of method Session::SendersAddress  ----- */

