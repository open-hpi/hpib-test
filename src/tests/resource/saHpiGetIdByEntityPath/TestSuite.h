/*      
 * (C) Copyright IBM Corp. 2008
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 * You should have received a copy of the GNU General Public License along with 
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple 
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 *
 *  Authors:
 *  Suntrupth S Yadav <suntrupth@in.ibm.com>
 */

#ifndef __GETIDBYENTITIYPATH_TESTSUITE_H__
#define __GETIDBYENTITIYPATH_TESTSUITE_H__

#include "HpiTestSuite.h"

/*****************************************************************************
 * saHpiGetIdByEntityPath Test Suite
 *****************************************************************************/

namespace ns_saHpiGetIdByEntityPath
{
    class TestSuite : public HpiTestSuite
    {
    public:
        TestSuite();

        const char *getName();
    
        const char *getDescription();
    };
}

#endif
