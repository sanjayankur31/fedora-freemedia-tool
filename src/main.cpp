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
 *       Filename:  main.cpp
 *
 *    Description:  The main loop for the ffmtool
 *
 *        Version:  1.0
 *        Created:  21/01/12 20:39:21
 *       Revision:  1
 *       Compiler:  gcc
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
    if (currentSession.ParseCommandLine(argc, argv) == -1)
       return EXIT_SUCCESS;
    else
    {
        /*  write a better error message! */
        std::cout << "Something went wrong. Please file a bug" << std::endl;
        return EXIT_SUCCESS;

    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
