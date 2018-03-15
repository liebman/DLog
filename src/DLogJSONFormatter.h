/*
 * DLogJsonFormater.h
 *
 *  Created on: Mar 12, 2018
 *      Author: chris.l
 */

#ifndef DLOGJSONFORMATTER_H_
#define DLOGJSONFORMATTER_H_

#include "DLogFormatter.h"

#if defined(ESP8266) || defined(ESP_PLATFORM)
// these have support for std::function
#include <functional>
typedef std::function<void(DLogBuffer& buffer, const char* prefix, const char* postfix)> DLogJSONFunc;
#else
// default to no std::function support! (like avr currently)
typedef void (*DLogJSONFunc)(DLogBuffer& buffer, const char* prefix, const char* postfix);
#endif

class DLogJSONFormatter: public DLogFormatter
{
public:
    DLogJSONFormatter(DLogJSONFunc json_func, bool pretty);
    DLogJSONFormatter(DLogJSONFunc json_func);
    DLogJSONFormatter(bool pretty);
    DLogJSONFormatter();
    virtual ~DLogJSONFormatter();

    virtual void start(DLogBuffer& buffer);
    virtual void format(DLogBuffer& buffer, const char* tag, DLogLevel level, const char* fmt, va_list ap);
    virtual void format(DLogBuffer& buffer, const char* tag, DLogLevel level, const __FlashStringHelper* fmt, va_list ap);
    virtual void end(DLogBuffer& buffer);

protected:
    virtual void startContents(DLogBuffer& buffer, const char* tag, DLogLevel level);
    virtual void endContents(DLogBuffer& buffer, const char* tag, DLogLevel level);

private:
    DLogJSONFunc _json_func;
    const char*  _pre_line;
    const char*  _post_line;
    bool         _pretty;
};

#endif /* DLOGJSONFORMATTER_H_ */
