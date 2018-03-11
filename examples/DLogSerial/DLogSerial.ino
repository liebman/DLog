
#include "Arduino.h"

#include "DLog.h"
#include "DLogPrintWriter.h"

DLog& dlog = DLog::getLog();

static const char* sTAG = "setup";
static const char* lTAG = "loop";

void pre_log(DLogBuffer& buffer, DLogLevel level)
{
    (void)level; // we know its not used
    buffer.printf(F("%010u: "), millis());
}

void setup()
{
    Serial.begin(115200);
    dlog.setLevel(lTAG, DLOG_LEVEL_DEBUG);
    dlog.setPreFunc(pre_log);
    dlog.begin(new DLogPrintWriter(Serial));
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
