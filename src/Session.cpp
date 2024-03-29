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
    mConfigFileLocation = mConfigDirectory + "config.cfg";
    mFASUsername = "";
    mUserDataDirectory = home_dir + "/" + ".local/share/fedora-freemedia-tool/";
    mDatabaseFileLocation = home_dir + "/.local/share/fedora-freemedia-tool/freemedia-database.db";
    mInputReportFileLocation = home_dir + "/.local/share/fedora-freemedia-tool/report.csv";
    mEnvelopeTemplateLocation = DATADIR "/fedora-freemedia-tool/Freemedia-mailer.png";
    mSendersName = "Free media contributors name comes here!";
    mSendersAddress = "Address with %precent sign as %line break comes here!%";
    mListWhat = "all";
    mListLongWhat = "all";
    mVerboseLevel = 0;
    mListToPrint.push_back(0);
    mResetTicketNumbers.push_back(0);
    mResolveTicketNumbers.push_back(0);
    mAssignLCNumbers.push_back(0);
    mModifyTicket = 0;
    mTicketToPrintInfoFor = 0;
    mDesc.add_options()
        ("help,h", "Print this usage message.")
        ("config-file,c",boost::program_options::value<std::string>(&mConfigFileLocation)->implicit_value(mConfigFileLocation),"Configuration file\n")
        ("database,d",boost::program_options::value<std::string>(&mDatabaseFileLocation)->implicit_value(mDatabaseFileLocation.c_str()),"Complete output file path\n")
        ("fas-username,x",boost::program_options::value<std::string>(&mFASUsername)->implicit_value(mFASUsername.c_str()),"FAS Username. Password will be asked if required.\nNo command line option is provided to enter password to avoid entering of password in plaintext on the terminal.\nUse with -u\n")
        ("import,i",boost::program_options::value<std::string>(&mInputReportFileLocation)->implicit_value(mInputReportFileLocation.c_str()),"Import data\nOptional argument: Complete input file path\n")
        ("resolve,r",boost::program_options::value<std::vector <int> >(&mResolveTicketNumbers)->multitoken(),"Change status of provided ticket numbers to RESOLVED\n(default: 0 meaning all new tickets)\n")
        ("reset,e",boost::program_options::value<std::vector <int> >(&mResetTicketNumbers)->multitoken(),"Change status of provided ticket numbers to PENDING\n(default: 0 meaning all fixed tickets)\n")
        ("assign-to-lc,A",boost::program_options::value<std::vector <int> >(&mAssignLCNumbers)->multitoken(),"Assign these tickets to a Local Contact\n(default: 0 meaning all)\n")
        ("force,f",boost::program_options::value<std::string>()->implicit_value(""),"Force import even if the ticket exists in database\n")
        ("add-new,a",boost::program_options::value<std::string>()->implicit_value(""),"Manually add a new entry: unimplemented\n")
        ("modify,m",boost::program_options::value<int>(&mModifyTicket),"Modify the address in a ticket entry.\nGenerally required when the address is malformed and the splitter can't handle it.\narg: Ticket number\n")
        ("output-dir,o",boost::program_options::value<std::string>(&mOutputDirectory)->implicit_value(mOutputDirectory.c_str()),"Directory to put the printed envelopes\n")
        ("print-ticket-info,P",boost::program_options::value <int> (&mTicketToPrintInfoFor),"Print ticket info for any one ticket number\n")
        ("print,p",boost::program_options::value< std::vector<int> >(&mListToPrint)->multitoken(),"List of ticket numbers to print envelopes for\n(default: 0 meaning all new tickets)\n")
        ("list,l",boost::program_options::value<std::string>(&mListWhat)->implicit_value(mListWhat.c_str()),"List records in database\nall,pending,complete,local-contact\n")
        ("list-long,L",boost::program_options::value<std::string>(&mListLongWhat)->implicit_value(mListLongWhat.c_str()),"List records with description\nall,pending,complete,local-contact\n")
        ("update,u",boost::program_options::value<std::string>()->implicit_value(""),"Download latest report from the trac and update the database\nThis automatically stores the information in default database directory\n")
        ("v-level,v",boost::program_options::value<int>(&mVerboseLevel)->implicit_value(mVerboseLevel),"Debug level: 1,2,3\n")
        ("sender-name,n",boost::program_options::value<std::string>(&mSendersName)->multitoken(),"Senders name\n")
        ("sender-add,s",boost::program_options::value<std::string>(&mSendersAddress)->multitoken(),"Senders address\nUse % as a line limiter\n")
        ("template,t",boost::program_options::value<std::string>(&mEnvelopeTemplateLocation)->implicit_value(mEnvelopeTemplateLocation.c_str()),"Location of envelope template\n")
        ("version,V",boost::program_options::value<std::string>()->implicit_value(""),"Package information: version etc.")
        ;

    /*  Initialize cURLpp */
    cURLpp::initialize();


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
    try
    {
        int counter;
        /*  notify required to save the values into my variables. */
        /*  TODO: confirm this behaviour */

        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, mDesc), mVariableMap);
        boost::program_options::notify(mVariableMap);

        std::ifstream config_file_handle(mConfigFileLocation.c_str());
        if(!config_file_handle)
        {
            std::cout << "[X] No config file found at: " << mConfigFileLocation << std::endl;
        }
        else
        {
            std::cout << "[+] Parsing available options from config file: " << mConfigFileLocation << std::endl;
            boost::program_options::store(boost::program_options::parse_config_file(config_file_handle,mDesc),mVariableMap);
        }
        boost::program_options::notify(mVariableMap);

        if (mVariableMap.count("help")) 
        {
            std::cout << mDesc << std::endl;
        }
        else if(mVariableMap.count("version"))
        {
            std::cout << ">> " << PACKAGE_NAME  << " version: " << VERSION << std::endl;
            std::cout << ">> Please report all bugs to: " << PACKAGE_BUGREPORT << std::endl;
        }
        else 
        {
            if(PrepareSession() == -1)
                return 0;

            if (mVariableMap.count("import"))
            {
                ImportData newInstance(mInputReportFileLocation,mDatabaseFileLocation);
                if(newInstance.FileIsSane())
                {
                    newInstance.ImportDataToDatabase();
                }
            }
            else if(mVariableMap.count("print-ticket-info"))
            {
                ExportData newExportInstance(mDatabaseFileLocation,mOutputDirectory,mEnvelopeTemplateLocation);
                newExportInstance.GetTicketInfoFromNumber(mTicketToPrintInfoFor);
                newExportInstance.PrintTicketInfoFromNumber(mTicketToPrintInfoFor);
            }
            else if(mVariableMap.count("resolve"))
            {
                ImportData newInstance(mInputReportFileLocation,mDatabaseFileLocation);
                newInstance.ToggleTickets(mResolveTicketNumbers,"2");
            }
            else if(mVariableMap.count("reset"))
            {
                ImportData newInstance(mInputReportFileLocation,mDatabaseFileLocation);
                newInstance.ToggleTickets(mResetTicketNumbers,"1");
            }
            else if(mVariableMap.count("assign-to-lc"))
            {
                ImportData newInstance(mInputReportFileLocation,mDatabaseFileLocation);
                newInstance.ToggleTickets(mAssignLCNumbers,"3");
            }
            else if(mVariableMap.count("modify"))
            {
                ExportData newExportInstance(mDatabaseFileLocation,mOutputDirectory, mEnvelopeTemplateLocation);
                newExportInstance.GetTicketInfoFromNumber(mModifyTicket);
                std::cout << "Current information:" << std::endl;
                newExportInstance.PrintRawTicketInfoFromNumber(mModifyTicket);

                ImportData newInstance(mInputReportFileLocation,mDatabaseFileLocation);
                newInstance.ModifyTicketNumber(mModifyTicket);

            }
            else if(mVariableMap.count("update"))
            {
                GetReport newReportToGet;
                if(mVariableMap.count("fas-username"))
                {
                    newReportToGet.SetUsername(mFASUsername);
                }
                newReportToGet.SetDownloadLocation(mInputReportFileLocation);
                newReportToGet.DownloadReport();

                ImportData newInstance(mInputReportFileLocation,mDatabaseFileLocation);
                if(newInstance.FileIsSane())
                {
                    newInstance.ImportDataToDatabase();
                }
            }
            else if(mVariableMap.count("print"))
            {
                ExportData newExportInstance(mDatabaseFileLocation,mOutputDirectory, mEnvelopeTemplateLocation);
                std::vector<int> temp_vector;

                newExportInstance.ImportTemplate();
                newExportInstance.SetSendersName(SendersName());
                newExportInstance.SetSendersAddress(SendersAddress());
                if(mListToPrint.size() == 1 && mListToPrint[0] == 0)
                {
                    newExportInstance.GetPendingTicketNumbers();
                    mListToPrint = newExportInstance.PendingTicketNumbers();
                    if(mListToPrint.size() == 0)
                    {
                        std::cout << "[++] There are no pending tickets!" << std::endl;
                        return 0;
                    }
                }
                for (counter = 0; counter < mListToPrint.size(); counter++)
                {
                    if(newExportInstance.OverlayTemplate(mListToPrint[counter]) == -1)
                    {
                        std::cout << "[X] Error printing envelope for ticket number: " << mListToPrint[counter] << std::endl;
                    }
                    else
                    {
                        temp_vector.push_back(mListToPrint[counter]);
                    }
                }

                newExportInstance.CloseDatabaseConnection();

                if(temp_vector.size() != 0)
                {
                    ImportData newInstance(mInputReportFileLocation,mDatabaseFileLocation);
                    newInstance.ToggleTickets(temp_vector,"4"); /* mark tickets as printed */
                }
                else
                    std::cout << "[+] No envelopes printed" << std::endl;
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
                else if(mListWhat == "local-contact")
                {
                    newExportInstance.GetLocalContactTicketNumbers();
                    newExportInstance.PrintLocalContactTicketNumbers();
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
                else if(mListLongWhat == "local-contact")
                {
                    newExportInstance.GetLocalContactTicketNumbers();
                    newExportInstance.PrintLocalContactTickets();
                }
                else
                {
                    newExportInstance.GetAllTicketNumbers();
                    newExportInstance.PrintAllTickets();
                }
            }
        }
        config_file_handle.close();
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
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
                    std::cout << "[X] Error creating " << mConfigDirectory << " directory. Please report a bug" << std::endl;
                    return -1;
                }
                else
                    std::cout << "[+] " << mConfigDirectory << " already exists. Continuing.." << std::endl;
            }
            else
            {
                    std::cout << "[+] Creating " << mConfigDirectory << " directory.." << std::endl;

            }
        }

    }

    if(mkdir(user_dir.c_str(), 0700) == -1)
    {
        if(errno != EEXIST)
        {
            std::cout << "[X] Error creating ~/.local/share directory. Please report a bug" << std::endl;
            return -1;
        }
        else 
        {
            if(mkdir(mUserDataDirectory.c_str(), 0700) == -1)
            {
                if(errno != EEXIST)
                {
                    std::cout << "[X] Error creating " << mUserDataDirectory << " directory. Please report a bug" << std::endl;
                    return -1;
                }
                else
                    std::cout << "[+] " << mUserDataDirectory << " already exists. Continuing.." << std::endl;
            }
            else
            {
                    std::cout << "[+] Creating " << mUserDataDirectory << " directory.." << std::endl;

            }
        }
    }
    /*  all directories set up */
    return 0;
}		/* -----  end of method Session::PrepareSession  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Session
 *      Method:  Session :: PrintListAsString
 * Description:  Debugging method
 *--------------------------------------------------------------------------------------
 */
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



/*
 *--------------------------------------------------------------------------------------
 *       Class:  Session
 *      Method:  Session :: ~Session
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Session::~Session ()
{
    cURLpp::terminate();
}		/* -----  end of method Session::~Session  ----- */

