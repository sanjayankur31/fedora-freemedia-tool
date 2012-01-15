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
 *       Filename:  ExportData.cpp
 *
 *    Description:  Export data from the database to various
 *    destinations
 *
 *        Version:  1.0
 *        Created:  11/01/12 22:24:09
 *       Revision:  1
 *       Compiler:  g++
 *
 *         Author:  Ankur Sinha (FranciscoD), sanjay DOT ankur AT gmail DOT com
 *        Company:  None
 *
 * =====================================================================================
 */


#include	"ExportData.h"

/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
ExportData::ExportData (std::string databaseFile, std::string outputDirectory)
{
    mDatabaseFile = databaseFile;
    mOutputDirectory = outputDirectory;
}  /* -----  end of method ExportData::ExportData  (constructor)  ----- */



    void
ExportData::GetAllTicketsFull ( )
{
    int sqlite_return_value = 0;
    char* error_message;
    char *dummy;
    std::vector<std::string> string_vector_return;

    sqlite_return_value = sqlite3_open(mDatabaseFile.c_str(), &mpDatabaseHandle);
    if(sqlite_return_value == SQLITE_OK)
    {
        std::string select_query = "SELECT * FROM FREEMEDIA;";
        sqlite_return_value = sqlite3_prepare_v2(mpDatabaseHandle, (const char*)select_query.c_str(),select_query.size(),&mpStatementHandle,(const char**)&dummy);
        if(sqlite_return_value == SQLITE_OK)
        {
            do
            {
                sqlite_return_value = sqlite3_step(mpStatementHandle);
                if(sqlite_return_value = SQLITE_ERROR)
                {
                    std::cout << "Error preparing select query" << std::endl;
                    std::cout << "SQlite error description: " << sqlite3_errmsg(mpDatabaseHandle) << std::endl;
                    sqlite3_close(mpDatabaseHandle);
                    return;

                }
                // TODO: put the data someplace

            }while(sqlite_return_value = SQLITE_ROW);

        }
        else
        {
            std::cout << "Error preparing select query" << std::endl;
            std::cout << "SQlite error description: " << sqlite3_errmsg(mpDatabaseHandle) << std::endl;
            sqlite3_close(mpDatabaseHandle);
        }

    }
    return ;
}		/* -----  end of method ExportData::GetAllTicketsFull  ----- */



    void
ExportData::GetPendingTicketsFull ( )
{
    return ;
}		/* -----  end of method ExportData::GetPendingTicketsFull  ----- */



    void
ExportData::GetCompleteTicketsFull ( )
{
    return ;
}		/* -----  end of method ExportData::GetCompleteTicketsFull  ----- */


    void
ExportData::GetAllTicketNumbers ( )
{
    int sqlite_return_value = 0;
    char* error_message;
    char *dummy;

    mAllTicketNumbers.clear();

    sqlite_return_value = sqlite3_open(mDatabaseFile.c_str(), &mpDatabaseHandle);
    if(sqlite_return_value == SQLITE_OK)
    {
        std::string select_query = "SELECT TICKET_NUMBER FROM FREEMEDIA;";
        sqlite_return_value = sqlite3_prepare_v2(mpDatabaseHandle, (const char*)select_query.c_str(),select_query.size(),&mpStatementHandle,(const char**)&dummy);
        if(sqlite_return_value == SQLITE_OK)
        {
            do
            {
                sqlite_return_value = sqlite3_step(mpStatementHandle);
                if(sqlite_return_value == SQLITE_ERROR)
                {
                    std::cout << "Error stepping returned rows" << std::endl;
                    std::cout << "SQlite error description: " << sqlite3_errmsg(mpDatabaseHandle) << std::endl;
                    sqlite3_close(mpDatabaseHandle);
                    return;

                }
                mAllTicketNumbers.push_back(sqlite3_column_int(mpStatementHandle,0));
            }while(sqlite_return_value != SQLITE_DONE);

        }
        else
        {
            std::cout << "Error preparing select query" << std::endl;
            std::cout << "SQlite error description: " << sqlite3_errmsg(mpDatabaseHandle) << std::endl;
            sqlite3_close(mpDatabaseHandle);
        }

    }
    /*  why is this extra 0 being added? sqlite quirkyness? */
    mAllTicketNumbers.pop_back();
    mNumberOfTotalTickets = mAllTicketNumbers.size();
    sqlite3_close(mpDatabaseHandle);
    return ;
}		/* -----  end of method ExportData::GetAllTicketNumbers  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: PrintAllTicketNumbers
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::PrintAllTicketNumbers ( )
{
    std::cout << "All tickets in data base (ticket numbers only): " << mNumberOfTotalTickets << std::endl;
    if(mAllTicketNumbers.empty())
    {
        std::cout << "Either the retrieval method has not been called, or there are no tickets in the database!" << std::endl;
        return;
    }
    PrintVectorContents (mAllTicketNumbers);
    return ;
}		/* -----  end of method ExportData::PrintAllTicketNumbers  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: GetPendingTicketNumbers
 * Description:  Get the tickets with status=1
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::GetPendingTicketNumbers ( )
{
    int sqlite_return_value = 0;
    char* error_message;
    char *dummy;

    mPendingTicketNumbers.clear();

    sqlite_return_value = sqlite3_open(mDatabaseFile.c_str(), &mpDatabaseHandle);
    if(sqlite_return_value == SQLITE_OK)
    {
        std::string select_query = "SELECT TICKET_NUMBER FROM FREEMEDIA WHERE STATUS=1;";
        sqlite_return_value = sqlite3_prepare_v2(mpDatabaseHandle, (const char*)select_query.c_str(),select_query.size(),&mpStatementHandle,(const char**)&dummy);
        if(sqlite_return_value == SQLITE_OK)
        {
            do
            {
                sqlite_return_value = sqlite3_step(mpStatementHandle);
                if(sqlite_return_value == SQLITE_ERROR)
                {
                    std::cout << "Error stepping returned rows" << std::endl;
                    std::cout << "SQlite error description: " << sqlite3_errmsg(mpDatabaseHandle) << std::endl;
                    sqlite3_close(mpDatabaseHandle);
                    return;

                }
                mPendingTicketNumbers.push_back(sqlite3_column_int(mpStatementHandle,0));
            }while(sqlite_return_value != SQLITE_DONE);

        }
        else
        {
            std::cout << "Error preparing select query" << std::endl;
            std::cout << "SQlite error description: " << sqlite3_errmsg(mpDatabaseHandle) << std::endl;
            sqlite3_close(mpDatabaseHandle);
        }

    }
    /*  why is this extra 0 being added? sqlite quirkyness? */
    mPendingTicketNumbers.pop_back();
    mNumberOfPendingTickets = mPendingTicketNumbers.size(); 
    sqlite3_close(mpDatabaseHandle);
    return ;
}		/* -----  end of method ExportData::GetPendingTicketNumbers  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: PrintPendingTicketNumbers
 * Description:  Print the ticket numbers that the Get method filled
 * up
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::PrintPendingTicketNumbers ( )
{
    std::cout << "Pending tickets in data base (ticket numbers only): " << mNumberOfPendingTickets << std::endl;
    if(mPendingTicketNumbers.empty())
    {
        std::cout << "Either the retrieval method has not been called, or there are no pending tickets in the database!" << std::endl;
        return;
    }
    PrintVectorContents(mPendingTicketNumbers);
    return ;
}		/* -----  end of method ExportData::PrintPendingTicketNumbers  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: PrintVectorContents
 * Description:  A general method to print any vector out
 *--------------------------------------------------------------------------------------
 */
