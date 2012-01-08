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
 *       Filename:  Addresses.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/01/12 23:28:37
 *       Revision:  1
 *       Compiler:  g++
 *
 *         Author:  Ankur Sinha (FranciscoD), sanjay DOT ankur AT gmail DOT com
 *        Company:  None
 *
 * =====================================================================================
 */


#ifndef  ADDRESSES_INC
#define  ADDRESSES_INC

#include	<Magick++.h>
#include	<sqlite3.h>


/*
 * =====================================================================================
 *        Class:  Addresses
 *  Description:  
 * =====================================================================================
 */
class Addresses
{
    public:
    /* ====================  LIFECYCLE     ======================================= */
    Addresses ();                             /* constructor */

    /* ====================  ACCESSORS     ======================================= */

    /* ====================  MUTATORS      ======================================= */

    /* ====================  OPERATORS     ======================================= */
    int PrintToAddressOnEnvelope(); /* crucial method */
    int PrintFromAddressOnEnvelope(); /* crucial method */

    protected:
    /* ====================  DATA MEMBERS  ======================================= */

    private:
    /* ====================  DATA MEMBERS  ======================================= */
    std::string mToAddress;
    std::string mFromAddress;
    sqlite3 *mpDatabaseHandle;

}; /* -----  end of class Addresses  ----- */

#endif   /* ----- #ifndef ADDRESSES_INC  ----- */
