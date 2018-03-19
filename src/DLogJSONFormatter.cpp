/*
 * DLogJsonFormater.cpp
 *
 *  Created on: Mar 12, 2018
 *      Author: chris.l
 */

#include <DLogJSONFormatter.h>

#if defined ESP8266
//
// Issues with PROGMEM and templates in gcc force us to redefine F()
// keep these strings in ram and not flash on ESP8266
#undef F
#define F(s) (s)
#endif

DLogJSONFormatter::DLogJSONFormatter(DLogJSONFunc json_func, bool pretty) : _json_func(json_func), _pretty(pretty), _first_item(false)
{
}

DLogJSONFormatter::DLogJSONFormatter(DLogJSONFunc json_func) : DLogJSONFormatter(json_func, false)
{
}

DLogJSONFormatter::DLogJSONFormatter(bool pretty) : DLogJSONFormatter(nullptr, pretty)
{
}

DLogJSONFormatter::DLogJSONFormatter() : DLogJSONFormatter(nullptr, false)
{
}

DLogJSONFormatter::~DLogJSONFormatter()
{
}

void DLogJSONFormatter::start(DLogBuffer& buffer)
{
    buffer.printf(F("{"));
    _first_item = true;
}

void DLogJSONFormatter::format(DLogBuffer& buffer, const char* tag, DLogLevel level, const char* fmt, va_list ap)
{
    addItem(buffer, "name", tag);
    addItem(buffer, "level", levels[level]);
    addItem(buffer, "message", fmt, ap);
    if (_json_func)
    {
        _json_func(buffer, *this);
    }
}

void DLogJSONFormatter::format(DLogBuffer& buffer, const char* tag, DLogLevel level, const __FlashStringHelper* fmt, va_list ap)
{
    addItem(buffer, "name", tag);
    addItem(buffer, "level", levels[level]);
    addItem(buffer, "message", fmt, ap);
    if (_json_func)
    {
        _json_func(buffer, *this);
    }
}

void DLogJSONFormatter::format(DLogBuffer& buffer, const __FlashStringHelper* tag, DLogLevel level, const char* fmt, va_list ap)
{
    addItem(buffer, "name", tag);
    addItem(buffer, "level", levels[level]);
    addItem(buffer, "message", fmt, ap);
    if (_json_func)
    {
        _json_func(buffer, *this);
    }
}

void DLogJSONFormatter::format(DLogBuffer& buffer, const __FlashStringHelper* tag, DLogLevel level, const __FlashStringHelper* fmt, va_list ap)
{
    addItem(buffer, "name", tag);
    addItem(buffer, "level", levels[level]);
    addItem(buffer, "message", fmt, ap);
    if (_json_func)
    {
        _json_func(buffer, *this);
    }
}

void DLogJSONFormatter::end(DLogBuffer& buffer)
{
   buffer.printf(F("%s}\n"), _pretty ? "\n" : "");
}

void DLogJSONFormatter::addItem(DLogBuffer& buffer, const char* name, const char value)
{
    // if its not the first item we need to add a comma (,) and a newline if also pretty
    if (!_first_item)
    {
        buffer.printf(F(",%s"), _pretty ? "\n" : "");
    }
    else
    {
        // not the first item anymore!
        _first_item = false;
    }
    buffer.printf(F("%s\"%s\":\"%c\""), _pretty ? "  " : "", name, value);
}

void DLogJSONFormatter::addItem(DLogBuffer& buffer, const char* name, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    addItem(buffer, name, fmt, ap);
    va_end(ap);
}

void DLogJSONFormatter::addItem(DLogBuffer& buffer, const char* name, const __FlashStringHelper* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    addItem(buffer, name, fmt, ap);
    va_end(ap);
}

template<class T, class F>void DLogJSONFormatter::addItem(DLogBuffer& buffer, T name, F fmt, va_list ap)
{
    // if its not the first item we need to add a comma (,) and a newline if also pretty
    if (!_first_item)
    {
        buffer.printf(F(",%s"), _pretty ? "\n" : "");
    }
    else
    {
        // not the first item anymore!
        _first_item = false;
    }
    buffer.printf(F("%s\"%s\":\""), _pretty ? "  " : "", name);
    buffer.vprintf(fmt, ap);
    buffer.printf(F("\""));
}
