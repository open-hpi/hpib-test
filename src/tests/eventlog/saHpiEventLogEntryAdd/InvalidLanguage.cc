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

#include "InvalidLanguage.h"
#include "TextBufferHelper.h"
#include "EventHelper.h"
#include "EventLogHelper.h"

using namespace ns_saHpiEventLogEntryAdd;

/*****************************************************************************
 * Constructor
 *****************************************************************************/

InvalidLanguage::InvalidLanguage(char *line) : AddEventLogTestCase(line) {
}

/*****************************************************************************
 * Return the name of the test case.
 *****************************************************************************/

const char *InvalidLanguage::getName() {
    return "InvalidLanguage";
}

/*****************************************************************************
 * Return the description of the test case.
 *****************************************************************************/

const char *InvalidLanguage::getDescription() {
    return "The <i>Language</i> is not one of the enumerated values for that type\n"
           "when the <i>DataType</i> is SAHPI_TL_TYPE_UNICODE or SAHPI_TL_TYPE_TEXT.";
}

/*****************************************************************************
 * Return the precondition of the test case.
 *****************************************************************************/

const char *InvalidLanguage::getPrecondition() {
    return "Requires the ability to add an entry to an Event Log.";
}

/*****************************************************************************
 * Return the expected error code.
 *****************************************************************************/

SaErrorT InvalidLanguage::getExpectedReturn() {
    return SA_ERR_HPI_INVALID_PARAMS;
}

/*****************************************************************************
 * Run the test.
 *****************************************************************************/

HpiTestStatus InvalidLanguage::runAddTest(SaHpiSessionIdT sessionId,
                                          SaHpiResourceIdT resourceId) {
    HpiTestStatus status;
    SaHpiTextBufferT buf;
    SaHpiEventT event;
    SaHpiTextTypeT dataType[] = { SAHPI_TL_TYPE_UNICODE, SAHPI_TL_TYPE_TEXT };
    int invalidLanguage = (int) SAHPI_LANG_ZULU + 1;

    if (EventLogHelper::hasEvtLogAddCapability(sessionId, resourceId)) {  
      for (int i = 0; i < 2; i++) {
        TextBufferHelper::fillByDataType(&buf, dataType[i]);
        buf.Language = (SaHpiLanguageT) invalidLanguage;
        EventHelper::fill(&event, &buf);

        SaErrorT error = saHpiEventLogEntryAdd(sessionId, resourceId, &event);
        if (error == SA_ERR_HPI_INVALID_PARAMS) {
            status.assertPass();
        } else {
	  status.assertFailure(TRACE, EVENT_LOG_ENTRY_ADD,
			       SA_ERR_HPI_INVALID_PARAMS, error);
        }
      }

    } else {
      status.assertNotSupport();
    }
    return status;
}

