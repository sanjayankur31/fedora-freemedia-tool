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
 *       Filename:  Addresses.cpp
 *
 *    Description:  Pick the addresses from the database and overlay
 *    them on the envelope template
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


#include	"Addresses.h"

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Addresses
 *      Method:  Addresses
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Addresses::Addresses ()
{
    int sqlite_return_value = sqlite3_open(mDatabaseFile.c_str(), &mpDatabaseHandle);
}  /* -----  end of method Addresses::Addresses  (constructor)  ----- */

