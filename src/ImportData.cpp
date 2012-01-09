/*
 * =====================================================================================
 *
 *  Copyright 2011 Ankur Sinha
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
 *       Filename:  ImportData.cpp
 *
 *    Description:  Import from data files
 *
 *        Version:  1.0
 *        Created:  23/12/11 17:41:06
 *       Revision:  2
 *       Compiler:  g++
 *
 *         Author:  Ankur Sinha (FranciscoD), sanjay DOT ankur AT gmail DOT com
 *        Company:  None
 *
 * =====================================================================================
 */

#include	"ImportData.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  dummy_callback_function
 *  Description:  
 * =====================================================================================
 */
    static int
dummy_callback_function (void *notUsed, int argc, char **argv, char **columnNames)
{
    return 0;
}		/* -----  end of static function dummy_callback_function  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  ImportData
 *      Method:  ImportData
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
ImportData::ImportData (std::string dataFile, std::string databaseFile)
{
    mAllGood = true;
    int sqlite_return_value = 0;
    char* error_message;
//    std::cout << home_dir << std::endl << mConfigDirectory << std::endl << mUserDataDirectory << std::endl;

    mDataFile = dataFile;
    std::cout << "Datafile set to: " << mDataFile << std::endl;
    mDatabaseFile = databaseFile;
    std::cout << "Databasefile set to: " << mDatabaseFile << std::endl;
     /*
     *  - csv, tsv
     *  TODO: xml */

    
    /*  initialize database connection 
     *  TODO: do we use the same handle for all transactions or do we
     *  make handles as and when required and destroy them?
     *
     *  Check if database file exists, and act accordingly*/
    std::ifstream temporary_stream(databaseFile.c_str());
    if(temporary_stream)
    {
        std::cout << "Database already exists. Continuing.." << std::endl;
        temporary_stream.close();
    }
    else
    {
        std::cout << "Database does not exist. Creating.." << std::endl;
        sqlite_return_value = sqlite3_open(databaseFile.c_str(), &mpDatabaseHandle);
        if(sqlite_return_value == SQLITE_OK)
        {
            std::string create_table_query = "CREATE TABLE FREEMEDIA (TICKET_NUMBER INTEGER, NAME VARCHAR2(100), ADDRESS_COMPLETE VARCHAR2(500), REQUIREMENT INTEGER, STATUS INTEGER, SERVICE_DATE DATE, PRIMARY KEY (TICKET_NUMBER));";
            sqlite_return_value = sqlite3_exec(mpDatabaseHandle, create_table_query.c_str(), dummy_callback_function, 0, &error_message);
            if(sqlite_return_value != SQLITE_OK)
            {
                std::cout << "Error creating new table in database. Please file a bug.." << std::endl;
                std::cout << "SQlite error description: " << error_message << std::endl;
                sqlite3_free(error_message);
                mAllGood = false;
            }
            sqlite3_close(mpDatabaseHandle);

        }
        else
        {
            std::cout << "Error connecting to/opening database. Please file a bug." << std::endl;
            std::cout << "SQlite error description: " << sqlite3_errmsg(mpDatabaseHandle) << std::endl;
            sqlite3_close(mpDatabaseHandle);
            mAllGood = false;
        }

    }

}  /* -----  end of method ImportData::ImportData  (constructor)  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ImportData
 *      Method:  ImportData :: ImportDataToDatabase
 * Description:  Import data from the data file to the database
 *--------------------------------------------------------------------------------------
 */
void
ImportData::ImportDataToDatabase (std::string filenameWithPath)
{
    if(!filenameWithPath.empty())
    {
        mDataFile = filenameWithPath;
    }
    std::cout << "Using datafile: " << mDataFile << std::endl;
    ImportDataToDatabase();
    return ;
}		/* -----  end of method ImportData::ImportDataToDatabase  ----- */

