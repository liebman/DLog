/*
 * DLogFormatter.h
 *
 *  Created on: Mar 10, 2018
 *      Author: chris.l
 */

#ifndef DLOGFORMATTER_H_
#define DLOGFORMATTER_H_

#include <stdarg.h>
#include "DLogLevel.h"
#include "DLogBuffer.h"

class DLogFormatter
{
public:
    DLogFormatter();
    virtual ~DLogFormatter();

    virtual void start(DLogBuffer& buffer);
    virtual void format(DLogBuffer& buffer, const char* tag, DLogLevel level, const char* fmt, va_list ap);
    virtual void format(DLogBuffer& buffer, const char* tag, DLogLevel level, const __FlashStringHelper* fmt, va_list ap);
    virtual void format(DLogBuffer& buffer, const __FlashStringHelper* tag, DLogLevel level, const char* fmt, va_list ap);
    virtual void format(DLogBuffer& buffer, const __FlashStringHelper* tag, DLogLevel level, const __FlashStringHelper* fmt, va_list ap);
    virtual void end(DLogBuffer& buffer);

protected:
    const char* levels = "0EWIDT0";

private:
    template<class T, class F> void _format(DLogBuffer& buffer, T tag, DLogLevel level, F fmt, va_list ap);
};

#endif /* DLOGFORMATTER_H_ */
