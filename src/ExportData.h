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
#include	<string>
#include	<iostream>
#include	<sqlite3.h>

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
    ExportData (std::string databaseFile, std::string outputDirectory);

    /* ====================  ACCESSORS     ======================================= */
    void PrintAllTicketNumbers();
    void PrintPendingTicketNumbers();
    void PrintCompleteTicketNumbers();

    /* ====================  MUTATORS      ======================================= */
    void GetAllTicketsFull();
    void GetPendingTicketsFull();
    void GetCompleteTicketsFull();
    void GetAllTicketNumbers();
    void GetPendingTicketNumbers();
    void GetCompleteTicketNumbers();
    int NumberOfPendingTickets();
    int NumberOfTotalTickets();
    int NumberOfCompleteTickets();
    void PrintTicketSummaryReport();

    /* ====================  OPERATORS     ======================================= */

    protected:
    /* ====================  DATA MEMBERS  ======================================= */

    private:
    template <typename I> void PrintVectorContents(std::vector<I> input_vector);
    /* ====================  DATA MEMBERS  ======================================= */
    sqlite3 *mpDatabaseHandle;
    sqlite3_stmt *mpStatementHandle;
    std::string mDatabaseFile;
    std::string mOutputDirectory;
    std::vector<int> mAllTicketNumbers;
    std::vector<int> mPendingTicketNumbers;
    std::vector<int> mCompleteTicketNumbers;
    int mNumberOfPendingTickets;
    int mNumberOfCompleteTickets;
    int mNumberOfTotalTickets;


}; /* -----  end of class ExportData  ----- */

#endif   /* ----- #ifndef EXPORTDATA_INC  ----- */