void
ImportData::ImportDataToDatabase ()
{

    std::string temp_buffer = "";
    std::vector <std::string> string_tokens;
    int sqlite_return_value = sqlite3_open(mDatabaseFile.c_str(), &mpDatabaseHandle);
    bool in_address = false;
    char* error_message;

    if(sqlite_return_value != SQLITE_OK)
    {

        std::cout << "Error opening database file.. Please file a bug." << std::endl;
        std::cout << "SQlite error description: " << sqlite3_errmsg(mpDatabaseHandle) << std::endl;
        return;
    }
    std::cout << "Entered worker import function.." << std::endl;
    mDataFileHandle.open(mDataFile.c_str());
    if (mDataFileHandle.good())
    {
        /*  discard header line */
        getline(mDataFileHandle,temp_buffer);

        while(mDataFileHandle.good() && !mDataFileHandle.eof())
        {
            in_address = false;
//            std::cout << "Got a new line now.." << std::endl;
            string_tokens.clear();
            temp_buffer.clear();
            getline(mDataFileHandle,temp_buffer);

            if(temp_buffer.empty())
                continue;

            /*  iterate and simply tokenize
             *
             *  Not using boost::Tokenizer to keep dependencies to a
             *  minimum 
             */

            std::string::iterator string_iterator;
            std::string::iterator comma_start = temp_buffer.begin();
            for(string_iterator = temp_buffer.begin(); string_iterator != temp_buffer.end(); string_iterator++)
            {
                /*  toggle flag 
                 *
                 *  I'm using this flag to prevent it from breaking up
                 *  my address. I'll break it up myself since I want
                 *  it to be five lines only 
                 *
                 *  May sometimes need manual intervention
                 */
                if(*string_iterator == '"')
                    in_address = !in_address;
                if(*string_iterator == ',' && !in_address)
                {
                    if(comma_start  != string_iterator)
                    {
                        std::string token = temp_buffer.substr(comma_start - temp_buffer.begin() + 1, string_iterator - comma_start -1);
                        if(!token.empty())
                        {
                            string_tokens.push_back(SanitizeSummary(token));
                        }
                    }
                comma_start = string_iterator;
                }
            }
            /*  using % as a place holder for a \c\r */
            std::string insert_statement = "INSERT INTO FREEMEDIA VALUES (" + string_tokens[1] + ", '" + string_tokens[2] + "', '" + ReplaceAll(string_tokens[6],"[[BR]]"," % ") + "', " + MediaCode(string_tokens[3]) + ", 1, '');";
//            std::cout << "SQL statement is: " << insert_statement << std::endl;

            sqlite_return_value = sqlite3_exec(mpDatabaseHandle, insert_statement.c_str(), dummy_callback_function, 0, &error_message);
            /*  duplicate entries */
            if(sqlite_return_value == SQLITE_CONSTRAINT)
            {
                std::cout << "Ticket " + string_tokens[1] + " already exists in table, skipping." << std::endl;
            }
            else if(sqlite_return_value != SQLITE_OK)
            {
                std::cout << "Error inserting data to table in database. Please file a bug.." << std::endl;
                std::cout << "SQlite error description: " << sqlite_return_value << ": " << error_message << std::endl;
                sqlite3_free(error_message);
            }
        }
    }
    mDataFileHandle.close();
    sqlite3_close(mpDatabaseHandle);
    return ;
}		/* -----  end of method ImportData::ImportDataToDatabase  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  ImportData
 *      Method:  ImportData :: SanitizeSummary
 * Description:  Extract requester name from the Summary
 *--------------------------------------------------------------------------------------
 */
std::string
ImportData::SanitizeSummary (std::string summaryToStrip)
{
    summaryToStrip = ToSentenceCase(summaryToStrip);
    std::string strippedSummary = summaryToStrip.substr(0,summaryToStrip.find(" From "));
    return strippedSummary;
}		/* -----  end of method ImportData::SanitizeSummary  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  ImportData
 *      Method:  ImportData :: SanitizeAddress
 * Description:  Sanitize address, maybe break it into different
 * address lines
 *
 * TODO: Logic to break into 5 address lines
 *--------------------------------------------------------------------------------------
 */
std::string
ImportData::SanitizeAddress (std::string addressToSanitize)
{
    /*  Come up with logic to break address into 5 lines to fit the
     *  envelope */
/*     for(std::string::iterator string_iterator = addressToSanitize.begin(); string_iterator != addressToSanitize.end(); string_iterator++)
 *     {
 *         std::string strippedAddress = addressToSanitize.erase(addressToSanitize.find("[[BR]]"),6);
 *     }
 */
    return ToSentenceCase(addressToSanitize);
//    return strippedAddress;
}		/* -----  end of method ImportData::SanitizeAddress  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  ImportData
 *      Method:  ImportData :: ToSentenceCase
 * Description:  Convert text to sentence case
 *
 * http://stackoverflow.com/questions/8530705/lowercase-string-to-sentence-case
 *--------------------------------------------------------------------------------------
 */
std::string
ImportData::ToSentenceCase (std::string textToModify)
{
    std::string::iterator string_iterator;

    for(string_iterator = textToModify.begin() + 1; string_iterator != textToModify.end(); string_iterator++)
    {
        if(!isalpha(*(string_iterator -1)) && islower(*string_iterator))
        {
            *string_iterator = toupper(*string_iterator);
        }
    }
    return textToModify;
}		/* -----  end of method ImportData::ToSentenceCase  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  ImportData
 *      Method:  ImportData :: MediaCode
 * Description:  Look at the string and get the media code to insert
 * into database. Using integers makes it just a little easier than
 * using text to lookup. 
 *
 * NOTE: Even though this method returns a string, in the database,
 * this value is stored as an integer
 *--------------------------------------------------------------------------------------
 */
std::string
ImportData::MediaCode ( std::string stringMediaName )
{
    /*
     * Media codes
     *
     * 0 - error
     * 1000 - GNOME + DVD + i386
     * 1100 - KDE + DVD + i386
     * 1010 - GNOME + LIVE + i386
     * 1001 - GNOME + DVD + x86_64
     *
     * TODO: add more codes later
     */
    if(stringMediaName == "x86_64 DVD")
        return "1001";
    if(stringMediaName == "i386 DVD")
        return "1000";
    if(stringMediaName == "x86_64 Live")
        return "1011";
    if(stringMediaName == "i386 Live")
        return "1010";

    return 0;

}		/* -----  end of method ImportData::MediaCode  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  ImportData
 *      Method:  ImportData :: ReplaceAll
 * Description:  My replace string routine. Not using boost to keep
 * deps to a minimum. May later use.
 *
 * http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string
 *--------------------------------------------------------------------------------------
 */
std::string
ImportData::ReplaceAll(std::string str, const std::string from, const std::string to) 
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) 
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
    return str;
}       /* ----- end of method ImportData::ReplaceAll  ----- */


