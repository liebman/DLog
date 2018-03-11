/*
 * DLogFormatter.cpp
 *
 *  Created on: Mar 10, 2018
 *      Author: chris.l
 */

#include "DLogFormatter.h"

DLogFormatter::DLogFormatter()
{
}

DLogFormatter::~DLogFormatter()
{
}

void DLogFormatter::start(DLogBuffer& buffer)
{
    (void)buffer;
}

void DLogFormatter::format(DLogBuffer& buffer, const char* tag, DLogLevel level, const char* fmt, va_list ap)
{
    _format(buffer, tag, level, fmt, ap);
}

void DLogFormatter::format(DLogBuffer& buffer, const char* tag, DLogLevel level, const __FlashStringHelper* fmt, va_list ap)
{
    _format(buffer, tag, level, fmt, ap);
}

void DLogFormatter::end(DLogBuffer& buffer)
{
    buffer.printf("\n");
}

template<class F>
void DLogFormatter::_format(DLogBuffer& buffer, const char* tag, DLogLevel level, F fmt, va_list ap)
{
    buffer.printf(F("%c %s "), levels[level], tag);
    buffer.vprintf(fmt, ap);
}
