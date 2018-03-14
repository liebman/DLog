
#include "Arduino.h"

#include "DLog.h"
#include "DLogPrintWriter.h"

DLog& dlog = DLog::getLog();

static const char* sTAG = "setup";
static const char* lTAG = "loop";

//
// We will use this to add a timestamp to the start of each log line.
//
// While we dont use level it could be used send character sequences
// to change the color of lines based on level
//
void pre_log(DLogBuffer& buffer, DLogLevel level)
{
    (void)level; // we know its not used
    buffer.printf(F("%010u: "), millis());
}

void setup()
{
    Serial.begin(115200);

    //
    // The default log level is info.  Here we change the log level for
    // 'loop' tagged lines to debug.
    //
    dlog.setLevel(lTAG, DLOG_LEVEL_DEBUG);

    //
    // Here we add a "pre" function to add a timestamp at the start of each line
    //
    dlog.setPreFunc(pre_log);

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
