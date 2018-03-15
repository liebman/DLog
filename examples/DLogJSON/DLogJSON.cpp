
#include "Arduino.h"

#include "DLog.h"
#include "DLogPrintWriter.h"
#include "DLogJSONFormatter.h"

DLog& dlog = DLog::getLog();

static const char* sTAG = "setup";
static const char* lTAG = "loop";

//
// We will register this function to add a timestamp field to the json  output.
//
void log_json(DLogBuffer& buffer, const char* preline, const char* postline)
{
    //
    // preline and postline are empty strings unless we configured the json formatter
    // with pretty enabled.  In that case preline has any needed indentation and postline
    // will be an end of line.
    //
    buffer.printf(F("%s\"timestamp\":\"%010u\""), preline, millis(), postline);
}

void setup()
{
    delay(2000);
    Serial.begin(115200);

    //
    // The default log level is info.  Here we change the log level for
    // 'loop' tagged lines to debug.
    //
    dlog.setLevel(lTAG, DLOG_LEVEL_DEBUG);

    //
    // Configure a json formatter and include our hook to add a timestamp.
    //
    dlog.setFormatter(new DLogJSONFormatter(&log_json, false));

    //
    // Start the logger with Serial as output.  This could be any object implementing "Print"
    //
    dlog.begin(new DLogPrintWriter(Serial));

    //
    // Start logging!
    //
    dlog.info(sTAG, "Startup!");
    dlog.debug(sTAG, "this wont show because 'setup' level not set to at least DEBUG");
    dlog.info(sTAG, F("Done"));
}

void loop()
{
    dlog.debug(lTAG, "this will show because 'loop' level us set to DEBUG");
    dlog.trace(lTAG, "this won't show because level does not include TRACE!");
    delay(60000); // one minute
}
