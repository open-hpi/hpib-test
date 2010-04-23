/*
 * (C) Copyright Lars Wetzel, 2009
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
 *     Lars Wetzel <larswetzel@users.sourceforge.net>
 */

#include "NoCapability.h"

using namespace ns_saHpiRdrUpdateCountGet;

/*****************************************************************************
 * Constructor
 *****************************************************************************/

NoCapability::NoCapability(char *line)
: HpiNoCapabilityTestCase(line, "Event Log") {
}

/*****************************************************************************
 * Return the precondition of the test case.
 *****************************************************************************/

const char *NoCapability::getPrecondition() {
    return "Requires one or more resources without the RDR capability.";
}

/*****************************************************************************
 * Run the test.
 *****************************************************************************/

HpiTestStatus NoCapability::runResourceTest(SaHpiSessionIdT sessionId,
                                            SaHpiRptEntryT *rptEntry) {
    HpiTestStatus status;

    if (hasRdrCapability(rptEntry)) {
        status.assertNotSupport();
    } else {
	    SaHpiUint32T  UpdateCount;

        SaErrorT error = saHpiRdrUpdateCountGet(sessionId, rptEntry->ResourceId, 
                                                &UpdateCount);
        
        if (error == SA_ERR_HPI_CAPABILITY) {
            status.assertPass();
        } else {
            status.assertFailure(TRACE, RDR_UPDATE_COUNT_GET,
                                 SA_ERR_HPI_CAPABILITY, error);
        }
    }

    return status;
}

