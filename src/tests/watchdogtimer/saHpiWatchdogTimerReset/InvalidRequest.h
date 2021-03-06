/*
 * (C) Copyright University of New Hampshire, 2006
 * (C) Copyright Emerson Network Power, 2009
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple 
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 *
 * Author(s):
 *     Donald A. Barre <dbarre@unh.edu>
 *     Klaus Mittermaier <klaus.mittermaier@emerson.com>
 *     Lars Wetzel <lars.wetzel@emerson.com>
 */

#ifndef __INVALIDREQUEST_H__
#define __INVALIDREQUEST_H__

#include "SafTest.h"
#include "HpiSessionTestCase.h"
#include "WatchdogHelper.h"

/*****************************************************************************
 * Constants
 *****************************************************************************/

#ifndef MAX_WATCHDOGS
#define MAX_WATCHDOGS 100
#endif

/*****************************************************************************
 * Event Generation Test Case
 *****************************************************************************/

namespace ns_saHpiWatchdogTimerReset
{
    class InvalidRequest : public HpiSessionTestCase, public WatchdogFinderCallback
    {
    private:
        typedef struct {
            SaHpiResourceIdT resourceId;
            SaHpiWatchdogNumT watchdogNum;
            SaHpiWatchdogT origWatchdog;
        } WatchdogData;

        int watchdogCount;
        WatchdogData watchdogData[MAX_WATCHDOGS];

    public:
        InvalidRequest(char *line);

        HpiTestStatus runSessionTest(SaHpiSessionIdT sessionId);

        const char *getName();

        const char *getDescription();

        const char *getPrecondition();

    private:

        void addWatchdog(SaHpiSessionIdT sessionId,
			 SaHpiResourceIdT resourceId,
                         SaHpiWatchdogNumT watchdogNum,
                         SaHpiWatchdogT &watchdog);

        HpiTestStatus testWatchdogs(SaHpiSessionIdT sessionId);

        HpiTestStatus restoreWatchdogs(SaHpiSessionIdT sessionId);
    };
}

#endif
