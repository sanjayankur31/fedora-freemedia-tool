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
 *       Filename:  ExportData.h
 *
 *    Description:  Header to ExportData.cpp
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



#ifndef  EXPORTDATA_INC
#define  EXPORTDATA_INC


#include	<vector>
#include	<unistd.h>
#include	<string>
#include	<iostream>
#include	<sqlite3.h>
#include	<map>
#include	<iomanip>
#include	<cstdio>
#include	<Magick++.h>


/*
 * =====================================================================================
 *        Class:  ExportData
 *  Description:  Export data from the database to various formats
 * =====================================================================================
 */
class ExportData
{
    public:
    /* ====================  LIFECYCLE     ======================================= */
    ExportData (std::string databaseFile, std::string outputDirectory, std::string templateLocation);

    /* ====================  ACCESSORS     ======================================= */
    void PrintAllTicketNumbers();
    void PrintAllTickets();
    void PrintPendingTicketNumbers();
    void PrintPendingTickets();
    void PrintCompleteTicketNumbers();
    void PrintLocalContactTicketNumbers();
    void PrintLocalContactTickets();
    void PrintCompleteTickets();
    std::vector<int> PendingTicketNumbers();

    /* ====================  MUTATORS      ======================================= */
    void GetAllTicketNumbers();
    void GetPendingTicketNumbers();
    void GetCompleteTicketNumbers();
    void GetLocalContactTicketNumbers();
    int NumberOfPendingTickets();
    int NumberOfTotalTickets();
    int NumberOfCompleteTickets();
    void PrintTicketSummaryReport();
    int GetTicketInfoFromNumber(int ticketNumber); /* This method will get the other data for a passed ticket number from the database on demand */
    void PrintTicketInfoFromNumber(int ticketNumber);
    void PrintRawTicketInfoFromNumber(int ticketNumber);
    void ImportTemplate();
    int OverlayTemplate(int ticketNumber);
    void SetSendersAddress(std::string sendersAddress);
    void SetSendersName(std::string sendersName);
    std::string OutputDirectory();
    void CloseDatabaseConnection();

    /* ====================  OPERATORS     ======================================= */

    protected:
    /* ====================  DATA MEMBERS  ======================================= */

    private:
    template <typename I> void PrintVectorContents(std::vector<I> input_vector);
    std::string StatusToString(int status);
    std::string RequestToString(int request);
    std::vector<std::string> BreakAddressToMultiline(std::string addressToFormat, char delimiter);
    /* ====================  DATA MEMBERS  ======================================= */
    sqlite3 *mpDatabaseHandle;
    sqlite3_stmt *mpStatementHandle;
    std::string mDatabaseFile;
    std::string mOutputDirectory;
    std::string mImageTemplateLocation;
    std::vector <int> mAllTicketNumbers;
    std::vector <int> mPendingTicketNumbers;
    std::vector <int> mCompleteTicketNumbers;
    std::vector <int> mLocalContactTicketNumbers;
    std::map <int, std::string > mNameMap;
    std::map <int, std::string > mAddressMap;
    std::map <int, std::string > mRequirementMap;
    std::map <int, std::string > mStatusMap;
    std::map <int, std::string > mServiceDateMap;
    int mNumberOfPendingTickets;
    int mNumberOfCompleteTickets;
    int mNumberOfTotalTickets;
    int mNumberOfLocalContactTickets;
    Magick::Image mImageTemplate;
    Magick::Image mDestinationImageTemplate;
    int mSendersAddressStartX;
    int mSendersAddressStarty;
    int mReceiversAddressStartX;
    int mReceiversAddressStarty;
    std::string mSendersAddress;
    std::string mSendersName;


}; /* -----  end of class ExportData  ----- */

#endif   /* ----- #ifndef EXPORTDATA_INC  ----- */
