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

#include "NoCapability.h"

using namespace ns_saHpiEventLogEntryGet;

/*****************************************************************************
 * Constructor
 *****************************************************************************/

NoCapability::NoCapability(char *line)
: HpiNoCapabilityTestCase(line, "Event Log") {
}

/*****************************************************************************
 * Return the precondition for this test case.
 *****************************************************************************/

const char *NoCapability::getPrecondition() {
    return "Requires a resource that does not support Event Logs.";
}

/*****************************************************************************
 * Run the test.
 *****************************************************************************/

HpiTestStatus NoCapability::runResourceTest(SaHpiSessionIdT sessionId,
                                            SaHpiRptEntryT *rptEntry) {
    HpiTestStatus status;
    SaHpiEventLogEntryIdT prevEntryId;
    SaHpiEventLogEntryIdT nextEntryId;
    SaHpiEventLogEntryT eventLogEntry;

    if (hasEventLogCapability(rptEntry)) {
        status.assertNotSupport();
    } else {
        SaErrorT error = saHpiEventLogEntryGet(sessionId, rptEntry->ResourceId,
                                               SAHPI_OLDEST_ENTRY, 
                                               &prevEntryId, &nextEntryId,
                                               &eventLogEntry, NULL, NULL);
        if (error == SA_ERR_HPI_CAPABILITY) {
            status.assertPass();
        } else {
            status.assertFailure(TRACE, EVENT_LOG_ENTRY_GET, 
                                 SA_ERR_HPI_CAPABILITY, error);
        } 
    }

    return status;
}

