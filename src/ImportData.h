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
 *       Filename:  ImportData.h
 *
 *    Description:  Header
 *
 *        Version:  1.0
 *        Created:  23/12/11 17:41:06
 *       Revision:  1
 *       Compiler:  g++
 *
 *         Author:  Ankur Sinha (FranciscoD), sanjay DOT ankur AT gmail DOT com
 *        Company:  None
 *
 * =====================================================================================
 */

/*  Include guard  */
#ifndef  IMPORTDATA_INC
#define  IMPORTDATA_INC


#include	<iostream>
#include	<fstream>
#include	<string>
#include	<cctype>
#include	<sqlite3.h>
#include	<vector>


/*
 * =====================================================================================
 *        Class:  ImportData
 *  Description:  Import data to the database
 * =====================================================================================
 */
class ImportData
{
    public:
    /* ====================  LIFECYCLE     ======================================= */
    ImportData (std::string dataFile, std::string databaseFile);                             /* constructor */

    /* ====================  ACCESSORS     ======================================= */

    /* ====================  MUTATORS      ======================================= */
    void ImportDataToDatabase();
    void ImportDataToDatabase(std::string dataFilenameWithPath);
    std::string SanitizeSummary(std::string summaryToStrip);
    std::string ReplaceAll(std::string str,const std::string from, const std::string to);
    std::string MediaCode(std::string stringMediaName);
    std::string SanitizeAddress(std::string addressToSanitize);
    std::string ToSentenceCase(std::string textToModify);

    /* ====================  OPERATORS     ======================================= */

    protected:
    /* ====================  DATA MEMBERS  ======================================= */

    private:
    /* ====================  DATA MEMBERS  ======================================= */
    std::string mDataFile;
    std::string mConfigFile;
    std::string mDatabaseFile;
    sqlite3 *mpDatabaseHandle;
    bool mAllGood;
    std::ifstream mDataFileHandle; 

}; /* -----  end of class ImportData  ----- */


#endif   /* ----- #ifndef IMPORTDATA_INC  ----- */


/*  token order 
 * 1. status: discard
 * 2. ticket number: use
 * 3. summary: extract name
 * 4. Timestamp: discard
 * 5. Timestamp: discard
 * 6. Complete address: break into 5 address lines and request user to
 * check
 */

/*
 * status: 
 * 1 -> new
 * 2 -> fixed
 *
 */
