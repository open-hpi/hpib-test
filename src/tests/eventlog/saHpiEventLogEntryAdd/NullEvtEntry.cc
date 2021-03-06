/*
 * (C) Copyright University of New Hampshire, 2006
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
 */

#include "NullEvtEntry.h"
#include "EventHelper.h"
#include "EventLogHelper.h"

using namespace ns_saHpiEventLogEntryAdd;

/*****************************************************************************
 * Constructor
 *****************************************************************************/

NullEvtEntry::NullEvtEntry(char *line) : AddEventLogTestCase(line) {
}

/*****************************************************************************
 * Return the name of the test case.
 *****************************************************************************/

const char *NullEvtEntry::getName() {
    return "NullEvtEntry";
}

/*****************************************************************************
 * Return the description of the test case.
 *****************************************************************************/

const char *NullEvtEntry::getDescription() {
    return "The <i>EvtEntry</i> pointer is passed in as NULL.";
}

/*****************************************************************************
 * Return the precondition of the test case.
 *****************************************************************************/

const char *NullEvtEntry::getPrecondition() {
    return "Requires the ability to add an entry to an Event Log.";
}

/*****************************************************************************
 * Return the expected error code.
 *****************************************************************************/

SaErrorT NullEvtEntry::getExpectedReturn() {
    return SA_ERR_HPI_INVALID_PARAMS;
}

/*****************************************************************************
 * Run the test.
 *****************************************************************************/

HpiTestStatus NullEvtEntry::runAddTest(SaHpiSessionIdT sessionId,
                                       SaHpiResourceIdT resourceId) {
    HpiTestStatus status;

    if (EventLogHelper::hasEvtLogAddCapability(sessionId, resourceId)) {   
      SaErrorT error = saHpiEventLogEntryAdd(sessionId, resourceId, NULL);
      if (error == SA_ERR_HPI_INVALID_PARAMS) {
        status.assertPass();
      } else {
        status.assertFailure(TRACE, EVENT_LOG_ENTRY_ADD,
                             SA_ERR_HPI_INVALID_PARAMS, error);
      }
    } else {
      status.assertNotSupport();
    }

    return status;
}

