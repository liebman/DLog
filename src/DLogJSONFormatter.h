/*
 * DLogJsonFormater.h
 *
 *  Created on: Mar 12, 2018
 *      Author: chris.l
 */

#ifndef DLOGJSONFORMATTER_H_
#define DLOGJSONFORMATTER_H_

#include "DLogFormatter.h"

class DLogJSONFormatter;
#if defined(ESP8266) || defined(ESP_PLATFORM)
// these have support for std::function
#include <functional>
typedef std::function<void(DLogBuffer& buffer, DLogJSONFormatter& formatter)> DLogJSONFunc;
#else
// default to no std::function support! (like avr currently)
typedef void (*DLogJSONFunc)(DLogBuffer& buffer, DLogJSONFormatter& formatter);
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
    virtual void format(DLogBuffer& buffer, const __FlashStringHelper* tag, DLogLevel level, const char* fmt, va_list ap);
    virtual void format(DLogBuffer& buffer, const __FlashStringHelper* tag, DLogLevel level, const __FlashStringHelper* fmt, va_list ap);
    virtual void end(DLogBuffer& buffer);

    void addItem(DLogBuffer& buffer, const char* name, const char value);
    void addItem(DLogBuffer& buffer, const char* name, const char* fmt, ...);
    void addItem(DLogBuffer& buffer, const char* name, const __FlashStringHelper* fmt, ...);

    template<class T, class F> void addItem(DLogBuffer& buffer, T name, F fmt, va_list ap);

private:
    DLogJSONFunc _json_func;
    bool         _pretty;
    bool         _first_item;
};

#endif /* DLOGJSONFORMATTER_H_ */
