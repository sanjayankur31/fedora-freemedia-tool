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
 *       Filename:  test.cpp
 *
 *    Description:  a test file to test my classes etc
 *
 *
 *        Version:  1.0
 *        Created:  23/12/11 17:58:13
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Ankur Sinha (FranciscoD), sanjay DOT ankur AT gmail DOT com
 *        Company:  None
 *
 * =====================================================================================
 */


#include	"ImportData.h"

#include	"ExportData.h"
#include	"Session.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int
main ( int argc, char *argv[] )
{
    Session currentSession; 
    if(currentSession.PrepareSession() == -1)
    {
        return EXIT_FAILURE;
    }
    if (currentSession.ParseCommandLine(argc, argv) == -1)
       return EXIT_SUCCESS;

    std::cout << "Output directory entered is: " << currentSession.OutputDirectory() << std::endl;
    std::cout << "Input report file location is: " <<  currentSession.InputReportFileLocation() << std::endl;
    std::cout << "Database file location is: " <<  currentSession.DatabaseFileLocation() << std::endl;
    std::cout << "Print list is: " << currentSession.PrintListAsString() << std::endl;

    ImportData newInstance(currentSession.InputReportFileLocation(),currentSession.DatabaseFileLocation());
    newInstance.ImportDataToDatabase("");

    ExportData newExportInstance(currentSession.DatabaseFileLocation(),currentSession.OutputDirectory());
    newExportInstance.GetAllTicketNumbers();
    newExportInstance.PrintAllTicketNumbers();
    newExportInstance.GetPendingTicketNumbers();
    newExportInstance.PrintPendingTicketNumbers();
    newExportInstance.GetCompleteTicketNumbers();
    newExportInstance.PrintCompleteTicketNumbers();
    newExportInstance.GetTicketInfoFromNumber(7262);
    newExportInstance.PrintTicketInfoFromNumber(7262);
    newExportInstance.PrintTicketInfoFromNumber(7263);

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
