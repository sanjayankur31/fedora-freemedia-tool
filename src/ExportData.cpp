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
ExportData::ExportData (std::string databaseFile, std::string outputDirectory, std::string templateLocation)
{
    mDatabaseFile = databaseFile;
    mOutputDirectory = outputDirectory;
    mImageTemplateLocation = templateLocation;
    mSendersAddressStartX = 191;
    mSendersAddressStarty = 206;
    mReceiversAddressStartX = 310;
    mReceiversAddressStarty = 395;

}  /* -----  end of method ExportData::ExportData  (constructor)  ----- */

    void
ExportData::GetAllTicketNumbers ( )
{
    int sqlite_return_value = 0;
    char* error_message;
    const char *dummy;

    mAllTicketNumbers.clear();

    sqlite_return_value = sqlite3_open(mDatabaseFile.c_str(), &mpDatabaseHandle);
    if(sqlite_return_value == SQLITE_OK)
    {
        std::string select_query = "SELECT TICKET_NUMBER FROM FREEMEDIA;";
        sqlite_return_value = sqlite3_prepare_v2(mpDatabaseHandle, (const char*)select_query.c_str(),select_query.size(),&mpStatementHandle,&dummy);
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
    const char *dummy;

    mPendingTicketNumbers.clear();

    sqlite_return_value = sqlite3_open(mDatabaseFile.c_str(), &mpDatabaseHandle);
    if(sqlite_return_value == SQLITE_OK)
    {
        std::string select_query = "SELECT TICKET_NUMBER FROM FREEMEDIA WHERE STATUS=1;";
        sqlite_return_value = sqlite3_prepare_v2(mpDatabaseHandle, (const char*)select_query.c_str(),select_query.size(),&mpStatementHandle,&dummy);
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
    const char *dummy;

    mCompleteTicketNumbers.clear();

    sqlite_return_value = sqlite3_open(mDatabaseFile.c_str(), &mpDatabaseHandle);
    if(sqlite_return_value == SQLITE_OK)
    {
        std::string select_query = "SELECT TICKET_NUMBER FROM FREEMEDIA WHERE STATUS=2;";
        sqlite_return_value = sqlite3_prepare_v2(mpDatabaseHandle, (const char*)select_query.c_str(),select_query.size(),&mpStatementHandle,&dummy);
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


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: GetTicketInfoFromNumber
 * Description:  This method gets the information for a ticket and
 * fills up my maps
 *--------------------------------------------------------------------------------------
 */
    int
ExportData::GetTicketInfoFromNumber (int ticketNumber )
{
    int sqlite_return_value = 0;
    char* error_message;
    const char *dummy, *dummy_string1;
    const unsigned char *dummy_string;
    char ticketNumberString[30];
    sprintf(ticketNumberString,"%d",ticketNumber);

    if(mNameMap.find(ticketNumber) != mNameMap.end()) /* if the value isn't already in there! */
        return 0;

    sqlite_return_value = sqlite3_open(mDatabaseFile.c_str(), &mpDatabaseHandle);
    if(sqlite_return_value == SQLITE_OK)
    {
        std::string select_query = "SELECT * FROM FREEMEDIA WHERE TICKET_NUMBER=" + std::string(ticketNumberString) + ";";
        sqlite_return_value = sqlite3_prepare_v2(mpDatabaseHandle, (const char*)select_query.c_str(),select_query.size(),&mpStatementHandle,&dummy);
        if(sqlite_return_value == SQLITE_OK)
        {
            sqlite_return_value = sqlite3_step(mpStatementHandle);
            if(sqlite_return_value == SQLITE_ERROR)
            {
                std::cout << "Could not find info on ticket number " << ticketNumber << " in the database!"  << std::endl;
                std::cout << "SQlite error description: " << sqlite3_errmsg(mpDatabaseHandle) << std::endl;
                sqlite3_close(mpDatabaseHandle);
                return -1;

            }
            dummy_string = sqlite3_column_text(mpStatementHandle,1);
            mNameMap.insert(std::pair <int, std::string> (ticketNumber, std::string(reinterpret_cast<const char*>(dummy_string))));
            dummy_string = sqlite3_column_text(mpStatementHandle,2);
            mAddressMap.insert(std::pair <int, std::string> (ticketNumber, std::string(reinterpret_cast<const char*>(dummy_string))));
            dummy_string1 = RequestToString(sqlite3_column_int(mpStatementHandle,3)).c_str();
            mRequirementMap.insert(std::pair <int, std::string> (ticketNumber,std::string(dummy_string1)));
            dummy_string1 = StatusToString(sqlite3_column_int(mpStatementHandle,4)).c_str();
            mStatusMap.insert(std::pair <int, std::string> (ticketNumber,std::string(dummy_string1)));
            dummy_string = sqlite3_column_text(mpStatementHandle,5);
            mServiceDateMap.insert(std::pair <int, std::string> (ticketNumber, std::string(reinterpret_cast<const char*>(dummy_string))));

        }
        else
        {
            std::cout << "Error preparing select query" << std::endl;
            std::cout << "SQlite error description: " << sqlite3_errmsg(mpDatabaseHandle) << std::endl;
            sqlite3_close(mpDatabaseHandle);
            return -1;
        }

    }
    sqlite3_close(mpDatabaseHandle);
    return 0;
}		/* -----  end of method ExportData::GetTicketInfoFromNumber  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: PrintTicketInfoFromNumber
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::PrintTicketInfoFromNumber (int ticketNumber )
{
    std::vector<std::string> returned_vector;
    int i = 0;
    if(mNameMap.find(ticketNumber) == mNameMap.end()) /* Not found */
    {
        std::cout << std::setw(25) << "***" << std::endl;
        std::cout << std::setw(26) << "Ticket: #" << ticketNumber << std::endl << std::setw(24) << ":" << " not in map, please retrieve it first." << std::endl;
    }
    else
    {
        std::cout << std::setw(25) << "***" << std::endl;
        std::cout << std::setw(26) << "Ticket: #" << ticketNumber << std::endl;
        std::cout << std::setw(25) << "Requester Name: " << mNameMap[ticketNumber] << std::endl;

        returned_vector = BreakAddressToMultiline(mAddressMap[ticketNumber],'%');
        if(returned_vector.empty())
        {
            std::cout << "An error occured while printing information on ticket: " << ticketNumber << std::endl;
            return;
        }
        std::cout << std::setw(25) << "Requester Address: " << returned_vector[0] << std::endl;
        for(i = 1; i < returned_vector.size(); i++)
        {
            std::cout << std::setw(25) << ": " << returned_vector[i] << std::endl; 

        }

        std::cout << std::setw(25) << "Request: " << mRequirementMap[ticketNumber] << std::endl;
        std::cout << std::setw(25) << "Status: " << mStatusMap[ticketNumber] << std::endl;
        std::cout << std::setw(25) << "Service Date: " << mServiceDateMap[ticketNumber] << std::endl;
    }

    return ;
}		/* -----  end of method ExportData::PrintTicketInfoFromNumber  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: StatusToString
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    std::string
ExportData::StatusToString (int status )
{
    if(status == 1)
    {
        return std::string("PENDING");
    }
    else if(status == 2)
    {
        return std::string("FIXED");
    }
    else if(status == 3)
    {
        return std::string("Assigned to Local Contact");
    }
    return std::string("Unknown status");
}		/* -----  end of method ExportData::StatusToString  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: RequestToString
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    std::string
ExportData::RequestToString (int request )
{
    switch(request)
    {
        case 1000:
            return std::string("i386 DVD");
        case 1001:
            return std::string("x86_64 DVD");
        case 1011:
            return std::string("x86_64 Live");
        case 1010:
            return std::string("i386 Live");
    }

    return std::string("Unknown") ;
}		/* -----  end of method ExportData::RequestToString  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: BreakAddressToMultiline
 * Description:  Format the address according to line breaks
 *--------------------------------------------------------------------------------------
 */
    std::vector<std::string>
ExportData::BreakAddressToMultiline (std::string addressToFormat, char delimiter )
{
    std::vector<std::string> vector_to_return;
    std::string temp_buffer;
    size_t search_origin = 0;
    size_t found_pos = std::string::npos;
    while((found_pos = addressToFormat.find(delimiter,search_origin)) != std::string::npos)
    {
        temp_buffer = addressToFormat.substr(search_origin ,found_pos - search_origin);
        if(temp_buffer.size() < 36)
            vector_to_return.push_back(temp_buffer);
        else
        {
            std::vector<std::string> line_broken_down = BreakAddressToMultiline(temp_buffer, ',');
            if(line_broken_down.empty())
            {
                std::cout << "Splitter function failed to format the address.\nPlease modify the address manually and retry!" << std::endl;
                vector_to_return.clear();
                return vector_to_return;
            }

            int total_size = line_broken_down[0].size();
            std::string string_to_push = line_broken_down[0];
            for (int i = 1; i < line_broken_down.size() ; i++)
            {
                if((total_size + line_broken_down[i].size()) < 36)
                {
                    string_to_push += ("," + line_broken_down[i]);
                    total_size += (1 + line_broken_down[i].size());
                }
                else
                {
                    if(string_to_push != "")
                    {
                        vector_to_return.push_back(string_to_push);
                        string_to_push = line_broken_down[i];
                        total_size = line_broken_down[i].size();
                    }
                }
            }
            if(string_to_push != "")
            {
                vector_to_return.push_back(string_to_push);
            }
        }

        search_origin = found_pos + 1;
    }
    return vector_to_return;
}		/* -----  end of method ExportData::BreakAddressToMultiline  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: ImportTemplate
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::ImportTemplate ()
{
    mImageTemplate.read(mImageTemplateLocation);
    //    mDestinationImageTemplate.font("@Comfortaa-Regular");
    return ;
}		/* -----  end of method ExportData::ImportTemplate  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: OverlayTemplate
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    int
ExportData::OverlayTemplate (int ticketNumber)
{
    int i;
    std::vector<std::string>  formatted_address ;
    formatted_address = BreakAddressToMultiline(mSendersAddress,'%');
    if(formatted_address.empty())
    {
        std::cout << "Error printing senders address: " << mSendersAddress << ". Please recheck the value provided" << std::endl;
        return -1;
    }
    char ticket_number_string[50];
    sprintf(ticket_number_string,"%d",ticketNumber);
    std::string output_file_name = OutputDirectory() + "freemediaEnvelope" + std::string(ticket_number_string) + ".png";

    mDestinationImageTemplate = mImageTemplate;
    mDestinationImageTemplate.fontPointsize(13);

    mDestinationImageTemplate.draw(Magick::DrawableText(mSendersAddressStartX,mSendersAddressStarty + 14,mSendersName.c_str()));
    for (i = 0; i < formatted_address.size(); i++)
    {
        mDestinationImageTemplate.draw(Magick::DrawableText(mSendersAddressStartX,mSendersAddressStarty + (i + 2) * 14,formatted_address[i].c_str()));
    }

    formatted_address.clear();

    GetTicketInfoFromNumber(ticketNumber);      /* fill up the maps */
    formatted_address = BreakAddressToMultiline(mAddressMap[ticketNumber],'%');

    if(formatted_address.empty())
    {
        return -1;
    }
    for (i = 0; i < formatted_address.size(); i++)
    {
        mDestinationImageTemplate.draw(Magick::DrawableText(mReceiversAddressStartX,mReceiversAddressStarty + (i + 1) * 14,formatted_address[i].c_str()));
    }
//    mDestinationImageTemplate.display();
    mDestinationImageTemplate.write(output_file_name.c_str());
    std::cout << "Printed envelope for ticket number " << ticketNumber << " to " << output_file_name  << "." << std::endl;
    return 0;
}		/* -----  end of method ExportData::OverlayTemplate  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: SetSendersName
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::SetSendersName (std::string sendersName )
{
    mSendersName = sendersName;
    return ;
}		/* -----  end of method ExportData::SetSendersName  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: SetSendersAddress
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::SetSendersAddress (std::string sendersAddress )
{
    mSendersAddress = sendersAddress;
    return ;
}		/* -----  end of method ExportData::SetSendersAddress  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: OutputDirectory
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    std::string
ExportData::OutputDirectory ( )
{
    return mOutputDirectory;
}		/* -----  end of method ExportData::OutputDirectory  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: PrintAllTickets
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::PrintAllTickets ( )
{
    GetAllTicketNumbers();

    for(int i = 0; i < mAllTicketNumbers.size(); i++)
    {
        GetTicketInfoFromNumber(mAllTicketNumbers[i]);
        PrintTicketInfoFromNumber(mAllTicketNumbers[i]);
    }
    return ;
}		/* -----  end of method ExportData::PrintAllTickets  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: PrintPendingTickets
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::PrintPendingTickets ( )
{
    std::cout << "Total Pending tickets are: " << mPendingTicketNumbers.size() << std::endl;
    for(int i = 0; i < mPendingTicketNumbers.size(); i++)
    {
        GetTicketInfoFromNumber(mPendingTicketNumbers[i]);
        PrintTicketInfoFromNumber(mPendingTicketNumbers[i]);
    }
    return ;
}		/* -----  end of method ExportData::PrintPendingTickets  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: PrintCompleteTickets
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::PrintCompleteTickets ( )
{
    GetCompleteTicketNumbers();

    for(int i = 0; i < mCompleteTicketNumbers.size(); i++)
    {
        GetTicketInfoFromNumber(mCompleteTicketNumbers[i]);
        PrintTicketInfoFromNumber(mCompleteTicketNumbers[i]);
    }
    return ;
}		/* -----  end of method ExportData::PrintCompleteTickets  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: PendingTicketNumbers
 * Description:  Need this to implement one of the options
 *--------------------------------------------------------------------------------------
 */
    std::vector<int>
ExportData::PendingTicketNumbers ( )
{
    return mPendingTicketNumbers;
}		/* -----  end of method ExportData::PendingTicketNumbers  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: GetLocalContactTicketNumbers
 * Description:  Get a list of all the complete tickets
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::GetLocalContactTicketNumbers ( )
{
    int sqlite_return_value = 0;
    char* error_message;
    const char *dummy;

    mLocalContactTicketNumbers.clear();

    sqlite_return_value = sqlite3_open(mDatabaseFile.c_str(), &mpDatabaseHandle);
    if(sqlite_return_value == SQLITE_OK)
    {
        std::string select_query = "SELECT TICKET_NUMBER FROM FREEMEDIA WHERE STATUS=3;";
        sqlite_return_value = sqlite3_prepare_v2(mpDatabaseHandle, (const char*)select_query.c_str(),select_query.size(),&mpStatementHandle,&dummy);
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
                mLocalContactTicketNumbers.push_back(sqlite3_column_int(mpStatementHandle,0));
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
    mLocalContactTicketNumbers.pop_back();
    mNumberOfLocalContactTickets = mLocalContactTicketNumbers.size();
    sqlite3_close(mpDatabaseHandle);
    return ;
}		/* -----  end of method ExportData::GetLocalContactTicketNumbers  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: PrintLocalContactTicketNumbers
 * Description:  Print the list
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::PrintLocalContactTicketNumbers ( )
{
    std::cout << "Tickets in data base assigned to local contacts (ticket numbers only): " << mNumberOfLocalContactTickets << std::endl;
    if(mLocalContactTicketNumbers.empty())
    {
        std::cout << "Either the retrieval method has not been called, or there are no complete tickets in the database!" << std::endl;
        return;
    }
    PrintVectorContents(mLocalContactTicketNumbers);
    return ;
}		/* -----  end of method ExportData::PrintLocalContactTicketNumbers  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  ExportData
 *      Method:  ExportData :: PrintLocalContactTickets
 * Description:  
 *--------------------------------------------------------------------------------------
 */
    void
ExportData::PrintLocalContactTickets ( )
{
    GetLocalContactTicketNumbers();

    for(int i = 0; i < mLocalContactTicketNumbers.size(); i++)
    {
        GetTicketInfoFromNumber(mLocalContactTicketNumbers[i]);
        PrintTicketInfoFromNumber(mLocalContactTicketNumbers[i]);
    }
    return ;
}		/* -----  end of method ExportData::PrintLocalContactTickets  ----- */