template <typename I>
    void
ExportData::PrintVectorContents (std::vector<I> input_vector)
{
    typename std::vector<I>::iterator ticketNumber;


    for(ticketNumber = input_vector.begin(); ticketNumber != input_vector.end(); ticketNumber++)
    {
        std::cout << "#" << *ticketNumber << std::endl;
    }
    return ;
}		/* -----  end of method ExportData::PrintVectorContents  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: GetCompleteTicketNumbers
 * Description:  Get a list of all the complete tickets
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::GetCompleteTicketNumbers ( )
{
    int sqlite_return_value = 0;
    char* error_message;
    char *dummy;

    mCompleteTicketNumbers.clear();

    sqlite_return_value = sqlite3_open(mDatabaseFile.c_str(), &mpDatabaseHandle);
    if(sqlite_return_value == SQLITE_OK)
    {
        std::string select_query = "SELECT TICKET_NUMBER FROM FREEMEDIA WHERE STATUS=0;";
        sqlite_return_value = sqlite3_prepare_v2(mpDatabaseHandle, (const char*)select_query.c_str(),select_query.size(),&mpStatementHandle,(const char**)&dummy);
        if(sqlite_return_value == SQLITE_OK)
        {
            do
            {
                sqlite_return_value = sqlite3_step(mpStatementHandle);
                if(sqlite_return_value == SQLITE_ERROR)
                {
                    std::cout << "Error stepping returned rows" << std::endl;
                    std::cout << "SQlite error description: " << sqlite3_errmsg(mpDatabaseHandle) << std::endl;
                    sqlite3_close(mpDatabaseHandle);
                    return;

                }
                mCompleteTicketNumbers.push_back(sqlite3_column_int(mpStatementHandle,0));
            }while(sqlite_return_value != SQLITE_DONE);

        }
        else
        {
            std::cout << "Error preparing select query" << std::endl;
            std::cout << "SQlite error description: " << sqlite3_errmsg(mpDatabaseHandle) << std::endl;
            sqlite3_close(mpDatabaseHandle);
        }

    }
    /*  why is this extra 0 being added? sqlite quirkyness? */
    mCompleteTicketNumbers.pop_back();
    mNumberOfCompleteTickets = mCompleteTicketNumbers.size();
    sqlite3_close(mpDatabaseHandle);
    return ;
}		/* -----  end of method ExportData::GetCompleteTicketNumbers  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: PrintCompleteTicketNumbers
 * Description:  Print the list
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::PrintCompleteTicketNumbers ( )
{
    std::cout << "Complete tickets in data base (ticket numbers only): " << mNumberOfCompleteTickets << std::endl;
    if(mCompleteTicketNumbers.empty())
    {
        std::cout << "Either the retrieval method has not been called, or there are no complete tickets in the database!" << std::endl;
        return;
    }
    PrintVectorContents(mCompleteTicketNumbers);
    return ;
}		/* -----  end of method ExportData::PrintCompleteTicketNumbers  ----- */

